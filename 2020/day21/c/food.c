#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "food.h"


IngredientList* newIngredientList(char* input) {
    IngredientList* output = malloc(sizeof(IngredientList));

    Ingredients* ingredients = newIngredients();
    Allergens* allergens = newAllergens();
    
    output->ingredients = ingredients;
    output->allergens = allergens;

    char buffer[10] = {0};
    int bufferIndex = 0;
    bool readingIngredients = true;
    for (int i = 0; input[i] != '!'; i++) {

        switch (input[i]) {
        case '(':
            i += 9;
            break;
        
        case ')':
        case ',':
            break;

        case '!':
        case ' ':
            if (readingIngredients) {
                addIngredient(ingredients, newIngredient(buffer, bufferIndex));
            } else {
                addAllregen(allergens, newAllergen(buffer, bufferIndex));
            }
            bufferIndex = 0;
            break;
        
        default:
            buffer[bufferIndex] = input[i];
            bufferIndex++;
            break;
        }
    }

    return output;
}



Ingredients* newIngredients() {
    Ingredients* output = malloc(sizeof(Ingredients));
    output->ingredient = malloc(0);
    output->size = 0;
    return output;
}

void addIngredient(Ingredients* ingredients, Ingredient* ingredient) {
    ingredients->size++;
    ingredients->ingredient = realloc(ingredients->ingredient, ingredients->size * sizeof(Ingredient*));
    ingredients->ingredient[ingredients->size - 1] = ingredient;
}

void freeIngredients(Ingredients* ingredients) {
    for (int i = 0; i < ingredients->size; i++) {
        freeIngredient(ingredients->ingredient[i]);
    }
    free(ingredients->ingredient);
    free(ingredients);
}

Ingredient* newIngredient(char* input, int size) {
    Ingredient* output = malloc(sizeof(Ingredient));
    output->id = malloc(size * sizeof(char));
    memcpy(output->id, input, size);
    return output;
}

void freeIngredient(Ingredient* ingredient) {
    free(ingredient->id);
    free(ingredient);
}

Allergens* newAllergens() { 
    Allergens* output = malloc(sizeof(Allergens));
    output->alergens = malloc(0);
    output->size = 0;
    return output;
}

void addAllregen(Allergens* allergens, Allergen* allergen) {
    allergens->size++;
    allergens->alergens = realloc(allergens->alergens, allergens->size * sizeof(Allergen*));
    allergens->alergens[allergens->size - 1];
}

void freeAllergens(Allergens* allergens) {
    for (int i = 0; i < allergens->size; i++) {
        freeAllergen(allergens->alergens[i]);
    }
    free(allergens->alergens);
    free(allergens);
}

Allergen* newAllergen(char* input, int size) {
    Allergen* output = malloc(sizeof(Allergen));
    output->id = malloc(size * sizeof(char));
    memcpy(output->id, input, size);
    return output;
}
