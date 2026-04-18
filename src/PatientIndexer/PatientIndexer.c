#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PatientIndexer.h"

// Data structure creation and deletion
IndexerManager CreateIndexerManager(int numberOfIndexers) {
    IndexerManager manager;
    manager.indexerCount = numberOfIndexers;
    manager.indexers = (PatientIndexer*)malloc(sizeof(PatientIndexer) * numberOfIndexers);

    if(manager.indexers == NULL) {
        fprintf(stderr, "Malloc issue when creating the manager indexer.");
        abort();
    }

    return manager;
}

PatientFile* CreatePatient(char* lastName, char* firstName) {
    PatientFile* patient = (PatientFile*)malloc(sizeof(PatientFile));

    if(patient == NULL) {
        fprintf(stderr, "Malloc issue when creating the patient file.");
        abort();
    }

    patient->lastName = NULL;
    patient->firstName = NULL;

    patient->lastName = (char*)malloc(sizeof(char) * strlen(lastName) + 1);
    patient->firstName = (char*)malloc(sizeof(char) * strlen(firstName) + 1);

    if(patient->lastName == NULL || patient->firstName == NULL) {
        fprintf(stderr, "Malloc issue when creating the patient file.");
        abort();
    }

    int errorCode = 0;
    errorCode = snprintf(patient->lastName, strlen(lastName) + 1, "%s", lastName);
    if(errorCode != 0) {
        fprintf(stderr, "Error when copying the patient last name.");
        DeletePatientFile(&patient);
        return NULL;
    }

    errorCode = snprintf(patient->firstName, strlen(firstName) + 1, "%s", firstName);
    if(errorCode != 0) {
        fprintf(stderr, "Error when copying the patient first name.");
        DeletePatientFile(&patient);
        return NULL;
    }

    patient->appointmentCount = 0;
    patient->appointments = NULL;

    patient->parentPatient = NULL;
    patient->leftPatient = NULL;
    patient->rightPatient = NULL;

    return patient;
}

Appointment* CreateAppointment(char* date, char* reason, int emergencyLevel) {
    Appointment* appointment = (Appointment*)malloc(sizeof(Appointment));

    if(appointment == NULL) {
        fprintf(stderr, "Malloc issue when creating the appointment.");
        abort();
    }

    appointment->date = NULL;
    appointment->reason = NULL;

    appointment->date = (char*)malloc(sizeof(char) * strlen(date) + 1);
    appointment->reason = (char*)malloc(sizeof(char) * strlen(reason) + 1);

    if(appointment->date == NULL || appointment->reason == NULL) {
        fprintf(stderr, "Malloc issue when creating the appointment.");
        abort();
    }

    int errorCode = 0;
    errorCode = snprintf(appointment->date, strlen(date) + 1, "%s", date);
    if(errorCode != 0) {
        fprintf(stderr, "Error when copying the appointment date.");
        DeleteAppointment(&appointment);
        return NULL;
    }

    errorCode = snprintf(appointment->reason, strlen(reason) + 1, "%s", reason);
    if(errorCode != 0) {
        fprintf(stderr, "Error when copying the appointment reason.");
        DeleteAppointment(&appointment);
        return NULL;
    }

    appointment->emergencyLevel = emergencyLevel;
    appointment->nextAppointment = NULL;

    return appointment;
}

void DeletePatientIndexer(PatientIndexer* indexer) {
    if(indexer == NULL || *indexer == NULL)
        return;

    DeletePatientFile(&(*indexer)->leftPatient);
    DeletePatientFile(&(*indexer)->rightPatient);
    DeletePatientFile(indexer);

    return;
}

void DeletePatientFile(PatientFile** patient) {
    if(patient == NULL)
        return;
    free((*patient)->lastName);
    free((*patient)->firstName);
    DeleteAppointmentList(&(*patient)->appointments);

    free(*patient);
    *patient = NULL;
}

void DeleteAppointment(Appointment** appointment) {
    if(appointment == NULL || *appointment == NULL)
        return;

    free((*appointment)->date);
    free((*appointment)->reason);
    (*appointment)->nextAppointment = NULL;

    free(*appointment);
    *appointment = NULL;

    return;
}

void DeleteAppointmentList(AppointmentList* list) {
    if(list == NULL || *list == NULL)
        return;

    Appointment* listTraversal = *list;
    while(listTraversal != NULL) {
        Appointment* temp = listTraversal;
        listTraversal = listTraversal->nextAppointment;
        DeleteAppointment(&temp);
    }

    *list = NULL;
}

