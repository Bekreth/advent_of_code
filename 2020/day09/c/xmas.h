#ifndef xmas_h
#define xmas_h

#include <stdio.h>
#include <stdbool.h>

#include "intArray.h"

typedef struct XMASProtocol {
    int headPointer;
    int bufferSize;
    int* buffer;
} XMASProtocol;

void warmup(XMASProtocol* protocol, IntArray intArray);
bool updateProtocol(XMASProtocol* protocol, int value);

void printProtocol(XMASProtocol protocol);

#endif