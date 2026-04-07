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
