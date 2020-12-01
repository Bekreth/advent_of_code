#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.c"
#include "operator.c"

#define TARGET 2020


int * readFileByLine(char * fileLocation) {
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) 
        exit(EXIT_FAILURE);
    char bufferLength = 8;
    char buffer[bufferLength];

    int intermediate[256];
    int index = 0;
    while (fgets(buffer, bufferLength, file)) {
        intermediate[index] = atoi(buffer);
        index++;
    }
    fclose(file);


    int * output = malloc(sizeof(int)*index);
    for (int i = 0; i < index; i++) {
        output[i] = intermediate[i];
    }
    return output;
}

bool containsCompliment(Operator *operator, Node *node) {
    int value = node->value;
    int compliment = TARGET - value;
    if (contains(operator->tree, compliment)) {
        printf("compliments found! %d & %d; product is %d\n", value, compliment, compliment*value);
        return true;
    } else {
        return false;
    }
}

void solveSilver(Node *tree) {
    Operator *operator = newOperator(tree->right);
    operateOnTree(operator, tree->left, containsCompliment);
    printf("finished search\n");
}

int main() {
    int *data = readFileByLine("../input/silver.txt");
    printf("%d\n", data[0]);
    Node *tree = loadTree(data);
    printf("finished loading tree\n");
    solveSilver(tree);
}

