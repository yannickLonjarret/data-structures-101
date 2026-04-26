#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(MemoryManagement) {
    RUN_TEST_CASE(MemoryManagement, TestCreateIndexerManager);
    RUN_TEST_CASE(MemoryManagement, TestCreatePatient);
    RUN_TEST_CASE(MemoryManagement, TestCreateAppointment);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientIndexer);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientFile);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointment);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointmentList);
}

TEST_GROUP_RUNNER(NodeRemoval) {
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileLeaf_RootNode);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileLeaf_LeftNode);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileLeaf_RightNode);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileLeaf_Failure);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientSingleChild_RootNodeLeftChild);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientSingleChild_RootNodeRightChild);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientSingleChild_RightChild);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientSingleChild_LeftChild);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileSingleChild_Failure);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileTwoChildren_RootNode);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileTwoChildren_RootNodeChildSuccessor);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileTwoChildren);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileTwoChildren_ChildSuccessor);
    RUN_TEST_CASE(NodeRemoval, TestRemovePatientFileTwoChildren_Failure);
}

TEST_GROUP_RUNNER(TreeInsertion) {
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_EmptyIndexer);
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_LeftPosition);
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_RightPosition);
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_AlreadyExist);
}

TEST_GROUP_RUNNER(TreeMinimum) {
    RUN_TEST_CASE(TreeMinimum, TestGetMinimumNullInput);
    RUN_TEST_CASE(TreeMinimum, TestGetMinimumNoChildNode);
    RUN_TEST_CASE(TreeMinimum, TestGetMinimum);
}

TEST_GROUP_RUNNER(TreeSearch) {
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_EmptyIndexer);
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_NotExist);
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_RootNode);
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_AnyNode);
}