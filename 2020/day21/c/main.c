#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"

#include "food.h"

int postProcessorBufferSize;

void solveSilver(IngredientList** lists, int size) {

}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData fileData = readFile(argv[1]);

    IngredientList** ingredientLists = malloc(fileData.size * sizeof(IngredientList*));
    for (int i = 0; i < fileData.size; i++) {
        ingredientLists[i] = newIngredientList(fileData.data[i]);
    }

    solveSilver(ingredientLists, fileData.size);

}
