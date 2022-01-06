//
//  Queue.h
//  issacl2c
//
//  Created by Issac on 06/01/22.
// This file implements a Queue with a linked list implementation. (single linked list).
// The methods used to get and put items into the Queue are also implemented.

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdlib.h>
#include "Types.h"

/* Generic Types */
#ifndef QUEUE_ENTITY
#define QUEUE_ENTITY unsigned int
#endif

/* Exported Types */
typedef struct Queue_ListElement_T
{
    QUEUE_ENTITY entity;
    struct Queue_ListElement_T  *nextPtr;
}QueueListElementType;

typedef struct Queue_List_T
{
    QueueListElementType        *list;
    QueueListElementType        *getPtr;
    QueueListElementType        *putPtr;
    unsigned int                currentSize;
}Queue_ListType;

/* Exported Functions */
/*------------------------------------------------------*/
/* Initialize a Queue of list type                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* Returns:                                             */
/* Pointer to the Queue after initialization            */
/*------------------------------------------------------*/
extern Queue_ListType *Queue_List_Init(Queue_ListType *queuePtr);

/*------------------------------------------------------*/
/* Put an item into the list queue                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* 2: Pointer to the entity                             */
/* Returns:                                             */
/* Status of the insert                                 */
/*------------------------------------------------------*/
extern boolean *Queue_List_Insert(Queue_ListType *queuePtr, QUEUE_ENTITY *entity);

/*------------------------------------------------------*/
/* Get an item from the list queue                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* Returns:                                             */
/* 1: Pointer to the entity                             */
/* NOTE: Return NULL if nothing to get                  */
/*------------------------------------------------------*/
extern QUEUE_ENTITY *Queue_List_Extract(Queue_ListType *queuePtr);

/*------------------------------------------------------*/
/* Clear a Queue of list type                           */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* Returns:                                             */
/* Pointer to the Queue after clearing                  */
/* NOTE: Queue pointer itself is not made NULL          */
/*------------------------------------------------------*/
extern void Queue_List_Clear(Queue_ListType *queuePtr);


#endif /* Queue_h */
