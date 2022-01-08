//
//  TimedTask.c
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

#include "TimedTask.h"
#include "stdlib.h"

/* static variables */
static TimedTask_HashType *TimedTask_HashPtr = NULL;
static volatile unsigned int TimedTask_OsCounter = 0;

/* Static functions */
static void TimedTask_InitHash(void)
{
    TimedTask_HashPtr = (TimedTask_HashType *)malloc(sizeof(struct TimedTask_Hash_T));  /* allocate main hash struct */
    TimedTask_HashPtr->hashSize = HASH_SIZE;
    
    /* allocate the list */
    TimedTask_HashPtr->taskList = (TimedTask_HashElementType *)malloc(sizeof(struct TimedTask_HashElement_T) * HASH_SIZE);
    
    for (unsigned int hashIndex = 0; hashIndex < HASH_SIZE; hashIndex++)
    {
        TimedTask_HashPtr->taskList[hashIndex].nextPtr = NULL;
    }
}

static void TimedTask_InsertHashEntry(TimedTask_TaskType *taskPtr)
{
    unsigned int hashIndex = ((unsigned int)(taskPtr->sched_period)) % HASH_SIZE;  /* get Hash Index */
    TimedTask_HashElementType *elementPtr = &(TimedTask_HashPtr->taskList[hashIndex]);
    
    while (elementPtr->nextPtr != NULL)
    {
        elementPtr = elementPtr->nextPtr;
    }
    
    elementPtr->nextPtr = (TimedTask_HashElementType *)malloc(sizeof(struct TimedTask_HashElement_T));
    elementPtr->nextPtr->timedTask = taskPtr;
    elementPtr->nextPtr->nextPtr = NULL;
}

static void TimedTask_DeleteHashEntry(TimedTask_TaskType *taskPtr)
{
    unsigned int hashIndex = ((unsigned int)(taskPtr->sched_period)) % HASH_SIZE;  /* get Hash Index */
    TimedTask_HashElementType *elementPtr = &(TimedTask_HashPtr->taskList[hashIndex]);
    
    while (elementPtr->nextPtr != NULL)
    {
        if (elementPtr->nextPtr->timedTask->task == taskPtr->task)
        {
            elementPtr->nextPtr = elementPtr->nextPtr->nextPtr;
            free(elementPtr);
            free(taskPtr);
        }
        elementPtr = elementPtr->nextPtr;
    }
}

/* Exported Functions */
TimedTask_TaskType *TimedTask_RegisterTask(TASK_IDENTIFIER task, unsigned long delayMs, unsigned int periodic)
{
    TimedTask_TaskType *taskPtr = (TimedTask_TaskType *)malloc(sizeof(struct TimedTask_Task_T));
    unsigned int counterVal = 0;
    unsigned int counterMulFactor = 0;
    unsigned int flags = (unsigned int)( (periodic << 0) | (1u << 1u) ); /* periodicity and activeness */
    
    /* calculation of counter value and multiplier value
        counter value is a delta from current counter regardless of values above the range of the counter.
        this is the lower 32 bits of delayMs, added to current counter, truncated to 32bits. (ignore carry).
    */
    counterVal = (unsigned int)(TimedTask_OsCounter + (unsigned int)delayMs);
    
    /* Multiplication factor is the upper 32 bits of delay, added by 1 to account for the first overflow. */
    counterMulFactor = (unsigned int)(delayMs >> 32u) + 1u;
    
    taskPtr->task = task;
    taskPtr->sched_flags = flags;
    taskPtr->sched_period = ( ((((unsigned long)counterMulFactor) << 32u) ) | (unsigned long)counterVal );
    taskPtr->currentMultiplier = counterMulFactor;
    
    TimedTask_InsertHashEntry(taskPtr);
    
    return taskPtr;
}

void TimedTask_DeactivateTask(TimedTask_TaskType *timeTaskPtr)
{
    timeTaskPtr->sched_flags &= (~(2u));    /* set bit 2 to 0 */
}

void TimedTask_DeleteTask(TimedTask_TaskType *timeTaskPtr)
{
    timeTaskPtr->sched_flags &= (~(2u));    /* first deactivate */
    TimedTask_DeleteHashEntry(timeTaskPtr);     /* now Delete */
}

/* To be called by the OS Timer ISR */
void TimedTask_OsTimerTick(void)
{
    TimedTask_OsCounter++;
    TimedTask_HashElementType *hashElementPtr = NULL;
    
    unsigned int hashIndex = TimedTask_OsCounter % HASH_SIZE;
    
    if (TimedTask_HashPtr == NULL) /* first time, create HASH */
    {
        TimedTask_InitHash();
    }
    else
    {
        hashElementPtr = TimedTask_HashPtr->taskList[hashIndex].nextPtr;
        
        /* here we have to find a possible task to invoke */
        while ( hashElementPtr != NULL )
        {
            if ( hashElementPtr->timedTask->currentMultiplier == 0)
            {
                /* invoke the task */
                TASK_INVOKE(hashElementPtr->timedTask->task)
                
                if ( (hashElementPtr->timedTask->sched_flags & 1u) == 0u )  /* one time */
                {
                    TimedTask_DeleteTask(hashElementPtr->timedTask);
                }
                else
                {
                    hashElementPtr->timedTask->currentMultiplier = (unsigned int)(hashElementPtr->timedTask->sched_period >> 32u);  /* rewrite the multiplier*/
                }
            }
            else
            {
                /* reduce the multiplier */
                hashElementPtr->timedTask->currentMultiplier -= 1u;
            }
            hashElementPtr = hashElementPtr->nextPtr;
        }
    }
}

