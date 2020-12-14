#include <stdlib.h>
#include <stdio.h>

#include "bitMask.h"

#define START 7
#define END 42

void showLongLongBits(unsigned long long x) {
    for (int i = (sizeof(unsigned long long) * 8) - 1 ; i >= 0; i--) {
        if (i % 8 == 7) putchar(' ');
        putchar(x & (1ULL << i) ? '1' : '0');
    }
    printf("\n");
}


BitMask* newMask(char* input) {
    BitMask* output = calloc(sizeof(BitMask), 1);

    for (int i = START; i <= END; i++) {
        switch (input[i]) {
        case '1':
            output->onesMask |= (1ULL << (END - i));
            break;
        
        case '0':
            output->zerosMask |= (1ULL << (END - i));
            break;

        case 'X':
            output->floatingMask |= (1ULL << (END - i));
            break;
        }
    }
    return output;
}

void applyGoldMask(BitMask* mask, Register* reg) {
    // reg->value |= mask->zerosMask;
    // reg->floatingMask |= mask->zerosMask;

    reg->value |= mask->onesMask;
    reg->floatingMask |= mask->floatingMask;

    reg->value = ~reg->value;
    reg->value |= mask->floatingMask;
    reg->value = ~reg->value;

    reg->floatingMask = ~reg->floatingMask;
    reg->floatingMask |= mask->onesMask;
    reg->floatingMask = ~reg->floatingMask;
}

void applySilverMask(BitMask* mask, Register* reg) {
    reg->value |= mask->onesMask;
    reg->value = ~reg->value;
    reg->value |= mask->zerosMask;
    reg->value = ~reg->value;
}

void printMask(BitMask* mask) {
    printf("=== Bit Mask ===\n");
    printf("ones  : ");
    showLongLongBits(mask->onesMask);
    printf("zeros : ");
    showLongLongBits(mask->zerosMask);
    printf("X-es  : ");
    showLongLongBits(mask->floatingMask);
}

void freeMask(BitMask* mask) {
    free(mask);
}