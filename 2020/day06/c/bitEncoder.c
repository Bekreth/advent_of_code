#include <stdlib.h>
#include <stdio.h>

#include "bitEncoder.h"

void showBits(int x) {
    for (int i = (sizeof(int) * 8) - 1 ; i >= 0; i--) {
       putchar(x & (1 << i) ? '1' : '0');
    }
    printf("\n\n");
}

int compactAndData(char *data) {
    //printf("%s\n\n", data);
    int output = -1;
    char character;
    int incrementor = 0;
    int index = 0;

    char *buffer = malloc(128 * sizeof(char));
    for (int i = 0; 1; i++) {
        character = data[i];
        switch (character) {
        case '\n':
            buffer[index] = '!';
            index = 0;
            incrementor = compactOrData(buffer);
            if (output == -1) output = incrementor;
            else output &= incrementor;
            break;
        case '!':
            // showBits(output);
            buffer[index] = '!';
            incrementor = compactOrData(buffer);
            if (output == -1) output = incrementor;
            else output &= incrementor;
            free(buffer);
            // showBits(output);
            return output;
            break;
        
        default:
            buffer[index] = character;
            index++;
            break;
        }
    }
}

int compactOrData(char *data) {
    // printf("%s\n", data);
    int output = 0;
    char character;
    int incrementor = 0;
    for (int i = 0; 1; i++) {
        character = data[i];
        switch (character) {
        case '\n':
            break;
        case '!':
            // showBits(output);
            return output;
            break;
        
        default:
            incrementor = character - 'a';
            output |= (1 << incrementor);
            break;
        }
    }
}

