#include "bagTree.h"

void addParentToChilder(BagNode* child, BagNode* parent) {
    for (int i = 0; i < child->numberOfParents; i++) {
        if (matchingIDs(child->parentBags[i], parent)) return;
    }
    child->numberOfParents++;
    child->parentBags = realloc(child->parentBags, child->numberOfParents * sizeof(BagNode));
    child->parentBags[child->numberOfParents - 1] = parent;
}

bool addBagToTree(BagNode* parent, BagNode* bagToAdd) {
    BagNode *node;
    bool output = false;
    for (int i = 0; i < parent->numberOfChildren; i++) {
        node = parent->childBags[i];
        if (matchingIDs(node, bagToAdd)) {
            parent->childBags[i] = bagToAdd;
            addParentToChilder(bagToAdd, parent);
            output = true;
        }
        if (addBagToTree(node, bagToAdd)) output = true;
    }
    return output;
}

bool matchingDescriptors(BagNode* bag1, BagNode* bag2) {
    return strcmp(bag1->descriptor, bag2->descriptor) == 0;
}

bool matchingColors(BagNode* bag1, BagNode* bag2) {
    return strcmp(bag1->color, bag2->color) == 0;
}

bool matchingIDs(BagNode* bag1, BagNode* bag2) {
    return matchingDescriptors(bag1, bag2) && matchingColors(bag1, bag2);
}

typedef enum ParseStage{
    DESCRIPTOR,
    COLOR,
    CHILD_COUNT,
    CHILD_DESCRIPTOR,
    CHILD_COLOR
} ParseStage;

ParseStage incrementParseStage(ParseStage stage) {
    if (stage == DESCRIPTOR) return COLOR;
    if (stage == COLOR) return CHILD_COUNT;
    if (stage == CHILD_COUNT) return CHILD_DESCRIPTOR;
    if (stage == CHILD_DESCRIPTOR) return CHILD_COLOR;
    if (stage == CHILD_COLOR) return CHILD_COUNT;
}

void applyStage(BagNode *bag, ParseStage stage, char* data) {
    BagNode *newChild;
    switch (stage) {
    case DESCRIPTOR:
        bag->descriptor = data;
        break;
    
    case COLOR:
        bag->color = data;
        break;

    case CHILD_COUNT:
        bag->numberOfChildren++;
        bag->childCount = realloc(bag->childCount, bag->numberOfChildren * sizeof(int));
        // printf("%d\n", atoi(data));
        bag->childCount[bag->numberOfChildren - 1] = atoi(data);
        break;
    
    case CHILD_DESCRIPTOR:
        newChild = malloc(sizeof(BagNode));
        newChild->parentBags = malloc(0);
        newChild->numberOfParents = 0;
        newChild->childBags = malloc(0);
        newChild->childCount = malloc(0);
        newChild->numberOfChildren = 0;

        applyStage(newChild, DESCRIPTOR, data);
        bag->childBags = realloc(bag->childBags, bag->numberOfChildren * sizeof(BagNode));
        bag->childBags[bag->numberOfChildren - 1] = newChild;
        break;

    case CHILD_COLOR:
        applyStage(bag->childBags[bag->numberOfChildren - 1], COLOR, data);
        break;
    
    default:
        break;
    }
}

typedef enum TokenAction {
    SKIP,
    APPLY,
    TERMINATE
} TokenAction;

TokenAction tokenAction(char* token) {
    if (strstr(token, "bag") != NULL || strcmp(token, "contain") == 0) return SKIP;
    if (strcmp(token, "no") == 0) return TERMINATE;
    return APPLY;
}

BagNode * newBag(char* data) {
    BagNode* output = malloc(sizeof(BagNode));
    output->parentBags = malloc(0);
    output->numberOfParents = 0;
    output->childBags = malloc(0);
    output->childCount = malloc(0);
    output->numberOfChildren = 0;

    char* token;
    ParseStage stage = DESCRIPTOR;
    char buffer[20];
    int bufferIndex = 0;
    for(int i = 0; ; i++) {
        switch (data[i]) {
        case ' ':
            token = calloc(bufferIndex * sizeof(char), 1);
            memcpy(token, buffer, bufferIndex);
            bufferIndex = 0;
            switch (tokenAction(token)) {
            case SKIP:
                free(token);
                break;

            case APPLY:
                applyStage(output, stage, token);
                stage = incrementParseStage(stage);
                break;

            case TERMINATE:
                free(token);
                return output;
                break;
            }
            break;

        case '!':
            return output;
            break;
        
        default:
            buffer[bufferIndex] = data[i];
            bufferIndex++;
            break;
        }
    }
}

BagNode * findBag(BagNode* bag, BagNode* searchFor) {
    BagNode* output = NULL;
    if (matchingIDs(bag, searchFor)) return bag;
    for (int i = 0; i < bag->numberOfChildren; i++) {
        output = findBag(bag->childBags[i], searchFor);
        if (output != NULL) return output;
    }
    return output;
}

void printBagID(BagNode* bag) {
    printf("Descriptor:\t%s\n", bag->descriptor);
    printf("Color:\t\t%s\n", bag->color);
}

void printBag(BagNode* bag) {
    printf("== BAG ==\n");
    printBagID(bag);
    printf("# of parents:\t%d\n", bag->numberOfParents);
    printf(" -Parents-\n");
    for (int i = 0; i < bag->numberOfParents; i++) {
        printf(" -P%d\n", i);
        printBagID(bag->parentBags[i]);
    }
    printf("# of children:\t%d\n", bag->numberOfChildren);
    printf(" -Children-\n");
    for (int i = 0; i < bag->numberOfChildren; i++) {
        printf(" -C%d\n", i);
        printBagID(bag->childBags[i]);
        printf("Count\t\t%d\n", bag->childCount[i]);
    }
}

