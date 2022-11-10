#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "gold.h"

Registers registersMaker(Instruction** instructions, int size, void (*maskOperator)(BitMask* , Register*)) {
    BitMask* activeMask;
    Register** registers = malloc(0);
    Register* activeRegister;
    int registerCount = 0;
    unsigned long long handOver = 0ULL;

    for (int i = 0; i < size; i++) {
        if (instructions[i]->isMask) {
            activeMask = instructions[i]->data.mask;
        }
        else {
            registerCount++;
            activeRegister = malloc(sizeof(Register));
            memcpy(activeRegister, instructions[i]->data.reg, sizeof(Register));
            handOver = activeRegister->value;

            registers = realloc(registers, registerCount * sizeof(Register*));
            registers[registerCount - 1] = activeRegister;
            maskOperator(activeMask, activeRegister);
            activeRegister->id = activeRegister->value;
            activeRegister->value = handOver;
        }
    }
    Registers output = { registers, registerCount };
    return output;
}


void writeValue(unsigned long long** addressSpace, 
    unsigned long long floatingMask, 
    unsigned long long address,
    unsigned long long value) {

    if (floatingMask == 0ULL) {
        printf("%lld", address);
        *(addressSpace[address]) = value;
    } else {
        for (int i = 0; i < 63; i++) {
            if (floatingMask & (1ULL << i) != 0ULL) {
                writeValue(addressSpace, 
                    floatingMask ^ (1ULL << i), 
                    address | (0ULL << i),
                    value);
                writeValue(addressSpace, 
                    floatingMask ^ (1ULL << i), 
                    address | (1ULL << i),
                    value);
                break;
            }
        }
    }
}

unsigned long long**** makeAddressSpace() {
    unsigned short size = USHRT_MAX;
    unsigned long long**** addressSpace = malloc(size * sizeof(unsigned long long***));
    for (unsigned short i = 0; i < size; i++) {
        addressSpace[i] = malloc(size * sizeof(unsigned long long**));
        for (unsigned short j = 0; j < size; j++) {
            addressSpace[i][j] = malloc(size * sizeof(unsigned long long*));
            for (unsigned short k = 0; k < size; k++) {
                addressSpace[i][j][k] = calloc(size * sizeof(unsigned long long), 1);
            }
        }
    }
    return addressSpace;
}

void freeAddressSpace(unsigned long long**** addressSpace) {
    for (unsigned short i = 0; i < USHRT_MAX; i++) {
        for (unsigned short j = 0; j < USHRT_MAX; j++) {
            for (unsigned short k = 0; k < USHRT_MAX; k++) {
                free(addressSpace[i][j][k]);
            }
            free(addressSpace[i][j]);
        }
        free(addressSpace[i]);
    }
    free(addressSpace);
}

void solveGold(Instruction** instructions, int size) {
    printf("solving gold\n");
    unsigned long long****  addressSpace = makeAddressSpace();
    printf("Address space made\n");
    freeAddressSpace(addressSpace);

    // printf("Address space freed\n");
    // unsigned long long*** addressSpace = malloc(UCHAR_MAX * sizeof(unsigned long long**));
    // for (unsigned int i = 0; i < UCHAR_MAX; i++) {
    //    addressSpace[i] = malloc(max * sizeof(unsigned long long*));
    //    for (unsigned int j = 0; j < UINT_MAX; j++) {
    //        addressSpace[i][j] = calloc(sizeof(unsigned long long), 1);
    //    }
    // }
    Registers registers = registersMaker(instructions, size, applyGoldMask);
    printRegisters(&registers);
    //unsigned long long output = 0ULL;
    //for (int i = 0; i < registers.size; i++) { 
    //    output += countFloaters(registers.reg[i]->floatingMask, registers.reg[i]->value);
    //    free(registers.reg[i]);
    //}
    //printf("- %lld -\n", output);
}
