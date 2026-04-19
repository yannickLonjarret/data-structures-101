#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int readUserIntegerInput(int* userInput) {
    char line[MAX_CHAR_SIZE];
    int errorCode = 0;

    if(fgets(line, sizeof(line), stdin) == NULL) {
        errorCode = fprintf(stderr, "Error when reading user input.\n");
        *userInput = 0;
        if(errorCode != 0)
            return 2;

        return 1;
    }

    char* str_end = NULL;
    const int base_10 = 10;
    errno = 0;

    *userInput = (int)strtol(line, &str_end, base_10);

    if(errno == ERANGE) {
        errorCode = fprintf(stderr, "Error when parsing user input, value out of range.\n");
        *userInput = 0;
        if(errorCode != 0)
            return 2;
        return 1;
    }

    if(str_end == line) {
        errorCode = fprintf(stderr, "Error when parsing user input, invalid input.\n");
        if(errorCode != 0)
            return 2;
        *userInput = 0;
        return 1;
    }

    return 0;
}

int getValidUserIntegerInput(int* userInput, int lowRange, int highRange) {
    if(highRange <= lowRange)
        return 1;
    *userInput = 0;
    int errorCode = 0;

    errorCode = readUserIntegerInput(userInput);

    if(errorCode != 0) {
        printf("Input not parsable, skip\n");
        return 1;
    }

    while(*userInput < lowRange || *userInput > highRange) {
        printf("Please type in value between %d and %d: \n", lowRange, highRange);
        errorCode = readUserIntegerInput(userInput);

        if(errorCode != 0) {
            printf("Input not parsable, skip\n");
            return 1;
        }
    }

    return 0;
}

int isNameValid(char* name) {
    if(name == NULL || name[0] == '\0')
        return 0;

    for(int i = 0; name[i] != '\0'; i++)
        if(!isalpha((unsigned char)name[i]))
            return 0;

    return 1;
}