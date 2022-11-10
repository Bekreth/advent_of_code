#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "password.c"

char ** readFile(char *fileLocation) { 
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) 
        exit(EXIT_FAILURE);
    char bufferLength = 64;
    char buffer[bufferLength];

    char **output = malloc(sizeof(char*)*1000);
    int index = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read-1] == '\n') {
            char *subString = malloc(read - 1);
            strncpy(subString, line, read - 1);
            output[index] = subString;
        } else {
            output[index] = line;
        }
        index++;
    }
    fclose(file);
    return output;
}

bool silverValidity(Password *password) {
    int counter = 0;
    for (int i = 0; i < strlen(password->password); i++) {
        if (password->password[i] == password->targetCharacter) counter++;
    }
    return counter >= password->minimum && counter <= password->maximum;

}

bool goldValidity(Password *password) {
    //printPassword(password);
    char minimumChar = password->password[password->minimum-1];
    bool hasMinimum = minimumChar == password->targetCharacter;
    //printf("min: %c\n", minimumChar);
    char maximumChar = password->password[password->maximum-1];
    bool hasMaximum = maximumChar == password->targetCharacter;
    //printf("max: %c\n", maximumChar);
    bool output = (hasMinimum && !hasMaximum) || (!hasMinimum && hasMaximum);
    //printf("comparison: %d\n", output);
    return output;
}

void solveSilver(Password **passwords, int iterations) {
    printf("*******\n");
    printf("solving silver\n");
    int successes = 0;
    for (int i = 0; i < iterations; i++) {
        if (silverValidity(passwords[i])) successes++;
    }
    printf("Valid passwords: %d\n", successes);
}

void solveGold(Password **passwords, int iterations) {
    printf("*******\n");
    printf("solving gold\n");
    int successes = 0;
    for (int i = 0; i < iterations; i++) {
        if (goldValidity(passwords[i])) successes++;
    }
    printf("Valid passwords: %d\n", successes);
}

int main(int argc, char **argv) {
    char **data = readFile(argv[1]);
    int iterations = atoi(argv[2]);
    Password **passwords = malloc(sizeof(Password*)*iterations);
    for (int i = 0; i < iterations; i++) {
        passwords[i] = newPassword(data[i]);
    }
    solveSilver(passwords, iterations);
    solveGold(passwords, iterations);
}