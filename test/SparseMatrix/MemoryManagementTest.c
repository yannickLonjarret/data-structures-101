#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(MemoryManagement);

TEST_SETUP(MemoryManagement) {}

TEST_TEAR_DOWN(MemoryManagement) {}

TEST(MemoryManagement, test_Create_Matrix_Element) {
    MatrixElement* element = CreateMatrixElement(1, 2);

    TEST_ASSERT_NOT_NULL(element);
    TEST_ASSERT_NULL(element->nextElement);
    TEST_ASSERT_EQUAL_INT(2, element->column);
    TEST_ASSERT_EQUAL_INT(1, element->value);

    DeleteElement(&element);
}

TEST(MemoryManagement, test_Free_Matrix_Element) {
    MatrixElement* element = CreateMatrixElement(1, 2);
    TEST_ASSERT_NOT_NULL(element);
    DeleteElement(&element);
    TEST_ASSERT_NULL(element);
}

TEST(MemoryManagement, test_Create_Sparse_Matrix) {
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);

    TEST_ASSERT_NOT_NULL(matrix);
    TEST_ASSERT_NOT_NULL(matrix->lines);
    TEST_ASSERT_EQUAL_INT(3, matrix->lineCount);
    TEST_ASSERT_EQUAL_INT(3, matrix->columnCount);

    DeleteMatrix(&matrix);
}

TEST(MemoryManagement, test_Create_Matrix_Lines) {
    MatrixLine* lines = CreateMatrixLines(3);
    TEST_ASSERT_NOT_NULL(lines);
    for(int i = 0; i < 3; i++) {
        TEST_ASSERT_NULL(lines[i]);
        DeleteMatrixLine(&lines[i]);
    }
    free(lines);
}

TEST(MemoryManagement, test_Free_Matrix_Lines) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(lines, element);
    DeleteMatrixLine(&lines[0]);

    TEST_ASSERT_NULL(lines[0]);
    free(lines);
}

TEST(MemoryManagement, test_Free_Sparse_Matrix) {
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&matrix->lines[0], element);

    DeleteMatrix(&matrix);
    TEST_ASSERT_NULL(matrix);
}