#include <stdlib.h>
#include <stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "intArray.h"
#include "xmas.h"

int postProcessorBufferSize = 2;

void solveGold(int point, IntArray array) {
    printf("starting gold\n");

    int comparingSum = 0;
    for (int i = 0; i < array.size - 1; i++) {
        comparingSum = array.data[i];
        for (int j = i+1; comparingSum < point; j++) {
            comparingSum += array.data[j];
            if (comparingSum == point) {
                printf("sum of values: %d\n\n", minMaxSum(array, i, j));
                return;
            }
        }
    }
}

int solveSilver(XMASProtocol* protocol, IntArray array) {
    printf("starting silver\n");
    int index = protocol->bufferSize;
    bool running = true;
    while (running && index < array.size) {
        running = updateProtocol(protocol, array.data[index]);
        index++;
    }
    printf("value 1: %d\n\n", array.data[index-1]);
    return array.data[index-1];
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData fileData = readFile(argv[1]);
    int bufferSize = atoi(argv[2]);
    if (bufferSize == 0) {
        printf("failed to parse buffer\n");
        return 1;
    }

    int* intArrayData = malloc(fileData.size * sizeof(int));
    for (int i = 0; i < fileData.size; i++) {
        intArrayData[i] = atoi(fileData.data[i]);
        free(fileData.data[i]);
    }
    free(fileData.data);
    IntArray intArray = {intArrayData, fileData.size};

    int* buffer = malloc(bufferSize * sizeof(int));
    XMASProtocol* protocol = malloc(sizeof(XMASProtocol));
    protocol->headPointer = 0;
    protocol->bufferSize = bufferSize;
    protocol->buffer = buffer;
    warmup(protocol, intArray);

    int point1 = solveSilver(protocol, intArray);

    free(protocol->buffer);
    free(protocol);

    solveGold(point1, intArray);
    free(intArray.data);
}