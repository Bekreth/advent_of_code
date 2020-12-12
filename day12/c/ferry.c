#include "ferry.h"

#include <stdlib.h>
#include <stdio.h>

void applyInstruction(Ferry* ferry, Instruction* instruction) {
    Direction direction;
    if (instruction->forward) {
        direction = ferry->facingDirection;
    }
    else direction = instruction->direction;

    if (instruction->hasDirection || instruction->forward) {
        switch (direction) {
        case NORTH:
            ferry->posY += instruction->amount;
            break;
        case EAST:
            ferry->posX += instruction->amount;
            break;
        case SOUTH:
            ferry->posY -= instruction->amount;
            break;
        case WEST:
            ferry->posX -= instruction->amount;
            break;
        }
    }

    char rotator;
    if (instruction->hasRotation) {
        switch (instruction->amount) {
        case 90:
            rotator = 1;
            break;
        case 180:
            rotator = 2;
            break;
        case 270:
            rotator = 3;
            break;
        }
        if (instruction->rotation == LEFT) rotator = (4 - rotator);
        ferry->facingDirection = (ferry->facingDirection + rotator) % 4;
    }
}

void applyInstructions(Ferry* ferry, Instruction** instruction, int length) {
    for (int i = 0; i < length; i++) {
        applyInstruction(ferry, instruction[i]);
    }
}

void printFerry(Ferry* ferry) {
    printf("=== Ferry ===\n");
    printf("(%d, %d)\n", ferry->posX, ferry->posY);
    printf("Direction: %d\n", ferry->facingDirection);
}

