#ifndef PATIENTINDEXER_H_INCLUDED
#define PATIENTINDEXER_H_INCLUDED

typedef struct appointment {
    char* date;
    char* reason;
    int emergencyLevel;
    appointment* nextAppointment;
} Appointment;

typedef struct patient {
    char* firstName;
    char* lastName;
    int appointmentCount;
    Appointment* appointments;
    patient* leftPatient;
    patient* rightPatient;
} PatientFile;

typedef PatientFile* PatientIndexer;

PatientFile* CreatePatient(char* lastName, char* firstName);
void InsertPatient(PatientIndexer* indexer, char* lastName, char* firstName);
PatientFile* SearchPatientFile(PatientIndexer* indexer, char* lastName);
void DisplayPatientFile(PatientIndexer* indexer, char* lastName);
void DisplayAllPatients(PatientIndexer* indexer);
Appointment* CreateAppointment(char* date, char* reason, int emergencyLevel);
void InsertAppointment(PatientIndexer* indexer, char* lastName, char* date, char* reason, int emergencyLevel);
void DeletePatientFile(PatientIndexer* indexer, char* lastName);
void UpdateIndexerBackup(PatientIndexer* indexer, PatientIndexer* backup);

#endif