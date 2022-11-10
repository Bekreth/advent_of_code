#ifndef file_reader_h
#define file_reader_h

#include<stdio.h>
#include<stdlib.h>

typedef struct FileData {
    int size;
    char *row;
    char *column;
} FileData;

FileData * readFile(char *fileLocation);

#endif