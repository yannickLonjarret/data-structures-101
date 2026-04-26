#include <stdlib.h>

#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(LinkedListSearch);

TEST_SETUP(LinkedListSearch) {}

TEST_TEAR_DOWN(LinkedListSearch) {}

TEST(LinkedListSearch, test_Search_Value_In_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(1, SearchValueInLine(lines[0], 2));

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListSearch, test_Search_Zero_After_Value_In_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 3));

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListSearch, test_Search_Zero_Before_Value_In_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 1));

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListSearch, test_Search_Value_In_Empty_Line) {
    MatrixLine* lines = CreateMatrixLines(1);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 3));

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListSearch, test_Search_Value_Beyond_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 5));

    DeleteMatrixLine(&lines[0]);
    free(lines);
}