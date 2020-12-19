#ifndef rules_h
#define rules_h

#include <stdbool.h>

typedef struct Rule {
    bool reduced;
    int ruleCount;
    int* size;
    int id;
    union data {
        char* value;
        int** referenceRule;
    } data;
} Rule;


Rule* newRule(char* input);
void freeRule(Rule* rule);
void printRule(Rule* rule);

unsigned int hash(void* data);
bool equals(void* data1, void* data2);


#endif