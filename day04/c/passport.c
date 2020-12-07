#include "passport.h"

typedef struct Token {
    char *type;
    char *value;
} Token;

Token ** tokenizer(char *input) {
    int i = 0;
    Token **tokens = malloc(sizeof(Token*));
    int tokenIndex = 0;
    bool writingType = true;
    char* typeBuffer = calloc(3*sizeof(char), 1);
    int typeBufferIndex = 0;
    char* dataBuffer = calloc(10*sizeof(char), 1);
    int dataBufferIndex = 0;
    bool reading = true;
    while (reading) {
        char character = input[i];
        switch (character) {
        case ':':
            writingType = false;
            break;
        case ' ':
            writingType = true;
            Token *newToken = malloc(sizeof(Token));
            newToken->type = calloc(typeBufferIndex * sizeof(char), 1);
            newToken->value = calloc(dataBufferIndex * sizeof(char), 1);
            memcpy(newToken->type, typeBuffer, typeBufferIndex);
            memcpy(newToken->value, dataBuffer, dataBufferIndex);
            typeBufferIndex = 0;
            dataBufferIndex = 0;
            tokenIndex++;
            tokens = realloc(tokens, (tokenIndex + 1) * sizeof(Token*));
            tokens[tokenIndex-1] = newToken;
            break;
        case '!':
            reading = false;
            Token *endToken = malloc(sizeof(Token));
            endToken->type = calloc(3 * sizeof(char), 1);
            endToken->type = "end";
            tokenIndex++;
            tokens = realloc(tokens, (tokenIndex + 1) * sizeof(Token*));
            tokens[tokenIndex-1] = endToken;
            break;
        default:
            if (writingType) {
                typeBuffer[typeBufferIndex] = character;
                typeBufferIndex++;
            } else {
                dataBuffer[dataBufferIndex] = character;
                dataBufferIndex++;
            }
            break;
        }
        i++;
    }
    return tokens;
}

void printToken(Token *token) {
    printf("-- Token --\n");
    printf("type : %s\n", token->type);
    printf("value: %s\n\n", token->value);
}

Passport * newEmptyPassport() {
    Passport *output = malloc(sizeof(Passport));
    output->birthYear = calloc(sizeof(char*), 1);
    output->issueYear = calloc(sizeof(char*), 1);
    output->expirationYear = calloc(sizeof(char*), 1);
    output->height = calloc(sizeof(char*), 1);
    output->hairColor = calloc(sizeof(char*), 1);
    output->eyeColor = calloc(sizeof(char*), 1);
    output->passportID = calloc(sizeof(char*), 1);
    output->countryID = calloc(sizeof(char*), 1);
    return output;
}
Passport * newPassport(char *input) {
    Passport *output = newEmptyPassport();
    Token **tokens = tokenizer(input);
    int tokenIndex = 0;
    bool reading = true;
    while (reading) {
        Token *token = tokens[tokenIndex];
        // printToken(token);
        char *type = token->type;
        char *value = token->value;
        if (strcmp(type, "byr") == 0) output->birthYear = value;
        else if (strcmp(type, "iyr") == 0) output->issueYear = value;
        else if (strcmp(type, "eyr") == 0) output->expirationYear = value;
        else if (strcmp(type, "hgt") == 0) output->height = value;
        else if (strcmp(type, "hcl") == 0) output->hairColor = value;
        else if (strcmp(type, "ecl") == 0) output->eyeColor = value;
        else if (strcmp(type, "pid") == 0) output->passportID = value;
        else if (strcmp(type, "cid") == 0) output->countryID = value;
        else if (strcmp(type, "end") == 0) reading = false;
        else printf("something is wrong: %s\n", type);
        // printPassport(output);
        // free(token->type);
        free(token);
        tokenIndex++;
    }
    free(tokens);
    return output;
}

void printPassport(Passport *passport) {
    printf("== Passport == ");
    if (isPassportSilver(passport)) printf("vvvvvv\n");
    else printf("!! INVALID !!\n");
    printf("Birth Year\t: %s\n", passport->birthYear);
    printf("Issue Year\t: %s\n", passport->issueYear);
    printf("Expire Year\t: %s\n", passport->expirationYear);
    printf("Height\t\t: %s\n", passport->height);
    printf("Hair Color\t: %s\n", passport->hairColor);
    printf("Eye Color\t: %s\n", passport->eyeColor);
    printf("Passport ID\t: %s\n", passport->passportID);
    printf("Country ID\t: %s\n", passport->countryID);
    printf("\n");
}


bool isPassportSilver(Passport * passport) {
    if (strcmp(passport->birthYear, "") == 0) return false;
    if (strcmp(passport->issueYear, "") == 0) return false;
    if (strcmp(passport->expirationYear, "") == 0) return false;
    if (strcmp(passport->height, "") == 0) return false;
    if (strcmp(passport->hairColor, "") == 0) return false;
    if (strcmp(passport->eyeColor, "") == 0) return false;
    if (strcmp(passport->passportID, "") == 0) return false;
    return true;
}

bool isPassportGold(Passport * passport) {
    int birthYear = atoi(*passport->birthYear);
    if (birthYear < 1920 || birthYear > 2002) return false;
    int issueYear = atoi(*passport->issueYear);
    if (issueYear < 2010 || issueYear > 2020) return false;
    int expirationYear = atoi(*passport->expirationYear);
    if (expirationYear < 2020 || expirationYear > 2030) return false;
    
}

bool validHeight(char* height) {

}

bool validHairColor(char* hairColor) {

}

bool validEyeColor(char* eyeColor) {
    if (strcmp(eyeColor, "amb")) return true;
    if (strcmp(eyeColor, "blu")) return true;
    if (strcmp(eyeColor, "brn")) return true;
    if (strcmp(eyeColor, "gry")) return true;
    if (strcmp(eyeColor, "grn")) return true;
    if (strcmp(eyeColor, "hzl")) return true;
    if (strcmp(eyeColor, "oth")) return true;
    return false;
}
bool validHeight(char* height) {

}
bool validHeight(char* height) {

}