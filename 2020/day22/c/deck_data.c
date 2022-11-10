#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "deck.h"

#define SIZE 25

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
    int initCards[25] = {
        19,
        22,
        43,
        38,
        23,
        21,
        2,
        40,
        31,
        17,
        27,
        28,
        35,
        44,
        41,
        47,
        50,
        7,
        39,
        5,
        42,
        25,
        33,
        3,
        48
    };
    initializeCards(deck, initCards);
    return deck;
}

Deck* getPlayer2() {
    Deck* deck = makeDeck();
    int initCards[25] = {
        16,
        24,
        36,
        6,
        34,
        11,
        8,
        30,
        26,
        15,
        9,
        10,
        14,
        1,
        12,
        4,
        32,
        13,
        18,
        46,
        37,
        29,
        20,
        45,
        49
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