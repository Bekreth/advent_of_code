#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"

#include "image.h"
#include "placeMat.h"

int postProcessorBufferSize;

Image* solveSilver(ImageSegment** segments, int size) {
    printf("solving silver\n");

    Image* output = createImage();
    PlaceMat* mat = newPlaceMat(size);
    mat->pieceCount = size;

    int centerX = mat->width / 2;
    int centerY = mat->width / 2;

    mat->segments[centerX][centerY] = segments[0];
    mat->status[centerX][centerY] = UNEXAMINED;

    solvePuzzel(mat, segments);



    return output;
}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData imageData = readFile(argv[1]);

    ImageSegment** segments = malloc(imageData.size * sizeof(ImageSegment*));
    for (int i = 0; i < imageData.size; i++) {
        segments[i] = createImageSegment(imageData.data[i]);
    }

    Image* assembledImage = solveSilver(segments, imageData.size);
}
