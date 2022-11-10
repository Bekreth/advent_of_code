#include "xmas.h"


void warmup(XMASProtocol* protocol, IntArray intArray) {
    for (int i = 0; i < protocol->bufferSize; i++) {
        protocol->buffer[i] = intArray.data[i];
    }
}

bool updateProtocol(XMASProtocol* protocol, int value) {
    for (int i = 0; i < protocol->bufferSize; i++) {
        for (int j = 0; j < protocol->bufferSize; j++) {
            if (j == i) continue;
            if (protocol->buffer[i % protocol->bufferSize] 
                + protocol->buffer[j % protocol->bufferSize] == value) {

                protocol->buffer[protocol->headPointer] = value;
                protocol->headPointer = (protocol->headPointer + 1) % protocol->bufferSize;
                return true;
            }
        }
    }
    protocol->headPointer = (protocol->headPointer + 1) % protocol->bufferSize;
    return false;
}

void printProtocol(XMASProtocol protocol) {
    printf("== Protocol ==\n");
    printf("Buffer Size: %d\n", protocol.bufferSize);
    printf("Header Pointer: %d\n", protocol.headPointer);
    for (int i = 0; i < protocol.bufferSize; i++) {
        printf("\t%d\n", protocol.buffer[i]);
    }
    printf("\n");
}