#include <stdlib.h>
#include <string.h>

#include "expression.h"


Expressions* newExpressions(FileData fileData) {
    Expressions* output = malloc(sizeof(Expressions));
    output->expressions = malloc(fileData.size * sizeof(Expression));
    output->size = fileData.size;

    int* offset = malloc(sizeof(int));
    for (int i = 0; i < fileData.size; i++) {
        *offset = 0;
        output->expressions[i] = newExpression(fileData.data[i], offset);
    }
    free(offset);

    return output;
}

Expression* newExpression(char* input, int* offset) {
    Expression* output = malloc(sizeof(Expression));
    output->data = malloc(0);
    int size = 0;

    while (input[*offset] != '!') {
        switch (input[*offset]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            size++;
            output->data = realloc(output->data, size * sizeof(expressionData));
            output->data[size - 1].evaluatable.isNumber = true;
            output->data[size - 1].evaluatable.data.value = atoi(&(input[*offset]));
            break;
        
        case '+':
            size++;
            output->data = realloc(output->data, size * sizeof(expressionData));
            output->data[size - 1].operation = ADDITION;
            break;
        case '*':
            size++;
            output->data = realloc(output->data, size * sizeof(expressionData));
            output->data[size - 1].operation = MULTIPLICATION;
            break;

        case '(':
            size++;
            output->data = realloc(output->data, size * sizeof(expressionData));
            (*offset)++;
            output->data[size - 1].evaluatable.isNumber = false;
            output->data[size - 1].evaluatable.data.innerExpression = newExpression(input, offset);
            break;
        case ')':
            output->size = size;
            return output;

        case ' ':
            break;
        }
        (*offset)++;
    }

    output->size = size;
    return output;
}

unsigned long valueOf(Evaluatable input) {
    if (input.isNumber) return input.data.value;
    else return evaluate(input.data.innerExpression);
}

unsigned long eval(unsigned long collector, int offset, Expression* expression) {
    unsigned long value = valueOf(expression->data[offset + 1].evaluatable);
    switch (expression->data[offset].operation) {
    case ADDITION:
        collector += value;
        break;
    case MULTIPLICATION:
        collector *= value;
        break;
    }
    offset += 2;

    if (offset == expression->size) return collector;
    else eval(collector, offset, expression);
}

unsigned long evaluate(Expression* expression) {
    unsigned long startingCollector = valueOf(expression->data[0].evaluatable);
    return eval(startingCollector, 1, expression);
}

void freeExpressions(Expressions* input) {
    for (int i = 0; i < input->size; i++) {
        freeExpression(input->expressions[i]);
    }
    free(input->expressions);
    free(input);
}

void freeExpression(Expression* expression) {
    free(expression->data);
    free(expression);
}