#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "silver.h"

Registers silverRegisterMaker(Instruction** instructions, int size, void (*maskOperator)(BitMask* , Register*)) {
    BitMask* activeMask;
    Register** registers = malloc(0);
    Register* activeRegister;
    int registerCount = 0;
    bool newRegister = true;
    for (int i = 0; i < size; i++) {
        if (instructions[i]->isMask) {
            activeMask = instructions[i]->data.mask;
        }
        else {
            newRegister = true;
            for (int j = 0; j < registerCount; j++) {
                if (registers[j]->id == instructions[i]->data.reg->id) {
                    activeRegister = registers[j];
                    activeRegister->value = instructions[i]->data.reg->value;
                    newRegister = false;
                }
            }
            if (newRegister) {
                registerCount++;
                activeRegister = malloc(sizeof(Register));
                memcpy(activeRegister, instructions[i]->data.reg, sizeof(Register));
                registers = realloc(registers, registerCount * sizeof(Register*));
                registers[registerCount - 1] = activeRegister;
            }
            maskOperator(activeMask, activeRegister);
        }
    }
    Registers output = { registers, registerCount };
    return output;
}

void solveSilver(Instruction** instructions, int size) {
    printf("solving silver\n");
    Registers registers = silverRegisterMaker(instructions, size, applySilverMask);

    unsigned long long output = 0ULL;
    for (int i = 0; i < registers.size; i++) {
        output += registers.reg[i]->value;
        free(registers.reg[i]);
    }
    free(registers.reg);
    printf("- %lld -\n", output);
}
