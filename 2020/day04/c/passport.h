#ifndef passport_h
#define passport_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Passport {
    char* birthYear;
    char* issueYear;
    char* expirationYear;
    char* height;
    char* hairColor;
    char* eyeColor;
    char* passportID;
    char* countryID;
} Passport;

Passport * newPassport(char *input);

bool isPassportSilver(Passport * passport);

void printPassport(Passport *passport);

#endif