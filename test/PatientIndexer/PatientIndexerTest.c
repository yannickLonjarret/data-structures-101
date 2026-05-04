#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(MemoryManagement) {
    RUN_TEST_CASE(MemoryManagement, TestCreateIndexerManager);
    RUN_TEST_CASE(MemoryManagement, TestCreateIndexerManager_NegativeIndexerCount);
    RUN_TEST_CASE(MemoryManagement, TestCreatePatient);
    RUN_TEST_CASE(MemoryManagement, TestCreatePatient_InvalidName);
    RUN_TEST_CASE(MemoryManagement, TestCreatePatient_NULLName);
    RUN_TEST_CASE(MemoryManagement, TestCreateAppointment);
    RUN_TEST_CASE(MemoryManagement, TestCreateAppointment_InvalidDate);
    RUN_TEST_CASE(MemoryManagement, TestCreateAppointment_NULLDate);
    RUN_TEST_CASE(MemoryManagement, TestCreateAppointment_NULLReason);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientIndexer);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientIndexer_NULLIndexer);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientIndexer_PointToNULL);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientFile);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientFile_NULLPatientFile);
    RUN_TEST_CASE(MemoryManagement, TestDeletePatientFile_PointToNULL);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointment);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointment_NULLAppointment);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointment_PointToNULL);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointmentList);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointmentList_NULLAppointmentList);
    RUN_TEST_CASE(MemoryManagement, TestDeleteAppointmentList_PointToNULL);
    RUN_TEST_CASE(MemoryManagement, TestDeleteIndexerManager);
    RUN_TEST_CASE(MemoryManagement, TestDeleteIndexerManager_NULLManager);
    RUN_TEST_CASE(MemoryManagement, TestDeleteIndexerManager_PointToNULL);
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
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_InvalidName);
    RUN_TEST_CASE(TreeInsertion, TestInsertPatient_NULLName);
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
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_NULLIndexer);
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_NULLName);
    RUN_TEST_CASE(TreeSearch, TestSearchPatient_InvalidName);
}

TEST_GROUP_RUNNER(DeepCopy) {
    RUN_TEST_CASE(DeepCopy, DeepCopyPatient_NULLOriginal);
    RUN_TEST_CASE(DeepCopy, DeepCopyPatient_NoAppointment);
    RUN_TEST_CASE(DeepCopy, DeepCopyPatient_Appointment);
    RUN_TEST_CASE(DeepCopy, DeepCopyAppointment_NULLOriginal);
    RUN_TEST_CASE(DeepCopy, DeepCopyAppointment_NULLCopy);
    RUN_TEST_CASE(DeepCopy, DeepCopyAppointment_ExpectedBehavior);
    RUN_TEST_CASE(DeepCopy, DeepCopyList_NULLOriginal);
    RUN_TEST_CASE(DeepCopy, DeepCopyList_NULLCopy);
    RUN_TEST_CASE(DeepCopy, DeepCopyList_ExpectedBehavior);
    RUN_TEST_CASE(DeepCopy, DeepCopyIndexer_NULLOriginal);
    RUN_TEST_CASE(DeepCopy, DeepCopyIndexer_NULLCopy);
    RUN_TEST_CASE(DeepCopy, DeepCopyIndexer_EmptyOriginal);
    RUN_TEST_CASE(DeepCopy, DeepCopyIndexer_NormalOriginal);
}