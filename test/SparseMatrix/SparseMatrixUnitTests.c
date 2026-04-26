#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LinkedListManip) {
    RUN_TEST_CASE(LinkedListManip, test_Insert_Element_At_Head);
    RUN_TEST_CASE(LinkedListManip, test_Insert_Element_At_Tail);
    RUN_TEST_CASE(LinkedListManip, test_Insert_Element_At_Middle);
    RUN_TEST_CASE(LinkedListManip, test_Update_Element_Value);
    RUN_TEST_CASE(LinkedListManip, test_Remove_Element_At_Head_Empty_Line);
    RUN_TEST_CASE(LinkedListManip, test_Remove_Element_At_Head_Filled_Line);
    RUN_TEST_CASE(LinkedListManip, test_Remove_Element_At_Tail);
    RUN_TEST_CASE(LinkedListManip, test_Remove_Element_At_Middle);
}

TEST_GROUP_RUNNER(LinkedListSearch) {
    RUN_TEST_CASE(LinkedListSearch, test_Search_Value_In_Line);
    RUN_TEST_CASE(LinkedListSearch, test_Search_Zero_After_Value_In_Line);
    RUN_TEST_CASE(LinkedListSearch, test_Search_Zero_Before_Value_In_Line);
    RUN_TEST_CASE(LinkedListSearch, test_Search_Value_In_Empty_Line);
    RUN_TEST_CASE(LinkedListSearch, test_Search_Value_Beyond_Line);
}

TEST_GROUP_RUNNER(MatrixAdd) {
    RUN_TEST_CASE(MatrixAdd, test_Add_Matrix_Empty_Second_Line);
    RUN_TEST_CASE(MatrixAdd, test_Add_Matrix_Line_Merge);
    RUN_TEST_CASE(MatrixAdd, test_Add_Matrix_Line_Sum);
}

TEST_GROUP_RUNNER(MemoryManagement) {
    RUN_TEST_CASE(MemoryManagemet, test_Create_Matrix_Element);
    RUN_TEST_CASE(MemoryManagemet, test_Free_Matrix_Element);
    RUN_TEST_CASE(MemoryManagemet, test_Create_Sparse_Matrix);
    RUN_TEST_CASE(MemoryManagemet, test_Create_Matrix_Lines);
    RUN_TEST_CASE(MemoryManagemet, test_Free_Matrix_Lines);
    RUN_TEST_CASE(MemoryManagemet, test_Free_Sparse_Matrix);
}

TEST_GROUP_RUNNER(Misc) { RUN_TEST_CASE(Misc, test_Memory_Gain_Computation); }

TEST_GROUP_RUNNER(PutValueTest) {
    RUN_TEST_CASE(PutValueTest, test_Put_Zero_In_Line_At_Head_Empty_Line);
    RUN_TEST_CASE(PutValueTest, test_Put_Zero_In_Line_At_Head_Non_Empty_Line);
    RUN_TEST_CASE(PutValueTest, test_Put_Zero_In_Line_At_Middle);
    RUN_TEST_CASE(PutValueTest, test_Put_Value_In_Line_At_Head);
    RUN_TEST_CASE(PutValueTest, test_Put_Value_In_Line_At_Middle);
    RUN_TEST_CASE(PutValueTest, test_Put_Update_Value_In_Line);
    RUN_TEST_CASE(PutValueTest, test_Put_Value_Line_Out_Of_Bounds);
    RUN_TEST_CASE(PutValueTest, test_Put_Value_Column_Out_Of_Bounds);
    RUN_TEST_CASE(PutValueTest, test_Add_Matrix_Empty_Lines);
    RUN_TEST_CASE(PutValueTest, test_Add_Matrix_Empty_First_Line);
}
