#ifndef deck_h
#define deck_h

typedef struct Card {
    int value;
    struct Card* nextCard;
    struct Card* previousCard;
} Card;

typedef struct Deck {
    int size;
    Card* topOfDeck;
} Deck;

Deck* getPlayer1();
Deck* getPlayer2();
void printDeck(Deck* deck);


#endif