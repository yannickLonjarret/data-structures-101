#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PatientIndexer.h"
#include "utils.h"

// Data structure creation and deletion
IndexerManager* CreateIndexerManager(const int numberOfIndexers) {
    IndexerManager* manager = (IndexerManager*)malloc(sizeof(IndexerManager));

    if(manager == NULL) {
        logError("Malloc issue when creating the manager indexer.\n");
        abort();
    }

    manager->indexerCount = numberOfIndexers;
    manager->indexers = (PatientIndexer*)calloc(numberOfIndexers, sizeof(PatientIndexer));

    if(manager->indexers == NULL) {
        logError("Malloc issue when creating the manager indexer.\n");
        abort();
    }

    return manager;
}

PatientFile* CreatePatient(const char* lastName, const char* firstName) {
    if(!isNameValid(lastName) || !isNameValid(firstName)) {
        logError("Name invalid in CreatePatient.\n");
        return NULL;
    }

    PatientFile* patient = (PatientFile*)malloc(sizeof(PatientFile));

    if(patient == NULL) {
        logError("Malloc issue when creating the patient file.\n");
        abort();
    }

    patient->lastName = NULL;
    patient->firstName = NULL;

    patient->lastName = (char*)malloc(sizeof(char) * (strlen(lastName) + 1));
    patient->firstName = (char*)malloc(sizeof(char) * (strlen(firstName) + 1));

    if(patient->lastName == NULL || patient->firstName == NULL) {
        logError("Malloc issue when creating the patient file.\n");
        abort();
    }

    int errorCode = 0;
    errorCode = snprintf(patient->lastName, strlen(lastName) + 1, "%s", lastName);
    if(errorCode < 0) {
        logError("Error when copying the patient last name.\n");
        DeletePatientFile(&patient);
        return NULL;
    }

    errorCode = snprintf(patient->firstName, strlen(firstName) + 1, "%s", firstName);
    if(errorCode < 0) {
        logError("Error when copying the patient first name.\n");
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

Appointment* CreateAppointment(const char* date, const char* reason, const int emergencyLevel) {
    if(!isDateValid(date)) {
        logError("Invalid date in CreateAppointment. \n");
        return NULL;
    }

    Appointment* appointment = (Appointment*)malloc(sizeof(Appointment));

    if(appointment == NULL) {
        logError("Malloc issue when creating the appointment.\n");
        abort();
    }

    appointment->date = NULL;
    appointment->reason = NULL;

    appointment->date = (char*)malloc(sizeof(char) * strlen(date) + 1);
    appointment->reason = (char*)malloc(sizeof(char) * strlen(reason) + 1);

    if(appointment->date == NULL || appointment->reason == NULL) {
        logError("Malloc issue when creating the appointment.\n");
        abort();
    }

    int errorCode = 0;
    errorCode = snprintf(appointment->date, strlen(date) + 1, "%s", date);
    if(errorCode < 0) {
        logError("Error when copying the appointment date.\n");
        DeleteAppointment(&appointment);
        return NULL;
    }

    errorCode = snprintf(appointment->reason, strlen(reason) + 1, "%s", reason);
    if(errorCode < 0) {
        logError("Error when copying the appointment reason.\n");
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

    DeletePatientIndexer(&(*indexer)->leftPatient);
    DeletePatientIndexer(&(*indexer)->rightPatient);
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

void DeleteIndexerManager(IndexerManager** manager) {
    if(manager == NULL || *manager == NULL)
        return;

    for(int i = 0; i < (*manager)->indexerCount; i++)
        DeletePatientIndexer(&(*manager)->indexers[i]);

    free((*manager)->indexers);
    (*manager)->indexers = NULL;
    free(*manager);
    manager = NULL;
    return;
}

// Indexer management functions
void InsertPatient(PatientIndexer* indexer, const char* lastName, const char* firstName) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return;
    }

    if(!isNameValid(lastName) || !isNameValid(firstName)) {
        logError("First or last name invalid in InsertPatient.\n");
        return;
    }

    if(SearchPatientFile(indexer, lastName) != NULL) {
        printf("Patient last name already exist. \n");
        return;
    }

    PatientFile* patientToInsert = CreatePatient(lastName, firstName);
    if(patientToInsert == NULL) {
        logError("Failed to create patient for insertion.\n");
        return;
    }

    if(InsertNewPatientFile(indexer, patientToInsert) != 0) {
        logError("Insertion failed.\n");
        return;
    }

    return;
}

int InsertNewPatientFile(PatientIndexer* indexer, PatientFile* patient) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return 1;
    }

    if(patient == NULL) {
        logError("Patient is NULL.\n");
        return 1;
    }

    if(*indexer == NULL) {
        *indexer = patient;
        return 0;
    }

    PatientFile* parent = NULL;
    PatientFile* traversal = *indexer;
    int stringCompare = 0;

    while(traversal != NULL) {
        parent = traversal;
        stringCompare = strcmp(patient->lastName, traversal->lastName);
        if(stringCompare < 0)
            traversal = traversal->leftPatient;
        else
            traversal = traversal->rightPatient;
    }

    patient->parentPatient = parent;
    stringCompare = strcmp(patient->lastName, parent->lastName);
    if(stringCompare < 0)
        parent->leftPatient = patient;
    else
        parent->rightPatient = patient;

    return 0;
}

