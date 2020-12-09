#ifndef int_array_h
#define int_array_h

typedef struct IntArray {
    int* data;
    int size;
} IntArray;

int minMaxSum(IntArray intArray, int start, int end);

#endif