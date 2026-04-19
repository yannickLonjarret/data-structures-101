#include "PatientIndexer.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void TestCreateIndexerManager(void) {
    IndexerManager manager = CreateIndexerManager(2);

    TEST_ASSERT_EQUAL_INT(2, manager.indexerCount);

    for(int i = 0; i++; i < manager.indexerCount)
        TEST_ASSERT_NULL(manager.indexers[i]);

    DeleteIndexerManager(&manager);
}

void TestCreatePatient(void) {
    PatientFile* patient = CreatePatient("Freeman", "Gordon");

    TEST_ASSERT_EQUAL_INT(0, patient->appointmentCount);
    TEST_ASSERT_NULL(patient->appointments);

    TEST_ASSERT_NULL(patient->parentPatient);
    TEST_ASSERT_NULL(patient->leftPatient);
    TEST_ASSERT_NULL(patient->rightPatient);

    TEST_ASSERT_EQUAL_STRING("Freeman", patient->lastName);
    TEST_ASSERT_EQUAL_STRING("Gordon", patient->firstName);

    DeletePatientFile(&patient);
}

void TestCreateAppointment(void) {
    Appointment* appointment = CreateAppointment("04_18_26", "Fever", 0);

    TEST_ASSERT_EQUAL_INT(0, appointment->emergencyLevel);
    TEST_ASSERT_EQUAL_STRING("04_18_26", appointment->date);
    TEST_ASSERT_EQUAL_STRING("Fever", appointment->reason);

    TEST_ASSERT_NULL(appointment->nextAppointment);

    DeleteAppointment(&appointment);
}

void TestDeletePatientIndexer(void) {
    PatientFile* indexer = CreatePatient("D", "test");
    PatientFile* leftNode = CreatePatient("A", "test");
    PatientFile* rightNode = CreatePatient("Z", "test");

    indexer->leftPatient = leftNode;
    indexer->rightPatient = rightNode;

    DeletePatientIndexer(&indexer);

    TEST_ASSERT_NULL(indexer);
}

void TestDeletePatientFile(void) {
    PatientFile* patient = CreatePatient("Test", "test");

    DeletePatientFile(&patient);

    TEST_ASSERT_NULL(patient);
}

void TestDeleteAppointment(void) {
    Appointment* appointment = CreateAppointment("04_18_26", "Fever", 0);
    DeleteAppointment(&appointment);
    TEST_ASSERT_NULL(appointment);
}

void TestDeleteAppointmentList(void) {
    Appointment* appointment1 = CreateAppointment("04_18_26", "Fever", 0);
    Appointment* appointment2 = CreateAppointment("04_18_26", "Fever", 0);

    appointment1->nextAppointment = appointment2;

    DeleteAppointmentList(&appointment1);

    TEST_ASSERT_NULL(appointment1);
}

void TestInsertPatient_EmptyIndexer(void) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");

    TEST_ASSERT_EQUAL_STRING("D", indexer->lastName);
    TEST_ASSERT_EQUAL_STRING("Test", indexer->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->leftPatient);
    TEST_ASSERT_NULL(indexer->rightPatient);
    TEST_ASSERT_NULL(indexer->parentPatient);

    DeletePatientIndexer(&indexer);
}

void TestInsertPatient_LeftPosition(void) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "A", "Left");

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

void TestInsertPatient_RightPosition(void) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "Z", "Right");

    TEST_ASSERT_EQUAL_STRING("D", indexer->lastName);
    TEST_ASSERT_EQUAL_STRING("Test", indexer->firstName);
    TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
    TEST_ASSERT_NULL(indexer->appointments);
    TEST_ASSERT_NULL(indexer->leftPatient);

    TEST_ASSERT_NOT_NULL(indexer->rightPatient);
    if(indexer->rightPatient != NULL) {
        PatientFile* rightNode = indexer->rightPatient;
        TEST_ASSERT_EQUAL_STRING("Z", rightNode->lastName);
        TEST_ASSERT_EQUAL_STRING("Right", rightNode->firstName);
        TEST_ASSERT_EQUAL_INT(0, rightNode->appointmentCount);
        TEST_ASSERT_NULL(rightNode->appointments);
        TEST_ASSERT_NULL(rightNode->rightPatient);
        TEST_ASSERT_NULL(rightNode->leftPatient);

        TEST_ASSERT_EQUAL_PTR(indexer, rightNode->parentPatient);
    }
    DeletePatientIndexer(&indexer);
}