PatientFile* SearchPatientFile(const PatientIndexer* indexer, const char* lastName) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return NULL;
    }

    if(!isNameValid(lastName)) {
        logError("Name invalid in SearchPatientFile.\n");
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

        if(traversal != NULL)
            stringCompare = strcmp(lastName, traversal->lastName);
    }

    return traversal;
}

void RemovePatientFile(PatientIndexer* indexer, const char* lastName) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return;
    }

    if(!isNameValid(lastName)) {
        logError("Name invalid in RemovePatientFile.\n");
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
    if(root == NULL || *root == NULL)
        return 1;

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
    if(root == NULL || *root == NULL)
        return 1;

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
    if(root == NULL || *root == NULL)
        return 1;

    if(nodeToRemove == NULL)
        return 1;

    PatientFile* successor = GetMinimum(nodeToRemove->rightPatient);

    if(successor == NULL) {
        logError("Successor is NULL in RemovePatientFileTwoChildren.\n");
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

void UpdateIndexerBackup(const PatientIndexer* indexer, PatientIndexer* backup) {
    PatientIndexer temporaryBackup = NULL;

    int error = DeepCopyIndexer(indexer, &temporaryBackup);
    if(error != 0) {
        logError("Backup update failure.\n");
        DeletePatientIndexer(&temporaryBackup);
        return;
    }
    DeletePatientIndexer(backup);
    *backup = temporaryBackup;
    return;
}

int DeepCopyIndexer(const PatientIndexer* indexerToCopy, PatientIndexer* copy) {
    if(indexerToCopy == NULL)
        return 1;

    if(*indexerToCopy == NULL)
        return 0;

    PatientFile* fileCopy = DeepCopyPatient(*indexerToCopy);
    if(fileCopy == NULL) {
        logError("Error when inserting copying patient file. \n");
        return 1;
    }

    int error = InsertNewPatientFile(copy, fileCopy);
    if(error != 0) {
        logError("Error when inserting copied patient file to backup. \n");
        DeletePatientFile(&fileCopy);
        return 1;
    }

    error = DeepCopyIndexer(&(*indexerToCopy)->leftPatient, copy);
    if(error != 0) {
        logError("Error when inserting copied patient file to backup. \n");
        return 1;
    }

    error = DeepCopyIndexer(&(*indexerToCopy)->rightPatient, copy);
    if(error != 0) {
        logError("Error when inserting copied patient file to backup. \n");
        return 1;
    }

    return 0;
}

PatientFile* DeepCopyPatient(const PatientFile* patientToCopy) {
    if(patientToCopy == NULL)
        return NULL;

    PatientFile* copy = CreatePatient(patientToCopy->lastName, patientToCopy->firstName);

    if(copy == NULL) {
        logError("Failed to copy patient file. \n");
        return NULL;
    }

    copy->appointmentCount = patientToCopy->appointmentCount;
    int error = DeepCopyAppointmentList(patientToCopy->appointments, &copy->appointments);

    if(error != 0) {
        logError("Failed to copy appointment list. \n");
        DeletePatientFile(&copy);
        return NULL;
    }

    return copy;
}

int DeepCopyAppointment(const Appointment* appointmentToCopy, Appointment** copy) {
    if(appointmentToCopy == NULL)
        return 0;

    *copy = CreateAppointment(appointmentToCopy->date, appointmentToCopy->reason, appointmentToCopy->emergencyLevel);

    if(*copy == NULL) {
        logError("Failed to copy appointment. \n");
        return 1;
    }
    return 0;
}

int DeepCopyAppointmentList(const Appointment* listToCopy, AppointmentList* copy) {
    if(listToCopy == NULL)
        return 0;

    int error = DeepCopyAppointment(listToCopy, copy);

    if(error != 0) {
        logError("Failed to copy appointment list. \n");
        return 1;
    }

    Appointment* originalTraversal = listToCopy;
    Appointment* copyTravesal = *copy;

    while(originalTraversal != NULL) {
        error = DeepCopyAppointment(originalTraversal->nextAppointment, &copyTravesal->nextAppointment);

        if(error != 0) {
            logError("Failed to copy appointment list. \n");
            return 1;
        }

        copyTravesal = copyTravesal->nextAppointment;
        originalTraversal = originalTraversal->nextAppointment;
    }

    return 0;
}

void InsertAppointment(PatientIndexer* indexer, const char* lastName, const char* date, const char* reason, const int emergencyLevel) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return;
    }

    if(!isDateValid(date)) {
        logError("Invalid date in InsertAppointment. \n");
        return;
    }

    if(!isNameValid(lastName)) {
        logError("Invalid name in InsertAppointment.\n");
        return;
    }

    PatientFile* patientToUpdate = SearchPatientFile(indexer, lastName);
    if(patientToUpdate == NULL) {
        printf("Patient does not exist. \n");
        return;
    }

    Appointment* appointmentToInsert = CreateAppointment(date, reason, emergencyLevel);

    if(appointmentToInsert == NULL) {
        logError("Error when creating the appointment. \n");
        return;
    }

    appointmentToInsert->nextAppointment = patientToUpdate->appointments;
    patientToUpdate->appointments = appointmentToInsert;

    patientToUpdate->appointmentCount++;

    return;
}

// Utils
PatientFile* GetMinimum(const PatientFile* patient) {
    if(patient == NULL)
        return NULL;

    PatientFile* traversal = patient;

    while(traversal != NULL) {
        if(traversal->leftPatient == NULL)
            return traversal;
        traversal = traversal->leftPatient;
    }

    return traversal;
}

// Display functions
void DisplayPatientFile(const PatientIndexer* indexer, const char* lastName) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return;
    }

    if(!isNameValid(lastName)) {
        logError("Name invalid in DisplayPatientFile.\n");
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

void DisplayAppointment(const Appointment* appointment) {
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

void DisplayAllPatients(const PatientIndexer* indexer) {
    if(indexer == NULL) {
        logError("Patient indexer is NULL.\n");
        return;
    }
    PatientFile* patientToDisplay = *indexer;
    if(patientToDisplay == NULL)
        return;

    printf("%s %s\n", patientToDisplay->lastName, patientToDisplay->firstName);
    DisplayAllPatients(&patientToDisplay->leftPatient);
    DisplayAllPatients(&patientToDisplay->rightPatient);
}
