#ifndef nagivation_ferry_h
#define nagivation_ferry_h

#include "direction.h"

typedef struct Waypoint {
    int posX;
    int posY;
} Waypoint;

typedef struct NavFerry {
    Waypoint* waypoint;
    int posX;
    int posY;
} NavFerry;

void applyNavInstruction(NavFerry* ferry, Instruction* instruction);
void applyNavInstructions(NavFerry* ferry, Instruction** instruction, int length);
void printNavFerry(NavFerry* ferry);

#endif 