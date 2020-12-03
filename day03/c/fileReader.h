#ifndef file_reader_h
#define file_reader_h

#include <stdlib.h>
#include <stdio.h>

typedef struct FileData {
    char* data;
    int size;
} FileData;

FileData readFile(char *fileLocation);

#endif