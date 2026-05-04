#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(DeepCopy);

TEST_SETUP(DeepCopy) {}

TEST_TEAR_DOWN(DeepCopy) {}

TEST(DeepCopy, DeepCopyPatient_NULLOriginal) {
    PatientFile* copy = DeepCopyPatient(NULL);
    TEST_ASSERT_NULL(copy);
}

TEST(DeepCopy, DeepCopyPatient_NoAppointment) {
    PatientFile* original = CreatePatient("D", "Test");
    PatientFile* copy = DeepCopyPatient(original);
    TEST_ASSERT_NOT_NULL(copy);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_EQUAL_STRING(original->firstName, copy->firstName);
    TEST_ASSERT_EQUAL_STRING(original->lastName, copy->lastName);
    TEST_ASSERT_EQUAL_STRING(original->appointmentCount, copy->appointmentCount);

    DeletePatientFile(original);
    DeletePatientFile(copy);
}

TEST(DeepCopy, DeepCopyAppointment_NULLOriginal) {
    Appointment* copy = NULL;
    int error = DeepCopyAppointment(NULL, copy);
    TEST_ASSERT_EQUAL(0, error);
}

TEST(DeepCopy, DeepCopyAppointment_NULLCopy) {
    Appointment* original = CreateAppointment("05_04_2026", "Fever", 1);
    int error = DeepCopyAppointment(original, NULL);
    TEST_ASSERT_EQUAL(1, error);

    DeleteAppointment(original);
}

TEST(DeepCopy, DeepCopyAppointment_ExpectedBehavior) {
    Appointment* copy = NULL;
    Appointment* original = CreateAppointment("05_04_2026", "Fever", 1);
    int error = DeepCopyAppointment(NULL, copy);
    TEST_ASSERT_EQUAL(0, error);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_EQUAL_STRING(original->date, copy->date);
    TEST_ASSERT_EQUAL_STRING(original->reason, copy->reason);
    TEST_ASSERT_EQUAL(original->emergencyLevel, copy->emergencyLevel);
    TEST_ASSERT_NULL(copy->nextAppointment);

    DeleteAppointment(copy);
    DeleteAppointment(original);
}

TEST(DeepCopy, DeepCopyAppointmentList_NULLOriginal) {
    AppointmentList copy = NULL;
    int error = DeepCopyAppointmentList(NULL, &copy);
    TEST_ASSERT_EQUAL(0, error);
}

TEST(DeepCopy, DeepCopyAppointmentList_NULLCopy) {
    AppointmentList original = CreateAppointment("05_04_2026", "Fever", 1);
    int error = DeepCopyAppointmentList(original, NULL);
    TEST_ASSERT_EQUAL(1, error);
    DeleteAppointmentList(&original);
}

TEST(DeepCopy, DeepCopyAppointmentList_ExpectedBehavior) {
    AppointmentList copy = NULL;
    AppointmentList original = CreateAppointment("05_04_2026", "Fever", 1);
    original->nextAppointment = CreateAppointment("05_04_2026", "Blood", 2);

    int error = DeepCopyAppointment(original, &copy);
    TEST_ASSERT_EQUAL(0, error);
    TEST_ASSERT_EQUAL_STRING(original->date, copy->date);
    TEST_ASSERT_EQUAL_STRING(original->reason, copy->reason);
    TEST_ASSERT_EQUAL(original->emergencyLevel, copy->emergencyLevel);
    TEST_ASSERT_NOT_NULL(copy->nextAppointment);

    AppointmentList nextOriginal, nextCopy;

    nextOriginal = original->nextAppointment;
    nextCopy = copy->nextAppointment;

    TEST_ASSERT_EQUAL_STRING(nextOriginal->date, nextCopy->date);
    TEST_ASSERT_EQUAL_STRING(nextOriginal->reason, nextCopy->reason);
    TEST_ASSERT_EQUAL(nextOriginal->emergencyLevel, nextCopy->emergencyLevel);
    TEST_ASSERT_NULL(copy->nextAppointment);

    DeleteAppointmentList(&original);
    DeleteAppointmentList(&copy);
}

TEST(DeepCopy, DeepCopyIndexer_NULLOriginal) {}
TEST(DeepCopy, DeepCopyIndexer_NULLCopy) {}
TEST(DeepCopy, DeepCopyIndexer_EmptyOriginal) {}
TEST(DeepCopy, DeepCopyIndexer_NormalOriginal) {}
