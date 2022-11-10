#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bootCode.h"

int maxOperationSize = 8;
int actionOffset = 4;

InstrutionAction mapInstructionAction(char data[3]) {
    if (strcmp("acc", data) == 0) return ACCUMULATE;
    if (strcmp("jmp", data) == 0) return JUMP;
    if (strcmp("nop", data) == 0) return NO_OPERATION;
}

Instruction* createInstruction(char* data) {
    Instruction* output = malloc(sizeof(Instruction));
    char actionString[3];
    memcpy(actionString, data, 3 * sizeof(char));
    output->action = mapInstructionAction(actionString);
    char* value = calloc(maxOperationSize * sizeof(char), 1);

    bool positive = true;
    if (data[actionOffset] == '-') positive = false;

    for (int i = (actionOffset + 1); ; i++) {
        if (data[i] == '!') {
            output->value = atoi(value);
            if (!positive) output->value *= -1;
            break;
        }
        value[i - (actionOffset + 1)] = data[i];
    }
    return output;
}


Application createApplication(FileData fileData) {
    Instruction** instructions = malloc(fileData.size * sizeof(Instruction*));
    for (int i = 0; i < fileData.size; i++) {
        instructions[i] = createInstruction(fileData.data[i]);
    }
    Application output = {0, instructions, fileData.size};
    return output;
}

RunOutput runApplication(Application app, void* meter) {
    RunOutput output = {0, false};
    while(true) {
        if (applyMeter(meter, app)) {
            output.accumulatorValue = app.globalAggregator;
            output.wasInteruppted = true;
            return output;
        }
        switch (app.instructions[app.instructionPointer]->action) {
        case ACCUMULATE:
            app.globalAggregator += app.instructions[app.instructionPointer]->value;
            app.instructionPointer++;
            break;
        case JUMP:
            app.instructionPointer += app.instructions[app.instructionPointer]->value; 
            break;
        case NO_OPERATION:
            app.instructionPointer++;
            break;
        }
        if (app.instructionPointer >= app.numberOfInstructions) {
            output.accumulatorValue = app.globalAggregator;
            output.wasInteruppted = false;
            return output;
        }
    }
}

Instruction* cloneInstruction(Instruction* input) {
    Instruction* output = malloc(sizeof(Instruction));
    output->action = input->action;
    output->value = input->value;
    return output;
}

Application cloneApplication(Application input) {
    Application output;
    output.globalAggregator = input.globalAggregator;
    output.instructionPointer = input.instructionPointer;
    output.numberOfInstructions = input.numberOfInstructions;
    output.instructions = malloc(input.numberOfInstructions * sizeof(Instruction*));
    for (int i = 0; i < input.numberOfInstructions; i++) {
        output.instructions[i] = cloneInstruction(input.instructions[i]);
    }
    return output;
}

void printApplication(Application app, bool withInstructions) {
    printf("== APPLICATION ==\n");
    printf("Accumulator: %d\n", app.globalAggregator);
    printf("Instruction Count: %d\n", app.numberOfInstructions);
    printf("Instruction Pointer: %d\n", app.instructionPointer);
    if (withInstructions) {
        for (int i = 0; i < app.numberOfInstructions; i++) {
            printf("\t");
            printInstruction(app.instructions[i]);
        }
    }
}

void printInstruction(Instruction* instruction) {
    char action[4];
    switch (instruction->action) {
    case ACCUMULATE:
        strcpy(action, "acc");
        break;
    case JUMP:
        strcpy(action, "jmp");
        break;
    case NO_OPERATION:
        strcpy(action, "nop");
        break;
    default:
        strcpy(action, "bad");
        break;
    }
    printf("%s: %d\n", action, instruction->value);
}