#include <stdlib.h>
#include <stdbool.h>

#include "binaryTree.h"

//bool isBalanced(Node* node) {
//    unsigned int size = treeSize(node);
//    for (int i = (sizeof(int) * 8) - 1; i >= 0; i--) {
//        if (size & (1ul << i) != 0) return (size / treeDepth(node)) == i + 1;
//    }
//}

Node* evenTree(Node* node) {
    Node* output = node;
    if (node->left == NULL && node->right->left == NULL) {
        output = node->right;

        node->parent = output;
        output->left = node;
        node->right = NULL;

        output->right = evenTree(output->right);
    } else if (node->right == NULL && node->left->right == NULL) {
        output = node->left;

        node->parent = output;
        output->right = node;
        node->left = NULL;

        output->left = evenTree(output->right);
    }
    return node;
}

Node* rebalanceAboutValue(Node* node, int pointOfInterest) {

}

Node* unbalanceTreeRight(Node* node) {
    
}

Node* unbalanceTreeLeft(Node* node) {
}
