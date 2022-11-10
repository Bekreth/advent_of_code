#include "postProcessReader.h"

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