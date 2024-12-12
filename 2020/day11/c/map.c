#include "map.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

int countRowWidth(char* row) {
    int index = 0;
    while (true) {
        if (row[index] == '!') return index;
        index++;
    }
}

Space* newState(int row, int column, char state) {
    Space* output = malloc(sizeof(Space));
    output->row = row;
    output->column = column;
    switch (state) {
    case '.':
        output->State = FLOOR;
        output->NextState = FLOOR;
        break;
    
    case 'L':
        output->State = SEAT;
        output->NextState = SEAT;
        break;
    }
    return output;
}

void primeSimulation(Space* space, Map* map) {
    if (space->State == FLOOR) return;
    int counter = 0;
    for (int i = space->row - 1; i <= space->row + 1; i++) {
        for (int j = space->column - 1; j <= space->column + 1; j++) {
            if (i < 0 || i > map->height - 1 || j < 0 || j > map->width - 1) continue;
            if (i == space->row  && j == space->column) continue;
            if (map->spaces[i][j]->State == OCUPPIED) counter++;
        }
    }
    // printf("%d %d\n", space->row, space->column);
    if (space->State == SEAT) {
        if (counter == 0) space->NextState = OCUPPIED;
    } else if (space->State == OCUPPIED) {
        if (counter >= 4) space->NextState = SEAT;
    }
}

void applySimulation(Space* space) {
    space->State = space->NextState;
}

void freeSpace(Space* space) {
    free(space);
}

Map* newMap(FileData fileData) {
    Map* map = malloc(sizeof(Map));
    map->width = countRowWidth(fileData.data[0]);
    map->height = fileData.size;
    map->spaces = malloc(map->height * sizeof(Space**));
    for (int i = 0; i < fileData.size; i++) {
        map->spaces[i] = malloc(map->width * sizeof(Space*));
        for (int j = 0; j < map->width; j++) {
            map->spaces[i][j] = newState(i, j, fileData.data[i][j]);
        }
    }
    return map;
}

void simulate(Map* map, void(*primeSimulation)(Space*, Map*)) {
    // printf("test - %d %d\n", map->spaces[1][0]->row, map->spaces[1][0]->column);
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            primeSimulation(map->spaces[i][j], map);
        }
    }
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            applySimulation(map->spaces[i][j]);
        }
    }
}

int countOccupiedSeats(Map* map) {
    int counter = 0;
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->spaces[i][j]->State == OCUPPIED) counter++;
        }
    }
    return counter;
}

void printMap(Map* map) {
    // printf("==== Map ====\n");
    // printf("Width: %d\n", map->width);
    // printf("Height: %d\n", map->height);
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            switch (map->spaces[i][j]->State) {
            case 0:
                printf(".");
                break;
            case 1:
                printf("L");
                break;
            case 2:
                printf("#");
                break;
            }
        }
        putchar('\n');
    }
}

void freeMap(Map* map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            freeSpace(map->spaces[i][j]);
        }
        free(map->spaces[i]);
    }
    free(map);
}
