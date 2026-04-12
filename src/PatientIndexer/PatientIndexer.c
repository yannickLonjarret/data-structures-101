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
        // DeletePatientFile(&patient);
        return NULL;
    }

    errorCode = snprintf(patient->firstName, strlen(firstName) + 1, "%s", firstName);
    if(errorCode != 0) {
        fprintf(stderr, "Error when copying the patient first name.");
        // DeletePatientFile(&patient);
        return NULL;
    }

    patient->appointmentCount = 0;
    patient->appointments = NULL;

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

void DeleteAppointment(Appointment** appointment) {
    if(appointment == NULL || *appointment == NULL)
        return;

    free((*appointment)->date);
    free((*appointment)->reason);
    (*appointment)->nextAppointment = NULL;

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
        return;
    }

    // TODO: Create a better way to validate strings
    if(lastName == NULL) {
        fprintf(stderr, "Last name null.\n");
        return;
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
