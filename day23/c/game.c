#include <stdlib.h>
#include <stdio.h>

#include "game.h"

void extractCups(Game* game);
Cup* newCup(int value);
int calculateNextValue(Game* game, int base);
void insertCups(Game* game, Cup* target);

Game* newGame(int* input, int size) {
    Game* game = malloc(sizeof(Game));
    game->size = size;
    Cup** cups = calloc(size, sizeof(Cup*));
    for (int i = 0; i < size; i++) {
        cups[i] = malloc(sizeof(Cup));
        cups[i]->value = input[i];
    }
    for (int i = 0; i < size - 1; i++) {
        cups[i]->nextCup = cups[i+1];
    }

    cups[size-1]->nextCup = cups[0];
    game->currentCup = cups[0];

    free(cups);
    return game;
}

void playRound(Game* game) {
    extractCups(game);
    int searchTarget = calculateNextValue(game, game->currentCup->value);
    Cup* targetCup = searchForCup(game, searchTarget);
    insertCups(game, targetCup);
    game->currentCup = game->currentCup->nextCup;
}

void extractCups(Game* game) {
    game->headOfExtracted = game->currentCup->nextCup;
    game->currentCup->nextCup = game->currentCup->nextCup->nextCup->nextCup->nextCup;
}

Cup* searchForCup(Game* game, int value) {
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

int calculateNextValue(Game* game, int base) {
    int output = base - 1;
    if (output < 1) output += game->size;
    Cup* extractedHead = game->headOfExtracted;
    for (int i = 0; i < 3; i++) {
        if (extractedHead->value == output) {
            return calculateNextValue(game, output);
        }
        extractedHead = extractedHead->nextCup;
    }
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
    for (int i = 0; i < game->size; i++) {
        holder = game->currentCup->nextCup;
        free(game->currentCup);
        game->currentCup = holder;
    }
    free(game);
}

void printGame(Game* game) {
    Cup* holder = game->currentCup;
    printf(" -");
    for (int i = 0; i < game->size; i++) {
        printf(" %d", holder->value);
        holder = holder->nextCup;
    }
    printf(" -\n");
}
