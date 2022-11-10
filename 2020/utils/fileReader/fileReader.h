#ifndef file_reader_h
#define file_reader_h

typedef struct FileData {
    char **data;
    int size;
} FileData;

FileData readFile(char* input);

void printFileData(FileData data);

#endif

