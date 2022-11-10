#ifndef validator_h
#define validator_h

#include <stdbool.h>

#include "../../utils/fileReader/fileReader.h"

#include "ticket.h"


typedef struct DataType {
    char* name;
    int data[4];
} DataType;

typedef struct Validator {
    int size;
    DataType** types;
} Validator;

typedef struct ValidationData {
    bool passed;
    char* name;
    int value;
} ValidationData;

typedef struct ValidationReport {
    int size;
    ValidationData** data;
} ValidationReport;

Validator* newValidator(FileData fileData);
void freeValidator(Validator* validator);
void printValidator(Validator* validator);

DataType* newDataType(char* data);
void freeDataType(DataType* type);

ValidationReport* validateData(Validator* validator, Ticket* ticket);
void freeValidationReport(ValidationReport* report);
void printReport(ValidationReport* report);


#endif