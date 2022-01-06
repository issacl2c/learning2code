//
//  Heap.h
//  issacl2c
//
//  Created by Issac on 30/12/21.
//
// This implements a heap data structure, and common operations on the heap
// Note: This is a MIN heap. (Node with Minimum value of key is the root)

#ifndef Heap_h
#define Heap_h

#include <stdio.h>
#include "Types.h"


/* Exported Types */
//typedef void* (*HeapAttrType)(void *);
typedef unsigned int HeapAttrType;

typedef struct Heap_Entry_T
{
    unsigned int                    key;                // Key
    HeapAttrType                    attr;               // Value @ this entry
}Heap_EntryType;

typedef Heap_EntryType *HEAP_ENTRY;

typedef struct Heap_T
{
    unsigned int                    maxSize;            // Max Size of Heap
    unsigned int                    currSize;           // Current Size of Heap
    Heap_EntryType                  *heap;              // Array of Heap Entries
}Heap_Type;

typedef Heap_Type *HEAP;


/* Exported Variables */
extern HEAP HeapPtr;

/* Exported Defines */

/* Heap Function Declarations */

/*------------------------------------------------------*/
/* Demo function for Heap                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Heap_Demo(void);

/*------------------------------------------------------*/
/* Initialize a Heap                                    */
/* Expects:                                             */
/* 1: Size of the Heap                                  */
/* Returns:                                             */
/* Pointer to the initialized Heap                      */
/*------------------------------------------------------*/
extern HEAP Heap_Init(unsigned int heapSize);

/*------------------------------------------------------*/
/* Insert an entry to the Heap                          */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 2: Value for the entry                               */
/* 3: Pointer to the heap                               */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Heap_Insert(unsigned int key, HeapAttrType attr, HEAP heapPtr);

/*------------------------------------------------------*/
/* Pop min value out of Heap                            */
/* Expects:                                             */
/* 1: Pointer to the heap                               */
/* Returns:                                             */
/* Attribute of the minimum value key                   */
/*------------------------------------------------------*/
extern HeapAttrType Heap_GetMinValue(HEAP heapPtr);

/*------------------------------------------------------*/
/* Build a Heap from an array of elements               */
/* Expects:                                             */
/* 1: Pointer to the array                              */
/* 3: Pointer to the heap                               */
/* Returns:                                             */
/* Pointer to the built heap                            */
/*------------------------------------------------------*/
extern HEAP Heap_Build(HEAP_ENTRY inputArray, HEAP heapPtr, unsigned int size);

/*------------------------------------------------------*/
/* Utility to do a Heap sort on an array of items       */
/* This is for normal integer values                    */
/* Expects:                                             */
/* 1: Pointer to the unsorted array                     */
/* Returns:                                             */
/* Pointer to the sorted array                          */
/*------------------------------------------------------*/
extern unsigned int *Heap_Utility_Sort(unsigned int *inputArray, unsigned int size);

/*------------------------------------------------------*/
/* Utility to print a Heap (Key,Attr)                   */
/* Note: Only supports int types of Key, Attr           */
/* Expects:                                             */
/* Pointer to the heap                                  */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Heap_Utility_PrintHeap(HEAP heapPtr);

#endif /* Heap_h */
