#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define MAX_CHAR_SIZE 1024

static const int base_10 = 10;

static const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const int dateLength = 10;

int readUserIntegerInput(int* userInput);

int getValidUserIntegerInput(int* userInput, int lowRange, int highRange);

int isNameValid(char* name);

int parseDateField(const char* field, int* parsedField);

int isDateValid(char* date);

int canFormValidDate(const int day, const int month, const int year);

int getValidDateInput(char* dateInput);
#endif