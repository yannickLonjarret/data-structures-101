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
