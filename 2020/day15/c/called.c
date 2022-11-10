#include "called.h"

#define SALT 8265198
#define PEPPER 15

unsigned int hash(void* data) {
    Called* d = data;
    return (d->value + PEPPER) * SALT;
}

bool equals(void* data1, void* data2) {
    return ((Called*)data1)->value == ((Called*)data2)->value;
}
