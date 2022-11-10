#include <stdlib.h>
#include <string.h>

#include "message.h"


Message* newMessage(char* data) {
    Message* output = malloc(sizeof(Message));
    output->data = malloc(0);

    int index = 0;
    while (data[index] != '!') {
        index++;
    }
    output->data = memcpy(output->data, data, index);
    output->size = index + 1;
    return output;
}

void freeMessage(Message* message) {
    free(message->data);
    free(message);
}
