#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "deck.h"

#define SIZE 5

Deck* makeDeck() {
    Deck* deck = malloc(sizeof(Deck));
    deck->size = SIZE;
    return deck;
}

void initializeCards(Deck* deck, int initCards[SIZE]) {
    Card* topCard = malloc(sizeof(Card));
    topCard->value = initCards[0];
    Card* previousCard = topCard;
    Card* currentCard;
    for (int i = 1; i < SIZE; i++) {
        currentCard = malloc(sizeof(Card));
        currentCard->value = initCards[i];
        currentCard->previousCard = previousCard;
        previousCard->nextCard = currentCard;
        previousCard = currentCard;
    }
    previousCard->nextCard = topCard;
    topCard->previousCard = previousCard;
    deck->topOfDeck = topCard;
}

Deck* getPlayer1() {
    Deck* deck = makeDeck();
    int initCards[SIZE] = {
        9,
        2,
        6,
        3,
        1,
    };
    initializeCards(deck, initCards);
    return deck;
}

Deck* getPlayer2() {
    Deck* deck = makeDeck();
    int initCards[SIZE] = {
        5,
        8,
        4,
        7,
        10,
    };
    initializeCards(deck, initCards);
    return deck;
}

void printDeck(Deck* deck) {
    printf("deck size %d\n", deck->size);
    for (int i = 0; i < deck->size; i++) {
        printf("  %d\n", deck->topOfDeck->previousCard->value);
        printf("%d: %d\n", i, deck->topOfDeck->value);
        printf("  %d\n", deck->topOfDeck->nextCard->value);
        deck->topOfDeck = deck->topOfDeck->nextCard;
    }
}