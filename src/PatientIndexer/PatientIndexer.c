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
