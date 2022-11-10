#ifndef instruction_c
#define instruction_c

#include "register.h"
#include "bitMask.h"

typedef struct Instruction {
    bool isMask;
    union data {
        BitMask* mask;
        Register* reg;
    } data;
} Instruction;

Instruction* newInstruction(char* input);
void freeInstruction(Instruction* instruction);

#endif