void TestInsertPatient_AlreadyExist(void) {
    PatientIndexer indexer = NULL;

    InsertPatient(&indexer, "D", "Test");
    InsertPatient(&indexer, "Z", "Exist");
    PatientFile* existing = indexer->rightPatient;

    TEST_ASSERT_NOT_NULL(existing);
    if(existing != NULL) {
        TEST_ASSERT_EQUAL_STRING("Z", existing->lastName);
        TEST_ASSERT_EQUAL_STRING("Exist", existing->firstName);
        TEST_ASSERT_EQUAL_INT(0, existing->appointmentCount);
        TEST_ASSERT_NULL(existing->appointments);
        TEST_ASSERT_NULL(existing->rightPatient);
        TEST_ASSERT_NULL(existing->leftPatient);

        TEST_ASSERT_EQUAL_PTR(indexer, existing->parentPatient);
    }
    InsertPatient(&indexer, "Z", "Test");

    TEST_ASSERT_EQUAL_PTR(existing, indexer->rightPatient);
    TEST_ASSERT_NOT_NULL(indexer->rightPatient);
    if(indexer->rightPatient != NULL) {
        TEST_ASSERT_EQUAL_STRING("Z", indexer->rightPatient->lastName);
        TEST_ASSERT_EQUAL_STRING("Exist", indexer->rightPatient->firstName);
        TEST_ASSERT_EQUAL_INT(0, indexer->rightPatient->appointmentCount);
        TEST_ASSERT_NULL(indexer->rightPatient->appointments);
        TEST_ASSERT_NULL(indexer->rightPatient->rightPatient);
        TEST_ASSERT_NULL(indexer->rightPatient->leftPatient);

        TEST_ASSERT_EQUAL_PTR(indexer, indexer->rightPatient->parentPatient);
    }

    DeletePatientIndexer(&indexer);
}

void TestSearchPatient_EmptyIndexer(void) {
    PatientIndexer indexer = NULL;

    PatientFile* searchResult = SearchPatientFile(&indexer, "Any");

    TEST_ASSERT_NULL(searchResult);
}

void TestSearchPatient_NotExist(void) {
    PatientIndexer indexer = CreatePatient("D", "Test");

    PatientFile* searchResult = SearchPatientFile(&indexer, "Any");

    TEST_ASSERT_NULL(searchResult);

    DeletePatientIndexer(&indexer);
}

void TestSearchPatient_RootNode(void) {
    PatientIndexer indexer = CreatePatient("D", "Test");

    PatientFile* searchResult = SearchPatientFile(&indexer, "D");

    TEST_ASSERT_NOT_NULL(searchResult);
    TEST_ASSERT_EQUAL_PTR(indexer, searchResult);
    if(searchResult != NULL) {
        TEST_ASSERT_EQUAL_STRING(indexer->firstName, searchResult->firstName);
        TEST_ASSERT_EQUAL_STRING(indexer->lastName, searchResult->lastName);
        TEST_ASSERT_EQUAL_INT(0, indexer->appointmentCount);
        TEST_ASSERT_NULL(indexer->appointments);
        TEST_ASSERT_NULL(indexer->rightPatient);
        TEST_ASSERT_NULL(indexer->leftPatient);
        TEST_ASSERT_NULL(indexer->parentPatient);
    }
    DeletePatientIndexer(&indexer);
}

void TestSearchPatient_AnyNode(void) {
    PatientIndexer indexer = CreatePatient("D", "Test");

    InsertPatient(&indexer, "B", "Search");
    InsertPatient(&indexer, "A", "Test");
    InsertPatient(&indexer, "C", "Test");

    PatientFile* toSearch = indexer->leftPatient;
    PatientFile* searchResult = SearchPatientFile(&indexer, "B");

    TEST_ASSERT_EQUAL_PTR(toSearch, searchResult);
    TEST_ASSERT_NOT_NULL(searchResult);
    if(searchResult != NULL) {
        TEST_ASSERT_EQUAL_STRING("Search", searchResult->firstName);
        TEST_ASSERT_EQUAL_STRING("B", searchResult->lastName);
        TEST_ASSERT_EQUAL_INT(0, searchResult->appointmentCount);
        TEST_ASSERT_NULL(searchResult->appointments);
        TEST_ASSERT_EQUAL_PTR(toSearch->rightPatient, searchResult->rightPatient);
        TEST_ASSERT_EQUAL_PTR(toSearch->leftPatient, searchResult->leftPatient);
        TEST_ASSERT_EQUAL_PTR(toSearch->parentPatient, searchResult->parentPatient);
    }
    DeletePatientIndexer(&indexer);
}

