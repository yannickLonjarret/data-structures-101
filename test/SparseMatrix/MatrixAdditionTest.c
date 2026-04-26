#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(MatrixAdd);

TEST_SETUP(MatrixAdd) {}

TEST_TEAR_DOWN(MatrixAdd) {}

TEST(MatrixAdd, test_Add_Matrix_Empty_Second_Line) {
    MatrixLine* linesA = CreateMatrixLines(1);
    MatrixLine* linesB = CreateMatrixLines(1);

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&linesA[0], element);

    AddMatrixLine(&linesA[0], &linesB[0]);
    TEST_ASSERT_NOT_NULL(linesA[0]);
    TEST_ASSERT_EQUAL_INT(2, linesA[0]->column);
    TEST_ASSERT_EQUAL_INT(1, linesA[0]->value);

    DeleteMatrixLine(&linesA[0]);
    DeleteMatrixLine(&linesB[0]);
    free(linesA);
    free(linesB);
}
TEST(MatrixAdd, test_Add_Matrix_Line_Merge) {
    MatrixLine* linesA = CreateMatrixLines(1);
    MatrixLine* linesB = CreateMatrixLines(1);

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&linesA[0], element);

    element = CreateMatrixElement(1, 3);
    UpdateSparseLine(&linesB[0], element);

    AddMatrixLine(&linesA[0], &linesB[0]);

    TEST_ASSERT_EQUAL_INT(2, linesA[0]->column);
    TEST_ASSERT_EQUAL_INT(1, linesA[0]->value);

    TEST_ASSERT_EQUAL_INT(3, linesA[0]->nextElement->column);
    TEST_ASSERT_EQUAL_INT(1, linesA[0]->nextElement->value);

    DeleteMatrixLine(&linesA[0]);
    DeleteMatrixLine(&linesB[0]);
    free(linesA);
    free(linesB);
}

TEST(MatrixAdd, test_Add_Matrix_Line_Sum) {
    MatrixLine* linesA = CreateMatrixLines(1);
    MatrixLine* linesB = CreateMatrixLines(1);

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&linesA[0], element);

    element = CreateMatrixElement(2, 2);
    UpdateSparseLine(&linesB[0], element);

    AddMatrixLine(&linesA[0], &linesB[0]);

    TEST_ASSERT_EQUAL_INT(2, linesA[0]->column);
    TEST_ASSERT_EQUAL_INT(3, linesA[0]->value);

    DeleteMatrixLine(&linesA[0]);
    DeleteMatrixLine(&linesB[0]);
    free(linesA);
    free(linesB);
}
