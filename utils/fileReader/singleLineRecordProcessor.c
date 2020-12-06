#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "postProcessReader.h"

ProcessorOutput applyProcessor(int dataRead, bool suspicious, PostProcessor processor) {
    bool readIntoCurrent = true;
    for (int i = 0; i < dataRead; i++) {
        switch (processor.buffer[i]) {
            case '\n':
                readIntoCurrent = false;
                processor.currentEntry[*processor.currentEntryIndex] = '!';
                *processor.currentEntryIndex++;

                if (readIntoCurrent) {
                } else {
                    processor.nextEntry[*processor.nextEntryIndex] = ' ';
                    *processor.nextEntryIndex++;
                }
                break;
            
            default:
                if (suspicious) {
                    suspicious = false;
                    processor.currentEntry[*processor.currentEntryIndex] = ' ';
                    *processor.currentEntryIndex++;
                }
                if (readIntoCurrent) {
                    processor.currentEntry[*processor.currentEntryIndex] = processor.buffer[i];
                    *processor.currentEntryIndex++;
                } else {
                    processor.nextEntry[*processor.nextEntryIndex] = processor.buffer[i];
                    *processor.nextEntryIndex++;
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

}