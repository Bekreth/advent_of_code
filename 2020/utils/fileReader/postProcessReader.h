#ifndef post_process_reader_h
#define post_process_reader_h

#include <stdio.h>
#include <stdbool.h>

extern int postProcessorBufferSize;

typedef struct PostProcessor {
    int bufferSize;
    char *buffer;

    char *currentEntry;
    int *currentEntryIndex;

    char *nextEntry;
    int *nextEntryIndex;
} PostProcessor;

typedef struct ProcessorOutput {
    bool readIntoCurrent;
    bool suspicious;
} ProcessorOutput;


ProcessorOutput applyProcessor(int dataRead, bool suspicious, PostProcessor processor);

void printProcessor(PostProcessor processor);

#endif