#include <stdlib.h>
#include <stdio.h>

#include "called.h"
#include "../../utils/hashTable/hashTable.h"


void printHashTable(HashTable* table);
void printEntry(Entry* entry);

int main(int argc, char** argv) {
    printf("starting\n");
    printf("running : %s\n", argv[1]);

    int count = 10000;

    HashTable* table = newHashTable(1000);
    Called* called;
    for (int i = 0; i < count; i++) {
        called = malloc(sizeof(Called));
        called->value = i * i;
        called->lastCalled = i;
        addData(table, called);
    }
    printf("Size: %d\n", table->size);

    for (int i = 0; i < count; i++) {
        called = malloc(sizeof(Called));
        called->value = i * i;
        called->lastCalled = i;
        free(called);
    }

    printf("Deleting \n");
    for (int i = 0; i < count/2; i++) {
        called = malloc(sizeof(Called));
        called->value = i * i;
        called->lastCalled = i;
        removeData(table, called);
        free(called);
    }
    printf("Size %d\n", table->size);

    printf("Deleted \n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        called = malloc(sizeof(Called));
        called->value = i * i;
        called->lastCalled = i;
        if (exists(table, called)) found++;
        free(called);
    }
    printf("Found %d\n", found);

    freeHashTable(table);
}