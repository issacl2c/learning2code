//
//  MatrixRotation.c
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

#include "MatrixRotation.h"
#include "stdlib.h"

/* Static variables */
unsigned int MatrixRation_Size = 0;
unsigned int **MatrixRotation_Array = NULL;

/* functions */
static void MatrixRotation_rotate(unsigned int **array, unsigned int squaresize)
{
    unsigned int squareIndex = squaresize-1;
    unsigned int rotIndex = 0, row = 0, column = 0;
    unsigned int tempValue;
    
    while (squareIndex > 1)
    {
        for (rotIndex = 0; rotIndex < (squareIndex); rotIndex++)
        {
            tempValue = array[row][column + rotIndex];
            array[row][column + rotIndex]                   = array[squareIndex - rotIndex][column];
            array[squareIndex - rotIndex][column]           = array[squareIndex][squareIndex - rotIndex];
            array[squareIndex][squareIndex - rotIndex]      = array[row + rotIndex][squareIndex];
            array[row + rotIndex][squareIndex]              = tempValue;
            
            if (squareIndex == 2)
            {
                break;  /* for 2, we only do this once. */
            }
        }
        squareIndex --;
        row++;
        column++;
    }
}


void MatrixRotation_Demo(void)
{
    printf("\n-------------------------Matrix Rotation DEMO application-------------------------\n");
    printf("\nEnter the square matrix size\n");
    scanf("%d", &MatrixRation_Size);
    
    /* Allocate Array */
    MatrixRotation_Array = (unsigned int **)malloc(sizeof(unsigned int *) * MatrixRation_Size);
    
    for (unsigned int row = 0; row < MatrixRation_Size; row++)
    {
        MatrixRotation_Array[row] = (unsigned int *)malloc(sizeof(unsigned int) * MatrixRation_Size);
    }
    
    printf("\n Please Enter the Array elements, Row by Row. NEW_LINE after each entry please! \n ");
    for (unsigned int row = 0; row < MatrixRation_Size; row++)
    {
        for (unsigned int column = 0; column < MatrixRation_Size; column++)
        {
            scanf("%d", &(MatrixRotation_Array[row][column]));
        }
    }
    printf("\n Thank You. Your Input MATRIX is as below: \n");
    
    for (unsigned int row = 0; row < MatrixRation_Size; row++)
    {
        for (unsigned int column = 0; column < MatrixRation_Size; column++)
        {
            printf("    %d    ", MatrixRotation_Array[row][column]);
        }
        printf("\n");
    }
    
    MatrixRotation_rotate(MatrixRotation_Array, MatrixRation_Size);
    
    printf("\n Rotation Complete! Please find your rotated matrix: \n");
    
    for (unsigned int row = 0; row < MatrixRation_Size; row++)
    {
        for (unsigned int column = 0; column < MatrixRation_Size; column++)
        {
            printf("    %d    ", MatrixRotation_Array[row][column]);
        }
        printf("\n");
    }
    
    
}

