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

    DeleteElement(&element);
}

void test_Free_Matrix_Element(void)
{
    MatrixElement* element = CreateMatrixElement(1, 2);
    TEST_ASSERT_NOT_NULL(element);
    DeleteElement(&element);
    TEST_ASSERT_NULL(element);
}

void test_Create_Matrix_Lines(void)
{
    MatrixLine* lines = CreateMatrixLines(3);
    TEST_ASSERT_NOT_NULL(lines);
    for(int i = 0; i < 3; i++)
    {
        TEST_ASSERT_NULL(lines[i]);
        DeleteMatrixLine(&lines[i]);
    }
}
}

void test_Create_Sparse_Matrix(void)
{
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);
    
    TEST_ASSERT_NOT_NULL(matrix);
    TEST_ASSERT_NOT_NULL(matrix->lines);
    TEST_ASSERT_EQUAL_INT(3, matrix->lineCount);
    TEST_ASSERT_EQUAL_INT(3, matrix->columnCount);

    DeleteMatrix(&matrix);
}
}