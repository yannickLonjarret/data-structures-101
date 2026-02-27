#include <stdlib.h>
#include <stdio.h>

#include "SparseMatrix.h"

int main(int argc, char const *argv[])
{
    const int matrixCount = 10;
    SparseMatrix** matrices = (SparseMatrix**)malloc(matrixCount * sizeof(SparseMatrix*));

    for(int i = 0; i < matrixCount; i++)
        matrices[i] = NULL;
    
    int menuChoice = 0;
    do {

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

        scanf("%d", &menuChoice);
        system("clear");

        int linePosition, columnPosition, valueToPut;
        int firstMatrixToAdd, secondMatrixToAdd;

        int matrixToFill, matrixToPutValue;
        int matrixToComputeGain;
        int matrixToDisplayList, matrixToDisplayTable;

        int matrixToCreate;
        int lineCount, columnCount;

        int matrixToGetValue;
        switch (menuChoice) {
            case 0:
                
                printf("Please choose a matrix to create (0-9): \n");
                scanf("%d", &matrixToCreate);

                if(matrixToCreate < 0 || matrixToCreate >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                } 

                if(matrices[matrixToCreate] != NULL){
                    printf("Matrix already exists. \n");
                    break;
                }
                
                printf("Please enter line count: \n");
                scanf("%d", &lineCount);
                while (lineCount <= 0)
                {
                    printf("Line count cannot be negative or zero. Please enter line count: \n");
                    scanf("%d", &lineCount);
                }
                
                printf("Please enter column count: \n");
                scanf("%d", &columnCount);
                while (columnCount <= 0)
                {
                    printf("Column count cannot be negative or zero. Please enter column count: \n");
                    scanf("%d", &columnCount);
                }

                matrices[matrixToCreate] = CreateSparseMatrix(lineCount, columnCount);
                break;  
            case 1:
                printf("Please choose a matrix to fill (0-9): \n");
                scanf("%d", &matrixToFill);

                if(matrixToFill < 0 || matrixToFill >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                } 

                if(matrices[matrixToFill] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }

                FillMatrix(matrices[matrixToFill], matrices[matrixToFill]->lineCount, matrices[matrixToFill]->columnCount);
                break;
            case 2:
                printf("Please choose a matrix to display (0-9): \n");
                scanf("%d", &matrixToDisplayTable);
                if(matrixToDisplayTable < 0 || matrixToDisplayTable >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[matrixToDisplayTable] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }
                DisplayMatrixAsTable(matrices[matrixToDisplayTable ]);
                break;
            case 3:
                printf("Please choose a matrix to display (0-9): \n");
                scanf("%d", &matrixToDisplayList);
                if(matrixToDisplayList < 0 || matrixToDisplayList >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[matrixToDisplayList] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }
                DisplayMatrixAsLists(matrices[matrixToDisplayList]);
                break;
            case 4:
                printf("Please choose a matrix to put value in (0-9): \n");
                scanf("%d", &matrixToPutValue);
                if(matrixToPutValue < 0 || matrixToPutValue >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[matrixToPutValue] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }

                printf("Please enter line position: \n");
                scanf("%d", &linePosition);
                while (linePosition < 0 || linePosition >= matrices[matrixToPutValue]->lineCount)
                {
                    printf("Invalid line position. Please enter line position (0-%d): \n", matrices[matrixToPutValue]->lineCount - 1);
                    scanf("%d", &linePosition);
                }
                
                printf("Please enter column position: \n");
                scanf("%d", &columnPosition);
                while (columnPosition < 0 || columnPosition >= matrices[matrixToPutValue]->columnCount)
                {
                    printf("Invalid column position. Please enter column position (0-%d): \n", matrices[matrixToPutValue]->columnCount - 1);
                    scanf("%d", &columnPosition);
                }
                printf("Please enter value to put: \n");
                scanf("%d", &valueToPut);

                PutValue(matrices[matrixToPutValue], linePosition, columnPosition, valueToPut);
                break;
            case 5:
                printf("Please choose a matrix to get value from (0-9): \n");
                scanf("%d", &matrixToGetValue);
                if(matrixToGetValue < 0 || matrixToGetValue >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[matrixToGetValue] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }
                
                printf("Please enter line position: \n");
                scanf("%d", &linePosition);
                while (linePosition < 0 || linePosition >= matrices[matrixToGetValue]->lineCount)
                {
                    printf("Invalid line position. Please enter line position (0-%d): \n", matrices[matrixToGetValue]->lineCount - 1);
                    scanf("%d", &linePosition);
                }
                printf("Please enter column position: \n");
                scanf("%d", &columnPosition);
                while (columnPosition < 0 || columnPosition >= matrices[matrixToGetValue]->columnCount)
                {
                    printf("Invalid column position. Please enter column position (0-%d): \n", matrices[matrixToGetValue]->columnCount - 1);
                    scanf("%d", &columnPosition);
                }
                int value = GetValue(matrices[matrixToGetValue], linePosition, columnPosition);
                printf("Value at position (%d, %d) is: %d\n", linePosition, columnPosition, value);
                break;
            case 6:
                printf("Please choose first matrix to add (0-9): \n");
                scanf("%d", &firstMatrixToAdd);
                printf("Please choose second matrix to add (0-9): \n");
                scanf("%d", &secondMatrixToAdd);
                if(firstMatrixToAdd < 0 || firstMatrixToAdd >= matrixCount || secondMatrixToAdd < 0 || secondMatrixToAdd >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[firstMatrixToAdd] == NULL || matrices[secondMatrixToAdd] == NULL){
                    printf("One of the matrices does not exist. \n");
                    break;
                }
                AddMatrix(matrices[firstMatrixToAdd], matrices[secondMatrixToAdd]);
                break;
            case 7:
                
                printf("Please choose a matrix to compute gain for (0-9): \n");
                scanf("%d", &matrixToComputeGain);
                if(matrixToComputeGain < 0 || matrixToComputeGain >= matrixCount){
                    printf("Invalid matrix number. \n");
                    break;
                }
                if(matrices[matrixToComputeGain] == NULL){
                    printf("Matrix does not exist. \n");
                    break;
                }
                int gain = ComputeMemoryGain(matrices[matrixToComputeGain]);
                printf("Memory gain for matrix %d is: %d bytes\n", matrixToComputeGain, gain);
                break;
            default:
                if(menuChoice != 8)
                    printf("Invalid menu choice. Please choose a number between 0 and 8. \n");
                break;
        }
    
    }while (menuChoice != 8);

    for(int i = 0; i < matrixCount; i++){
        if(matrices[i] != NULL)
            DeleteMatrix(&matrices[i]);
    }
    return 0;
}
