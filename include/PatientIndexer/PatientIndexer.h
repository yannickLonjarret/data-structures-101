#ifndef PATIENTINDEXER_H_INCLUDED
#define PATIENTINDEXER_H_INCLUDED

typedef struct appointment {
    char* date;
    char* reason;
    int emergencyLevel;
    struct appointment* nextAppointment;
} Appointment;

typedef Appointment* AppointmentList;

typedef struct patient {
    char* firstName;
    char* lastName;
    int appointmentCount;
    AppointmentList appointments;
    struct patient* parentPatient;
    struct patient* leftPatient;
    struct patient* rightPatient;
} PatientFile;

typedef PatientFile* PatientIndexer;

typedef struct indexerManager {
    PatientIndexer* indexers;
    int indexerCount;
} IndexerManager;

// Data structure creation and deletion
IndexerManager* CreateIndexerManager(const int numberOfIndexers);
PatientFile* CreatePatient(const char* lastName, const char* firstName);
Appointment* CreateAppointment(const char* date, const char* reason, const int emergencyLevel);
void DeletePatientIndexer(PatientIndexer* indexer);
void DeletePatientFile(PatientFile** patient);
void DeleteAppointment(Appointment** appointment);
void DeleteAppointmentList(AppointmentList* list);
void DeleteIndexerManager(IndexerManager** manager);

// Utils
PatientFile* GetMinimum(const PatientFile* patient);

// Indexer management functions
void InsertPatient(PatientIndexer* indexer, const char* lastName, const char* firstName);
int InsertNewPatientFile(PatientIndexer* indexer, PatientFile* patient);
PatientFile* SearchPatientFile(const PatientIndexer* indexer, const char* lastName);
void InsertAppointment(PatientIndexer* indexer, const char* lastName, const char* date, const char* reason, const int emergencyLevel);
int RemovePatientFileLeaf(PatientIndexer* root, PatientFile* nodeToRemove);
int RemovePatientFileSingleChild(PatientIndexer* root, PatientFile* nodeToRemove);
int RemovePatientFileTwoChildren(PatientIndexer* root, PatientFile* nodeToRemove);
void RemovePatientFile(PatientIndexer* indexer, const char* lastName);

void UpdateIndexerBackup(const PatientIndexer* indexer, PatientIndexer* backup);

int DeepCopyIndexer(const PatientIndexer* indexerToCopy, PatientIndexer* copy);
PatientFile* DeepCopyPatient(const PatientFile* patientToCopy);
int DeepCopyAppointment(const Appointment* appointmentToCopy, Appointment** copy);
int DeepCopyAppointmentList(const Appointment* listToCopy, AppointmentList* copy);

// Display functions
void DisplayPatientFile(const PatientIndexer* indexer, const char* lastName);
void DisplayAppointment(const Appointment* appointment);
void DisplayAllPatients(const PatientIndexer* indexer);

#endif