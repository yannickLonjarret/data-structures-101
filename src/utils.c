#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int readUserIntegerInput(int* userInput) {
    char line[MAX_CHAR_SIZE];

    if(fgets(line, sizeof(line), stdin) == NULL) {
        fprintf_s(stderr, "Error when reading user input.\n");
        *userInput = 0;
        return 1;
    }

    char* str_end = NULL;
    const int base_10 = 10;
    errno = 0;

    *userInput = (int)strtol(line, &str_end, base_10);

    if(errno == ERANGE) {
        fprintf_s(stderr, "Error when parsing user input, value out of range.\n");
        *userInput = 0;
        return 1;
    }

    if(str_end == line) {
        fprintf_s(stderr, "Error when parsing user input, invalid input.\n");
        *userInput = 0;
        return 1;
    }

    return 0;
}