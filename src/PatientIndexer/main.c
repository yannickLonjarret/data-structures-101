#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "PatientIndexer.h"
#include "gui.h"
#include "utils.h"

enum menuOptions { ADD_PATIENT = 0, ADD_APPOINTMENT = 1, DISPLAY_FILE = 2, DISPLAY_PATIENTS = 3, DELETE = 4, UPDATE = 5, QUIT = 6 };

int main(void) {
    IndexerManager* manager = CreateIndexerManager(2);

    int emergencyLevel, errorCode, menuChoice = 0;
    char date[15];
    char firstName[MAX_CHAR_SIZE], lastName[MAX_CHAR_SIZE];
    char appointmentReason[MAX_CHAR_SIZE];
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
            printf("Please type in the patients last name: \n");
            errorCode = getValidNameInput(lastName);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            printf("Please type in the patients first name: \n");
            errorCode = getValidNameInput(firstName);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            InsertPatient(&manager->indexers[0], lastName, firstName);
            break;

        case ADD_APPOINTMENT:
            printf("Please type in the patients last name: \n");
            errorCode = getValidNameInput(lastName);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            printf("Please type in appointment date: \n");
            errorCode = getValidDateInput(date);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            printf("Please type in appointment date: \n");
            errorCode = readInput(appointmentReason);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            printf("Please type in the emergency level (0-5):\n");
            errorCode = getValidUserIntegerInput(&emergencyLevel, 0, 5);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            InsertAppointment(&manager->indexers[0], lastName, date, appointmentReason, emergencyLevel);
            break;

        case DISPLAY_FILE:
            printf("Please type in the patients last name: \n");
            errorCode = getValidNameInput(lastName);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            DisplayPatientFile(&manager->indexers[0], lastName);
            break;

        case DISPLAY_PATIENTS:
            DisplayAllPatients(&manager->indexers[0]);
            break;

        case DELETE:
            printf("Please type in the patients last name: \n");
            errorCode = getValidNameInput(lastName);
            if(errorCode != 0) {
                printf("Something wrong happened, skipping.\n");
                continue;
            }

            RemovePatientFile(&manager->indexers[0], lastName);
            break;

        case UPDATE:
            UpdateIndexerBackup(&manager->indexers[0], &manager->indexers[1]);
            printf("Update done.\n");
            break;

        default:
            if(menuChoice != QUIT)
                printf("Invalid menu choice. Please choose a number between 0 and 6. \n");
            break;
        }

    } while(menuChoice != QUIT);

    DeleteIndexerManager(&manager);
    return 0;
}
