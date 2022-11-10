#ifndef message_h
#define message_h

typedef struct Message {
    int size;
    char* data;
} Message;

Message* newMessage(char* data);
void freeMessage(Message* message);

#endif