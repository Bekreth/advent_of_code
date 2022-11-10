#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

#define MILLION 1000000
#define TEN_MILLION 10000000
#define TEN_THOUSAND 10000000

void solveGold(int* data) {
    printf("solving gold\n");
    Game* game = newGame(data, MILLION);
    for (int i = 0; i < TEN_THOUSAND; i++) {
        playRound(game);
    }
    Cup* headCup;
    if (game->currentCup->value == 1) headCup = game->currentCup;
    else headCup = searchForCup(game, 1);
    int value1 = headCup->nextCup->value;
    int value2 = headCup->nextCup->nextCup->value;
    printf("%d - %d : %d\n", value1, value2, value1 * value2);
    freeGame(game);
}

void solveSilver(int* data) {
    printf("solving silver\n");
    Game* game = newGame(data, 9);
    for (int i = 0; i < 100; i++) {
        playRound(game);
    }
    Cup* headCup;
    if (game->currentCup->value == 1) headCup = game->currentCup;
    else searchForCup(game, 1);

    for (int i = 0; i < 8; i++) {
        headCup = headCup->nextCup;
        printf("%d", headCup->value);
    }
    printf("\n\n");
    freeGame(game);
}

int main(int argc, char** argv) {
    char* input = argv[1];
    int data[MILLION];
    char hold;
    for (int i = 0; i < 9; i++) {
        hold = input[i];
        data[i] = atoi(&hold);
    }
    for (int i = 9; i < MILLION; i++) {
        data[i] = i + 1;
    }
    solveSilver(data);
    printf("While this solution technically works, it takes 16 hours\n");
    //solveGold(data);
}
