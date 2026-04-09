#ifndef PATIENTINDEXER_H_INCLUDED
#define PATIENTINDEXER_H_INCLUDED

typedef struct appointment {
    char* date;
    char* reason;
    int emergencyLevel;
    appointment* nextAppointment;
} Appointment;

typedef Appointment* AppointmentList;

typedef struct patient {
    char* firstName;
    char* lastName;
    int appointmentCount;
    Appointment* appointments;
    patient* leftPatient;
    patient* rightPatient;
} PatientFile;

typedef PatientFile* PatientIndexer;

typedef struct indexerManager {
    PatientIndexer* indexers;
    int indexerCount;
} IndexerManager;

// Data structure creation and deletion
IndexerManager CreateIndexerManager(int numberOfIndexers);
PatientFile* CreatePatient(char* lastName, char* firstName);
Appointment* CreateAppointment(char* date, char* reason, int emergencyLevel);
void DeletePatientIndexer(PatientIndexer* indexer);
void DeletePatientFile(PatientFile** patient);
void DeleteAppointment(Appointment** appointment);
void DeleteAppointMentList(AppointmentList* list);

// Indexer management functions
void InsertPatient(PatientIndexer* indexer, char* lastName, char* firstName);
PatientFile* SearchPatientFile(PatientIndexer* indexer, char* lastName);
void InsertAppointment(PatientIndexer* indexer, char* lastName, char* date, char* reason, int emergencyLevel);
void RemovePatientFile(PatientIndexer* indexer, char* lastName);
void UpdateIndexerBackup(PatientIndexer* indexer, PatientIndexer* backup);

// Display functions
void DisplayPatientFile(PatientIndexer* indexer, char* lastName);
void DisplayAppointment(Appointment* appointment);
void DisplayAllPatients(PatientIndexer* indexer);

#endif