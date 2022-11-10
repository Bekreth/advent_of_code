#ifndef expression_h
#define expression_h

#include <stdbool.h>

#include "../../utils/fileReader/fileReader.h"

typedef enum Operator {
    ADDITION,
    MULTIPLICATION
} Operator;

typedef struct Evaluatable {
    bool isNumber;
    union data {
        unsigned long value;
        struct Expression* innerExpression;
    } data;
} Evaluatable;

typedef union expressionData {
    Evaluatable evaluatable;
    Operator operation;
} expressionData;

typedef struct Expression {
    int size;
    expressionData* data;
} Expression;

typedef struct Expressions {
    int size;
    Expression** expressions;
} Expressions;

Expressions* newExpressions(FileData fileData);
Expression* newExpression(char* input, int *offset);

unsigned long evaluate(Expression* expression);

void freeExpression(Expression* input);
void freeExpressions(Expressions* input);

#endif