#include "unity.h"

extern void setUp(void);
extern void tearDown(void);
extern void test_Create_Matrix_Element(void);
extern void test_Free_Matrix_Element(void);
extern void test_Create_Matrix_Lines(void);
extern void test_Free_Matrix_Lines(void);
extern void test_Create_Sparse_Matrix(void);
extern void test_Free_Sparse_Matrix(void);
extern void test_Insert_Element_At_Head(void);
extern void test_Insert_Element_At_Tail(void);
extern void test_Insert_Element_At_Middle(void);
extern void test_Update_Element_Value(void);

extern void test_Remove_Element_At_Head_Empty_Line(void);
extern void test_Remove_Element_At_Head_Filled_Line(void);
extern void test_Remove_Element_At_Tail(void);
extern void test_Remove_Element_At_Middle(void);
extern void test_Memory_Gain_Computation(void);

extern void test_Put_Zero_In_Line_At_Head_Empty_Line(void);
extern void test_Put_Zero_In_Line_At_Head_Non_Empty_Line(void);
extern void test_Put_Zero_In_Line_At_Middle(void);
extern void test_Put_Value_In_Line_At_Head(void);
extern void test_Put_Value_In_Line_At_Middle(void);
extern void test_Put_Update_Value_In_Line(void);
extern void test_Put_Value_Line_Out_Of_Bounds(void);
extern void test_Put_Value_Column_Out_Of_Bounds(void);

extern void test_Search_Value_In_Line(void);
extern void test_Search_Zero_After_Value_In_Line(void);
extern void test_Search_Zero_Before_Value_In_Line(void);
extern void test_Search_Value_In_Empty_Line(void);
extern void test_Search_Value_Beyond_Line(void);

extern void test_Add_Matrix_Empty_Lines(void);
extern void test_Add_Matrix_Empty_First_Line(void);
extern void test_Add_Matrix_Empty_Second_Line(void);
extern void test_Add_Matrix_Line_Merge(void);
extern void test_Add_Matrix_Line_Sum(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Create_Matrix_Element);
    RUN_TEST(test_Free_Matrix_Element);
    RUN_TEST(test_Create_Matrix_Lines);
    RUN_TEST(test_Free_Matrix_Lines);
    RUN_TEST(test_Create_Sparse_Matrix);
    RUN_TEST(test_Free_Sparse_Matrix);

    RUN_TEST(test_Insert_Element_At_Head);
    RUN_TEST(test_Insert_Element_At_Tail);
    RUN_TEST(test_Insert_Element_At_Middle);
    RUN_TEST(test_Update_Element_Value);

    RUN_TEST(test_Remove_Element_At_Head_Empty_Line);
    RUN_TEST(test_Remove_Element_At_Head_Filled_Line);
    RUN_TEST(test_Remove_Element_At_Tail);
    RUN_TEST(test_Remove_Element_At_Middle);

    RUN_TEST(test_Memory_Gain_Computation);

    RUN_TEST(test_Search_Value_In_Line);
    RUN_TEST(test_Search_Zero_After_Value_In_Line);
    RUN_TEST(test_Search_Zero_Before_Value_In_Line);
    RUN_TEST(test_Search_Value_In_Empty_Line);
    RUN_TEST(test_Search_Value_Beyond_Line);

    RUN_TEST(test_Add_Matrix_Empty_Lines);
    RUN_TEST(test_Add_Matrix_Empty_First_Line);
    RUN_TEST(test_Add_Matrix_Empty_Second_Line);
    RUN_TEST(test_Add_Matrix_Line_Merge);
    RUN_TEST(test_Add_Matrix_Line_Sum);

    RUN_TEST(test_Put_Zero_In_Line_At_Head_Empty_Line);
    RUN_TEST(test_Put_Zero_In_Line_At_Head_Non_Empty_Line);
    RUN_TEST(test_Put_Zero_In_Line_At_Middle);
    RUN_TEST(test_Put_Value_In_Line_At_Head);
    RUN_TEST(test_Put_Value_In_Line_At_Middle);
    RUN_TEST(test_Put_Update_Value_In_Line);
    RUN_TEST(test_Put_Value_Line_Out_Of_Bounds);
    RUN_TEST(test_Put_Value_Column_Out_Of_Bounds);
    return UNITY_END();
}