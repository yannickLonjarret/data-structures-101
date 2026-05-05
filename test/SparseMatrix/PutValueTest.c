#include <stdlib.h>

#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(PutValueTest);

TEST_SETUP(PutValueTest) {}

TEST_TEAR_DOWN(PutValueTest) {}

TEST(PutValueTest, test_Put_Zero_In_Line_At_Head_Empty_Line) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 1);
    MatrixElement* element = CreateMatrixElement(1, 0);
    UpdateSparseLine(&matrix->lines[0], element);

    PutValue(matrix, 0, 0, 0);

    TEST_ASSERT_NULL(matrix->lines[0]);
    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Zero_In_Line_At_Head_Non_Empty_Line) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    MatrixElement* element = CreateMatrixElement(1, 0);
    UpdateSparseLine(&matrix->lines[0], element);

    element = CreateMatrixElement(1, 1);
    UpdateSparseLine(&matrix->lines[0], element);

    element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&matrix->lines[0], element);

    PutValue(matrix, 0, 0, 0);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->value);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->column);
    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Zero_In_Line_At_Middle) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    MatrixElement* element = CreateMatrixElement(1, 0);
    UpdateSparseLine(&matrix->lines[0], element);

    element = CreateMatrixElement(1, 1);
    UpdateSparseLine(&matrix->lines[0], element);

    element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&matrix->lines[0], element);

    PutValue(matrix, 0, 1, 0);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->value);
    TEST_ASSERT_EQUAL_INT(0, matrix->lines[0]->column);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]->nextElement);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->nextElement->value);
    TEST_ASSERT_EQUAL_INT(2, matrix->lines[0]->nextElement->column);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Value_In_Line_At_Head) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    PutValue(matrix, 0, 1, 1);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->value);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->column);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Value_In_Line_At_Middle) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    PutValue(matrix, 0, 0, 1);
    PutValue(matrix, 0, 2, 1);

    PutValue(matrix, 0, 1, 1);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->value);
    TEST_ASSERT_EQUAL_INT(0, matrix->lines[0]->column);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]->nextElement);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->nextElement->value);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->nextElement->column);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]->nextElement->nextElement);
    TEST_ASSERT_EQUAL_INT(1, matrix->lines[0]->nextElement->nextElement->value);
    TEST_ASSERT_EQUAL_INT(2, matrix->lines[0]->nextElement->nextElement->column);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Update_Value_In_Line) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    PutValue(matrix, 0, 0, 1);

    PutValue(matrix, 0, 0, 2);

    TEST_ASSERT_NOT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(2, matrix->lines[0]->value);
    TEST_ASSERT_EQUAL_INT(0, matrix->lines[0]->column);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Value_Line_Out_Of_Bounds) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    PutValue(matrix, 1, 0, 1);

    TEST_ASSERT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lineCount);
    TEST_ASSERT_EQUAL_INT(3, matrix->columnCount);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Put_Value_Column_Out_Of_Bounds) {
    SparseMatrix* matrix = CreateSparseMatrix(1, 3);
    PutValue(matrix, 0, 3, 1);

    TEST_ASSERT_NULL(matrix->lines[0]);
    TEST_ASSERT_EQUAL_INT(1, matrix->lineCount);
    TEST_ASSERT_EQUAL_INT(3, matrix->columnCount);

    DeleteMatrix(&matrix);
}

TEST(PutValueTest, test_Add_Matrix_Empty_Lines) {
    MatrixLine* linesA = CreateMatrixLines(1);
    MatrixLine* linesB = CreateMatrixLines(1);

    AddMatrixLine(&linesA[0], &linesB[0]);
    TEST_ASSERT_NULL(linesA[0]);

    DeleteMatrixLine(&linesA[0]);
    DeleteMatrixLine(&linesB[0]);
    free(linesA);
    free(linesB);
}

TEST(PutValueTest, test_Add_Matrix_Empty_First_Line) {
    MatrixLine* linesA = CreateMatrixLines(1);
    MatrixLine* linesB = CreateMatrixLines(1);

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&linesB[0], element);

    AddMatrixLine(&linesA[0], &linesB[0]);
    TEST_ASSERT_NOT_NULL(linesA[0]);
    TEST_ASSERT_EQUAL_INT(2, linesA[0]->column);
    TEST_ASSERT_EQUAL_INT(1, linesA[0]->value);

    DeleteMatrixLine(&linesA[0]);
    DeleteMatrixLine(&linesB[0]);
    free(linesA);
    free(linesB);
}
