#include <stdlib.h>

#include "hashTable.h"

Entry* newEntry(void* data);
void freeEntry(Entry* entry);
void addToEntry(Entry* entry, void* data);
bool removeFromEntry(Entry* entry, void* data);
bool existsInEntry(Entry* entry, void* data);

HashTable* newHashTable(unsigned int size) {
    HashTable* output = malloc(sizeof(HashTable));

    output->size = 0;
    output->capacity = size;
    output->data = malloc(size * sizeof(Entry*));

    return output;
}

Entry* newEntry(void* data) {
    Entry* output = malloc(sizeof(Entry));
    output->size = 1;
    output->capacity = 1;
    output->data = malloc(sizeof(void**));
    output->data[0] = data;
    return output;
}

void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->capacity; i++) {
        if (hashTable->data[i] != NULL) freeEntry(hashTable->data[i]);
    }
    free(hashTable->data);
    free(hashTable);
}

void freeEntry(Entry* entry) {
    for (int i = 0; i < entry->capacity; i++) {
        if (entry->data[i] != NULL) free(entry->data[i]);
    }
    free(entry->data);
    free(entry);
}

void addData(HashTable*  hashTable, void* data) {
    if (exists(hashTable, data)) return;
    unsigned int hashIndex = hash(data) % hashTable->capacity;
    Entry* entry = hashTable->data[hashIndex];

    if (entry == NULL) hashTable->data[hashIndex] = newEntry(data);
    else addToEntry(entry, data);

    hashTable->size++;
}

void addToEntry(Entry* entry, void* data) {
    if (entry->size < entry->capacity) {
        for (int i = 0; i < entry->capacity; i++) {
            if (entry->data[i] == NULL) {
                entry->data[i] == data;
            }
        }
    } else {
        entry->capacity++;
        entry->data = realloc(entry->data, entry->capacity * sizeof(void**));
        entry->data[entry->capacity - 1] = data;
    }
    entry->size++;
}

void removeData(HashTable* hashTable, void* data) {
    unsigned int hashIndex = hash(data) % hashTable->capacity;
    Entry* entry = hashTable->data[hashIndex];
    if (entry != NULL) {
        if (removeFromEntry(entry, data)) {
            hashTable->size--;
            return;
        }
    }
}

bool removeFromEntry(Entry* entry, void* data) {
    void* handle;
    for (int i = 0; i < entry->capacity; i++) {
        if (entry->data[i] == NULL) continue;
        if (equals(entry->data[i], data)) {
            handle = entry->data[i];
            entry->data[i] = NULL;
            free(handle);
            entry->size--;
            return true;
        }
    }
    return false;
}

bool exists(HashTable* hashTable, void* data) {
    unsigned int hashIndex = hash(data) % hashTable->capacity;
    Entry* entry = hashTable->data[hashIndex];
    if (entry == NULL) return false;
    return existsInEntry(entry, data);
}

bool existsInEntry(Entry* entry, void* data) {
    for (int i = 0; i < entry->capacity; i++) {
        if (entry->data[i] == NULL) continue;
        if (equals(entry->data[i], data)) return true;
    }
    return false;
}

SearchResults* searchTable(HashTable* table, bool(*predicate)(void*)) {
    SearchResults* results = malloc(sizeof(SearchResults));
    results->size = 0;
    results->data = malloc(0);

    Entry* entry;
    for (int i = 0; i < table->capacity; i++) {
        entry = table->data[i];
        for (int j = 0; j < entry->capacity; j++) {
            if (predicate(entry->data[j])) {
                results->size++;
                results->data = realloc(results->data, results->size * sizeof(void*));
                results->data[results->size - 1] = entry->data[j];
            }
        }
    }
    return results;
}

void freeSearchResults(SearchResults* results) {
    free(results->data);
    free(results);
}

void printHashTable(HashTable* table) {
    printf("== Hash Table ==\n");
    for (int i = 0; i < table->capacity; i++) {
        if (table->data[i] == NULL) printf("- entry[%d] = NULL\n", i);
        else {
            printf("- entry[%d] = \n", i);
            printEntry(table->data[i]);
        }
    }
}

void printEntry(Entry* entry) {
    printf("\t = Entry = \n");
    for (int i = 0; i < entry->capacity; i++) {
        if (entry->data[i] == NULL) printf("\t - data[%d] = NULL\n", i);
        else printf("\t - data[%d] = %d\n", i, hash(entry->data[i]));
    }
}