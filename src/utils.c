#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int parseDateField(const char* field, int* parsedField) {
    char* str_end = NULL;
    errno = 0;
    *parsedField = (int)strtol(field, &str_end, base_10);
    if(errno == ERANGE || str_end == field)
        return 1;
    return 0;
}

int isDateValid(char* date) {
    // Date format: MM_DD_YYYY
    if(date == NULL || date[0] == '\0')
        return 0;
    const int dateLength = 10;

    if(strlen(date) != dateLength)
        return 0;

    if(date[2] != '_' || date[5] != '_')
        return 0;

    for(int i = 0; i < dateLength; i++) {
        if(i == 2 || i == 5)
            continue;
        if(!isdigit((unsigned char)date[i]))
            return 0;
    }

    char buf[11];
    strncpy(buf, date, dateLength);
    buf[dateLength] = '\0';

    char* monthString = strtok(buf, "_");
    if(monthString == NULL || strlen(monthString) != 2)
        return 0;

    char* dayString = strtok(NULL, "_");
    if(dayString == NULL || strlen(dayString) != 2)
        return 0;

    char* yearString = strtok(NULL, "_");
    if(yearString == NULL || strlen(yearString) != 4)
        return 0;

    int error = 0;
    int month, day, year;

    error = parseDateField(monthString, &month);
    if(error != 0)
        return 0;

    error = parseDateField(dayString, &day);
    if(error != 0)
        return 0;

    error = parseDateField(yearString, &year);
    if(error != 0)
        return 0;

    if(month < 1 || month > 12)
        return 0;

    if(year < 1900)
        return 0;

    const int leapYearFeb = 29;
    int maxDay = daysPerMonth[month];
    if(month == 2) {
        int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if(isLeapYear)
            maxDay = leapYearFeb;
    }

    if(day < 1 || day > maxDay)
        return 0;

    return 1;
}
