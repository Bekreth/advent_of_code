#include <stdlib.h>
#include <stdbool.h>

#include "image.h"

int readTileID(char* input);
char readTransformedData(ImageSegment* segment, int x, int y);

ImageSegment* createImageSegment(char* input) {
    ImageSegment* output = malloc(sizeof(ImageSegment));
    output->id = readTileID(input);

    int rowCounter = 0;
    int columnIndex = 0;
    for (int i = 11; rowCounter < SEGMENT_SIZE; i++) {
        switch (input[i]) {
        case '\n':
            columnIndex = 0;
            rowCounter++;
            break;
        default:
            output->data[rowCounter][columnIndex] = input[i];
            columnIndex++;
            break;
        }
    }
    return output;
}

int readTileID(char* input) {
    char intBuffer[4] = {0};
    int index = 0;
    for (int i = 0; input[i] != '!'; i++) {
        switch (input[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            intBuffer[index] = input[i];
            index++;
            break;
        }
    }
    return atoi(intBuffer);
}

void printImageSegment(ImageSegment* segment) {
    printf("= SEGMENT = \n");
    printf("ID: %d\n", segment->id);
    for (int i = 0; i < SEGMENT_SIZE; i++) {
        printf("%s\n", segment->data[i]);
    }
}

void freeImageSegment(ImageSegment* segment) {
    for (int i = 0; i < SEGMENT_SIZE; i++) {
        free(segment->data[i]);
    }
    free(segment->data);
    free(segment);
}

char* imageEdge(ImageSegment* segment, Edge edge) {
    char* output = calloc(SEGMENT_SIZE, sizeof(char));
    for (int i = 0; i < SEGMENT_SIZE; i++) {
        switch (edge) {
        case RIGHT:
            output[i] = readTransformedData(segment, SEGMENT_SIZE - 1, i);
            break;
        case LEFT:
            output[i] = readTransformedData(segment, 0, i);
            break;
        case TOP:
            output[i] = readTransformedData(segment, i, SEGMENT_SIZE - 1);
            break;
        case BOTTOM:
            output[i] = readTransformedData(segment, i, 0);
            break;
        }
    }
    return output;
}

Image* createImage() {
    return malloc(sizeof(Image));
}

void freeImage(Image* image) {
    for (int i = 0; i < 12; i++) {
        free(image->segmentIDs[i]);
    }
    free(image->segmentIDs);
    for (int i = 0; i < 120; i++) {
        free(image->compositeData[i]);
    }
    free(image->compositeData);
    free(image);
}

void writeSegementToOffset(Image* image, ImageSegment* segment, int x, int y) {
    image->segmentIDs[x][y] = segment->id;
    for (int i = x; i < SEGMENT_SIZE; i++) {
        for (int j = y; j < SEGMENT_SIZE; j++) {
            image->segmentIDs[i][j] = readTransformedData(segment, i, j);
        }
    }
}

char readTransformedData(ImageSegment* segment, int x, int y) {
    int xPrime = x;
    int yPrime = y;
    int holding = 0;

    switch (segment->rotation) {
    case NONE:
        break;
    case QUARTER_RIGHT:
        holding = xPrime;
        xPrime = yPrime * -1;
        yPrime = holding;
    case HALF:
        xPrime *= -1;
        yPrime *= -1;
    case QUARTER_LEFT:
        holding = xPrime;
        xPrime = yPrime;
        yPrime = -1 * holding;
        break;
    }

    if (segment->flipped) {
        holding = xPrime;
        xPrime = yPrime;
        yPrime = xPrime;
    }

    return segment->data[xPrime][yPrime];
}

