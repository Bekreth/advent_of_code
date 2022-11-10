#include "fileReader.h"

FileData readFile(char *fileLocation) { 
    printf("reading file: %s\n", fileLocation);
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) 
        exit(EXIT_FAILURE);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    fclose(file);

    FileData output = {
        buffer,
        size
    };
    printf("file read\n");
    return output;
}