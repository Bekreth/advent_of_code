#include "matrix.h"

ConwayMatrix* newMatrix(int xSize, int ySize, int zSize) {
    ConwayMatrix* matrix = malloc(sizeof(ConwayMatrix));

    bool*** xAddress = calloc(xSize * sizeof(bool**), 1);
    bool** yAddress;
    for (int x = 0; x < xSize; x++) {
        yAddress = calloc(ySize * sizeof(bool*), 1);
        xAddress[x] = yAddress;
        for (int y = 0; y < ySize; y++) {
            bool* zAddress = calloc(zSize * sizeof(bool), 1);
            yAddress[y] = zAddress;
        }
    }

    matrix->address=xAddress;
    matrix->xSize = xSize;
    matrix->ySize = ySize;
    matrix->zSize = zSize;

    return matrix;
}

void primeMatrix(ConwayMatrix* matrix, FileData data) {
    for (int i = 0; i < data.size; i++) {
        for (int j = 0; j < data.size; j++) {
            if (data.data[i + 1][j + 1] == '#') matrix->address[i + 1][j + 1][1] = true;
        }
    }
}

ConwayMatrix* createMatrix(FileData data) {
    ConwayMatrix* matrix = newMatrix(data.size + 2, data.size + 2, 3);
    primeMatrix(matrix, data);
    return matrix;
}

void freeMatrix(ConwayMatrix* matrix) {
    for (int x = 0; x <= matrix->xSize; x++) {
        for (int y = 0; y <= matrix->ySize; y++) {
            for (int z = 0; z <= matrix->xSize; z++) {
                free(matrix->address[x][y][z]);
            }
            free(matrix->address[x][y]);
        }
        free(matrix->address[x]);
    }
    free(matrix->address);
    free(matrix);
}

int activeCount(ConwayMatrix* matrix) {
    int output = 0;
    for (int x = 0; x < matrix->xSize; x++) {
        for (int y = 0; y < matrix->ySize; y++) {
            for (int z = 0; z < matrix->xSize; z++) {
                if (matrix->address[x][y][z]) output++;
            }
        }
    }
}

ConwayMatrix* applyNeihborRule(ConwayMatrix* matrix, 
    int(*activeNeihbors)(ConwayMatrix* matrix, int x, int y, int z)) {
    
    ConwayMatrix* output = newMatrix(matrix->xSize + 2, 
        matrix->ySize + 2, matrix->zSize + 2);

    int neihborCount = 0;
    bool* base;
    for (int x = 0; x < matrix->xSize; x++) {
        for (int y = 0; y < matrix->ySize; y++) {
            for (int z = 0; z < matrix->xSize; z++) {
                neihborCount = activeNeihbors(matrix, x, y, z);
                base = output->address[x + 1][y + 1];
                if (matrix->address[x][y][z]) {
                    if (neihborCount == 2 || neihborCount == 3) base[z + 1] = true;
                    else base[z + 1] = false;
                } else {
                    if (neihborCount == 3) base[z + 1] = true;
                    else base[z + 1] = false;
                }
            }
        }
    }

}


