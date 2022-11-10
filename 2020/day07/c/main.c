#include <stdlib.h>
#include <stdio.h>

#include "../../utils/fileReader/fileReader.h"
#include "bagTree.h"

int postProcessorBufferSize = 32;



typedef struct Tree {
    BagNode **bags;
    int width;
} Tree;

Tree buildBagTree(Tree tree) {
    printf("tree is growing!%d \n", tree.width);
    BagNode** newTree = calloc(tree.width * sizeof(BagNode), 1);
    int newTreeIndex = 1;
    bool addedToExistingTree = false;
    newTree[0] = tree.bags[0];
    for (int i = 1; i < tree.width; i++) {
        addedToExistingTree = false;
        for (int j = 0; j < newTreeIndex; j++) {
            if (addBagToTree(newTree[j], tree.bags[i])) {
                addedToExistingTree = true;
            }
        }
        if (!addedToExistingTree) {
            newTree[newTreeIndex] = tree.bags[i];
            newTreeIndex++;
        }
    }
    free(tree.bags);
    newTree = realloc(newTree, newTreeIndex * sizeof(BagNode));
    Tree output = {newTree, newTreeIndex};
    if (output.width < tree.width) return buildBagTree(output);
    else return output;
}

typedef struct Collector {
    BagNode** seen;
    int count;
} Collector;

Collector countParents(Collector collector, BagNode* bag) {
    for (int i = 0; i < bag->numberOfParents; i++) {
        collector = countParents(collector, bag->parentBags[i]);
    }
    for (int i = 0; i < collector.count; i++) {
        if (matchingIDs(collector.seen[i], bag)) return collector;
    }
    collector.count++;
    collector.seen = realloc(collector.seen, (collector.count + 1) * sizeof(BagNode*));
    collector.seen[collector.count] = bag;
    return collector;
}

void solveSilver(Tree tree, BagNode* goldBag) {
    printf("solving silver\n");
    // printBag(goldBag);
    int* output = malloc(sizeof(int));
    BagNode** seen = malloc(sizeof(BagNode*));
    seen[0] = goldBag;
    Collector collector = {seen, 0};
    collector = countParents(collector, goldBag);
    printf("number of parents: %d\n", collector.count);
}


int main(int argc, char **argv) {
    printf("starting\n");
    FileData fileData = readFile(argv[1]);
    printf("finished reading\n\n");

    BagNode** bags = malloc(fileData.size * sizeof(BagNode*));
    for (int i = 0; i < fileData.size; i++) {
        bags[i] = newBag(fileData.data[i]);
    }
    printf("build all bags\n");
    Tree tree = { bags, fileData.size };
    tree = buildBagTree(tree);
    printf("built tree\n");

    BagNode* searchFor = malloc(sizeof(BagNode));
    searchFor->descriptor="shiny";
    searchFor->color="gold";

    printBag(findBag(tree.bags[1], searchFor));

    solveSilver(tree, findBag(tree.bags[1], searchFor));
}

//31 is wrong