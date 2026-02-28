#include "unity.h"

extern void setUp(void);
extern void tearDown(void);
extern void test_Create_Matrix_Element(void);
extern void test_Free_Matrix_Element(void);
extern void test_Create_Matrix_Lines(void);
extern void test_Create_Sparse_Matrix(void);
extern void test_Insert_Element_At_Head(void);
extern void test_Insert_Element_At_Tail(void);
extern void test_Insert_Element_At_Middle(void);
extern void test_Remove_Element_At_Head_Empty_Line(void);
extern void test_Remove_Element_At_Head_Filled_Line(void);
extern void test_Remove_Element_At_Tail(void);
extern void test_Remove_Element_At_Middle(void);


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Create_Matrix_Element);
    RUN_TEST(test_Free_Matrix_Element);
    RUN_TEST(test_Create_Matrix_Lines);
    RUN_TEST(test_Create_Sparse_Matrix);

    RUN_TEST(test_Insert_Element_At_Head);
    RUN_TEST(test_Insert_Element_At_Tail);
    RUN_TEST(test_Insert_Element_At_Middle);

    RUN_TEST(test_Remove_Element_At_Head_Empty_Line);
    RUN_TEST(test_Remove_Element_At_Head_Filled_Line);
    RUN_TEST(test_Remove_Element_At_Tail);
    RUN_TEST(test_Remove_Element_At_Middle);
    return UNITY_END();
}