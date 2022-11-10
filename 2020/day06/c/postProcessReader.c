#include "../../utils/fileReader/postProcessReader.h"

int postProcessorBufferSize = 5;

ProcessorOutput applyProcessor(int dataRead, bool suspicious, PostProcessor processor) {
    bool readIntoCurrent = true;
    for (int i = 0; i < dataRead; i++) {
        switch (processor.buffer[i]) {
            case '\n':
                if (i == processor.bufferSize - 1) {
                    suspicious = true;
                }
                else if (suspicious) {
                    suspicious = false;
                    readIntoCurrent = false;
                    processor.currentEntry[*processor.currentEntryIndex] = '!';
                    (*processor.currentEntryIndex)++;
                    continue;
                }
                else if (processor.buffer[i + 1] == '\n') {
                    readIntoCurrent = false;
                    processor.currentEntry[*processor.currentEntryIndex] = '!';
                    (*processor.currentEntryIndex)++;
                    i++;
                    continue;
                } else {
                    if (readIntoCurrent) {
                        processor.currentEntry[*processor.currentEntryIndex] = '\n';
                        (*processor.currentEntryIndex)++;
                    } else {
                        processor.nextEntry[*processor.nextEntryIndex] = '\n';
                        (*processor.nextEntryIndex)++;
                    }
                }
                break;
            
            default:
                if (suspicious) {
                    suspicious = false;
                    processor.currentEntry[*processor.currentEntryIndex] = '\n';
                    (*processor.currentEntryIndex)++;
                }
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

    //printProcessor(processor);

    ProcessorOutput output = {readIntoCurrent, suspicious};
    return output;
}