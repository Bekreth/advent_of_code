#include <stdlib.h>
#include <stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "bitEncoder.h"

int countBits(int input) {
    int runningTotal = 0;
    for (int i = 0; i < 26; i++) {
        if ((input >> i) & 1 == 1) runningTotal++;
    }
    return runningTotal;
}

void solveSilver(FileData data) {
    printf("solving silver\n");
    int runningTotal = 0;
    for (int i = 0; i < data.size; i++) {
        runningTotal += countBits(compactOrData(data.data[i]));
    }
    printf("count: %d\n\n", runningTotal);
}

void solveGold(FileData data) {
    printf("solving gold\n");
    int runningTotal = 0;
    int value = 0;
    for (int i = 0; i <= data.size; i++) {
        runningTotal += countBits(compactAndData(data.data[i]));
    }

    printf("count: %d\n\n", runningTotal);
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData data = readFile(argv[1]);

    printf("\n");
    solveSilver(data);
    solveGold(data);
}