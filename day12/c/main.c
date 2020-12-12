#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "direction.h"
#include "ferry.h"

int postProcessorBufferSize = 2;

int manhatanDistance(Ferry* ferry) {
    int absoluteX;
    int absoluteY;

    if (ferry->posX < 0) absoluteX = -1 * ferry->posX;
    else absoluteX = ferry->posX;

    if (ferry->posY < 0) absoluteY = -1 * ferry->posY;
    else absoluteY = ferry->posY;

    return absoluteX + absoluteY;
}

void solveSilver(Instruction** instructions, int length) {
    printf("solving silver\n");
    Ferry* ferry = malloc(sizeof(Ferry));
    ferry->posX = 0;
    ferry->posY = 0;
    ferry->facingDirection = EAST;

    applyInstructions(ferry, instructions, length);
    printFerry(ferry);
    printf("manhatan distance: %d\n", manhatanDistance(ferry));

    free(ferry);
    freeInstructions(instructions, length);
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
}
