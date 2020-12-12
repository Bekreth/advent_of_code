#ifndef ferry_h
#define ferry_h

#include "direction.h"

typedef struct Ferry {  
    int posX;
    int posY;
    Direction facingDirection;
} Ferry;

void applyInstruction(Ferry* ferry, Instruction* instruction);
void applyInstructions(Ferry* ferry, Instruction** instruction, int length);

void printFerry(Ferry* ferry);



#endif