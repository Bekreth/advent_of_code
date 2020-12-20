#ifndef image_h 
#define image_h

#define SEGMENT_SIZE 10
#define IMAGE_SIZE 12

#include <stdbool.h>

typedef enum Rotation {
    NONE,
    QUARTER_RIGHT,
    HALF, 
    QUARTER_LEFT
} Rotation;

typedef enum Edge {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
} Edge;

typedef struct ImageSegment {
    int id;
    Rotation rotation;
    bool flipped;
    char data[SEGMENT_SIZE][SEGMENT_SIZE];
} ImageSegment;

ImageSegment* createImageSegment(char* input);
void freeImageSegment(ImageSegment* segment);
void printImageSegment(ImageSegment* segment);
char* imageEdge(ImageSegment* segment, Edge edge);

typedef struct Image {
    int segmentIDs[IMAGE_SIZE][IMAGE_SIZE];
    char compositeData[IMAGE_SIZE * SEGMENT_SIZE][IMAGE_SIZE * SEGMENT_SIZE];
} Image;

Image* createImage();
void freeImage(Image* image);
void writeSegementToOffset(Image* image, ImageSegment* segment, int x, int y);

#endif