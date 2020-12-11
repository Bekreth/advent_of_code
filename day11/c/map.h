#ifndef map_h
#define map_h

#include "../../utils/fileReader/fileReader.h"

typedef enum State {
    FLOOR,
    SEAT,
    OCUPPIED
} State;

typedef struct Space {
    int row;
    int column;
    State State;
    State NextState;
} Space;

Space* newSpace(int row, int column, char state);
void applySimulation(Space* space);
void freeSpace(Space* space);

typedef struct Map {
    int width;
    int height;
    Space*** spaces;
} Map;

Map* newMap(FileData fileData);
void simulate(Map* map, void(*primeSimulation)(Space*, Map*));
int countOccupiedSeats(Map* map);
void printMap(Map* map);
void freeMap(Map* map);

// void primeSimulation(Space* space, Map* map);

#endif