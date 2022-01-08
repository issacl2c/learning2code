//
//  Heap.c
//  issacl2c
//
//  Created by Issac on 30/12/21.
//

#include "Heap.h"
#include "stdlib.h"

/* Exported Variables */
HEAP HeapPtr;
/*------------------------------------------------------*/
/* Demo function for Heap                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
void Heap_Demo(void)
{
    unsigned int operation = 0;
    unsigned int heapSize = 0,key = 0, attr = 0;
    unsigned int *arrayPtr = NULL;
    printf("HEAP DEMO APPLICATION\n\n");
    printf("This implements an Heap. The Keys are integer keys\n\n");
    while(1)
    {
        printf("Choose the operation you would like to perform:\
               \n1: Initialize the Heap\
               \n2: Insert Entry\
               \n3: Pop Min Entry Value\
               \n4: Show sorting demo\
               \n5: Print Heap\
               \n6: Exit Operation\n\n");
        
        scanf("%d", &operation);
        
        if (operation == 6)
            break;
        
        switch (operation)
        {
            case 1:
                printf("Enter the Heap Size\n");
                scanf("%d", &heapSize);
                HeapPtr = Heap_Init(heapSize);
                printf("Heap initialized. Ptr = %x, Heap Max Size = %d\n", (int)((void *)HeapPtr), HeapPtr->maxSize);
                break;
            case 2:
                printf("Enter the key and attribute\n");
                scanf("%d %d",&key,&attr);
                Heap_Insert(key, attr, HeapPtr);
                break;
            case 3:
                attr = Heap_GetMinValue(HeapPtr);
                printf("Min Value = %d\n", attr);
                break;
            case 4:
                printf("Let us BEGIN. STEP 1: Enter the size of the unsorted array:\n");
                scanf("%d", &heapSize);
                arrayPtr = (unsigned int *)malloc(sizeof(unsigned int) * (heapSize));
                printf("STEP 2: Please enter the array elements, 1 by 1\n");
                for (unsigned int i = 0; i < heapSize; i++)
                {
                    scanf("%d", &(arrayPtr[i]));
                }
                arrayPtr = Heap_Utility_Sort(arrayPtr, heapSize);
                printf("\n\nSorted Array after Heap Sort - \n");
                for (unsigned int i = 0; i < heapSize; i++)
                {
                    printf("%d ", arrayPtr[i]);
                    printf("\n");
                }
                break;
            case 5:
                Heap_Utility_PrintHeap(HeapPtr);
                break;
            case 6:
                break;
            default:
                printf("ERROR :@Heap_Demo: Invalid Input\n\n");
                break;
        }
    }
}

/*------------------------------------------------------*/
/* Initialize a Heap                                    */
/* Expects:                                             */
/* 1: Size of the Heap                                  */
/* Returns:                                             */
/* Pointer to the initialized Heap                      */
/*------------------------------------------------------*/
HEAP Heap_Init(unsigned int heapSize)
{
    HeapPtr = (HEAP)malloc(sizeof(Heap_Type));
    HeapPtr->maxSize = heapSize;
    HeapPtr->currSize = 0;
    HeapPtr->heap = (HEAP_ENTRY)malloc(sizeof(Heap_EntryType) * (heapSize+1));
    
    return HeapPtr;
}

/*------------------------------------------------------*/
/* Insert an entry to the Heap                          */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 2: Value for the entry                               */
/* 3: Pointer to the heap                               */
/* Returns:                                             */
/*------------------------------------------------------*/
void Heap_Insert(unsigned int key, HeapAttrType attr, HEAP heapPtr)
{
    HEAP_ENTRY heapPos = heapPtr->heap;
    unsigned int currPosition = heapPtr->currSize + 1;
    
    if (heapPtr->maxSize > heapPtr->currSize)
    {
        if (heapPtr->currSize > 0)
        {
            unsigned int indexPos = currPosition >> 1;    // divide by 2
            
            while (key < heapPos[indexPos].key)
            {
                heapPos[currPosition].key = heapPos[indexPos].key;
                heapPos[currPosition].attr = heapPos[indexPos].attr;
                
                currPosition = indexPos;
                
                if (currPosition <= 1)
                {
                    break;
                }
                else
                {
                    indexPos = currPosition >> 1;   // divide again by 2
                }
            }
            heapPos[currPosition].key = key;
            heapPos[currPosition].attr = attr;
        }
        else
        {
            heapPtr->heap[1].key = key;
            heapPtr->heap[1].attr = attr;
        }
        heapPtr->currSize += 1;
    }
    else
    {
        printf("#ERROR: @Heap_Insert : Max size of heap exceeded");
    }


}

