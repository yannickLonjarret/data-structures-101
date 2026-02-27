#include "unity.h"
#include "SparseMatrix.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_Create_Matrix_Element(void)
{
    MatrixElement* element = CreateMatrixElement(1, 2);
    TEST_ASSERT_NOT_NULL(element);
    TEST_ASSERT_EQUAL_INT(2, element->column);
    TEST_ASSERT_EQUAL_INT(1, element->value);
}
