#include <stdlib.h>
#include <stdio.h>

#include "fileReader.h"
#include "quickSort.h"

void solveSilver(FileData *fileData) {
    printf("solving silver\n");
    int largestID = 0;
    for (int i = 0; i < fileData->size; i++) {
        char row = fileData->row[i];
        char column = fileData->column[i];
        int id = 8 * row + column;
        //printf("r: %d,\tc: %d,\tID: %d\n", row, column, id);
        if (id > largestID) largestID = id;
    }
    printf("the largest ID is: %d\n\n", largestID);
}

void solveGold(FileData *fileData) {
    printf("solving gold\n");
    int *seatIDs = malloc(fileData->size * sizeof(int));
    for (int i = 0; i < fileData->size; i++) {
        char row = fileData->row[i];
        char column = fileData->column[i];
        int id = 8 * row + column;
        seatIDs[i] = id;
    }
    quickSort(seatIDs, 0, fileData->size - 1);
    for (int i = 1; i < fileData->size; i++) {
        if(seatIDs[i] - seatIDs[i-1] == 2) printf("your seatID is %d\n", seatIDs[i] - 1);
    }
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData *fileData = readFile(argv[1]);
    printf("finished reading\n\n");

    solveSilver(fileData);
    solveGold(fileData);
}