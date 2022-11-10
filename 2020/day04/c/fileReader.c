#include "fileReader.h"

FileData readFile(char *fileLocation) {
    printf("reading file: %s\n", fileLocation);
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) exit(EXIT_FAILURE);

    int bufferSize = 64;
    char *buffer = malloc(bufferSize * sizeof(char));
    char *currentEntry = malloc(bufferSize * sizeof(char));
    int currentEntryIndex = 0;
    char *nextEntry = malloc(bufferSize * sizeof(char));
    int nextEntryIndex = 0;

    char **dataValue = malloc(sizeof(char*));
    dataValue[0] = malloc(0);
    int dataIndex0 = 0;
    int dataIndex1 = 0;
    int dataRead;
    bool readIntoCurrent = true;
    bool suspicious = false;
    do {
        dataRead = fread(buffer, 1, bufferSize, file);
        for (int i = 0; i < dataRead; i++) {
            switch (buffer[i]) {
                case '\n':
                    if (i == bufferSize - 1) {
                        suspicious = true;
                    }
                    else if (suspicious) {
                        suspicious = false;
                        readIntoCurrent = false;
                        currentEntry[currentEntryIndex] = ' ';
                        currentEntryIndex++;
                        currentEntry[currentEntryIndex] = '!';
                        currentEntryIndex++;
                        continue;
                    }
                    else if (buffer[i + 1] == '\n') {
                        readIntoCurrent = false;
                        currentEntry[currentEntryIndex] = ' ';
                        currentEntryIndex++;
                        currentEntry[currentEntryIndex] = '!';
                        currentEntryIndex++;
                        i++;
                        continue;
                    } else {
                        if (readIntoCurrent) {
                            currentEntry[currentEntryIndex] = ' ';
                            currentEntryIndex++;
                        } else {
                            nextEntry[nextEntryIndex] = ' ';
                            nextEntryIndex++;
                        }
                    }
                    break;
                
                default:
                    if (suspicious) {
                        suspicious = false;
                        currentEntry[currentEntryIndex] = ' ';
                        currentEntryIndex++;
                    }
                    if (readIntoCurrent) {
                        currentEntry[currentEntryIndex] = buffer[i];
                        currentEntryIndex++;
                    } else {
                        nextEntry[nextEntryIndex] = buffer[i];
                        nextEntryIndex++;
                    }
                    break;
            }
        }

        //printf("====buffer contents====\n");
        //printf("%s\n", buffer);
        //printf("----register contents----\n");
        //printf("-c entry\n");
        //printf("%s\n", currentEntry);
        //printf("-n entry\n");
        //printf("%s\n", nextEntry);
        //printf("****    end    ****\n");

        if (currentEntryIndex != 0) {
            dataValue[dataIndex0] = realloc(dataValue[dataIndex0],
                (dataIndex1 + currentEntryIndex) * sizeof(char*));
            memcpy(dataValue[dataIndex0] + dataIndex1, currentEntry, currentEntryIndex);
            dataIndex1 += currentEntryIndex;
        }
        if (!readIntoCurrent) {
            dataIndex0++;
            dataIndex1 = 0;
            dataValue = realloc(dataValue, (dataIndex0+1)*sizeof(char*));
            dataValue[dataIndex0] = malloc(nextEntryIndex * sizeof(char));
            memcpy(dataValue[dataIndex0], nextEntry, nextEntryIndex);
            dataIndex1 += nextEntryIndex;
            readIntoCurrent = true;
        }

        //suspicious = false;
        currentEntryIndex = 0;
        nextEntryIndex = 0;
    } while(dataRead == bufferSize);


    FileData output = {
        dataValue,
        dataIndex0
    };

    fclose(file);
    free(buffer);
    free(nextEntry);
    free(currentEntry);
    printf("file read\n\n");
    return output;
}