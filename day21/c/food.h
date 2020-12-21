#ifndef food_h
#define food_h

typedef struct Allergen {
    char* id;
} Allergen;

typedef struct Allergens {
    int size;
    Allergen** alergens;
} Allergens;

typedef struct Ingredient {
    char* id;
} Ingredient;

typedef struct Ingredients {
    int size;
    Ingredient** ingredient;
} Ingredients;


typedef struct IngredientList {
    Ingredients* ingredients;
    Allergens* allergens;
} IngredientList;


IngredientList* newIngredientList(char* input);
void freeIngredientList(IngredientList* input);


#endif