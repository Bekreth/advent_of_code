#ifndef called_h
#define called_h

#include <stdbool.h>

typedef struct Called {
    int value;
    int lastCalled;
} Called;

unsigned int hash(void* data);
bool equals(void* data1, void* data2);

#endif