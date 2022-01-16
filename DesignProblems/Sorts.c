//
//  Sorts.c
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

#include "Sorts.h"
#include "stdlib.h"

/* functions */

/* Max Heapify */
static void Sorts_Heap_Heapify(unsigned int *heapPtr, unsigned int index, unsigned int size)
{
    unsigned int leftChild, rightChild, largest;
    largest     = index;
    leftChild   = index*2 + 1;
    rightChild  = index*2 + 2;
    
    if ( (leftChild < size)
        && (heapPtr[leftChild] > heapPtr[largest]) )
    {
        largest = leftChild;
    }
    if ( (rightChild < size)
        && (heapPtr[rightChild] > heapPtr[largest]) )
    {
        largest = rightChild;
    }
    if (largest != index)
    {
        heapPtr[largest]   ^= heapPtr[index];
        heapPtr[index]     ^= heapPtr[largest];
        heapPtr[largest]   ^= heapPtr[index];
        
        Sorts_Heap_Heapify(heapPtr, largest, size); /* IMPORTANT !!! - don't miss the recursion. */
    }
}

static void Sorts_HeapSort(unsigned int *arrayPtr, unsigned int size)
{
    for (int i = size-1; i >= 0; i--)
    {
        Sorts_Heap_Heapify(arrayPtr, i, size);
    }
    
    /* Take the largest element to the end, heapify the rest */
    for (unsigned int i = size-1; i > 0; i--)
    {
        arrayPtr[i]      ^= arrayPtr[0];
        arrayPtr[0]      ^= arrayPtr[i];
        arrayPtr[i]      ^= arrayPtr[0];
        
        Sorts_Heap_Heapify(arrayPtr, 0, i);
    }
}

static void Sorts_BubbleSort(unsigned int *arrayPtr, unsigned int size)
{
    for (int i = size-1; i >= 1; i--)
    {
        int j = i-1;
        while ( j >= 0)
        {
            if ( arrayPtr[i] < arrayPtr[j])
            {
                arrayPtr[i]      ^= arrayPtr[j];
                arrayPtr[j]      ^= arrayPtr[i];
                arrayPtr[i]      ^= arrayPtr[j];
            }
            j--;
        }
    }
}

void Sorts_Demo(void)
{
    unsigned int type, size;
    
    printf("\n-------------------------Sorting DEMO application-------------------------\n");
    printf("Choose the Type of Sort:\
            \n1: Heap Sort\
            \n2: Bubble Sort\
            \n7: Exit Operation\n\n");
    
    scanf("%d", &type);
    
    printf("\n Enter the Size of the Array you like to Sort\n");
    
    scanf("%d", &size);
    
    /* Allocate Array */
    unsigned int *array = (unsigned int *)malloc(sizeof(unsigned int) * size);
    
    printf("\n Please Enter the Array elements, Row by Row. NEW_LINE after each entry please! \n ");
    for (unsigned int column = 0; column < size; column++)
    {
        scanf("%d", &(array[column]));
    }
    
    printf("\n Thank You. Your Input array is as below: \n");
    
    for (unsigned int column = 0; column < size; column++)
    {
        printf("%d ", array[column]);
    }
    
    switch (type)
    {
        case 1:
            Sorts_HeapSort(array, size);
            printf("\nHeapSort Completed\n");
            break;
        case 2:
            Sorts_BubbleSort(array, size);
        default:
            break;
    }
    
    printf("\n\n Array after Sort \n");
    
    for (unsigned int column = 0; column < size; column++)
    {
        printf("%d ", array[column]);
    }
    printf("\n");
}
