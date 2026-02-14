#include <stdlib.h>
#include <stdio.h>
#include "SparseMatrix.h"

void DisplayMatrixAsTable(SparseMatrix *matrix){
    if(matrix == NULL){
        printf("Cannot display a non-existent matrix. \n");
        return;
    }

    for(int i = 0; i < matrix->lineCount; i++){
        DisplayLineAsTable(matrix->lines[i], matrix->columnCount);
    }
}

void DisplayLineAsTable(MatrixLine line, int columnCount){
    if(line == NULL){
        for(int i = 0; i < columnCount; i++)
            printf("%9d", 0);
    }
    int currentPosition = 0;
    MatrixElement* lineTraverse = line;
    
    while(lineTraverse || currentPosition < columnCount){
        if(lineTraverse->column < currentPosition)
            lineTraverse = lineTraverse->nextElement;
        else if(lineTraverse->column > currentPosition){
            printf("%9d", 0);
            currentPosition++;
        }
        else{
            printf("%9d", lineTraverse->value);
            lineTraverse = lineTraverse->nextElement;
        }
    }
    printf("\n");
}

void DisplayMatrixAsLists(SparseMatrix* matrix){
    if(matrix == NULL){
        printf("Cannot display a non-existent matrix. \n");
        return;
    }

    for(int i = 0; i < matrix->lineCount; i++){
        DisplayLineAsList(matrix->lines[i], matrix->columnCount);
    }
}


void DisplayLineAsList(MatrixLine line){
    if(line == NULL){
            printf("Empty line\n");
    }
    MatrixElement* lineTraverse = line;
    
    while(lineTraverse){
       printf("|col: %d, value:%d|>", lineTraverse->column, lineTraverse->value);
       lineTraverse = lineTraverse->nextElement;
    }
    printf("\n");
}


int GetValue(SparseMatrix* matrix, int linePosition, int columnPosition){
    if(matrix == NULL){
        printf("Cannot get value from a non-existent matrix \n");
        return 0;
    }

    if(matrix->lineCount < linePosition || matrix->columnCount < columnPosition){
        printf("Value coordinates are not correct. \n");
        return 0;
    }

    MatrixLine line = matrix->lines[linePosition];
    return SearchValueInLine(line, columnPosition);
}

int SearchValueInLine(MatrixLine line, int columnPosition){
    if(line == NULL) return 0;

    MatrixElement* lineTraverse = line;
    while(lineTraverse != NULL){
        if(lineTraverse->column > columnPosition)
            return 0;
        if(lineTraverse->column == columnPosition)
            return lineTraverse->value;

        lineTraverse = lineTraverse->nextElement;
    }
    return 0;
}


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

void DeleteMatrixLine(MatrixLine line){
    if(!line) DeleteMatrixLine(line->nextElement);
    DeleteElement(line);
}

void DeleteElement(MatrixElement* element){
    free(element);
    element = NULL;
    return;
}

void DeleteMatrix(SparseMatrix* matrix){
    for(int i = 0; i < matrix->lineCount; i++)
        DeleteMatrixLine(matrix->lines[i]);
    free(matrix);
    matrix = NULL;
    return;
}
