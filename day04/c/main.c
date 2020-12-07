#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "fileReader.h"
#include "passport.h"


void solveSilver(Passport **passports, int elementCount) {
    printf("solving silver\n");
    int counter = 0;
    for (int i = 0; i < elementCount; i++) {
        if (isPassportSilver(passports[i])) counter++;
    }
    printf("there were %d valid passports \n", counter);
}

int main(int argc, char **argv) {
    printf("starting\n");
    FileData data = readFile(argv[1]);

    Passport **passports = malloc(data.elementCount * sizeof(Passport*));
    for (int i = 0; i < data.elementCount; i++) {
        passports[i] = newPassport(data.data[i]);
        //printPassport(passports[i]);
    }

    solveSilver(passports, data.elementCount);
}

// between 241-266