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

            printf("Please choose a matrix to create (0-9): \n");
            if(readUserIntegerInput(&matrixToCreate) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToCreate < 0 || matrixToCreate >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToCreate] != NULL) {
                printf("Matrix already exists. \n");
                break;
            }

            printf("Please enter line count: \n");
            if(readUserIntegerInput(&lineCount) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(lineCount <= 0) {
                printf("Line count cannot be negative or zero. Please enter line count: \n");
                if(readUserIntegerInput(&lineCount) != 0) {
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            printf("Please enter column count: \n");
            if(readUserIntegerInput(&columnCount) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(columnCount <= 0) {
                printf("Column count cannot be negative or zero. Please enter column count: \n");
                if(readUserIntegerInput(&columnCount) != 0) {
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            matrices[matrixToCreate] = CreateSparseMatrix(lineCount, columnCount);
            clearTerminal();
            break;
        case FILL:
            printf("Please choose a matrix to fill (0-9): \n");
            if(readUserIntegerInput(&matrixToFill) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToFill < 0 || matrixToFill >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToFill] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            FillMatrix(matrices[matrixToFill], matrices[matrixToFill]->lineCount, matrices[matrixToFill]->columnCount);
            clearTerminal();
            break;
        case DISPLAY_TABLE:
            printf("Please choose a matrix to display (0-9): \n");
            if(readUserIntegerInput(&matrixToDisplayTable) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToDisplayTable < 0 || matrixToDisplayTable >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToDisplayTable] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            DisplayMatrixAsTable(matrices[matrixToDisplayTable]);
            clearTerminal();
            break;
        case DISPLAY_LIST:
            printf("Please choose a matrix to display (0-9): \n");
            if(readUserIntegerInput(&matrixToDisplayList) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToDisplayList < 0 || matrixToDisplayList >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToDisplayList] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            DisplayMatrixAsLists(matrices[matrixToDisplayList]);
            clearTerminal();
            break;
        case PUT:
            printf("Please choose a matrix to put value in (0-9): \n");
            if(readUserIntegerInput(&matrixToPutValue) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToPutValue < 0 || matrixToPutValue >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToPutValue] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            printf("Please enter line position: \n");
            if(readUserIntegerInput(&linePosition) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(linePosition < 0 || linePosition >= matrices[matrixToPutValue]->lineCount) {
                printf("Invalid line position. Please enter line position (0-%d): \n", matrices[matrixToPutValue]->lineCount - 1);
                if(readUserIntegerInput(&linePosition) != 0) {
                    linePosition = -1;
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            printf("Please enter column position: \n");
            if(readUserIntegerInput(&columnPosition) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(columnPosition < 0 || columnPosition >= matrices[matrixToPutValue]->columnCount) {
                printf("Invalid column position. Please enter column position (0-%d): \n", matrices[matrixToPutValue]->columnCount - 1);
                if(readUserIntegerInput(&columnPosition) != 0) {
                    columnPosition = -1;
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            printf("Please enter value to put: \n");
            if(readUserIntegerInput(&valueToPut) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            PutValue(matrices[matrixToPutValue], linePosition, columnPosition, valueToPut);
            clearTerminal();
            break;
        case GET:
            printf("Please choose a matrix to get value from (0-9): \n");
            if(readUserIntegerInput(&matrixToGetValue) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToGetValue < 0 || matrixToGetValue >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[matrixToGetValue] == NULL) {
                printf("Matrix does not exist. \n");
                break;
            }

            printf("Please enter line position: \n");
            if(readUserIntegerInput(&linePosition) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(linePosition < 0 || linePosition >= matrices[matrixToGetValue]->lineCount) {
                printf("Invalid line position. Please enter line position (0-%d): \n", matrices[matrixToGetValue]->lineCount - 1);
                if(readUserIntegerInput(&linePosition) != 0) {
                    linePosition = -1;
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            printf("Please enter column position: \n");
            if(readUserIntegerInput(&columnPosition) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            while(columnPosition < 0 || columnPosition >= matrices[matrixToGetValue]->columnCount) {
                printf("Invalid column position. Please enter column position (0-%d): \n", matrices[matrixToGetValue]->columnCount - 1);
                if(readUserIntegerInput(&columnPosition) != 0) {
                    columnPosition = -1;
                    printf("Input not parsable, skip\n");
                    continue;
                }
            }

            int value = GetValue(matrices[matrixToGetValue], linePosition, columnPosition);
            printf("Value at position (%d, %d) is: %d\n", linePosition, columnPosition, value);
            break;
        case ADD:
            printf("Please choose first matrix to add (0-9): \n");
            if(readUserIntegerInput(&firstMatrixToAdd) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            printf("Please choose second matrix to add (0-9): \n");
            if(readUserIntegerInput(&secondMatrixToAdd) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(firstMatrixToAdd < 0 || firstMatrixToAdd >= matrixCount || secondMatrixToAdd < 0 || secondMatrixToAdd >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

            if(matrices[firstMatrixToAdd] == NULL || matrices[secondMatrixToAdd] == NULL) {
                printf("One of the matrices does not exist. \n");
                break;
            }

            AddMatrix(matrices[firstMatrixToAdd], matrices[secondMatrixToAdd]);
            clearTerminal();
            break;
        case COMPUTE_GAIN:

            printf("Please choose a matrix to compute gain for (0-9): \n");
            if(readUserIntegerInput(&matrixToComputeGain) != 0) {
                printf("Input not parsable, skip\n");
                continue;
            }

            if(matrixToComputeGain < 0 || matrixToComputeGain >= matrixCount) {
                printf("Invalid matrix number. \n");
                break;
            }

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
    return 0;
}
