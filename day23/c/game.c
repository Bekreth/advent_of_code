#include <stdlib.h>
#include <stdio.h>

#include "game.h"

void extractCups(Game* game);
Cup* newCup(char value);
char calculateNextValue(char base, char index);
void insertCups(Game* game, Cup* target);

Game* newGame(char input[9]) {
    Game* game = malloc(sizeof(Game));
    Cup* cups[9] = {0};
    for (int i = 0; i < 9; i++) {
        cups[i] = newCup(input[i]);
    }
    for (int i = 0; i < 8; i++) {
        cups[i]->nextCup = cups[i+1];
    }
    cups[8]->nextCup = cups[0];
    game->currentCup = cups[0];
    return game;
}

Cup* newCup(char value) {
    Cup* output = malloc(sizeof(Cup));
    output->value = atoi(&value);
    return output;
}

void playRound(Game* game) {
    extractCups(game);
    Cup* targetCup = NULL;
    int index = 0;
    while (targetCup == NULL) {
        index++;
        targetCup = searchForCup(game, 
            calculateNextValue(game->currentCup->value, index));
    }
    insertCups(game, targetCup);
    game->currentCup = game->currentCup->nextCup;
}

void extractCups(Game* game) {
    game->headOfExtracted = game->currentCup->nextCup;
    game->currentCup->nextCup = game->currentCup->nextCup->nextCup->nextCup->nextCup;
}

Cup* searchForCup(Game* game, char value) {
    Cup* walkingCup = game->currentCup;
    Cup* possibleOutput = walkingCup->nextCup;
    while (possibleOutput->value != game->currentCup->value) {
        if (possibleOutput->value == value) {
            return possibleOutput;
        }
        walkingCup = possibleOutput;
        possibleOutput = walkingCup->nextCup;
    }
    return NULL;
}

char calculateNextValue(char base, char index) {
    char output = base - index;
    if (output < 1) output += 9;
    return output;
}

void insertCups(Game* game, Cup* target) {
    Cup* newTail = target->nextCup;
    target->nextCup = game->headOfExtracted;
    game->headOfExtracted->nextCup->nextCup->nextCup = newTail;
    game->headOfExtracted = NULL;
}

void freeGame(Game* game) {
    Cup* holder;
    for (int i = 0; i < 9; i++) {
        holder = game->currentCup->nextCup;
        free(game->currentCup);
        game->currentCup = holder;
    }
    free(game);
}

void printGame(Game* game) {
    Cup* holder = game->currentCup;
    printf(" -");
    for (int i = 0; i < 9; i++) {
        printf(" %d", holder->value);
        holder = holder->nextCup;
    }
    printf(" -\n");
}
