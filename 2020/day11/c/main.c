#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../../utils/fileReader/fileReader.h"
#include "map.h"

int postProcessorBufferSize = 9;

bool colidesNegativeXY(Space* space, Map* map, int column) {
    int row = space->row + (column - space->column);
    if (row < 0 || row > map->height - 1) return false;
    return map->spaces[row][column]->State == OCUPPIED;
}

bool colidesPositiveXY(Space* space, Map* map, int column) {
    int row = space->row - (column - space->column);
    if (row < 0 || row > map->height - 1) return false;
    return map->spaces[row][column]->State == OCUPPIED;
}

bool colidesHorizontal(Space* space, Map* map, int column) {
    return map->spaces[space->row][column]->State == OCUPPIED;
}

bool colidesVertical(Space* space, Map* map, int row) {
    return map->spaces[row][space->column]->State == OCUPPIED;
}

void goldRules(Space* space, Map* map) {
    if (space->State == FLOOR) return;
    int counter = 0;

    bool leftNegativeXY = false;
    bool leftPositiveXY = false;
    bool left = false;

    bool rightNegativeXY = false;
    bool rightPositiveXY = false;
    bool right = false;

    bool top = false;
    bool bottom = false;

    for (int i = 0; i < space->column; i++) {
        if (!leftNegativeXY && colidesNegativeXY(space, map, i)) {
            leftNegativeXY = true;
            counter++;
        }
        if (!leftPositiveXY && colidesPositiveXY(space, map, i)) {
            leftPositiveXY = true;
            counter++;
        }
        if (!left && colidesHorizontal(space, map, i)) {
            left = true;
            counter++;
        }
    }

    for (int i = space->column + 1; i < map->width; i++) {
        if (!rightNegativeXY && colidesNegativeXY(space, map, i)) {
            rightNegativeXY = true;
            counter++;
        }
        if (!rightPositiveXY && colidesPositiveXY(space, map, i)) {
            rightPositiveXY = true;
            counter++;
        }
        if (!right && colidesHorizontal(space, map, i)) {
            right = true;
            counter++;
        }
    }

    for (int i = 0; i < space->row; i++) {
        if (colidesVertical(space, map, i)){
            top = true;
            counter++;
            break;
        } 
    }
    for (int i = space->row + 1; i < map->height; i++) {
        if (colidesVertical(space, map, i)){
            bottom = true;
            counter++;
            break;
        } 
    }

    if (space->State == SEAT) {
        if (counter == 0) space->NextState = OCUPPIED;
    } else if (space->State == OCUPPIED) {
        if (counter >= 5) space->NextState = SEAT;
    }
}

void solveGold(Map* map) {
    printf("solving gold\n");
    int lastSeating = 0;
    int currentSeating = -1;
    while (lastSeating != currentSeating) {
        lastSeating = currentSeating;
        simulate(map, goldRules);
        currentSeating = countOccupiedSeats(map);
    }
    printf("the stable count is %d\n", currentSeating);
}

void silverRules(Space* space, Map* map) {
    if (space->State == FLOOR) return;
    int counter = 0;
    for (int i = space->row - 1; i <= space->row + 1; i++) {
        for (int j = space->column - 1; j <= space->column + 1; j++) {
            if (i < 0 || i > map->height - 1 || j < 0 || j > map->width - 1) continue;
            if (i == space->row  && j == space->column) continue;
            if (map->spaces[i][j]->State == OCUPPIED) counter++;
        }
    }
    if (space->State == SEAT) {
        if (counter == 0) space->NextState = OCUPPIED;
    } else if (space->State == OCUPPIED) {
        if (counter >= 4) space->NextState = SEAT;
    }
}

void solveSilver(Map* map) {
    printf("solving silver\n");
    int lastSeating = 0;
    int currentSeating = -1;
    while (lastSeating != currentSeating) {
        lastSeating = currentSeating;
        simulate(map, silverRules);
        currentSeating = countOccupiedSeats(map);
    }
    printf("the stable count is %d\n", currentSeating);
}

int main(int argc, char** argv) {
    printf("starting");
    FileData fileData = readFile(argv[1]);

    Map* map = newMap(fileData);

    for (int i = 0; i < 5; i++) {
        printMap(map);
        simulate(map, goldRules);
        printf("\n");
    }

    //solveSilver(map);
    //freeMap(map);

    //map = newMap(fileData);
    //solveGold(map);
    //freeMap(map);

}
