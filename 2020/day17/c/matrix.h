#ifndef matrix_h
#define matrix_h

#include <stdbool.h>
#include "../../utils/fileReader/fileReader.h"

typedef struct ConwayMatrix {
    bool*** address;
    int xSize;
    int ySize;
    int zSize;
} ConwayMatrix;

ConwayMatrix* createMatrix(FileData data);
void freeMatrix(ConwayMatrix* matrix);

int activeCount(ConwayMatrix* matrix);
ConwayMatrix* applyNeihborRule(ConwayMatrix* matrix, 
    int(*activeNeihbors)(ConwayMatrix* matrix, int x, int y, int z));


#endif