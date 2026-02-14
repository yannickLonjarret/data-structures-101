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


