#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "PatientIndexer.h"
#include "gui.h"
#include "utils.h"

enum menuOptions { ADD_PATIENT = 0, ADD_APPOINTMENT = 1, DISPLAY_FILE = 2, DISPLAY_PATIENTS = 3, DELETE = 4, UPDATE = 5, QUIT = 6 };

int main(void) {
    IndexerManager* indexers = CreateIndexerManager(2);

    int menuChoice = 0;
    do {
        printf("--------------MENU--------------\n");
        printf("What would you like to do:\n");
        printf("0. Add a patient\n");
        printf("1. Add an appointment to a patient\n");
        printf("2. Display a patient file\n");
        printf("3. Display patient list\n");
        printf("4. Delete a patient file\n");
        printf("5. Update backup\n");
        printf("6. Quit\n");

        if(readUserIntegerInput(&menuChoice) != 0) {
            printf("Input not parsable, skip\n");
            continue;
        }

        switch(menuChoice) {
        case ADD_PATIENT:
            break;

        case ADD_APPOINTMENT:
            break;

        case DISPLAY_FILE:
            break;

        case DISPLAY_PATIENTS:
            break;

        case DELETE:
            break;

        case UPDATE:
            break;

        default:
            if(menuChoice != QUIT)
                printf("Invalid menu choice. Please choose a number between 0 and 6. \n");
            break;
        }

    } while(menuChoice != QUIT);

    DeleteIndexerManager(&indexers);
    return 0;
}
