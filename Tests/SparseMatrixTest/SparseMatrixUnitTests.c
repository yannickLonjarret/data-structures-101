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
    TEST_ASSERT_NULL(element->nextElement);
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

void test_Free_Matrix_Lines(void)
{
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(lines, element);
    DeleteMatrixLine(&lines[0]);

    TEST_ASSERT_NULL(lines[0]);
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

void test_Free_Sparse_Matrix(void)
{
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&matrix->lines[0], element);

    DeleteMatrix(&matrix);
    TEST_ASSERT_NULL(matrix);
}

void test_Insert_Element_At_Head(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_NOT_NULL(lines[0]);
    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(1, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
}

void test_Insert_Element_At_Tail(void){
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
}

void test_Insert_Element_At_Middle(void){
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
}

void test_Update_Element_Value(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    element = CreateMatrixElement(3, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(2, lines[0]->column);
    TEST_ASSERT_EQUAL_INT(3, lines[0]->value);

    DeleteMatrixLine(&lines[0]);
}

void test_Remove_Element_At_Head_Empty_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);

    UpdateSparseLine(&lines[0], element);
    RemoveSparseLineElement(&lines[0], 2);

    TEST_ASSERT_NULL(lines[0]);

    DeleteMatrixLine(&lines[0]);
}

void test_Remove_Element_At_Head_Filled_Line(void){
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
}

void test_Remove_Element_At_Tail(void){
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
}

void test_Remove_Element_At_Middle(void){
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
}

void test_Memory_Gain_Computation(void){
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);
    MatrixLine* lines = &matrix->lines[0];

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(lines, element);

    int gain = (9 * sizeof(int)) - (2*sizeof(int) + 3*sizeof(int) + 3*sizeof(int));
    TEST_ASSERT_EQUAL_INT(gain, ComputeMemoryGain(matrix));

    DeleteMatrix(&matrix);
}

void test_Search_Value_In_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(1, SearchValueInLine(lines[0], 2));

    DeleteMatrixLine(&lines[0]);
}

void test_Search_Zero_After_Value_In_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 3));

    DeleteMatrixLine(&lines[0]);
}

void test_Search_Zero_Before_Value_In_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 1));

    DeleteMatrixLine(&lines[0]);
}

void test_Search_Value_In_Empty_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 3));

    DeleteMatrixLine(&lines[0]);
}

void test_Search_Value_Beyond_Line(void){
    MatrixLine* lines = CreateMatrixLines(1);
    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(&lines[0], element);

    TEST_ASSERT_EQUAL_INT(0, SearchValueInLine(lines[0], 5));

    DeleteMatrixLine(&lines[0]);
}




    