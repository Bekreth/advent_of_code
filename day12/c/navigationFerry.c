#include "navigationFerry.h"

#include <stdlib.h>
#include <stdio.h>

void updateWayPoint(Waypoint* waypoint, Instruction* instruction) {
    if (instruction->hasDirection || instruction->forward) {
        switch (instruction->direction) {
        case NORTH:
            waypoint->posY += instruction->amount;
            break;
        case EAST:
            waypoint->posX += instruction->amount;
            break;
        case SOUTH:
            waypoint->posY -= instruction->amount;
            break;
        case WEST:
            waypoint->posX -= instruction->amount;
            break;
        }
    }

    int newX;
    int newY;
    if (instruction->hasRotation) {
        switch (instruction->amount) {
        case 90:
            newX = waypoint->posY;
            newY = waypoint->posX;
            if (instruction->rotation == RIGHT) newY *= -1;
            else  newX *= -1;
            break;
        case 180:
            newX = -1 * waypoint->posX;
            newY = -1 * waypoint->posY;
            break;
        case 270:
            newX = waypoint->posY;
            newY = waypoint->posX;
            if (instruction->rotation == RIGHT) newX *= -1;
            else newY *= -1;
            break;
        }
        waypoint->posX = newX;
        waypoint->posY = newY;
    }
}

void applyNavInstruction(NavFerry* ferry, Instruction* instruction) {
    if (instruction->forward) {
        ferry->posX += ferry->waypoint->posX * instruction->amount;
        ferry->posY += ferry->waypoint->posY * instruction->amount;
    } else updateWayPoint(ferry->waypoint, instruction);
}

void applyNavInstructions(NavFerry* ferry, Instruction** instruction, int length) {
    for (int i = 0; i < length; i++) {
        applyNavInstruction(ferry, instruction[i]);
    }
}

void printNavFerry(NavFerry* ferry) {
    printf("=== NavFerry ===\n");
    printf("  - WayPoint -\n");
    printf("  - posX: %d \n", ferry->waypoint->posX);
    printf("  - posY: %d \n", ferry->waypoint->posY);
    printf("posX: %d\n", ferry->posX);
    printf("posY: %d\n", ferry->posY);
}



