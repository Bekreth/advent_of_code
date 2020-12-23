#ifndef game_h
#define game_h

typedef struct Cup {
    char value;
    struct Cup* nextCup;
} Cup;

typedef struct Game {
    Cup* currentCup;
    Cup* headOfExtracted;
} Game;

Game* newGame(char input[9]);
void playRound(Game* game);
Cup* searchForCup(Game* game, char value);

void freeGame(Game* game);
void printGame(Game* game);

#endif