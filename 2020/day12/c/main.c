#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "direction.h"
#include "ferry.h"
#include "navigationFerry.h"

int postProcessorBufferSize = 2;

int manhatanDistance(int posX, int posY) {
    int absoluteX;
    int absoluteY;

    if (posX < 0) absoluteX = -1 * posX;
    else absoluteX = posX;

    if (posY < 0) absoluteY = -1 * posY;
    else absoluteY = posY;

    return absoluteX + absoluteY;
}

void solveGold(Instruction** instructions, int length) {
    printf("solving gold\n");
    NavFerry* navFerry = malloc(sizeof(NavFerry));
    navFerry->waypoint = malloc(sizeof(Waypoint));
    navFerry->waypoint->posX = 10;
    navFerry->waypoint->posY = 1;
    navFerry->posX = 0;
    navFerry->posY = 0;

    applyNavInstructions(navFerry, instructions, length);
    printNavFerry(navFerry);
    printf("manhatan distance: %d\n", manhatanDistance(navFerry->posX, navFerry->posY));

    free(navFerry->waypoint);
    free(navFerry);
}

void solveSilver(Instruction** instructions, int length) {
    printf("solving silver\n");
    Ferry* ferry = malloc(sizeof(Ferry));
    ferry->posX = 0;
    ferry->posY = 0;
    ferry->facingDirection = EAST;

    applyInstructions(ferry, instructions, length);
    printFerry(ferry);
    printf("manhatan distance: %d\n", manhatanDistance(ferry->posX, ferry->posY));

    free(ferry);
    printf("\n");
    // 435 is too high
}

int main(int argc, char** argv) {
    printf("starting\n");
    FileData fileData = readFile(argv[1]);

    int length = fileData.size;
    Instruction** instructions = readInstructions(fileData);
    for (int i = 0; i < fileData.size; i++) {
        free(fileData.data[i]);
    }
    free(fileData.data);

    solveSilver(instructions, length);
    solveGold(instructions, length);

    freeInstructions(instructions, length);
}
