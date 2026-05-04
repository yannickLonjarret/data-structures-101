#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(TreeInsertion);

TEST_SETUP(TreeInsertion) {}

TEST_TEAR_DOWN(TreeInsertion) {}

TEST(TreeInsertion, TestInsertPatient_EmptyIndexer) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_EQUAL_STRING("D", indexer->lastName);
    TEST_ASSERT_EQUAL_STRING("Test", indexer->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->leftPatient);
    TEST_ASSERT_NULL(indexer->rightPatient);
    TEST_ASSERT_NULL(indexer->parentPatient);

    DeletePatientIndexer(&indexer);
}

TEST(TreeInsertion, TestInsertPatient_LeftPosition) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "A", "Left");

    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_EQUAL_STRING("D", indexer->lastName);
    TEST_ASSERT_EQUAL_STRING("Test", indexer->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->rightPatient);

    TEST_ASSERT_NOT_NULL(indexer->leftPatient);
    if(indexer->leftPatient != NULL) {
        PatientFile* leftNode = indexer->leftPatient;
        TEST_ASSERT_EQUAL_STRING("A", leftNode->lastName);
        TEST_ASSERT_EQUAL_STRING("Left", leftNode->firstName);
        TEST_ASSERT_EQUAL_INT(0, leftNode->appointmentCount);
        TEST_ASSERT_NULL(leftNode->appointments);
        TEST_ASSERT_NULL(leftNode->rightPatient);
        TEST_ASSERT_NULL(leftNode->leftPatient);

        TEST_ASSERT_EQUAL_PTR(indexer, leftNode->parentPatient);
    }
    DeletePatientIndexer(&indexer);
}

TEST(TreeInsertion, TestInsertPatient_RightPosition) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "Z", "Right");

    TEST_ASSERT_NOT_NULL(indexer);

    TEST_ASSERT_EQUAL_STRING("D", indexer->lastName);
    TEST_ASSERT_EQUAL_STRING("Test", indexer->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->leftPatient);

    TEST_ASSERT_NOT_NULL(indexer->rightPatient);
    PatientFile* rightNode = indexer->rightPatient;
    TEST_ASSERT_EQUAL_STRING("Z", rightNode->lastName);
    TEST_ASSERT_EQUAL_STRING("Right", rightNode->firstName);
    TEST_ASSERT_EQUAL_INT(0, rightNode->appointmentCount);
    TEST_ASSERT_NULL(rightNode->appointments);
    TEST_ASSERT_NULL(rightNode->rightPatient);
    TEST_ASSERT_NULL(rightNode->leftPatient);

    TEST_ASSERT_EQUAL_PTR(indexer, rightNode->parentPatient);

    DeletePatientIndexer(&indexer);
}

TEST(TreeInsertion, TestInsertPatient_AlreadyExist) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "Z", "Exist");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* existing = indexer->rightPatient;

    TEST_ASSERT_NOT_NULL(existing);

    TEST_ASSERT_EQUAL_STRING("Z", existing->lastName);
    TEST_ASSERT_EQUAL_STRING("Exist", existing->firstName);
    TEST_ASSERT_EQUAL_INT(0, existing->appointmentCount);
    TEST_ASSERT_NULL(existing->appointments);
    TEST_ASSERT_NULL(existing->rightPatient);
    TEST_ASSERT_NULL(existing->leftPatient);

    TEST_ASSERT_EQUAL_PTR(indexer, existing->parentPatient);

    InsertPatient(&indexer, "Z", "Test");

    TEST_ASSERT_EQUAL_PTR(existing, indexer->rightPatient);
    TEST_ASSERT_NOT_NULL(indexer->rightPatient);
    TEST_ASSERT_EQUAL_STRING("Z", indexer->rightPatient->lastName);
    TEST_ASSERT_EQUAL_STRING("Exist", indexer->rightPatient->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->rightPatient->appointmentCount);
    TEST_ASSERT_NULL(indexer->rightPatient->appointments);
    TEST_ASSERT_NULL(indexer->rightPatient->rightPatient);
    TEST_ASSERT_NULL(indexer->rightPatient->leftPatient);

    TEST_ASSERT_EQUAL_PTR(indexer, indexer->rightPatient->parentPatient);

    DeletePatientIndexer(&indexer);
}

TEST(TreeInsertion, TestInsertPatient_InvalidName) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "7777", "@H3770");

    TEST_ASSERT_NULL(indexer);
}

TEST(TreeInsertion, TestInsertPatient_NULLName) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, NULL, NULL);

    TEST_ASSERT_NULL(indexer);
}