void TestRemovePatientFileLeaf_RootNode(void) {
    PatientFile* patient = CreatePatient("D", "test");
    PatientIndexer indexer = patient;

    int error = RemovePatientFileLeaf(&indexer, patient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NULL(indexer);

    DeletePatientFile(&patient);
}

void TestRemovePatientFileLeaf_LeftNode(void) {
    PatientIndexer indexer = CreatePatient("D", "test");
    InsertPatient(&indexer, "A", "test");
    PatientFile* patient = indexer->leftPatient;

    int error = RemovePatientFileLeaf(&indexer, patient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_NULL(indexer->leftPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patient);
}

void TestRemovePatientFileLeaf_RightNode(void) {
    PatientIndexer indexer = CreatePatient("D", "test");
    InsertPatient(&indexer, "Z", "test");
    PatientFile* patient = indexer->rightPatient;
    int error = RemovePatientFileLeaf(&indexer, indexer->rightPatient);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_NOT_NULL(indexer);
    TEST_ASSERT_NULL(indexer->rightPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patient);
}

void TestRemovePatientFileLeaf_Failure(void) {
    PatientIndexer indexer = NULL;
    PatientFile* patientToRemove = CreatePatient("A", "Test");

    int error = RemovePatientFileLeaf(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);
    DeletePatientFile(&patientToRemove);

    error = RemovePatientFileLeaf(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);
}

void TestRemovePatientSingleChild_RootNodeLeftChild(void) {
    PatientIndexer indexer = CreatePatient("B", "test");
    InsertPatient(&indexer, "A", "test");
    PatientFile* patientToRemove = indexer;
    PatientFile* replacement = indexer->leftPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement);
    TEST_ASSERT_NULL(replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

void TestRemovePatientSingleChild_RootNodeRightChild(void) {
    PatientIndexer indexer = CreatePatient("A", "test");
    InsertPatient(&indexer, "B", "test");
    PatientFile* patientToRemove = indexer;
    PatientFile* replacement = indexer->rightPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement);
    TEST_ASSERT_NULL(replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

void TestRemovePatientSingleChild_RightChild(void) {
    PatientIndexer indexer = CreatePatient("A", "test");
    InsertPatient(&indexer, "B", "test");
    InsertPatient(&indexer, "C", "test");
    PatientFile* patientToRemove = indexer->rightPatient;
    PatientFile* replacement = patientToRemove->rightPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(replacement, indexer->rightPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

void TestRemovePatientSingleChild_LeftChild(void) {
    PatientIndexer indexer = CreatePatient("C", "test");
    InsertPatient(&indexer, "B", "test");
    InsertPatient(&indexer, "A", "test");
    PatientFile* patientToRemove = indexer->leftPatient;
    PatientFile* replacement = patientToRemove->leftPatient;

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);

    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_PTR(replacement, indexer->leftPatient);
    TEST_ASSERT_EQUAL_PTR(indexer, replacement->parentPatient);

    DeletePatientIndexer(&indexer);
    DeletePatientFile(&patientToRemove);
}

void TestRemovePatientFileSingleChild_Failure(void) {
    PatientIndexer indexer = NULL;
    PatientFile* patientToRemove = CreatePatient("A", "Test");

    int error = RemovePatientFileSingleChild(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);
    DeletePatientFile(&patientToRemove);

    error = RemovePatientFileSingleChild(&indexer, patientToRemove);
    TEST_ASSERT_EQUAL_INT(1, error);
}

void TestRemovePatientFileTwoChildren_RootNode(void) {
    PatientIndexer indexer = CreatePatient("L", "test");
    InsertPatient(&indexer, "R", "test");
    InsertPatient(&indexer, "E", "test");
    InsertPatient(&indexer, "O", "test");
    InsertPatient(&indexer, "P", "test");
    InsertPatient(&indexer, "V", "test");

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

