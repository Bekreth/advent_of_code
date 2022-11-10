#include<stdlib.h>
#include<stdio.h>

#include "../../utils/fileReader/fileReader.h"

#include "validator.h"
#include "ticket.h"

int postProcessorBufferSize;

void solveSilver(Validator* validator, Tickets* tickets) {
    printf("solving silver\n");
    int output = 0;
    ValidationReport* report;
    for (int i = 0; i < tickets->size; i++) {
        printf(":%d:\n", i);
        report = validateData(validator, tickets->tickets[i]);
        printReport(report);
        for (int j = 0; j < report->size; j++) {
            if (!report->data[j]->passed) {
                // TODO adding might be broken
                output += report->data[j]->value;
            }
        }
    }
    

    printf(" - %d - \n");
}

int main(int argc, char** argv) {
    printf("starting\n");
    postProcessorBufferSize = atoi(argv[2]);
    FileData fileData = readFile(argv[1]);

    for (int i = 0; i < fileData.size; i++) {
        printf("%s\n", fileData.data[i]);
    }

    Validator* validator = newValidator(fileData);
    printf("validator made \n");
    printValidator(validator);
    Ticket* myTicket = newTicket(fileData.data[validator->size]);
    printf("myTicket made \n");
    printTicket(myTicket);
    Tickets* tickets = newTickets(fileData, validator->size + 1);
    printf("tickets made \n");
    for (int i = 0; i < tickets->size; i++) {
        printTicket(tickets->tickets[i]);
        printf("\n");
    }
    printf("the other side\n");

    solveSilver(validator, tickets);
}
