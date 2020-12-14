#ifndef register_h
#define register_h

typedef struct Register {
    int id;
    unsigned long long value;
} Register;

Register* newRegister(char* input);
void freeRegister(Register* reg);

void printRegister(Register* reg);

#endif 
