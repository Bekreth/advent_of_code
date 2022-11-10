#ifndef map_h
#define map_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "fileReader.h"

typedef struct Map {
    bool **isTree;
    int width;
    int height;
} Map;

Map newMap(FileData fileData);
void printMap(Map map);

#endif