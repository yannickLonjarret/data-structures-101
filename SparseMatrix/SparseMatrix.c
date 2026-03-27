#include "SparseMatrix.h"
#include <stdio.h>
#include <stdlib.h>

void FillMatrix(SparseMatrix* matrix, int lineCount, int columnCount) {
    if(matrix == NULL) {
        printf("Cannot fill a non-existent matrix \n");
        return;
    }

    int currentValueToInsert = 0;
    MatrixElement* element = NULL;
    for(int i = 0; i < lineCount; i++) {

        for(int j = 0; j < columnCount; j++) {
            printf("Please type in value for element M[%d][%d]", i, j);
            scanf("%d", &currentValueToInsert);

            if(currentValueToInsert == 0)
                continue;

            element = CreateMatrixElement(currentValueToInsert, j);
            UpdateSparseLine(&matrix->lines[i], element);
        }
    }
    return;
}

void DisplayMatrixAsTable(SparseMatrix* matrix) {
    if(matrix == NULL) {
        printf("Cannot display a non-existent matrix. \n");
        return;
    }

    for(int i = 0; i < matrix->lineCount; i++)
        DisplayLineAsTable(&matrix->lines[i], matrix->columnCount);
}

void DisplayLineAsTable(MatrixLine* line, int columnCount) {
    if(*line == NULL) {
        for(int i = 0; i < columnCount; i++)
            printf("%9d", 0);
        printf("\n");
        return;
    }
    int currentPosition = 0;
    MatrixElement* lineTraverse = *line;

    while(lineTraverse || currentPosition < columnCount) {
        if((lineTraverse == NULL && currentPosition < columnCount) || lineTraverse->column > currentPosition) {
            printf("%9d", 0);
            currentPosition++;
        } else if(lineTraverse->column < currentPosition) {
            lineTraverse = lineTraverse->nextElement;
            currentPosition++;
        }

        else {
            printf("%9d", lineTraverse->value);
            lineTraverse = lineTraverse->nextElement;
            currentPosition++;
        }
    }
    printf("\n");
}

void DisplayMatrixAsLists(SparseMatrix* matrix) {
    if(matrix == NULL) {
        printf("Cannot display a non-existent matrix. \n");
        return;
    }

    for(int i = 0; i < matrix->lineCount; i++)
        DisplayLineAsList(matrix->lines[i]);
}

void DisplayLineAsList(MatrixLine line) {
    if(line == NULL)
        printf("Empty line\n");
    MatrixElement* lineTraverse = line;

    while(lineTraverse) {
        printf("|col: %d, value:%d|>", lineTraverse->column, lineTraverse->value);
        lineTraverse = lineTraverse->nextElement;
    }
    printf("\n");
}

int GetValue(SparseMatrix* matrix, int linePosition, int columnPosition) {
    if(matrix == NULL) {
        printf("Cannot get value from a non-existent matrix \n");
        return 0;
    }

    if(matrix->lineCount < linePosition || matrix->columnCount < columnPosition) {
        printf("Value coordinates are not correct. \n");
        return 0;
    }

    MatrixLine line = matrix->lines[linePosition];
    return SearchValueInLine(line, columnPosition);
}

int SearchValueInLine(MatrixLine line, int columnPosition) {
    if(line == NULL)
        return 0;

    MatrixElement* lineTraverse = line;
    while(lineTraverse != NULL) {
        if(lineTraverse->column > columnPosition)
            return 0;
        if(lineTraverse->column == columnPosition)
            return lineTraverse->value;

        lineTraverse = lineTraverse->nextElement;
    }
    return 0;
}

void PutValue(SparseMatrix* matrix, int linePosition, int columnPosition, int value) {
    if(matrix == NULL) {
        printf("Cannot set value in a non-existent matrix \n");
        return;
    }

    if(matrix->lineCount < linePosition || matrix->columnCount < columnPosition) {
        printf("Value coordinates are not correct. \n");
        return;
    }

    if(value == 0) {
        RemoveSparseLineElement(&matrix->lines[linePosition], columnPosition);
    } else {
        MatrixElement* newElement = CreateMatrixElement(value, columnPosition);
        UpdateSparseLine(&matrix->lines[linePosition], newElement);
    }
}

void AddMatrix(SparseMatrix* a, SparseMatrix* b) {
    if(!a || !b) {
        printf("One or more non existent matrix \n");
        return;
    }

    if(a->columnCount != b->columnCount || a->lineCount != b->lineCount) {
        printf("Cannot add two matrix of different dimension \n");
        return;
    }

    for(int i = 0; i < a->lineCount; i++)
        AddMatrixLine(&a->lines[i], &b->lines[i]);
}

