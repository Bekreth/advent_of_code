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

void printProcessor(PostProcessor processor) {

    printf("====buffer contents====\n");
    printf("%s---\n", processor.buffer);
    printf("----register contents----\n");
    printf("-c entry: index %d\n", *processor.currentEntryIndex);
    printf("%s---\n", processor.currentEntry);
    printf("-n entry: index %d\n", *processor.nextEntryIndex);
    printf("%s---\n", processor.nextEntry);
    printf("****    end    ****\n");

}

typedef struct ProcessorOutput {
    bool readIntoCurrent;
    bool suspicious;
} ProcessorOutput;


ProcessorOutput applyProcessor(int dataRead, bool suspicious, PostProcessor processor);

#endif