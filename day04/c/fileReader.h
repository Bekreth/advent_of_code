#ifndef file_reader_h
#define file_reader_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct FileData {
    char** data;
    int elementCount;
} FileData;

FileData readFile(char *fileLocation);

#endif