
typedef enum Parsing {
    MINIMUM,
    MAXIMUM,
    TARGET,
    PASSWORD
} Parsing;

typedef struct Password {
    int minimum;
    int maximum;
    char targetCharacter;
    char *password;
} Password;

Password * newPassword(char *input) {
    Password *output = malloc(sizeof(Password));

    char intBuffer[4] = "    ";
    int intBufferIndex = 0;
    Parsing parsingState = MINIMUM;
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        char letter = input[i];
        switch (parsingState) {
        case MINIMUM:
            if (letter == '-') {
                output->minimum = atoi(intBuffer);
                parsingState = MAXIMUM;
                intBufferIndex = 0;
                for (int j = 0; j < 4; j++) {
                    intBuffer[j] = ' ';
                }
            } else {
                intBuffer[intBufferIndex] = letter;
                intBufferIndex++;
            }
            break;
        
        case MAXIMUM:
            if (letter == ' ') {
                output->maximum = atoi(intBuffer);
                parsingState = TARGET;
            } else {
                intBuffer[intBufferIndex] = letter;
                intBufferIndex++;
            }
            break;
        
        case TARGET:
            if (letter == ':') {
                parsingState = PASSWORD;
            } else {
                output->targetCharacter = letter;
            }
            break;
        
        case PASSWORD:
            if (letter == ' ') continue;
            int remaining = length - i;
            char *subString = malloc(remaining+1);
            strncpy(subString, &input[i], remaining);
            output->password = subString;
            i = length;
            break;
        
        default:
            printf("something has gone wrong!\n");
            return output;
            break;
        }
    }

    return output;
}


void printPassword(Password *input) {
    printf("------\n");
    printf("Range   : %d-%d\n", input->minimum, input->maximum);
    printf("Target  : %c\n", input->targetCharacter);
    printf("Password: %s\n", input->password);
}



