#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(TreeMinimum);

TEST_SETUP(TreeMinimum) {}

TEST_TEAR_DOWN(TreeMinimum) {}

TEST(TreeMinimum, TestGetMinimumNullInput) {
    PatientFile* nullPointer = NULL;
    PatientFile* minimum = GetMinimum(nullPointer);
    TEST_ASSERT_NULL(minimum);
}

TEST(TreeMinimum, TestGetMinimumNoChildNode) {
    PatientFile* patient = CreatePatient("Test", "test");
    PatientFile* expected = CreatePatient("Min", "test");
    TEST_ASSERT_NOT_NULL(patient);
    patient->rightPatient = expected;

    PatientFile* minimum = GetMinimum(patient->rightPatient);
    TEST_ASSERT_EQUAL_PTR(expected, minimum);

    DeletePatientFile(&patient);
    DeletePatientFile(&expected);
}

TEST(TreeMinimum, TestGetMinimum) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "L", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "O", "test");
    InsertPatient(&indexer, "V", "test");
    InsertPatient(&indexer, "M", "test");

    PatientFile* expected = SearchPatientFile(&indexer, "M");
    TEST_ASSERT_NOT_NULL(expected);

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* minimum = GetMinimum(indexer->rightPatient);
    TEST_ASSERT_EQUAL_PTR(expected, minimum);

    DeletePatientIndexer(&indexer);
}
