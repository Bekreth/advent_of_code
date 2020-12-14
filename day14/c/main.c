#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../utils/fileReader/fileReader.h"
#include "register.h"
#include "bitMask.h"

#include "instruction.h"

int postProcessorBufferSize;

void solveSilver(Instruction** instructions, int size) {
    printf("solving silver\n");
    BitMask* activeMask;
    Register** registers = malloc(0);
    Register* activeRegister;
    int registerCount = 0;
    bool newRegister = true;
    for (int i = 0; i < size; i++) {
        if (instructions[i]->isMask) {
            // printf("mask changed \n");
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
            // printRegister(activeRegister);
            // printMask(activeMask);
            applyMask(activeMask, activeRegister);
            // printRegister(activeRegister);
            // printf("\n\n");
        }
    }

    unsigned long long output = 0ULL;
    for (int i = 0; i < registerCount; i++) {
        output += registers[i]->value;
        free(registers[i]);
    }
    free(registers);
    printf("- %lld -\n", output);
}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData fileData = readFile(argv[1]);

    Instruction** instructions = malloc(fileData.size * sizeof(Instruction*));
    printf(" - size: %d -\n", fileData.size);
    for (int i = 0; i < fileData.size; i++) {
        // printf("%s\n", fileData.data[i]);
        instructions[i] = newInstruction(fileData.data[i]);
        free(fileData.data[i]);
    }
    free(fileData.data[fileData.size]);
    free(fileData.data);

    solveSilver(instructions, fileData.size);

    for (int i = 0; i < fileData.size; i++) {
        freeInstruction(instructions[i]);
    }
    free(instructions);
}


// 8448560386057 is too low