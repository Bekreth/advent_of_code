#include "fileReader.h"

FileData * readFile(char *fileLocation) {
    printf("reading file: %s\n", fileLocation);
    FILE *file = fopen(fileLocation, "r");
    if (file == NULL) exit(EXIT_FAILURE);

    FileData *output = malloc(sizeof(FileData));
    output->row = malloc(0);
    output->column = malloc(0);

    int lineBufferSize = 11; //This is the length of a line of this encoding
    char *lineBuffer = malloc(lineBufferSize * sizeof(char));
    int elementCounter = 0;

    while (fread(lineBuffer, 1, lineBufferSize, file) != 0) {
        elementCounter++;
        char row = 0;
        char column = 0;

        int rowBitOffSet = 6;
        int columnBitOffSet = 2;

        for (int i = 0; i < lineBufferSize - 1; i++) {
            char letter = lineBuffer[i];
            switch (letter) {
            case 'B':
                row = row | (1 << rowBitOffSet);
            case 'F':
                rowBitOffSet--;
                break;
            case 'R':
                column = column | (1 << columnBitOffSet);
            case 'L':
                columnBitOffSet--;
                break;
            default:
                printf("something has gone wrong! : %c\n", letter);
                break;
            }
        }
        output->row = realloc(output->row, elementCounter * sizeof(char));
        output->column = realloc(output->column, elementCounter * sizeof(char));

        output->row[elementCounter - 1] = row;
        output->column[elementCounter - 1] = column;
    }

    output->size = elementCounter;
    return output;
}

void showBits(int x) {
    int i=0;
    for (i = (sizeof(char) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf(" : %d\n", x);
}
