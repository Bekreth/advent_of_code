#include "toboggan.h"

int collisionsPerSlope(Map map, int xMove, int yMove) {
    int posX = 0;
    int posY = 0;

    int collisionCounter = 0;

    while (posY < map.height-1) {
        if (map.isTree[posY][posX]) collisionCounter++;
        posX = (posX + xMove) % map.width;
        posY += yMove;
    }

    return collisionCounter;
}