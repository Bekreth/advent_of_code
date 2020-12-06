#include <stdlib.h>
#include <stdio.h>

#include "../../utils/fileReader/fileReader.h"

int main(int argc, char **argv) {
    printf("starting\n");
    FileData data = readFile(argv[1]);

    for (int i = 0; i < data.size; i++) {
        printf("%s\n", data.data[i]);
    }
}