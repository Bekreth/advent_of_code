#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rules.h"

Rule* newRule(char* input) {
    Rule* output = calloc(sizeof(Rule), 1);
    output->data.referenceRule = malloc(0);
    output->ruleCount = 1;
    output->

    int bufferIndex = 0;
    char* buffer = calloc(4* sizeof(char), 1);
    bool clearBuffer = false;
    bool startRuleCapture = false;
    bool running = true;

    for (int i = 0; running; i++) {
        switch (input[i]) {
        case '|':
            output->ruleCount++;
            output->size = realloc(output->size, output->ruleCount * sizeof(int));
            output->size[output->ruleCount - 1] = 0;
            output->data.referenceRule = realloc(output->data.referenceRule, 
                output->ruleCount * sizeof(int*));
            i++;
            break;
        case ':':
            i++;
            output->id = atoi(buffer);   
            break;

        case '!':
            running = false;
            /* FALLTHROUGH */
        case ' ':
            output->size[output->ruleCount]++;
            output->data.referenceRule[output->ruleCount] = realloc(output->data.referenceRule[output->ruleCount], 
                output->size[output->ruleCount]);
            output->data.referenceRule[output->ruleCount][output->size[output->ruleCount] - 1] = atoi(bufferIndex);
            break;

        case '"':
            output->reduced = true;
            if (startRuleCapture) {
                output->data.value = buffer[0];
                startRuleCapture = false;
                clearBuffer = true;
            } else {
                startRuleCapture = true;
            }
            break;

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
            if (output->ruleCount == 0) {
                output->ruleCount = 1;
                output->size = malloc(sizeof(int));
                output->size[0] = 0;
                output->data.referenceRule = malloc(sizeof(int*));
            }
        default:
            buffer[bufferIndex] = input[i];
            bufferIndex++;
            break;
        }

        if (clearBuffer) {
            buffer = memset(buffer, '0', 4);
            bufferIndex = 0;
        }
    }

    free(buffer);
    return output;
}

void freeRule(Rule* rule) {
    free(rule->data.referenceRule);
    free(rule);
}

void printRule(Rule* rule) {
    printf("= RULE =\n");
    printf("%d\n", rule->size);
    if (rule->size != 0) {
        for (int i = 0; i < rule->size; i++) {
            printf("r: %d\n", rule->data.referenceRule[i]);
        }
    } else {
        printf("d: %c\n", rule->data.value);
    }
}

unsigned int hash(void* data) {
    return ((Rule*)data)->id * 31;
}

bool equals(void* data1, void* data2) {
    return ((Rule*)data1)->id == ((Rule*)data2)->id;
}