// Indexer management functions
void InsertPatient(PatientIndexer* indexer, char* lastName, char* firstName) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return;
    }

    // TODO: Create a better way to validate strings
    if(lastName == NULL || firstName == NULL) {
        fprintf(stderr, "First or last name null.\n");
        return;
    }

    if(SearchPatientFile(indexer, lastName) != NULL) {
        printf("Patient last name already exist. \n");
        return;
    }

    PatientFile* patientToInsert = CreatePatient(lastName, firstName);
    if(patientToInsert == NULL) {
        fprintf(stderr, "Failed to create patient for insertion.");
        return;
    }

    if(*indexer == NULL) {
        *indexer = patientToInsert;
        return;
    }

    PatientFile* parent = NULL;
    PatientFile* traversal = *indexer;
    int stringCompare = 0;

    while(traversal != NULL) {
        parent = traversal;
        stringCompare = strcmp(patientToInsert->lastName, traversal->lastName);
        if(stringCompare < 0)
            traversal = traversal->leftPatient;
        else
            traversal = traversal->rightPatient;
    }

    patientToInsert->parentPatient = parent;
    stringCompare = strcmp(patientToInsert->lastName, parent->lastName);
    if(stringCompare < 0)
        parent->leftPatient = patientToInsert;
    else
        parent->rightPatient = patientToInsert;

    return;
}

PatientFile* SearchPatientFile(PatientIndexer* indexer, char* lastName) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return NULL;
    }

    // TODO: Create a better way to validate strings
    if(lastName == NULL) {
        fprintf(stderr, "Last name null.\n");
        return NULL;
    }

    if(*indexer == NULL)
        return NULL;

    PatientFile* traversal = *indexer;
    int stringCompare = 0;
    stringCompare = strcmp(lastName, traversal->lastName);

    while(traversal != NULL && stringCompare != 0) {
        if(stringCompare < 0)
            traversal = traversal->leftPatient;
        else
            traversal = traversal->rightPatient;

        stringCompare = strcmp(lastName, traversal->lastName);
    }

    return traversal;
}

void RemovePatientFile(PatientIndexer* indexer, char* lastName) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return;
    }

    if(lastName == NULL) {
        fprintf(stderr, "First or last name null.\n");
        return;
    }

    PatientFile* patient = SearchPatientFile(indexer, lastName);
    if(patient == NULL) {
        printf("Patient not present in indexer. \n");
        return;
    }
    int errorCode = 0;
    if(patient->leftPatient == NULL && patient->rightPatient == NULL)
        errorCode = RemovePatientFileLeaf(indexer, patient);
    else if(patient->leftPatient != NULL && patient->rightPatient != NULL)
        errorCode = RemovePatientFileTwoChildren(indexer, patient);
    else
        errorCode = RemovePatientFileSingleChild(indexer, patient);

    if(errorCode == 0)
        DeletePatientFile(&patient);

    return;
}

int RemovePatientFileLeaf(PatientIndexer* root, PatientFile* nodeToRemove) {
    if(nodeToRemove == NULL)
        return 1;

    if(nodeToRemove->parentPatient == NULL) {
        *root = NULL;
        return 0;
    }

    PatientFile* parent = nodeToRemove->parentPatient;
    if(parent->leftPatient == nodeToRemove)
        parent->leftPatient = NULL;
    else
        parent->rightPatient = NULL;

    return 0;
}

int RemovePatientFileSingleChild(PatientIndexer* root, PatientFile* nodeToRemove) {
    if(nodeToRemove == NULL)
        return 1;

    if(nodeToRemove->parentPatient == NULL) {
        if(nodeToRemove->leftPatient != NULL) {
            *root = nodeToRemove->leftPatient;
            (*root)->parentPatient = NULL;
        } else {
            *root = nodeToRemove->rightPatient;
            (*root)->parentPatient = NULL;
        }
        return 0;
    }

    PatientFile* parent = nodeToRemove->parentPatient;
    if(parent->leftPatient == nodeToRemove) {
        parent->leftPatient = (nodeToRemove->leftPatient != NULL) ? nodeToRemove->leftPatient : nodeToRemove->rightPatient;
        parent->leftPatient->parentPatient = parent;
    } else {
        parent->rightPatient = (nodeToRemove->leftPatient != NULL) ? nodeToRemove->leftPatient : nodeToRemove->rightPatient;
        parent->rightPatient->parentPatient = parent;
    }

    return 0;
}

