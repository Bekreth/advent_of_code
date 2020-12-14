#ifndef bit_mask_h
#define bit_mask_h

#include "register.h"

typedef struct BitMask {
    unsigned long long onesMask;
    unsigned long long zerosMask;
} BitMask;

BitMask* newMask(char* input);
void freeMask(BitMask* mask);
void printMask(BitMask* mask);

void applyMask(BitMask* mask, Register* reg);

#endif 