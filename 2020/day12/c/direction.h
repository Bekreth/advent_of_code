#ifndef direction_h
#define direction_h

#include <stdbool.h>

#include "../../utils/fileReader/fileReader.h"

typedef enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
} Direction;

typedef enum Rotation {
    LEFT,
    RIGHT
} Rotation;

typedef struct Instruction {
    Direction direction;
    bool hasDirection;
    Rotation rotation;
    bool hasRotation;
    bool forward;
    int amount;
} Instruction;


Instruction** readInstructions(FileData fileData);
void freeInstructions(Instruction** instractions, int length);

#endif