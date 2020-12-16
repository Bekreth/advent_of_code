#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ticket.h"

Ticket* newTicket(char* ticketData) {
    char intBuffer[4] = {0};
    int bufferIndex = 0;
    Ticket* output = malloc(sizeof(Ticket));
    output->data = malloc(0);
    output->size = 0;

    bool running = true;
    int index = 0;
    while(running) {
        switch (ticketData[index]) {
        case '!':
            running = false;
        case ',':
            output->size++;
            output->data = realloc(output->data, (output->size) * sizeof(int));
            output->data[output->size - 1] = atoi(intBuffer);
            bufferIndex = 0;
            memset(intBuffer, 0, 4);
            break;
        
        default:
            intBuffer[bufferIndex] = ticketData[index];
            bufferIndex++;
            break;
        }
        index++;
    }

    return output;
}

void freeTicket(Ticket* ticket) {
    free(ticket->data);
    free(ticket);
}


Tickets* newTickets(FileData fileData, int offset) {
    Tickets* output = malloc(sizeof(Tickets));
    output->tickets = malloc((fileData.size - offset) * sizeof(Ticket*));
    output->size = 0;
    Ticket* tick;
    for (int i = offset; i < fileData.size; i++) {
        output->tickets[i - offset] = newTicket(fileData.data[i]);
        output->size++;
    }
    return output;
}

void freeTickets(Tickets* tickets) {
    for (int i = 0; i < tickets->size; i++) {
        freeTicket(tickets->tickets[i]);
    }
    free(tickets->tickets);
    free(tickets);
}

void printTicket(Ticket* ticket) {
    printf(": TICKET :\n");
    for (int i = 0; i < ticket->size; i++) {
        printf(": %d\n", ticket->data[i]);
    }
}