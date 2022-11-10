#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "fileReader.h"
#include "postProcessReader.h"


FileData readFile(char *fileLocation) {
    printf("reading file: %s\n", fileLocation);
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) exit(EXIT_FAILURE);

    char *buffer = malloc(postProcessorBufferSize * sizeof(char));
    char *currentEntry = malloc(postProcessorBufferSize * sizeof(char));
    int *currentEntryIndex = malloc(sizeof(int));
    char *nextEntry = malloc(postProcessorBufferSize * sizeof(char));
    int *nextEntryIndex = malloc(sizeof(int));

    char **dataValue = malloc(sizeof(char*));
    dataValue[0] = malloc(0);
    int dataIndex0 = 0;
    int dataIndex1 = 0;
    int dataRead;

    PostProcessor processor = {
        postProcessorBufferSize,
        buffer,
        currentEntry,
        currentEntryIndex,
        nextEntry,
        nextEntryIndex
    };

    ProcessorOutput processerOutput = {true, false};

    do {
        dataRead = fread(buffer, 1, postProcessorBufferSize, file);

        processerOutput = applyProcessor(dataRead, processerOutput.suspicious, processor);

        if (*currentEntryIndex != 0) {
            dataValue[dataIndex0] = realloc(dataValue[dataIndex0],
                (dataIndex1 + *currentEntryIndex) * sizeof(char*));
            memcpy(dataValue[dataIndex0] + dataIndex1, currentEntry, *currentEntryIndex);
            dataIndex1 += *currentEntryIndex;
        }
        if (!processerOutput.readIntoCurrent) {
            dataIndex0++;
            dataIndex1 = 0;
            dataValue = realloc(dataValue, (dataIndex0+1) * sizeof(char*));
            dataValue[dataIndex0] = calloc((*nextEntryIndex + 1) * sizeof(char), 1);
            memcpy(dataValue[dataIndex0], nextEntry, *nextEntryIndex);
            dataIndex1 += *nextEntryIndex;
        }

        //suspicious = false;
        *currentEntryIndex = 0;
        *nextEntryIndex = 0;
    } while(dataRead == postProcessorBufferSize);


    FileData output = {
        dataValue,
        dataIndex0
    };

    fclose(file);
    free(buffer);

    free(nextEntry);
    free(nextEntryIndex);

    free(currentEntry);
    free(currentEntryIndex);

    printf("file read\n\n");
    return output;
}

void printFileData(FileData data) {
    for (int i = 0; i < data.size; i++) {
        printf("%s\n", data.data[i]);
    }
}