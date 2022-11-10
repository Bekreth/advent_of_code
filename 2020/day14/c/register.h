#ifndef register_h
#define register_h

typedef struct Register {
    unsigned long long id;
    unsigned long long value;
    unsigned long long floatingMask;
} Register;

Register* newRegister(char* input);
void freeRegister(Register* reg);

void printRegister(Register* reg);

typedef struct Registers {
    Register** reg;
    int size;
} Registers;

void printRegisters(Registers* registers);




#endif 
