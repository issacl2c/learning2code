//
//  Queue.c
//  issacl2c
//
//  Created by Issac on 06/01/22.
//

#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

/*------------------------------------------------------*/
/* Initialize a Queue of list type                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* Returns:                                             */
/* Pointer to the Queue after initialization            */
/*------------------------------------------------------*/
Queue_ListType *Queue_List_Init(Queue_ListType *queuePtr)
{
    queuePtr = (Queue_ListType *)malloc(sizeof(struct Queue_List_T));
    queuePtr->list = (Queue_ListElementType *)malloc(sizeof(struct Queue_ListElement_T));
    queuePtr->list->nextPtr = NULL;
    queuePtr->currentSize = 0;
    return queuePtr;
}

/*------------------------------------------------------*/
/* Put an item into the list queue                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* 2: Pointer to the entity                             */
/* Returns:                                             */
/* Status of the insert                                 */
/*------------------------------------------------------*/
boolean Queue_List_Insert(Queue_ListType *queuePtr, QUEUE_ENTITY entity)
{
    boolean returnStatus = FALSE;
    Queue_ListElementType *putPtr = queuePtr->list;
    
    while (putPtr->nextPtr != NULL)
    {
        putPtr = putPtr->nextPtr;
    }
    
    if (queuePtr != NULL)
    {
        putPtr->nextPtr = (Queue_ListElementType *)malloc(sizeof(struct Queue_ListElement_T));
        putPtr->nextPtr->nextPtr = NULL;
        //memcpy(&(putPtr->nextPtr->entity ), entity, sizeof(QUEUE_ENTITY));
        putPtr->nextPtr->entity = entity;
        queuePtr->currentSize++;
        returnStatus = TRUE;
    }
    return returnStatus;
}

/*------------------------------------------------------*/
/* Get an item from the list queue                      */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* 2: Pointer to the entity                             */
/* Returns:                                             */
/* 2: Pointer to the entity                             */
/* Status of the extract                                */
/*------------------------------------------------------*/
QUEUE_ENTITY Queue_List_Extract(Queue_ListType *queuePtr)
{
    QUEUE_ENTITY    returnEntity;
    Queue_ListElementType *queueItemPtr = queuePtr->list->nextPtr;
    if ( (queuePtr != NULL)
        && (queuePtr->currentSize > 0) )
    {
        //memcpy(itemPtr, &(queueItemPtr->entity), sizeof(QUEUE_ENTITY));
        returnEntity = queueItemPtr->entity;
        queuePtr->list->nextPtr = queueItemPtr->nextPtr;
        free(queueItemPtr);
        queuePtr->currentSize--;
    }
    return returnEntity;
}

/*------------------------------------------------------*/
/* Clear a Queue of list type                           */
/* Expects:                                             */
/* 1: Pointer to the Queue                              */
/* Returns:                                             */
/* Pointer to the Queue after clearing                  */
/* NOTE: Queue pointer itself is not made NULL          */
/*------------------------------------------------------*/
void Queue_List_Clear(Queue_ListType *queuePtr)
{
    Queue_ListElementType *freePtr = queuePtr->list->nextPtr;
    if (queuePtr != NULL)
    {
        while (freePtr != NULL)
        {
            queuePtr->list->nextPtr = freePtr->nextPtr;
            free(freePtr);
            freePtr = queuePtr->list->nextPtr;
        }
        queuePtr->currentSize = 0;
    }
}
