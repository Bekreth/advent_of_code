#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "postProcessReader.h"
#include "postProcessDebugger.c"

ProcessorOutput applyProcessor(int dataRead, bool suspicious, PostProcessor processor) {
    bool readIntoCurrent = true;
    for (int i = 0; i < dataRead; i++) {
        switch (processor.buffer[i]) {
            case '\n':
                readIntoCurrent = false;
                processor.currentEntry[*processor.currentEntryIndex] = '!';
                (*processor.currentEntryIndex)++;
                break;
            
            default:
                if (readIntoCurrent) {
                    processor.currentEntry[*processor.currentEntryIndex] = processor.buffer[i];
                    (*processor.currentEntryIndex)++;
                } else {
                    processor.nextEntry[*processor.nextEntryIndex] = processor.buffer[i];
                    (*processor.nextEntryIndex)++;
                }
                break;
        }
    }

    // printProcessor(processor);
    ProcessorOutput output = {readIntoCurrent, false};
    return output;
}