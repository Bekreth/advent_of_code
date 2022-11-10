#ifndef bag_tree_h
#define bag_tree_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct BagNode {
    char *descriptor;
    char *color;

    int numberOfChildren;
    struct BagNode **childBags;
    int *childCount;

    int numberOfParents;
    struct BagNode **parentBags;
} BagNode;

bool addBagToTree(BagNode* parent, BagNode* bagToAdd);

bool matchingDescriptors(BagNode* bag1, BagNode* bag2);
bool matchingColors(BagNode* bag1, BagNode* bag2);
bool matchingIDs(BagNode* bag1, BagNode* bag2);

BagNode * newBag(char* data);
BagNode * findBag(BagNode* bag, BagNode* searchingFor);

void printBagID(BagNode* bag);
void printBag(BagNode* bag);


#endif