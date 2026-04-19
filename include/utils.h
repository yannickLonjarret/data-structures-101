#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define MAX_CHAR_SIZE 1024
int readUserIntegerInput(int* userInput);

int getValidUserIntegerInput(int* userInput, int lowRange, int highRange);

int isNameValid(char* name);
#endif