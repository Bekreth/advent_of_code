#include <stdlib.h>
#include <stdio.h>

#include "deck.h"
#include "combat.h"

int countDeckValue(Deck* deck) {
    int counter = 0;
    for (int i = deck->size; i > 0; i--) {
        counter += (deck->topOfDeck->value * i);
        deck->topOfDeck = deck->topOfDeck->nextCard;
    }
    return counter;
}

void solveSilver() {
    printf("solving silver\n");
    Deck* player1 = getPlayer1();
    Deck* player2 = getPlayer2();

    printf(" - %d\n", countDeckValue(playGame(player1, player2)));
}

int main(int argc, char** argv) {
    printf("starting\n");

    solveSilver();
}
