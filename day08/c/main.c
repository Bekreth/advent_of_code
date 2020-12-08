#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "../../utils/bootCode/bootCode.h"
#include "../../utils/fileReader/fileReader.h"

void showBits(char x) {
    for (int i = (sizeof(char) * 8) - 1 ; i >= 0; i--) {
       putchar(x & (1 << i) ? '1' : '0');
    }
    printf("\n");
}


int postProcessorBufferSize = 6;

typedef struct Meter {
    char data[81];
} Meter;

bool applyMeter(void* meter, Application application) {
    int section = application.instructionPointer / 8;
    int offset = application.instructionPointer % 8;
    char bitMask = 1 << offset;
    char anded = ((Meter*)meter)->data[section] & bitMask;
    //showBits(anded);
    if (anded != 0) return true;
    ((Meter*)meter)->data[section] |= bitMask;
    return false;
}

void solveSilver(Application app) {
    printf("solving silver\n");
    // printApplication(app, true);
    Meter meter = {{0}};
    RunOutput output = runApplication(app, &meter);
    printf("accumulator output: %d\n", output.accumulatorValue);
}

void solveGold(Application app) {
    printf("solving gold\n");
    Application modifiedApp;
    Meter meter = {{0}};
    Meter runMeter = meter;
    RunOutput runOutput;
    for (int i = 0; i < app.numberOfInstructions; i++) {
        switch(app.instructions[i]->action) {
        case ACCUMULATE:
            continue;
            break;
        case NO_OPERATION:
            modifiedApp = cloneApplication(app);
            modifiedApp.instructions[i]->action = JUMP;
            break;
        case JUMP:
            modifiedApp = cloneApplication(app);
            modifiedApp.instructions[i]->action = NO_OPERATION;
            break;
        }
        runMeter = meter;
        runOutput = runApplication(modifiedApp, &runMeter);
        for (int i = 0; i < modifiedApp.numberOfInstructions; i++) {
            free(modifiedApp.instructions[i]);
        }
        free(modifiedApp.instructions);
        if (!runOutput.wasInteruppted) {
            printf("accumulator output: %d\n", runOutput.accumulatorValue);
            return;
        }
    }
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData fileData = readFile(argv[1]);

    Application app = createApplication(fileData);
    solveSilver(app);
    solveGold(app);
    sleep(20);
}