#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "fileReader.h"
#include "map.h"
#include "toboggan.h"


void solveSilver(Map map) {
    printf("solving silver\n");
    printf("collisions: %d\n\n", collisionsPerSlope(map, 3, 1));
}

void solveGold(Map map) {
    printf("solving gold\n");
    int collisionsOn1 = collisionsPerSlope(map, 1, 1);
    int collisionsOn3 = collisionsPerSlope(map, 3, 1);
    int collisionsOn5 = collisionsPerSlope(map, 5, 1);
    int collisionsOn7 = collisionsPerSlope(map, 7, 1);
    int collisionsOnHalf = collisionsPerSlope(map, 1, 2);

    int product = collisionsOn1 * collisionsOnHalf * collisionsOn3 
        * collisionsOn5 * collisionsOn7;
    printf("collisions: %d\n\n", product);
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData data = readFile(argv[1]);
    Map map = newMap(data);
    printf("\n===========\n");
    solveSilver(map);
    solveGold(map);
}