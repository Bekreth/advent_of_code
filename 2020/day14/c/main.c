#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../utils/fileReader/fileReader.h"
#include "register.h"
#include "bitMask.h"

#include "instruction.h"
#include "silver.h"
#include "gold.h"

int postProcessorBufferSize;

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData fileData = readFile(argv[1]);

    Instruction** instructions = malloc(fileData.size * sizeof(Instruction*));
    for (int i = 0; i < fileData.size; i++) {
        instructions[i] = newInstruction(fileData.data[i]);
        free(fileData.data[i]);
    }
    free(fileData.data[fileData.size]);
    free(fileData.data);

    // solveSilver(instructions, fileData.size);
    solveGold(instructions, fileData.size);

    for (int i = 0; i < fileData.size; i++) {
        freeInstruction(instructions[i]);
    }
    free(instructions);
}

