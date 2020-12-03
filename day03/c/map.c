#include "map.h"

Map newMap(FileData fileData) {
    int widthCounter = 0;
    int currentWidth = 0;
    int heightCounter = 0;
    bool isCountingWidth = true;

    bool *registerBuffer = malloc(32*sizeof(bool));
    bool **map;

    for (int i = 0; i < fileData.size; i++) {
        //printf("%d\n", i);
        char element = fileData.data[i];
        switch (element)
        {
        case '.':
            registerBuffer[currentWidth] = false;
            break;
        
        case '#':
            registerBuffer[currentWidth] = true;
            break;
        
        case '\n':
            if (isCountingWidth) {
                isCountingWidth = false;
                map = malloc(sizeof(bool*));
                map[heightCounter] = malloc((currentWidth)*sizeof(bool));
                memcpy(map[heightCounter], registerBuffer, widthCounter);
                registerBuffer = realloc(registerBuffer, (currentWidth));
            } else {
                map = realloc(map, (heightCounter+1)*sizeof(bool*));
                map[heightCounter] = malloc(widthCounter*sizeof(bool));
                memcpy(map[heightCounter], registerBuffer, widthCounter);
            }
            currentWidth=0;
            heightCounter++;
            continue;
            break;
        
        default:
            printf("something very bad has happened! %c\n", element);
            break;
        }

        if (isCountingWidth) {
            widthCounter++;
        }
        currentWidth++;
    }
    Map output = {
        map,
        widthCounter,
        heightCounter + 1
    };
    return output;
}

//void printMap(Map map) {
//    for (int i = 0; i < map.height; i++) {
//        for (int j = 0; j < map.width; j++) {
//            bool val = map.isTree[i][j];
//            if (val) printf('%c', '#');
//            else printf('%c', '.');
//        }
//        printf('%c', '\n');
//    }
//}

