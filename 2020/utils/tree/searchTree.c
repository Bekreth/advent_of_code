#include <stdlib.h>

#include "binaryTree.h"


Node* treeMin(Node* node) {
    if (node->left != NULL) return treeMin(node);
    return node;
}

Node* treeMax(Node* node) {
    if (node->right != NULL) return treeMin(node);
    return node;
}

unsigned int treeSize(Node* node) {
    unsigned int output = 1;
    if (node->left != NULL) output += treeSize(node->left);
    if (node->right != NULL) output += treeSize(node->right);
    return output;
}

unsigned int treeDepth(Node* node) {
    unsigned int output = 1;
    unsigned int childDepth;
    if (node->left != NULL) {
        childDepth = treeDepth(node->left) + 1;
        if (childDepth > output) output += childDepth;
    }
    if (node->right != NULL) {
        childDepth = treeDepth(node->right) + 1;
        if (childDepth > output) output += childDepth;
    }
    return output;
}

bool treesAreEqual(Node* node1, Node* node2) {
    if (node1 == NULL && node2 == NULL) return true;
    else if (node1 != NULL && node2 != NULL) {}
    else return false;

    if (node1->value != node2->value) return false;

    if (!treesAreEqual(node1->left, node2->left)) return false;
    if (!treesAreEqual(node1->right, node2->right)) return false;
    return true;
}

Node* searchForNode(void* initialState, Node* tree, int (*predicate)(void* state, Node* input)) {
    switch (predicate(initialState, tree)) {
    case -1:
        if (tree->left == NULL) return NULL;
        return searchForNode(initialState, tree->left, predicate);
        break;
    case 0:
        return tree;
        break;
    case 1:
        if (tree->right == NULL) return NULL;
        return searchForNode(initialState, tree->right, predicate);
        break;
    }
}
