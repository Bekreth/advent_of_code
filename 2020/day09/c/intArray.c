#include "intArray.h"

int minMaxSum(IntArray intArray, int start, int end) {
    int min = intArray.data[start];
    int max = intArray.data[end];
    for (int i = start; i < end; i++) {
        if (intArray.data[i] < min) min = intArray.data[i];
        else if (intArray.data[i] > max) max = intArray.data[i];
    }
    return min + max;
}