void AddMatrixLine(MatrixLine* a, MatrixLine* b) {
    if(*a == NULL) {
        MatrixElement* lineTraverse = *b;
        MatrixElement* copy = NULL;
        while(lineTraverse) {
            copy = CreateMatrixElement(lineTraverse->value, lineTraverse->column);
            UpdateSparseLine(a, copy);
            lineTraverse = lineTraverse->nextElement;
        }
        return;
    }

    MatrixElement* traverseA = *a;
    MatrixElement* traverseB = *b;

    while(traverseA != NULL && traverseB != NULL) {
        if(traverseA->column == traverseB->column) {
            traverseA->value += traverseB->value;
            traverseA = traverseA->nextElement;
            traverseB = traverseB->nextElement;
            continue;
        }

        if(traverseA->column < traverseB->column) {
            traverseA = traverseA->nextElement;
            continue;
        }

        if(traverseA->column > traverseB->column) {
            MatrixElement* copy = CreateMatrixElement(traverseB->value, traverseB->column);
            UpdateSparseLine(a, copy);
            traverseB = traverseB->nextElement;
            continue;
        }
    }

    while(traverseB != NULL) {
        MatrixElement* copy = CreateMatrixElement(traverseB->value, traverseB->column);
        UpdateSparseLine(a, copy);
        traverseB = traverseB->nextElement;
    }
}

int ComputeMemoryGain(SparseMatrix* matrix) {
    if(matrix == NULL) {
        printf("Cannot compute gain on an empty matrix \n");
        return -1;
    }
    int SparseMatrixSize = 2 * sizeof(int) + matrix->lineCount * sizeof(int);
    MatrixElement* lineTraverse = NULL;

    for(int i = 0; i < matrix->lineCount; i++) {
        if(!matrix->lines[i])
            continue;
        else {
            lineTraverse = matrix->lines[i];
            while(lineTraverse) {
                SparseMatrixSize += 3 * sizeof(int);
                lineTraverse = lineTraverse->nextElement;
            }
        }
    }

    int classicalMatrixSize = matrix->columnCount * matrix->lineCount * sizeof(int);
    return classicalMatrixSize - SparseMatrixSize;
}

MatrixLine* CreateMatrixLines(int size) {
    MatrixLine* lines = (MatrixLine*)malloc(sizeof(MatrixLine) * size);

    if(lines == NULL) {
        printf("Malloc issue when creating the matrix lines.");
        return NULL;
    }

    for(int i = 0; i < size; i++)
        lines[i] = NULL;

    return lines;
}

SparseMatrix* CreateSparseMatrix(int lineCount, int columnCount) {
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    MatrixLine* lines = CreateMatrixLines(lineCount);

    if(matrix == NULL || lines == NULL) {
        printf("Malloc issue when creating the matrix.");
        return NULL;
    }

    matrix->lines = lines;
    matrix->lineCount = lineCount;
    matrix->columnCount = columnCount;

    return matrix;
}

MatrixElement* CreateMatrixElement(int value, int column) {
    MatrixElement* elem = (MatrixElement*)malloc(sizeof(MatrixElement));

    if(elem == NULL) {
        printf("Malloc issue when creating an element.");
        return NULL;
    }

    elem->column = column;
    elem->value = value;
    elem->nextElement = NULL;

    return elem;
}

void RemoveSparseLineElement(MatrixLine* line, int positionToRemove) {
    if(*line == NULL)
        return;
    MatrixElement* temp = NULL;

    if((*line)->column == positionToRemove) {
        temp = *line;
        *line = (*line)->nextElement;
        DeleteElement(&temp);
        return;
    }

    MatrixElement* lineTraverse = *line;
    while(lineTraverse != NULL) {

        if(lineTraverse->nextElement && lineTraverse->nextElement->column == positionToRemove) {
            temp = lineTraverse->nextElement;
            lineTraverse->nextElement = lineTraverse->nextElement->nextElement;
            DeleteElement(&temp);
        }
        lineTraverse = lineTraverse->nextElement;
    }
}

void UpdateSparseLine(MatrixLine* line, MatrixElement* elementToInsert) {
    if(elementToInsert == NULL) {
        printf("Element is NULL, exiting.");
        return;
    }
    if(*line == NULL) {
        *line = elementToInsert;
        return;
    }

    if(elementToInsert->column < (*line)->column) {
        elementToInsert->nextElement = *line;
        *line = elementToInsert;
        return;
    }

    MatrixElement* lineTraverse = *line;
    while(lineTraverse != NULL) {

        if(lineTraverse->column == elementToInsert->column) {
            lineTraverse->value = elementToInsert->value;
            DeleteElement(&elementToInsert);
            return;
        }

        if(!lineTraverse->nextElement || lineTraverse->nextElement->column > elementToInsert->column) {
            elementToInsert->nextElement = lineTraverse->nextElement;
            lineTraverse->nextElement = elementToInsert;
            return;
        }

        lineTraverse = lineTraverse->nextElement;
    }
}

void DeleteMatrixLine(MatrixLine* line) {
    if(*line == NULL)
        return;
    MatrixLine lineTraverse = *line;
    while(lineTraverse != NULL) {
        MatrixLine temp = lineTraverse;
        lineTraverse = lineTraverse->nextElement;
        DeleteElement(&temp);
    }
    *line = NULL;
}

void DeleteElement(MatrixElement** element) {
    free(*element);
    *element = NULL;
    return;
}

void DeleteMatrix(SparseMatrix** matrix) {
    for(int i = 0; i < (*matrix)->lineCount; i++)
        DeleteMatrixLine(&((*matrix)->lines[i]));
    free(*matrix);
    *matrix = NULL;
    return;
}
