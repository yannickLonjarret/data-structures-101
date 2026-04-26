#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(TreeSearch);

TEST_SETUP(TreeSearch) {}

TEST_TEAR_DOWN(TreeSearch) {}

TEST(TreeSearch, TestSearchPatient_EmptyIndexer) {
    PatientIndexer indexer = NULL;

    PatientFile* searchResult = SearchPatientFile(&indexer, "Any");

    TEST_ASSERT_NULL(searchResult);
}

TEST(TreeSearch, TestSearchPatient_NotExist) {
    PatientIndexer indexer = CreatePatient("D", "Test");

    PatientFile* searchResult = SearchPatientFile(&indexer, "Any");

    TEST_ASSERT_NULL(searchResult);

    DeletePatientIndexer(&indexer);
}

TEST(TreeSearch, TestSearchPatient_RootNode) {
    PatientIndexer indexer = CreatePatient("D", "Test");

    PatientFile* searchResult = SearchPatientFile(&indexer, "D");

    TEST_ASSERT_NOT_NULL(searchResult);
    TEST_ASSERT_EQUAL_PTR(indexer, searchResult);

    TEST_ASSERT_EQUAL_STRING(indexer->firstName, searchResult->firstName);
    TEST_ASSERT_EQUAL_STRING(indexer->lastName, searchResult->lastName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->rightPatient);
    TEST_ASSERT_NULL(indexer->leftPatient);
    TEST_ASSERT_NULL(indexer->parentPatient);

    DeletePatientIndexer(&indexer);
}

TEST(TreeSearch, TestSearchPatient_AnyNode) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "B", "Search");
    InsertPatient(&indexer, "A", "Test");
    InsertPatient(&indexer, "C", "Test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* toSearch = indexer->leftPatient;
    PatientFile* searchResult = SearchPatientFile(&indexer, "B");

    TEST_ASSERT_EQUAL_PTR(toSearch, searchResult);
    TEST_ASSERT_NOT_NULL(searchResult);

    TEST_ASSERT_EQUAL_STRING("Search", searchResult->firstName);
    TEST_ASSERT_EQUAL_STRING("B", searchResult->lastName);
    TEST_ASSERT_EQUAL_INT(0, searchResult->appointmentCount);
    TEST_ASSERT_NULL(searchResult->appointments);
    TEST_ASSERT_EQUAL_PTR(toSearch->rightPatient, searchResult->rightPatient);
    TEST_ASSERT_EQUAL_PTR(toSearch->leftPatient, searchResult->leftPatient);
    TEST_ASSERT_EQUAL_PTR(toSearch->parentPatient, searchResult->parentPatient);

    DeletePatientIndexer(&indexer);
}
