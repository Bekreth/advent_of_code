#ifndef silver_solver_h
#define silver_solver_h

#include "image.h"

typedef enum ExaminationStatus {
    EMPTY,
    UNEXAMINED,
    EXAMINED
} ExaminationStatus;

typedef struct PlaceMat {
    int pieceCount;
    int width;
    ImageSegment*** segments;
    ExaminationStatus** status;
} PlaceMat;

PlaceMat* newPlaceMat(int size);
void freePlaceMat(PlaceMat* mat);
void solvePuzzel(PlaceMat* mat, ImageSegment** segment);

#endif 