#ifndef boot_code_h
#define boot_code_h

#include <stdbool.h>

#include "../fileReader/fileReader.h"


typedef enum InstrutionAction {
    ACCUMULATE,
    JUMP,
    NO_OPERATION
} InstrutionAction;

typedef struct Instruction {
    InstrutionAction action;
    int value;
} Instruction;

typedef struct Application {
    int globalAggregator; 
    Instruction** instructions;
    int numberOfInstructions;
    int instructionPointer;
} Application;

typedef struct RunOutput {
    int accumulatorValue;
    bool wasInteruppted;
} RunOutput;

extern bool applyMeter(void* meter, Application application);

Application createApplication(FileData fileData);
Application cloneApplication(Application input);
RunOutput runApplication(Application application, void* meter);

void printApplication(Application application, bool withInstructions);
void printInstruction(Instruction* instruction);


#endif