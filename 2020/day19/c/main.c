#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "../../utils/hashTable/hashTable.h"

#include "rules.h"
#include "message.h"

int postProcessorBufferSize;

char** compressRules(HashTable* rulesTable);

void solveSilver(HashTable* rulesTable, Message** messages, int size) {
    printf("solving silver\n");

    printf(" - %d - \n", 10);
}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[1]);
    FileData rules = readFile(argv[2]);
    FileData data = readFile(argv[3]);
    printf("data read\n");

    HashTable* rulesTable = newHashTable(20);
    for (int i = 0; i < rules.size; i++) {
        addData(rulesTable, newRule(rules.data[i]));
    }
    printf("rules tables built\n");


    Message** messages = malloc(data.size * sizeof(Message*));
    int messageSize = data.size;
    for (int i = 0; i < messageSize; i++) {
        messages[i] = newMessage(data.data[i]);
    }
    printf("messages built\n");

    solveSilver(rulesTable, messages, messageSize);


    freeHashTable(rulesTable);
    for (int i = 0; i < messageSize; i++) {
        freeMessage(messages[i]);
    }
    free(rulesTable);
}

bool returnAll(void* data) {
    return true;
}

char** compressRules(HashTable* rulesTable) {
    SearchResults* results = searchTable(rulesTable, returnAll);
    char** output = malloc(results->size * sizeof(char*));
    int outputIndex = 0;

    Rule* rule;
    for (int i = 0; i < results->size; i++) {
        rule = results->data[i];
        for (int j = 0; j < rule->ruleCount; j++) {
        }
    }

    return output;
}

typedef struct CompressedRule {
    int size;
    char** data;
} CompressedRule;

CompressedRule compressRule(HashTable* rulesTable, Rule* rule) {
    CompressedRule output;
    output.size = rule->ruleCount;
    output.data = malloc(output.size * sizeof(char*));
    for (int i = 0; i < rule->ruleCount; i++) {
        output.data[i] = malloc(rule->size[i] * sizeof(char));

    }

}