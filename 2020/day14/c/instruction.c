#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "instruction.h"

Instruction* newInstruction(char* input) {
    Instruction* output = malloc(sizeof(Instruction));
    if (input[1] == 'e') {
        output->isMask = false;
        output->data.reg = newRegister(input);
    } else {
        output->isMask = true;
        output->data.mask = newMask(input);
    }
    return output;
}

void freeInstruction(Instruction* instruction) {
    if (instruction->isMask) freeMask(instruction->data.mask);
    else freeRegister(instruction->data.reg);

    free(instruction);
}
