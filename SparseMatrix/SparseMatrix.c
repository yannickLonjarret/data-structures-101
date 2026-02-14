#include <stdlib.h>
#include <stdio.h>
#include "SparseMatrix.h"


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


