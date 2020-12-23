#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

void solveSilver(Game* game) {
    for (int i = 0; i < 100; i++) {
        playRound(game);
    }
    Cup* headCup = searchForCup(game, 1);
    printGame(game);
    for (int i = 0; i < 8; i++) {
        headCup = headCup->nextCup;
        printf("%d", headCup->value);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    char data[9];
    memcpy(data, argv[1], 9);
    Game* game = newGame(data);
    solveSilver(game);
    freeGame(game);
}
