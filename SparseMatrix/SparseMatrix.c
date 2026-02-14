#include <stdlib.h>
#include <stdio.h>
#include "SparseMatrix.h"


MatrixLine* CreateMatrixLines(int size){
    MatrixLine* lines = (MatrixLine*)malloc(sizeof(MatrixLine)*size);

    if(lines == NULL){
        printf("Malloc issue when creating the matrix lines.");
        return NULL;
    }

    for(int i = 0; i < size; i++)
        lines[i] = NULL;

    return lines;
}

SparseMatrix* CreateSparseMatrix(int lineCount, int columnCount){
    SparseMatrix* matrix = (SparseMatrix*)(sizeof(SparseMatrix));
    MatrixLine* lines = CreateMatrixLines(lineCount);

    if(matrix == NULL || lines == NULL){
        printf("Malloc issue when creating the matrix.");
        return NULL;
    } 

    matrix->lines = lines;
    matrix->lineCount = lineCount;
    matrix->columnCount = columnCount;

    return matrix;
}

MatrixElement* CreateMatrixElement(int value, int column){
    MatrixElement* elem = (MatrixElement*)malloc(sizeof(MatrixElement));

    if(elem == NULL){
        printf("Malloc issue when creating an element.");
        return NULL;
    }

    elem->column=column;
    elem->value=value;
    elem->nextElement = NULL;

    return elem;
}


void UpdateSparseLine(MatrixLine line, MatrixElement* elementToInsert){
    if(elementToInsert == NULL){
        printf("Element is NULL, exiting.");
        return;
    }

    if(line == NULL){
        line = elementToInsert;
        return;
    }

    if(elementToInsert->column < line->column){
        elementToInsert->nextElement = line;
        line = elementToInsert;
        return;
    }

    MatrixElement* lineTraverse = line;
    int shouldContinue = 1;
    while (lineTraverse!= NULL && shouldContinue){

        if(lineTraverse->column == elementToInsert->column){
            lineTraverse->value = elementToInsert->value;
            DeleteElement(elementToInsert);
            shouldContinue = 0;
        }

        if(!lineTraverse->nextElement || lineTraverse->nextElement->column > elementToInsert->column){
            elementToInsert->nextElement = lineTraverse->nextElement;
            lineTraverse->nextElement = elementToInsert; 
            shouldContinue = 0;
        }

        lineTraverse = lineTraverse->nextElement;
        
    }

}