int RemovePatientFileTwoChildren(PatientIndexer* root, PatientFile* nodeToRemove) {
    if(nodeToRemove == NULL)
        return 1;

    PatientFile* successor = GetMinimum(nodeToRemove->rightPatient);

    if(successor == NULL) {
        fprintf(stderr, "Successor is NULL in RemovePatientFileTwoChildren.\n");
        return 1;
    }

    if(successor->parentPatient != nodeToRemove) {
        successor->parentPatient->leftPatient = successor->rightPatient;
        if(successor->rightPatient != NULL)
            successor->rightPatient->parentPatient = successor->parentPatient;

        successor->rightPatient = nodeToRemove->rightPatient;
        successor->rightPatient->parentPatient = successor;
    }

    successor->leftPatient = nodeToRemove->leftPatient;
    successor->leftPatient->parentPatient = successor;

    successor->parentPatient = nodeToRemove->parentPatient;

    PatientFile* nodeToRemoveParent = nodeToRemove->parentPatient;

    if(nodeToRemoveParent != NULL)
        if(nodeToRemoveParent->leftPatient == nodeToRemove)
            nodeToRemoveParent->leftPatient = successor;
        else
            nodeToRemoveParent->rightPatient = successor;
    else
        *root = successor;

    return 0;
}

void DeleteIndexerManager(IndexerManager* manager) {
    if(manager == NULL)
        return;

    for(int i = 0; i < manager->indexerCount; i++)
        DeletePatientIndexer(&manager->indexers[i]);

    free(manager->indexers);
    manager->indexers = NULL;

    return;
}
void UpdateIndexerBackup(PatientIndexer* indexer, PatientIndexer* backup);

void InsertAppointment(PatientIndexer* indexer, char* lastName, char* date, char* reason, int emergencyLevel) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return;
    }

    // TODO check names validity and date vaidity

    PatientFile* patientToUpdate = SearchPatientFile(indexer, lastName);
    if(patientToUpdate == NULL) {
        printf("Patient does not exist. \n");
        return;
    }

    Appointment* appointmentToInsert = CreateAppointment(date, reason, emergencyLevel);

    if(appointmentToInsert == NULL) {
        fprintf(stderr, "Error when creating the appointment. \n");
        return;
    }

    appointmentToInsert->nextAppointment = patientToUpdate->appointments;
    patientToUpdate->appointments = appointmentToInsert;

    patientToUpdate->appointmentCount++;

    return;
}

// Utils
PatientFile* GetMinimum(PatientFile* patient) {
    if(patient == NULL)
        return NULL;

    PatientFile* traversal = *patient->leftPatient;

    while(traversal != NULL) {
        if(traversal->leftPatient == NULL)
            return traversal;
        traversal = traversal->leftPatient;
    }

    return traversal;
}

// Display functions
void DisplayPatientFile(PatientIndexer* indexer, char* lastName) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return;
    }

    // TODO: Create a better way to validate strings
    if(lastName == NULL) {
        fprintf(stderr, "First or last name null.\n");
        return;
    }

    PatientFile* patientToDisplay = SearchPatientFile(indexer, lastName);
    if(patientToDisplay == NULL) {
        printf("Patient file does not exist. \n");
        return;
    }

    printf("===== Patient %s %s =====\n", patientToDisplay->lastName, patientToDisplay->firstName);
    printf("Appointment count: %d\n", patientToDisplay->appointmentCount);
    DisplayAppointment(patientToDisplay->appointments);

    return;
}

void DisplayAppointment(Appointment* appointment) {
    Appointment* traversal = appointment;
    printf("===== Appointment start =====\n");

    while(traversal != NULL) {
        printf("Date: %s\n", traversal->date);
        printf("Emergency level: %d\n", traversal->emergencyLevel);
        printf("Reason: %s\n", traversal->reason);

        traversal = traversal->nextAppointment;
    }

    printf("===== Appointment end =====\n");
}

void DisplayAllPatients(PatientIndexer* indexer) {
    if(indexer == NULL) {
        fprintf(stderr, "Patient indexer is NULL.\n");
        return;
    }
    PatientFile* patientToDisplay = *indexer;
    if(patientToDisplay == NULL)
        return;

    printf("%s %s\n", patientToDisplay->lastName, patientToDisplay->firstName);
    DisplayAllPatients(&patientToDisplay->leftPatient);
    DisplayAllPatients(&patientToDisplay->rightPatient);
}
