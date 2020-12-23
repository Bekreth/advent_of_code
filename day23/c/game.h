#ifndef game_h
#define game_h

typedef struct Cup {
    int value;
    struct Cup* nextCup;
} Cup;

typedef struct Game {
    int size;
    Cup* currentCup;
    Cup* headOfExtracted;
} Game;

Game* newGame(int* input, int size);
void playRound(Game* game);
Cup* searchForCup(Game* game, int value);

void freeGame(Game* game);
void printGame(Game* game);

#endif