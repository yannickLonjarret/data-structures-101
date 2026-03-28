#include "gui.h"
#include <stdio.h>

void clearTerminal() { printf("\033[2J\033[H"); }

void printInitializedPointerArray(void** array, const int size) {
    for(int i = 0; i < size; i++)
        printf("+---");
    printf("+\n");
    for(int i = 0; i < size; i++) {
        printf("|");
        if(array[i] == NULL)
            printf("   ");
        else
            printf(" * ");
    }
    printf("|\n");
    for(int i = 0; i < size; i++)
        printf("+---");
    printf("+\n");
}
