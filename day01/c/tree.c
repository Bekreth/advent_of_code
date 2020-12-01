#define MIDPOINT 1010

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node * newNode(int value) {
    Node * output = malloc(sizeof(Node));
    output->value = value;
    return output;
}

void printNode(Node *node) {
    printf("---\n");
    printf("value: %d\n", node->value);
    if (node->left) {
        printf("value left: %d\n", node->left->value);
    } else {
        printf("value left: null\n");
    }

    if (node->right) {
        printf("value right: %d\n", node->right->value);
    } else {
        printf("value right: null\n");
    }
    printf("---\n");
}

void addNode(Node *tree, int input) {
    //printf("value: %d, tree value: %d\n", input, tree->value);
    if (input > tree->value) {
        //printf("going right\n");
        if (!tree->right) {
            tree->right = newNode(input);
            //printNode(tree);
            //printf("\n\n");
        } else {
            addNode(tree->right, input);
        }
    } else if(input < tree->value) {
        //printf("going left\n");
        if (!tree->left) {
            tree->left = newNode(input);
            //printNode(tree);
            // printf("\n\n");
        } else {
            addNode(tree->left, input);
        }
    }
}


Node * loadTree(int *input) {
    Node * output = newNode(MIDPOINT);
    //printNode(output);

    for (int i = 0; i < 200; i++) {
        int valueAtIndex = input[i];
        //printf("index %d, value: %d\n", i, valueAtIndex);
        if (valueAtIndex == 0) break;
        addNode(output, valueAtIndex);
    }
    return output;
}


bool contains(Node *tree, int value) {
    if (!tree) {
        return false;
    } else if (value == tree->value) {
        return true;
    } else if (value < tree->value) {
        return contains(tree->left, value);
    } else {
        return contains(tree->right, value);
    }
}