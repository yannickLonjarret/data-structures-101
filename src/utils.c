#include "utils.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readInput(char* input) {
    if(fgets(input, MAX_CHAR_SIZE, stdin) == NULL) {
        logError("Error when reading user input.\n");
        input[0] = '\0';
        return 1;
    }
    return 0;
}

int readUserIntegerInput(int* userInput) {
    char line[MAX_CHAR_SIZE];
    int errorCode = readInput(line);

    if(errorCode != 0)
        return errorCode;

    char* str_end = NULL;
    errno = 0;

    *userInput = (int)strtol(line, &str_end, base_10);

    if(errno == ERANGE) {
        logError("Error when parsing user input, value out of range.\n");
        *userInput = 0;
        return 1;
    }

    if(str_end == line) {
        logError("Error when parsing user input, invalid input.\n");
        *userInput = 0;
        return 1;
    }

    return 0;
}

int getValidUserIntegerInput(int* userInput, const int lowRange, const int highRange) {
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

int isNameValid(const char* name) {
    if(name == NULL || name[0] == '\0')
        return 0;

    const size_t nameLength = strlen(name);
    for(size_t i = 0; i < nameLength; i++)
        if(!isalpha((unsigned char)name[i]))
            return 0;

    return 1;
}

int readNameInput(char* name) {
    char line[MAX_CHAR_SIZE];
    int errorCode = readInput(line);

    if(errorCode != 0)
        return errorCode;

    line[strcspn(line, "\n")] = '\0';
    strncpy(name, line, strlen(line));
    return 0;
}

int getValidNameInput(char* name) {
    int errorCode = readNameInput(name);
    if(errorCode != 0) {
        logError("Failed to get name skip.\n");
        return 1;
    }
    while(!isNameValid(name)) {
        printf("Please input a name without figures or symbols. \n");
        errorCode = readNameInput(name);
        if(errorCode != 0) {
            logError("Failed to get name skip.\n");
            return 1;
        }
    }

    return 0;
}

int parseDateField(const char* field, int* parsedField) {
    const int fieldLength = strlen(field);
    for(int i = 0; i < fieldLength; i++)
        if(!isdigit((unsigned char)field[i]))
            return 1;

    char* str_end = NULL;
    errno = 0;
    *parsedField = (int)strtol(field, &str_end, base_10);
    if(errno == ERANGE || str_end == field)
        return 1;
    return 0;
}

int isDateValid(const char* date) {
    // Date format: MM_DD_YYYY
    if(date == NULL || date[0] == '\0')
        return 0;

    if(strlen(date) != dateLength)
        return 0;

    const int firstSeparatorPosition = 2;
    const int secondSeparatorPosition = 5;
    if(date[firstSeparatorPosition] != '_' || date[secondSeparatorPosition] != '_')
        return 0;

    for(int i = 0; i < dateLength; i++) {
        if(i == firstSeparatorPosition || i == secondSeparatorPosition)
            continue;
        if(!isdigit((unsigned char)date[i]))
            return 0;
    }

    char buf[dateLength + 1];
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

    return canFormValidDate(day, month, year);
}

int canFormValidDate(const int day, const int month, const int year) {
    const int firstMonth = 1;
    const int lastMonth = 12;
    const int yearLowBound = 1900;
    const int yearHihgound = 2100;
    const int february = 2;
    const int multipleOf100 = 100;
    const int multipleOf400 = 400;
    if(month < firstMonth || month > lastMonth)
        return 0;

    if(year < yearLowBound || year > yearHihgound)
        return 0;

    const int leapYearFeb = 29;
    int maxDay = daysPerMonth[month];
    if(month == february) {
        int isLeapYear = (year % 4 == 0 && year % multipleOf100 != 0) || (year % multipleOf400 == 0);
        if(isLeapYear)
            maxDay = leapYearFeb;
    }

    if(day < 1 || day > maxDay)
        return 0;

    return 1;
}

int getValidDateInput(char* dateInput) {
    const int firstDay = 1;
    const int lastDay = 31;
    const int firstMonth = 1;
    const int lastMonth = 12;
    const int yearLowBound = 1900;
    const int yearHihgound = 2100;
    int day, month, year;
    int dateValid = 0;
    int error;
    do {

        printf("Please input the day:\n");
        error = getValidUserIntegerInput(&day, firstDay, lastDay);
        if(error != 0)
            return 1;

        printf("Please input the month:\n");
        error = getValidUserIntegerInput(&month, firstMonth, lastMonth);
        if(error != 0)
            return 1;

        printf("Please input the year:\n");
        error = getValidUserIntegerInput(&year, yearLowBound, yearHihgound);
        if(error != 0)
            return 1;

        dateValid = canFormValidDate(day, month, year);
        if(!dateValid)
            printf("Please type in a valid date. \n");
    } while(!dateValid);

    error = snprintf(dateInput, dateLength + 1, "%02d_%02d_%04d", month, day, year);

    if(error < 0 || error > dateLength)
        return 1;
    return 0;
}

int clearBuffer(char* buffer, const int size) {
    if(size > MAX_CHAR_SIZE)
        return 1;
    if(buffer == NULL)
        return 1;
    memset(buffer, '\0', size);
    return 0;
}

void logError(const char* const errorMessage) {
    if(errorMessage == NULL)
        return;
    int error = 0;
    error = fprintf(stderr, "%s", errorMessage);
    if(error < 0)
        perror("Log error fprintf failure.\n");
    return;
}
