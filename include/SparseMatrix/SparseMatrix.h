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

void FillMatrix(SparseMatrix* matrix, const int lineCount, const int columnCount);
void DisplayMatrixAsTable(const SparseMatrix* matrix);
void DisplayLineAsTable(const MatrixLine* line, const int columnCount);
void DisplayMatrixAsLists(const SparseMatrix* matrix);
void DisplayLineAsList(const MatrixLine line);
int GetValue(const SparseMatrix* matrix, const int linePosition, const int columnPosition);
void PutValue(SparseMatrix* matrix, const int linePosition, const int columnPosition, const int value);
void AddMatrix(SparseMatrix* a, const SparseMatrix* b);
void AddMatrixLine(MatrixLine* a, const MatrixLine* b);
int ComputeMemoryGain(const SparseMatrix* matrix);

SparseMatrix* CreateSparseMatrix(const int lineCount, const int columnCount);
MatrixElement* CreateMatrixElement(const int value, const int column);
MatrixLine* CreateMatrixLines(const int size);

void UpdateSparseLine(MatrixLine* line, MatrixElement* elementToInsert);
void RemoveSparseLineElement(MatrixLine* line, const int positionToRemove);
int SearchValueInLine(MatrixLine line, const int columnPosition);

void DeleteMatrix(SparseMatrix** matrix);
void DeleteMatrixLine(MatrixLine* line);
void DeleteElement(MatrixElement** element);

#endif