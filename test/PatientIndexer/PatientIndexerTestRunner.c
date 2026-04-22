#include "unity.h"

extern void setUp(void);
extern void tearDown(void);

extern void TestCreateIndexerManager(void);
extern void TestCreatePatient(void);
extern void TestCreateAppointment(void);
extern void TestDeletePatientIndexer(void);
extern void TestDeletePatientFile(void);
extern void TestDeleteAppointment(void);
extern void TestDeleteAppointmentList(void);
extern void TestInsertPatient_EmptyIndexer(void);
extern void TestInsertPatient_LeftPosition(void);
extern void TestInsertPatient_RightPosition(void);
extern void TestInsertPatient_AlreadyExist(void);
extern void TestSearchPatient_EmptyIndexer(void);
extern void TestSearchPatient_NotExist(void);
extern void TestSearchPatient_RootNode(void);
extern void TestSearchPatient_AnyNode(void);
extern void TestRemovePatientFileLeaf_RootNode(void);
extern void TestRemovePatientFileLeaf_LeftNode(void);
extern void TestRemovePatientFileLeaf_RightNode(void);
extern void TestRemovePatientFileLeaf_Failure(void);
extern void TestRemovePatientSingleChild_RootNodeLeftChild(void);
extern void TestRemovePatientSingleChild_RootNodeRightChild(void);
extern void TestRemovePatientSingleChild_RightChild(void);
extern void TestRemovePatientSingleChild_LeftChild(void);
extern void TestRemovePatientFileSingleChild_Failure(void);
extern void TestRemovePatientFileTwoChildren(void);
extern void TestRemovePatientFileTwoChildren_ChildSuccessor(void);
extern void TestRemovePatientFileTwoChildren_RootNodeChildSuccessor(void);
extern void TestRemovePatientFileTwoChildren_RootNode(void);
extern void TestRemovePatientFileTwoChildren_Failure(void);
extern void TestGetMinimum(void);
extern void TestGetMinimumNoChildNode(void);
extern void TestGetMinimumNullInput(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(TestCreateIndexerManager);
    RUN_TEST(TestCreatePatient);
    RUN_TEST(TestCreateAppointment);
    RUN_TEST(TestDeletePatientIndexer);
    RUN_TEST(TestDeletePatientFile);
    RUN_TEST(TestDeleteAppointment);
    RUN_TEST(TestDeleteAppointmentList);
    RUN_TEST(TestInsertPatient_EmptyIndexer);
    RUN_TEST(TestInsertPatient_LeftPosition);
    RUN_TEST(TestInsertPatient_RightPosition);
    RUN_TEST(TestInsertPatient_AlreadyExist);
    RUN_TEST(TestSearchPatient_EmptyIndexer);
    RUN_TEST(TestSearchPatient_NotExist);
    RUN_TEST(TestSearchPatient_RootNode);
    RUN_TEST(TestSearchPatient_AnyNode);

    RUN_TEST(TestRemovePatientFileLeaf_RootNode);
    RUN_TEST(TestRemovePatientFileLeaf_LeftNode);
    RUN_TEST(TestRemovePatientFileLeaf_RightNode);
    RUN_TEST(TestRemovePatientFileLeaf_Failure);

    RUN_TEST(TestRemovePatientSingleChild_RootNodeLeftChild);
    RUN_TEST(TestRemovePatientSingleChild_RootNodeRightChild);
    RUN_TEST(TestRemovePatientSingleChild_RightChild);
    RUN_TEST(TestRemovePatientSingleChild_LeftChild);
    RUN_TEST(TestRemovePatientFileSingleChild_Failure);

    RUN_TEST(TestRemovePatientFileTwoChildren);
    RUN_TEST(TestRemovePatientFileTwoChildren_ChildSuccessor);
    RUN_TEST(TestRemovePatientFileTwoChildren_RootNodeChildSuccessor);
    RUN_TEST(TestRemovePatientFileTwoChildren_RootNode);
    RUN_TEST(TestRemovePatientFileTwoChildren_Failure);

    RUN_TEST(TestGetMinimum);
    RUN_TEST(TestGetMinimumNoChildNode);
    RUN_TEST(TestGetMinimumNullInput);
    return UNITY_END();
}