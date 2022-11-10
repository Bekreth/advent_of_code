#ifndef bit_mask_h
#define bit_mask_h

#include "register.h"

typedef struct BitMask {
    unsigned long long onesMask;
    unsigned long long zerosMask;
    unsigned long long floatingMask;
} BitMask;

BitMask* newMask(char* input);
void freeMask(BitMask* mask);
void printMask(BitMask* mask);

void applyGoldMask(BitMask* mask, Register* reg);
void applySilverMask(BitMask* mask, Register* reg);

#endif 