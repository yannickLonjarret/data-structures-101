#ifndef SPARSEMATRIX_H_INCLUDED
#define SPARSEMATRIX_H_INCLUDED

typedef struct element {
    int column;
    int value;
    struct element* nextElement;
} MatrixElement;

typedef MatrixElement* MatrixLine;

typedef struct matrix {
    MatrixLine* lines;
    int lineCount;
    int columnCount;
} SparseMatrix;

void FillMatrix(SparseMatrix* matrix, int lineCount, int columnCount);
void DisplayMatrixAsTable(SparseMatrix* matrix);
void DisplayLineAsTable(MatrixLine* line, int columnCount);
void DisplayMatrixAsLists(SparseMatrix* matrix);
void DisplayLineAsList(MatrixLine line);
int GetValue(SparseMatrix* matrix, int linePosition, int columnPosition);
void PutValue(SparseMatrix* matrix, int linePosition, int columnPosition, int value);
void AddMatrix(SparseMatrix* a, SparseMatrix* b);
void AddMatrixLine(MatrixLine* a, MatrixLine* b);
int ComputeMemoryGain(SparseMatrix* matrix);

SparseMatrix* CreateSparseMatrix(int lineCount, int columnCount);
MatrixElement* CreateMatrixElement(int value, int column);
MatrixLine* CreateMatrixLines(int size);

void UpdateSparseLine(MatrixLine* line, MatrixElement* elementToInsert);
void RemoveSparseLineElement(MatrixLine* line, int positionToRemove);
int SearchValueInLine(MatrixLine line, int columnPosition);

void DeleteMatrix(SparseMatrix** matrix);
void DeleteMatrixLine(MatrixLine* line);
void DeleteElement(MatrixElement** element);

#endif