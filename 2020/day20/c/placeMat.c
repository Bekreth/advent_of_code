#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "placeMat.h"

typedef struct Coordinates {
    int x;
    int y;
} Coordinates;

typedef struct Vacancies {
    int size;
    char* keys;
    Edge* edges;
    ExaminationStatus** status;
    ImageSegment** matSlot;
} Vacancies;

Coordinates* nextFocus(PlaceMat* mat);
void findAdjacent(PlaceMat* mat, Coordinates* coordinates, ImageSegment** segments);
char createKey(char input[SEGMENT_SIZE]);
bool matchSegment(Vacancies* vacancies, ImageSegment* segment);

void solvePuzzel(PlaceMat* mat, ImageSegment** segments) {
    Coordinates* target = nextFocus(mat);
    while (target != NULL) {
        findAdjacent(mat, target, segments);
        free(target);
        target = nextFocus(mat);
    }
}


Coordinates* nextFocus(PlaceMat *mat) {
    Coordinates* output = NULL;
    for (int i = 0; i < mat->width; i++) {
        for (int j = 0; j < mat->width; j++) {
            if (mat->segments[i][j] == UNEXAMINED) {
                output = malloc(sizeof(Coordinates));
                output->x = i;
                output->y = j;
                return output;
            }
        }
    }
    return output;
}

void findAdjacent(PlaceMat* mat, Coordinates* coordinates, ImageSegment** segments) {
    Vacancies* vacancies = getExistingAdjacent(mat, coordinates);
    ImageSegment* focus = mat->segments[coordinates->x][coordinates->y];
    for (int i = 0; i < mat->pieceCount; i++) {
        if (matchSegment(vacancies, segments[i]) && vacancies->size == 0) break;
    }
    mat->status[coordinates->x][coordinates->y] = EXAMINED;
}

Vacancies* getExistingAdjacent(PlaceMat* mat, Coordinates* coordinates) {
    Vacancies* output = malloc(sizeof(Vacancies));
    output->size = 0;
    output->keys = malloc(4 * sizeof(char));
    output->edges = malloc(4 * sizeof(Edge));

    int x = coordinates->x;
    int y = coordinates->y;

    if (mat->segments[x + 1][y] == NULL) {
        output->keys[output->size] = createKey(imageEdge(mat->segments[x][y], RIGHT));
        output->edges[output->size] = RIGHT;
        output->matSlot[output->size] = mat->segments[x + 1][y];
        output->size++;
    } else if (mat->segments[x - 1][y] == NULL) {
        output->keys[output->size] = createKey(imageEdge(mat->segments[x][y], LEFT));
        output->edges[output->size] = LEFT;
        output->matSlot[output->size] = mat->segments[x - 1][y];
        output->size++;
    } else if (mat->segments[x][y + 1] == NULL) {
        output->keys[output->size] = createKey(imageEdge(mat->segments[x][y], BOTTOM));
        output->edges[output->size] = BOTTOM;
        output->matSlot[output->size] = mat->segments[x][y + 1];
        output->size++;
    } else if (mat->segments[x][y - 1] == NULL) {
        output->keys[output->size] = createKey(imageEdge(mat->segments[x][y], TOP));
        output->edges[output->size] = TOP;
        output->matSlot[output->size] = mat->segments[x][y - 1];
        output->size++;
    }

    return output;
}

char createKey(char input[SEGMENT_SIZE]) {
    char output = 0;
    for (int i = 0; i < SEGMENT_SIZE; i++) {
        output = 1 << (SEGMENT_SIZE - 1) - i;
    }
    free(input);
    return output;
}

bool matchSegment(Vacancies* vacancies, ImageSegment* segment) {
    char edges[4] = {
        createKey(imageEdge(segment, TOP)),
        createKey(imageEdge(segment, RIGHT)),
        createKey(imageEdge(segment, BOTTOM)),
        createKey(imageEdge(segment, LEFT))
    };

    for (int i = 0; i < vacancies->size; i++) {
        for (int j = 0; j < 4; j++) {
            if (vacancies->keys[i] == edges[j]) {
                fillVacancy(vacancies, segment, i, j);
                return true;
            }
        }
    }
    
    segment->flipped = true;
    char flippedEdges[4] = {
        createKey(imageEdge(segment, TOP)),
        createKey(imageEdge(segment, RIGHT)),
        createKey(imageEdge(segment, BOTTOM)),
        createKey(imageEdge(segment, LEFT))
    };
    for (int i = 0; i < vacancies->size; i++) {
        for (int j = 0; j < 4; j++) {
            if (vacancies->keys[i] == flippedEdges[j]) {
                fillVacancy(vacancies, segment, i, j);
                return true;
            }
        }
    }
    segment->flipped = false;

    return false;
}

void fillVacancy(Vacancies* vacancies, ImageSegment* segment, 
    int index, Edge edge) {

    segment->rotation = (Rotation)(4-((vacancies->edges[index] + edge) % 4));
    vacancies->matSlot[index] = segment;
    vacancies->status[index] = UNEXAMINED;
    int newSize = vacancies->size - 1;

    ImageSegment** updatedSegments = malloc(newSize  * sizeof(ImageSegment*));
    Edge* updatedEdges = malloc(newSize * sizeof(Edge));
    char* updatedKeys = malloc(newSize * sizeof(char));
    ExaminationStatus** updatedStatus = malloc(newSize * sizeof(ExaminationStatus*));

    bool cutPoint = false;
    int newIndex = 0;
    for (int i = 0; i < vacancies->size; i++) {
        if (i == index) {
            cutPoint = true;
            continue;
        }
        if (cutPoint) newIndex = i + 1;
        else newIndex = i;

        updatedSegments[newIndex] = vacancies->matSlot[i];
        updatedEdges[newIndex] = vacancies->edges[i];
        updatedKeys[newIndex] = vacancies->keys[i];
        updatedStatus[newIndex] = vacancies->status[i];
    }

    free(vacancies->matSlot);
    free(vacancies->edges);
    free(vacancies->keys);
    free(vacancies->status);

    vacancies->matSlot = updatedSegments;
    vacancies->edges = updatedEdges;
    vacancies->keys = updatedKeys;
    vacancies->status = updatedStatus;
    vacancies->size--;
}

PlaceMat* newPlaceMat(int size) {
    PlaceMat* output = malloc(sizeof(PlaceMat));
    output->width = 2 * (size - 1) + size;
    output->segments = malloc(output->width * sizeof(ImageSegment**));
    output->status = malloc(output->width * sizeof(ExaminationStatus*));
    for (int i = 0; i < output->width; i++) {
        output->segments[i] = calloc(output->width, sizeof(ImageSegment*));
        output->status[i] = calloc(output->width, sizeof(ExaminationStatus));
    }
    return output;
}

void freePlaceMat(PlaceMat* mat) {
    for (int i = 0; i < mat->width; i++) {
        free(mat->segments[i]);
        free(mat->status[i]);
    }
    free(mat->segments);
    free(mat->status);
    free(mat);
}