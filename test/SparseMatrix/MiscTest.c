#include <stdlib.h>

#include "SparseMatrix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Misc);

TEST_SETUP(Misc) {}

TEST_TEAR_DOWN(Misc) {}

TEST(Misc, test_Memory_Gain_Computation) {
    SparseMatrix* matrix = CreateSparseMatrix(3, 3);
    MatrixLine* lines = &matrix->lines[0];

    MatrixElement* element = CreateMatrixElement(1, 2);
    UpdateSparseLine(lines, element);

    int gain = (9 * sizeof(int)) - (2 * sizeof(int) + 3 * sizeof(int) + 3 * sizeof(int));
    TEST_ASSERT_EQUAL_INT(gain, ComputeMemoryGain(matrix));

    DeleteMatrix(&matrix);
}