
typedef struct Operator {
    Node *tree;
} Operator;

Operator * newOperator(Node *tree) {
    Operator * output = malloc(sizeof(Operator));
    output->tree = tree;
    return output;
}

bool operateOnTree(Operator *op, Node *tree, bool(*operator)(Operator *, Node *)) {
    //printNode(tree);
    if (operator(op, tree)) {
        return true;
    } else if (tree->left && operateOnTree(op, tree->left, operator)) {
        return true;
    } else if (!tree->left) {
        return false;
    } else if (tree->right && operateOnTree(op, tree->right, operator)) {
        return true;
    } else {
        return false;
    }
}