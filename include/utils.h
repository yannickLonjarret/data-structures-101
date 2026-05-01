#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define MAX_CHAR_SIZE 1024

static const int base_10 = 10;

static const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const int dateLength = 10;

int readInput(char* input);

int readUserIntegerInput(int* userInput);

int getValidUserIntegerInput(int* userInput, const int lowRange, const int highRange);

int isNameValid(const char* name);

int readNameInput(char* name);

int getValidNameInput(char* name);

int parseDateField(const char* field, int* parsedField);

int isDateValid(const char* date);

int canFormValidDate(const int day, const int month, const int year);

int getValidDateInput(char* dateInput);

int clearBuffer(char* buffer, const int size);

void logError(const char* const errorMessage);
#endif