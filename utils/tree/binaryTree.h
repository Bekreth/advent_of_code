#ifndef binary_tree_h
#define binary_tree_h

#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* newNode(int value);
void addNode(Node* parent, Node* child);
void freeTree(Node* node);

Node* evenTree(Node* node);
Node* rebalanceAboutValue(Node* node, int pointOfInterest);
Node* unbalanceTreeRight(Node* node);
Node* unbalanceTreeLeft(Node* node);

Node* treeMin(Node* node);
Node* treeMax(Node* node);
unsigned int treeSize(Node* node);
unsigned int treeDepth(Node* node);
bool treesAreEqual(Node* node1, Node* node2);
Node* searchForNode(void* initialState, Node* tree, int (*predicate)(void* state, Node* input));



#endif