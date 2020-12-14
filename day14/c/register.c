#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "register.h"

const int regStartIndex = 4;

int registerNumber(char* input) {
    int regEndIndex = regStartIndex;
    while(input[regEndIndex] != ']') { regEndIndex++; }

    int bufferSize = regEndIndex+1 - regStartIndex;
    char* regBuffer = malloc(bufferSize * sizeof(char));
    memcpy(regBuffer, input + regStartIndex, bufferSize);
    int output = atoi(regBuffer);
    free(regBuffer);
    return output;
}

unsigned long long registerValue(char* input) {
    int startIndex = 0;
    while(input[startIndex] != '=') { startIndex++; }
    startIndex += 2;

    int endIndex = startIndex;
    while(input[endIndex] != '!') { endIndex++; }

    int bufferSize = endIndex+1 - startIndex;
    char* valueBuffer = malloc(bufferSize * sizeof(char));
    memcpy(valueBuffer, input + startIndex, bufferSize);
    unsigned long long output = atoll(valueBuffer);
    free(valueBuffer);
    return output;
}

Register* newRegister(char* input) {
    Register* output = malloc(sizeof(Register));

    output->id = registerNumber(input);
    output->value = registerValue(input);

    return output;
}

void freeRegister(Register* reg) {
    free(reg);
}

void printRegister(Register* reg) {
    printf("== Register ==\n");
    printf("ID:\t%d\n", reg->id);
    printf("value:\t%lld\n", reg->value);
}