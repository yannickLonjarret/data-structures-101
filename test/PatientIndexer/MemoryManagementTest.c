#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(MemoryManagement);

TEST_SETUP(MemoryManagement) {}

TEST_TEAR_DOWN(MemoryManagement) {}

TEST(MemoryManagement, TestCreateIndexerManager) {
    IndexerManager* manager = CreateIndexerManager(2);

    TEST_ASSERT_NOT_NULL(manager);
    TEST_ASSERT_EQUAL_INT(2, manager->indexerCount);

    TEST_ASSERT_EACH_EQUAL_PTR(NULL, manager->indexers, manager->indexerCount);

    DeleteIndexerManager(&manager);
}

TEST(MemoryManagement, TestCreateIndexerManager_NegativeIndexerCount) {
    IndexerManager* manager = CreateIndexerManager(-1);
    TEST_ASSERT_NULL(manager);
}

TEST(MemoryManagement, TestCreatePatient) {
    PatientFile* patient = CreatePatient("Freeman", "Gordon");

    TEST_ASSERT_NOT_NULL(patient);
    TEST_ASSERT_EQUAL_INT(0, patient->appointmentCount);
    TEST_ASSERT_NULL(patient->appointments);

    TEST_ASSERT_NULL(patient->parentPatient);
    TEST_ASSERT_NULL(patient->leftPatient);
    TEST_ASSERT_NULL(patient->rightPatient);

    TEST_ASSERT_EQUAL_STRING("Freeman", patient->lastName);
    TEST_ASSERT_EQUAL_STRING("Gordon", patient->firstName);

    DeletePatientFile(&patient);
}

TEST(MemoryManagement, TestCreatePatient_InvalidName) {
    PatientFile* patient = CreatePatient("1Invalid@@", "H3ll0");
    TEST_ASSERT_NULL(patient);
}

TEST(MemoryManagement, TestCreatePatient_NULLName) {
    PatientFile* patient = CreatePatient(NULL, NULL);
    TEST_ASSERT_NULL(patient);
}

TEST(MemoryManagement, TestCreateAppointment) {
    Appointment* appointment = CreateAppointment("04_18_2026", "Fever", 0);

    TEST_ASSERT_NOT_NULL(appointment);
    TEST_ASSERT_EQUAL_INT(0, appointment->emergencyLevel);
    TEST_ASSERT_EQUAL_STRING("04_18_2026", appointment->date);
    TEST_ASSERT_EQUAL_STRING("Fever", appointment->reason);

    TEST_ASSERT_NULL(appointment->nextAppointment);

    DeleteAppointment(&appointment);
}

TEST(MemoryManagement, TestCreateAppointment_InvalidDate) {
    Appointment* appointment = CreateAppointment("02_31_2026", "Fever", 0);
    TEST_ASSERT_NULL(appointment);
}

TEST(MemoryManagement, TestDeletePatientIndexer) {
    PatientFile* indexer = CreatePatient("D", "test");
    PatientFile* leftNode = CreatePatient("A", "test");
    PatientFile* rightNode = CreatePatient("Z", "test");

    indexer->leftPatient = leftNode;
    indexer->rightPatient = rightNode;

    DeletePatientIndexer(&indexer);

    TEST_ASSERT_NULL(indexer);
}

TEST(MemoryManagement, TestDeletePatientFile) {
    PatientFile* patient = CreatePatient("Test", "test");

    DeletePatientFile(&patient);

    TEST_ASSERT_NULL(patient);
}

TEST(MemoryManagement, TestDeleteAppointment) {
    Appointment* appointment = CreateAppointment("04_18_2026", "Fever", 0);
    DeleteAppointment(&appointment);
    TEST_ASSERT_NULL(appointment);
}

TEST(MemoryManagement, TestDeleteAppointmentList) {
    Appointment* appointment1 = CreateAppointment("04_18_2026", "Fever", 0);
    Appointment* appointment2 = CreateAppointment("04_18_2026", "Fever", 0);

    TEST_ASSERT_NOT_NULL(appointment1);
    TEST_ASSERT_NOT_NULL(appointment2);

    appointment1->nextAppointment = appointment2;

    DeleteAppointmentList(&appointment1);

    TEST_ASSERT_NULL(appointment1);
}
