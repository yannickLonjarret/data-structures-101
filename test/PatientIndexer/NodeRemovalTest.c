#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(NodeRemoval);

TEST_SETUP(NodeRemoval) {}

TEST_TEAR_DOWN(NodeRemoval) {}

TEST(NodeRemoval, TestRemovePatientFileLeaf_RootNode) {
    PatientFile* patient = CreatePatient("D", "test");
    PatientIndexer indexer = patient;

    int error = RemovePatientFileLeaf(&indexer, patient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NULL(indexer);

    DeletePatientFile(&patient);
}

TEST(NodeRemoval, TestRemovePatientFileLeaf_LeftNode) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "D", "test");
    InsertPatient(&indexer, "A", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patient = indexer->leftPatient;

    int error = RemovePatientFileLeaf(&indexer, patient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_NULL(indexer->leftPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patient);
}

TEST(NodeRemoval, TestRemovePatientFileLeaf_RightNode) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "D", "test");
    InsertPatient(&indexer, "Z", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patient = indexer->rightPatient;
    int error = RemovePatientFileLeaf(&indexer, indexer->rightPatient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_NULL(indexer->rightPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patient);
}

TEST(NodeRemoval, TestRemovePatientFileLeaf_Failure) {
    PatientIndexer indexer = NULL;
    PatientFile* patientToRemove = CreatePatient("A", "Test");

    TEST_ASSERT_NOT_NULL(patientToRemove);
    int error = RemovePatientFileLeaf(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);

    error = RemovePatientFileLeaf(&patientToRemove, NULL);
    TEST_ASSERT_EQUAL_INT(1, error);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientSingleChild_RootNodeLeftChild) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "B", "test");
    InsertPatient(&indexer, "A", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer;
    PatientFile* replacement = indexer->leftPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement);
    TEST_ASSERT_NULL(replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientSingleChild_RootNodeRightChild) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "A", "test");
    InsertPatient(&indexer, "B", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer;
    PatientFile* replacement = indexer->rightPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement);
    TEST_ASSERT_NULL(replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientSingleChild_RightChild) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "A", "test");
    InsertPatient(&indexer, "B", "test");
    InsertPatient(&indexer, "C", "test");
    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer->rightPatient;
    PatientFile* replacement = patientToRemove->rightPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(replacement, indexer->rightPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientSingleChild_LeftChild) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "C", "test");
    InsertPatient(&indexer, "B", "test");
    InsertPatient(&indexer, "A", "test");
    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer->leftPatient;
    PatientFile* replacement = patientToRemove->leftPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(replacement, indexer->leftPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileSingleChild_Failure) {
    PatientIndexer indexer = NULL;
    PatientFile* patientToRemove = CreatePatient("A", "Test");
    TEST_ASSERT_NOT_NULL(patientToRemove);
    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);

    error = RemovePatientFileSingleChild(&patientToRemove, NULL);
    TEST_ASSERT_EQUAL_INT(1, error);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileTwoChildren_RootNode) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "L", "test");
    InsertPatient(&indexer, "R", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "O", "test");
    InsertPatient(&indexer, "P", "test");
    InsertPatient(&indexer, "V", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer;
    PatientFile* leftSubtree = indexer->leftPatient;
    PatientFile* rightSubtree = indexer->rightPatient;
    PatientFile* successor = GetMinimum(indexer->rightPatient);
    TEST_ASSERT_NOT_NULL(successor);
    PatientFile* successorParent = successor->parentPatient;
    PatientFile* successorRightSubtree = successor->rightPatient;

    int error = RemovePatientFileTwoChildren(&indexer, indexer);

    TEST_ASSERT_EQUAL_INT(0, error);

    TEST_ASSERT_EQUAL_PTR(successor, indexer);
    TEST_ASSERT_EQUAL_PTR(leftSubtree, indexer->leftPatient);
    TEST_ASSERT_EQUAL_PTR(rightSubtree, indexer->rightPatient);
    TEST_ASSERT_NULL(indexer->parentPatient);

    TEST_ASSERT_EQUAL_PTR(successorRightSubtree, successorParent->leftPatient);
    TEST_ASSERT_EQUAL_PTR(successorParent, successorRightSubtree->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileTwoChildren_RootNodeChildSuccessor) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "L", "test");
    InsertPatient(&indexer, "R", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "Z", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer;
    PatientFile* leftSubtree = indexer->leftPatient;
    PatientFile* successor = GetMinimum(indexer->rightPatient);
    TEST_ASSERT_NOT_NULL(successor);
    PatientFile* successorRightSubtree = successor->rightPatient;

    int error = RemovePatientFileTwoChildren(&indexer, indexer);

    TEST_ASSERT_EQUAL_INT(0, error);

    TEST_ASSERT_EQUAL_PTR(successor, indexer);
    TEST_ASSERT_EQUAL_PTR(leftSubtree, indexer->leftPatient);
    TEST_ASSERT_EQUAL_PTR(successorRightSubtree, indexer->rightPatient);
    TEST_ASSERT_NULL(indexer->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileTwoChildren) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "A", "test");
    InsertPatient(&indexer, "L", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "O", "test");
    InsertPatient(&indexer, "M", "test");
    InsertPatient(&indexer, "N", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer->rightPatient;

    TEST_ASSERT_NOT_NULL(patientToRemove);
    PatientFile* leftSubtree = patientToRemove->leftPatient;
    PatientFile* rightSubtree = patientToRemove->rightPatient;
    PatientFile* successor = GetMinimum(patientToRemove->rightPatient);
    TEST_ASSERT_NOT_NULL(successor);
    TEST_ASSERT_NOT_NULL(successor->parentPatient);
    PatientFile* successorParent = successor->parentPatient;
    PatientFile* successorRightSubtree = successor->rightPatient;

    int error = RemovePatientFileTwoChildren(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);

    TEST_ASSERT_EQUAL_PTR(successor, indexer->rightPatient);
    TEST_ASSERT_EQUAL_PTR(leftSubtree, successor->leftPatient);
    TEST_ASSERT_EQUAL_PTR(rightSubtree, successor->rightPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, successor->parentPatient);

    TEST_ASSERT_EQUAL_PTR(successorRightSubtree, successorParent->leftPatient);
    TEST_ASSERT_EQUAL_PTR(successorParent, successorRightSubtree->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileTwoChildren_ChildSuccessor) {
    PatientIndexer indexer = NULL;
    InsertPatient(&indexer, "A", "test");
    InsertPatient(&indexer, "L", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "O", "test");
    InsertPatient(&indexer, "V", "test");

    TEST_ASSERT_NOT_NULL(indexer);
    PatientFile* patientToRemove = indexer->rightPatient;

    TEST_ASSERT_NOT_NULL(patientToRemove);
    PatientFile* leftSubtree = patientToRemove->leftPatient;
    PatientFile* successor = GetMinimum(patientToRemove->rightPatient);
    TEST_ASSERT_NOT_NULL(successor);
    PatientFile* successorRightSubtree = successor->rightPatient;

    int error = RemovePatientFileTwoChildren(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);

    TEST_ASSERT_EQUAL_PTR(successor, indexer->rightPatient);
    TEST_ASSERT_EQUAL_PTR(leftSubtree, successor->leftPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, successor->parentPatient);

    TEST_ASSERT_EQUAL_PTR(successorRightSubtree, successor->rightPatient);
    TEST_ASSERT_EQUAL_PTR(successor, successorRightSubtree->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

TEST(NodeRemoval, TestRemovePatientFileTwoChildren_Failure) {
    PatientIndexer indexer = NULL;
    PatientFile* patientToRemove = CreatePatient("A", "Test");

    TEST_ASSERT_NOT_NULL(patientToRemove);
    int error = RemovePatientFileTwoChildren(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);

    error = RemovePatientFileTwoChildren(&patientToRemove, NULL);
    TEST_ASSERT_EQUAL_INT(1, error);

    DeletePatientFile(&patientToRemove);
}