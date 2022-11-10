#ifndef ticket_h
#define ticket_h

#include "../../utils/fileReader/fileReader.h"

typedef struct Ticket {
    int size;
    int* data;
} Ticket;

typedef struct Tickets {
    int size;
    Ticket** tickets;
} Tickets;

Ticket* newTicket(char* ticketData);
void freeTicket(Ticket* ticket);

Tickets* newTickets(FileData fileData, int offset);
void freeTickets(Tickets* tickets);

void printTicket(Ticket* ticket);

#endif
