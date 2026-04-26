#include <stdlib.h>

#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(LinkedListManip);

TEST_SETUP(LinkedListManip) {}

TEST_TEAR_DOWN(LinkedListManip) {}

TEST(LinkedListManip, test_Insert_Element_At_Head) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Insert_Element_At_Tail) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);
    element = CreateMatrixElement(1, 4);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_NOT_NULL(lines[0]->nextElement);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    TEST_ASSERT_EQUAL_INT(4, lines[0]->nextElement->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->nextElement->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Insert_Element_At_Middle) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(1, 4);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(1, 3);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_NOT_NULL(lines[0]->nextElement);
    TEST_ASSERT_NOT_NULL(lines[0]->nextElement->nextElement);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    TEST_ASSERT_EQUAL_INT(3, lines[0]->nextElement->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->nextElement->value);

    TEST_ASSERT_EQUAL_INT(4, lines[0]->nextElement->nextElement->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->nextElement->nextElement->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Update_Element_Value) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(3, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(3, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Remove_Element_At_Head_Empty_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);
    RemoveSparseLineElement(&lines[0], 2);

    TEST_ASSERT_NULL(lines[0]);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Remove_Element_At_Head_Filled_Line) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);
    element = CreateMatrixElement(1, 4);
    UpdateSparseLine(&lines[0], element);

    RemoveSparseLineElement(&lines[0], 2);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_NULL(lines[0]->nextElement);

    TEST_ASSERT_EQUAL_INT(4, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Remove_Element_At_Tail) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);
    element = CreateMatrixElement(1, 4);
    UpdateSparseLine(&lines[0], element);

    RemoveSparseLineElement(&lines[0], 4);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_NULL(lines[0]->nextElement);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}

TEST(LinkedListManip, test_Remove_Element_At_Middle) {
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(1, 4);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(1, 3);
    UpdateSparseLine(&lines[0], element);

    RemoveSparseLineElement(&lines[0], 3);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_NOT_NULL(lines[0]->nextElement);
    TEST_ASSERT_NULL(lines[0]->nextElement->nextElement);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    TEST_ASSERT_EQUAL_INT(4, lines[0]->nextElement->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->nextElement->value);

    DeleteMatrixLine(&lines[0]);
    free(lines);
}