/*------------------------------------------------------*/
/* Pop min value out of Heap                            */
/* Also deletes the min value entry                     */
/* Expects:                                             */
/* 1: Pointer to the heap                               */
/* Returns:                                             */
/* Attribute of the minimum value key                   */
/*------------------------------------------------------*/
HeapAttrType Heap_GetMinValue(HEAP heapPtr)
{
    HeapAttrType attr = 0;
    
    HEAP_ENTRY heapPos = heapPtr->heap;
    unsigned int currPosition = 1;
    unsigned int indexPos = currPosition << 1;
    
    if (heapPtr->currSize >= 1)
    {
        attr = heapPtr->heap[1].attr;
        while (indexPos <= (heapPtr->currSize))
        {
            if ( (indexPos < heapPtr->currSize)
                && (heapPos[indexPos].key > heapPos[indexPos + 1].key) )
            {
                indexPos++;
            }
            heapPos[currPosition].key = heapPos[indexPos].key;
            heapPos[currPosition].attr = heapPos[indexPos].attr;
            
            currPosition = indexPos;
            indexPos = currPosition << 1;
        }
        if (currPosition != heapPtr->currSize)
        {
            heapPos[currPosition] = heapPos[heapPtr->currSize]; // Percolate last element horizontally left.
        }
        heapPtr->currSize -= 1; // Decrement size
    }
    else
    {
        printf("ERROR : @Heap_GetMinValue : empty heap\n");
    }
    
    return attr;
}

/*------------------------------------------------------*/
/* Build a Heap from an array of elements               */
/* Note: Assumes that heapPtr has enough space allocated*/
/* Expects:                                             */
/* 1: Pointer to the array                              */
/* 3: Pointer to the heap                               */
/* Returns:                                             */
/* Pointer to the built heap                            */
/*------------------------------------------------------*/
HEAP Heap_Build(HEAP_ENTRY inputArray, HEAP heapPtr, unsigned int size)
{
    unsigned int i = 0;
    if (heapPtr != NULL)
    {
        heapPtr->maxSize = size + 1;
        heapPtr->currSize = 0;
        while (i < size)
        {
            Heap_Insert(inputArray[i].key, inputArray[i].attr, heapPtr);
            i++;
        }
    }
    return heapPtr;
}

/*------------------------------------------------------*/
/* Utility to do a Heap sort on an array of items       */
/* This is for normal integer values                    */
/* Expects:                                             */
/* 1: Pointer to the unsorted array                     */
/* Returns:                                             */
/* Pointer to the sorted array                          */
/*------------------------------------------------------*/
unsigned int *Heap_Utility_Sort(unsigned int *inputArray, unsigned int size)
{
    HEAP_ENTRY unsortedHeapEntries = (HEAP_ENTRY)malloc(sizeof(Heap_EntryType) * (size+1));
    unsigned int *sortedArray = (unsigned int *)malloc(sizeof(unsigned int) * size);
    
    unsigned int i = 0;
    
    while (i < size)
    {
        unsortedHeapEntries[i].key = inputArray[i];
        unsortedHeapEntries[i].attr = inputArray[i]; // This array has no attribute.
        i++;
    }
    
    HEAP heapPtr;
    
    heapPtr = (HEAP)malloc(sizeof(Heap_Type));
    heapPtr->maxSize = size;
    heapPtr->currSize = 0;
    heapPtr->heap = (HEAP_ENTRY)malloc(sizeof(Heap_EntryType) * (size+1));
    
    heapPtr = Heap_Build(unsortedHeapEntries, heapPtr, size);
    
    i=0;
    while (i < size)
    {
        sortedArray[i] = Heap_GetMinValue(heapPtr);
        i++;
    }
    
    return sortedArray;
}

/*------------------------------------------------------*/
/* Utility to print a Heap (Key,Attr)                   */
/* Note: Only supports int types of Key, Attr           */
/* Expects:                                             */
/* Pointer to the heap                                  */
/* Returns:                                             */
/*------------------------------------------------------*/
void Heap_Utility_PrintHeap(HEAP heapPtr)
{
    if (heapPtr != NULL)
    {
        printf("Printing HEAP at ptr = %x, SIZE = %x\n", (int)((void *)heapPtr), heapPtr->currSize);
        unsigned int i;
        
        for (i = 1; i<= heapPtr->currSize; i++)
        {
            printf("heap[%d] : key: %d attr = %d\n", i, heapPtr->heap[i].key, heapPtr->heap[i].attr);
        }
    }
}
