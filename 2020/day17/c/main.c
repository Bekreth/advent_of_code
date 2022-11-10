#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"

int postProcessorBufferSize;


int silverAdjacency (ConwayMatrix* matrix, int x, int y, int z) {
    
}

void solveSilver(FileData data) {
    printf("solvingSilver\n");
    ConwayMatrix* matrix = createMatrix(data);
    int count = applyNeihborRule(matrix, silverAdjacency);
}

int main(int argc, char** argv) {
    printf("starting\n");
    //Calloc'ed bools are false
    bool* data = calloc(sizeof(bool), 1);
    if (*data == true) printf("truth\n");
    if (*data == false) printf("false\n");
    postProcessorBufferSize = atoi(argv[2]);

    printf("%d", *data);
}
