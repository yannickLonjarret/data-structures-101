#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "SparseMatrix.h"
#include "gui.h"
#include "utils.h"

enum menuOptions { CREATE = 0, FILL = 1, DISPLAY_TABLE = 2, DISPLAY_LIST = 3, PUT = 4, GET = 5, ADD = 6, COMPUTE_GAIN = 7, QUIT = 8 };

int main(void) {
    const int matrixCount = 10;
    SparseMatrix** matrices = (SparseMatrix**)malloc(matrixCount * sizeof(SparseMatrix*));

    for(int i = 0; i < matrixCount; i++)
        matrices[i] = NULL;

    int menuChoice = 0;
    do {
        printInitializedPointerArray((void**)matrices, matrixCount);
        printf("--------------MENU--------------\n");
        printf("What would you like to do:\n");
        printf("0. Create a new matrix\n");
        printf("1. Fill a matrix\n");
        printf("2. Display a matrix in table format\n");
        printf("3. Display a matrix in list format\n");
        printf("4. Put a value in a matrix\n");
        printf("5. Get a value from a matrix\n");
        printf("6. Add two matrices\n");
        printf("7. Compute the memory gain of using a sparse matrix\n");
        printf("8. Quit\n");

        if(readUserIntegerInput(&menuChoice) != 0) {
            printf("Input not parsable, skip\n");
            continue;
        }

        int linePosition, columnPosition, valueToPut;
        int firstMatrixToAdd, secondMatrixToAdd;

        int matrixToFill, matrixToPutValue;
        int matrixToComputeGain;
        int matrixToDisplayList, matrixToDisplayTable;

        int matrixToCreate;
        int lineCount, columnCount;

        int matrixToGetValue;
        switch(menuChoice) {
        case CREATE:
            printf("Please choose a matrix to create (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToCreate, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToCreate] != NULL) {
                printf("Matrix already exists. \n");
                break;
            }

            printf("Please enter line count: \n");
            if(getValidUserIntegerInput(&lineCount, 1, INT_MAX - 1) != 0)
                continue;

            printf("Please enter column count: \n");
            if(getValidUserIntegerInput(&columnCount, 1, INT_MAX - 1) != 0)
                continue;

            matrices[matrixToCreate] = CreateSparseMatrix(lineCount, columnCount);
            clearTerminal();
            break;

        case FILL:
            printf("Please choose a matrix to fill (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToFill, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToFill] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            FillMatrix(matrices[matrixToFill], matrices[matrixToFill]->lineCount, matrices[matrixToFill]->columnCount);
            clearTerminal();
            break;

        case DISPLAY_TABLE:
            printf("Please choose a matrix to display (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToDisplayTable, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToDisplayTable] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            DisplayMatrixAsTable(matrices[matrixToDisplayTable]);
            clearTerminal();
            break;

        case DISPLAY_LIST:
            printf("Please choose a matrix to display (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToDisplayList, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToDisplayList] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            DisplayMatrixAsLists(matrices[matrixToDisplayList]);
            clearTerminal();
            break;

        case PUT:
            printf("Please choose a matrix to put value in (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToPutValue, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToPutValue] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            printf("Please enter line position: \n");
            if(getValidUserIntegerInput(&linePosition, 0, matrices[matrixToPutValue]->lineCount) != 0)
                continue;

            printf("Please enter column position: \n");
            if(getValidUserIntegerInput(&linePosition, 0, matrices[matrixToPutValue]->columnCount) != 0)
                continue;

            printf("Please enter value to put: \n");
            if(getValidUserIntegerInput(&valueToPut, INT_MIN + 1, INT_MAX - 1) != 0)
                continue;

            PutValue(matrices[matrixToPutValue], linePosition, columnPosition, valueToPut);
            clearTerminal();
            break;

        case GET:
            printf("Please choose a matrix to get value from (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToGetValue, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToGetValue] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            printf("Please enter line position: \n");
            if(getValidUserIntegerInput(&linePosition, 0, matrices[matrixToPutValue]->lineCount) != 0)
                continue;

            printf("Please enter column position: \n");
            if(getValidUserIntegerInput(&linePosition, 0, matrices[matrixToPutValue]->columnCount) != 0)
                continue;

            int value = GetValue(matrices[matrixToGetValue], linePosition, columnPosition);
            printf("Value at position (%d, %d) is: %d\n", linePosition, columnPosition, value);
            break;

        case ADD:
            printf("Please choose first matrix to add (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&firstMatrixToAdd, 0, matrixCount - 1) != 0)
                continue;

            printf("Please choose second matrix to add (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&secondMatrixToAdd, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[firstMatrixToAdd] == NULL || matrices[secondMatrixToAdd] == NULL) {
                printf("One of the matrices does not exist. \n");
                break;
            }

            AddMatrix(matrices[firstMatrixToAdd], matrices[secondMatrixToAdd]);
            clearTerminal();
            break;

        case COMPUTE_GAIN:
            printf("Please choose a matrix to compute gain for (0-%d): \n", matrixCount - 1);
            if(getValidUserIntegerInput(&matrixToComputeGain, 0, matrixCount - 1) != 0)
                continue;

            if(matrices[matrixToComputeGain] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            int gain = ComputeMemoryGain(matrices[matrixToComputeGain]);
            printf("Memory gain for matrix %d is: %d bytes\n", matrixToComputeGain, gain);
            break;

        default:
            if(menuChoice != QUIT)
                printf("Invalid menu choice. Please choose a number between 0 and 8. \n");
            break;
        }

    } while(menuChoice != QUIT);

    for(int i = 0; i < matrixCount; i++)
        if(matrices[i] != NULL)
            DeleteMatrix(&matrices[i]);
    free((void*)matrices);
    return 0;
}
