#include <stdio.h>
#include "combat.h"

void swapCards(Card* card1, Card* card2) {
    if (card2 != card2->nextCard) {
        card2->nextCard->previousCard = card2->previousCard;
        card2->previousCard->nextCard = card2->nextCard;
    }

    card2->previousCard = card1;
    card2->nextCard = card1->nextCard;

    card1->nextCard->previousCard = card2;
    card1->nextCard = card2;
}

Deck* playGame(Deck* player1, Deck* player2) {
    Card* player1Next;
    Card* player2Next;
    // int index = 0;
    while (player1->size != 0 && player2->size != 0) {
        // index++;
        // printf("-- %d --\n", index);
        //printf("player1 %d: %d\n", player1->size, player1->topOfDeck->value);
        //printf("player2 %d: %d\n", player2->size, player2->topOfDeck->value);

        //printf("deck 1\n");
        //printDeck(player1);

        //printf("deck 2\n");
        //printDeck(player2);

        Card* player1Next = player1->topOfDeck->nextCard;
        Card* player2Next = player2->topOfDeck->nextCard;
        
        if (player1->topOfDeck->value > player2->topOfDeck->value) {
            swapCards(player1->topOfDeck, player2->topOfDeck);
            player1->size++;
            player2->size--;
        } else {
            swapCards(player2->topOfDeck, player1->topOfDeck);
            player2->size++;
            player1->size--;
        }
        player1->topOfDeck = player1Next;
        player2->topOfDeck = player2Next;
    }
    if (player1->size == 0) {
        return player2;
    } else {
        return player1;
    }
}