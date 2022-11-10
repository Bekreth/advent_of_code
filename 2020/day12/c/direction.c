#include "direction.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int parseInt(char* input) {
    int index = 1;
    while (true) {
        if (input[index] == '!') break;
        index++;
    }
    char* intBuffer = malloc(index * sizeof(char));
    memcpy(intBuffer, input + 1, index * sizeof(char));
    int output = atoi(intBuffer);
    free(intBuffer);
    return output;
}

Instruction** readInstructions(FileData fileData) {
    Instruction** output = malloc(fileData.size * sizeof(Instruction*));
    char* intBuffer[3];

    Instruction* instruction;

    for (int i = 0; i < fileData.size; i++) {
        instruction = malloc(sizeof(Instruction));
        instruction->amount = parseInt(fileData.data[i]);
        instruction->hasDirection = false;
        instruction->hasRotation = false;
        instruction->forward = false;
        switch (fileData.data[i][0]) {
        case 'N':
            instruction->direction = NORTH;
            instruction->hasDirection = true;
            break;
        case 'S':
            instruction->direction = SOUTH;
            instruction->hasDirection = true;
            break;
        case 'E':
            instruction->direction = EAST;
            instruction->hasDirection = true;
            break;
        case 'W':
            instruction->direction = WEST;
            instruction->hasDirection = true;
            break;

        case 'F':
            instruction->forward = true;
            break;

        case 'L':
            instruction->rotation = LEFT;
            instruction->hasRotation = true;
            break;
        case 'R':
            instruction->rotation = RIGHT;
            instruction->hasRotation = true;
            break;
        }
        output[i] = instruction;
    }
    
    return output;
}

void freeInstructions(Instruction** instractions, int length) {
    for (int i = 0; i < length; i++) {
        free(instractions[i]);
    }
    free(instractions);
}