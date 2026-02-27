#include "unity.h"

extern void setUp(void);
extern void tearDown(void);
extern void test_Create_Matrix_Element(void);
extern void test_Free_Matrix_Element(void);
extern void test_Create_Matrix_Lines(void);
extern void test_Create_Sparse_Matrix(void);


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Create_Matrix_Element);
    RUN_TEST(test_Free_Matrix_Element);
    RUN_TEST(test_Create_Matrix_Lines);
    RUN_TEST(test_Create_Sparse_Matrix);

    return UNITY_END();
}