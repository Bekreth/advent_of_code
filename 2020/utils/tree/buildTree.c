#include <stdlib.h>

#include "binaryTree.h"


Node* newNode(int value) {
    Node* output = malloc(sizeof(Node));
    output->value = value;
    return output;
}

void freeTree(Node* node) {
    free(node->parent);

    if (node->left != NULL) {
        freeTree(node);
        free(node->left);
    }
    if (node->right != NULL) {
        freeTree(node->right);
        free(node->right);
    }

    free(node);
}

void addNode(Node* parent, Node* child) {
    if (parent->value == child->value) return;

    if (parent->value > child->value) {
        if (parent->left == NULL) parent->left = malloc(sizeof(Node));
        parent->left = child;
    } else if (parent->value < child->value) {
        if (parent->right == NULL) malloc(sizeof(Node));
        parent->right = child;
    }

    child->parent = malloc(sizeof(Node));
    child->parent = parent;
}