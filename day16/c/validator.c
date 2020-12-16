#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "validator.h"


Validator* newValidator(FileData fileData) {
    Validator* output = malloc(sizeof(Validator));
    output->types = malloc(0);
    output->size = 0;
    for (int i = 0; i < fileData.size; i++) {
        printf("v: %d\n", i);
        output->types = realloc(output->types, (i+1) * sizeof(ValidationData*));
        output->types[i] = newDataType(fileData.data[i]);
        output->size++;
        switch (fileData.data[i+1][0])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            i = fileData.size;
            break;
        }
    }
    return output;
}

void freeValidator(Validator* validator) {
    for (int i = 0; i < validator->size; i++) {
        freeDataType(validator->types[i]);
    }
    free(validator->types);
    free(validator);
}

DataType* newDataType(char* fileData) {
    DataType* output = malloc(sizeof(DataType));

    char* buffer = calloc(100 * sizeof(char), 1);
    int bufferIndex = 0;
    int index = 0;

    int writeIntIndex = 0;
    bool capturingDigit = false;
    bool running = true;
    while (running) {
        switch (fileData[index]) {
        case ':':
            output->name = malloc(bufferIndex * sizeof(char));
            memcpy(output->name, buffer, bufferIndex);
            memset(buffer, 0, 100);
            bufferIndex = 0;
            break;

        case '!':
            running = false;
        case ' ':
            if (!capturingDigit) {
                memset(buffer, 0, 100);
                bufferIndex = 0;
                capturingDigit = true;
                break;
            } else capturingDigit = false;
        case '-':
            output->data[writeIntIndex] = atoi(buffer);
            writeIntIndex++;
            memset(buffer, 0, 100);
            bufferIndex = 0;
            break;
        
        default:
            buffer[bufferIndex] = fileData[index];
            bufferIndex++;
            break;
        }
        index++;
    }

    return output;
}

void freeDataType(DataType* type) {
    free(type->name);
    free(type);
}

ValidationData* validate(DataType* dataType, int ticketValue) {
    //TODO this doesn't seem to quite work
    ValidationData* output = malloc(sizeof(ValidationData));
    output->value = ticketValue;
    output->name = dataType->name;

    if (ticketValue >= dataType->data[0] && ticketValue <= dataType->data[1]) {
        output->passed = true;
    } else if (ticketValue >= dataType->data[1] && ticketValue <= dataType->data[2]) {
        output->passed = true;
    } else {
        output->passed = false;
    }

    return output;
}


ValidationReport* validateData(Validator* validator, Ticket* ticket) {
    ValidationReport* output = malloc(sizeof(ValidationReport));
    output->data = malloc(ticket->size * sizeof(ValidationData*));
    output->size = ticket->size;

    ValidationData* validation;
    for (int i = 0; i < ticket->size; i++) {
        for (int j = 0; j < validator->size; j++) {
            // TODO check this
            validation = validate(validator->types[j], ticket->data[i]);
            if (validation->passed) break;
        }
        output->data[i] = validation;
    }
    return output;
}

void freeValidationReport(ValidationReport* report) {
    for (int i = 0; i < report->size; i++) {
        free(report->data[i]->name);
        free(report->data[i]);
    }
    free(report->data);
    free(report);
}

void printDataType(DataType* dataType) {
    printf("!! DATA TYPE !!\n");
    printf("%s\n", dataType->name);
    printf("%d-%d, %d-%d\n", dataType->data[0], dataType->data[1], 
        dataType->data[2], dataType->data[3]);
}

void printValidator(Validator* validator) {
    printf(" -: VALIDATOR :- \n");
    for (int i = 0; i < validator->size; i++) {
        printDataType(validator->types[i]);
        printf("\n");
    }
}

void printValidation(ValidationData* data) {
    printf(" = = = = =\n");
    printf(" - %d\n", data->value);
    if (data->passed) {
        printf(" - PASSED\n");
        printf(" - %s\n", data->name);
    } else {
        printf(" - FAILED\n");
    }
}

void printReport(ValidationReport* report) {
    printf("== Report ==\n");
    for (int i = 0; i < report->size; i++) {
        printValidation(report->data[i]);
    }
    printf("\n");
}