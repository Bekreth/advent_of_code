#include <stdlib.h>
#include <stdio.h>

#include "../../utils/fileReader/fileReader.h"

#include "expression.h"

int postProcessorBufferSize;

void solveSilver(Expressions* expressions) {
    printf("solving silver\n");
    unsigned long output = 0;
    unsigned long temp = 0;
    for (int i = 0; i < expressions->size; i++) {   
        temp = evaluate(expressions->expressions[i]);
        printf("%lu: %lu \n", i, temp);
        output += temp;
    }
    printf(" - %lu - \n", output);
}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData fileData = readFile(argv[1]);

    Expressions* expressions = newExpressions(fileData);
    solveSilver(expressions);
    // freeExpressions(expressions);
}
