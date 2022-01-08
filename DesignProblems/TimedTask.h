//
//  TimedTask.h
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

/* A problem seen in one of the Apple interviews:
 Create a "timed task" functionality for an application.
 - You are an OS with a timer tick. (coming at TIMER_TICK_RESOLUTION).
 - You need to provide an API to "register task" for wakeup, after a specified amount of time. (periodically).
    - This can be periodic / or one time request.
 - At some point, a task needs to be
    - deactivated (no longer required to be called)
    - Activate thet task (it will start to be called again)
    - remove the task from schedule queue
 */

/* ASSUMPTIONS
 - The user shall also use a "task descriptor" to continue interacting with the schedule API.
 - The user specifies time in seconds always
 - The maximum range of a one-time delay can be (uint32 (ms) * (uint32)ms))
 - OS_WAKEUP_TASK macro shall hide mechanics of how a task will be woken up
 */

/* Demonstrated result:
 Data structures:
 - Create a struct task descriptor type to interact with the API:
    - It will contain TASK_IDENTIFIER (opaque type - can be a function pointer / task ID)
    - It will contain PERIODIC_TIME (opaque type depends on the resolution)
    - It will contain FLAGS ( PERIODIC , ACTIVE )
 
 - Create a HASH TABLE of size HASH_SIZE (which will be (uint32 MAX / HASH_FACTOR))
 - each hash table entry is a list of task descriptors.
 - each hash table entry corresponds to a certain HASH of the OS counter tick (each tick maps to a HASH Entry)
 
 WHY these data structures?
    - OS tick is a very precious ISR
    - avoid using a linked list (this will need parsing through o(n) time.
    - use of a hash ensure o(1) time to search, remove, modify as needed.
    - entry into hash is also o(1) time.
 
 Algorithms:
 - Register API: Enter the task into the hash table.
 - each tick:
    - hash into the table, see if any task matches the delay.
    - if active, invoke it.
    - if one-time : Delete after invoke.
- Deactivate/Delete/Activate aPI:
    - Hash into the table, modify the flags.
    
 */
#ifndef TimedTask_h
#define TimedTask_h

#include <stdio.h>


#define TASK_INVOKE(TASK)   TASK();
#define TASK_IDENTIFIER TimedTask_FuncPtrType

#define TIMER_MS_RESOLUTION (1000u)
#define TIMER_RESOLUTION TIMER_MS_RESOLUTION

#define OSCOUNTER_MAX ((unsigned long)(0xFFFFFFFF)) /* uint32 MAX for counter max */
#define HASH_FACTOR     (10000u)

#define HASH_SIZE ((unsigned int)( (OSCOUNTER_MAX + 1u) / HASH_FACTOR ))

/* Exported types */

typedef void (*TimedTask_FuncPtrType)(void);

typedef struct TimedTask_Task_T
{
    TASK_IDENTIFIER     task;
    unsigned long       sched_period;
    unsigned int        currentMultiplier;
    unsigned int        sched_flags;
}TimedTask_TaskType;

/* Here we implement the HASH table */
/* Default Hash table cannot be used as we have a special type here */

typedef struct TimedTask_HashElement_T
{
    TimedTask_TaskType                  *timedTask;     /* List of Timed Tasks */
    struct TimedTask_HashElement_T      *nextPtr;
}TimedTask_HashElementType;

typedef struct TimedTask_Hash_T
{
    TimedTask_HashElementType   *taskList;    /* List of sentinel list of tasks */
    unsigned int                hashSize;     /* HASH Size */
}TimedTask_HashType;

/* Exported Functions */
extern TimedTask_TaskType *TimedTask_RegisterTask(TASK_IDENTIFIER task, unsigned long delayMs, unsigned int periodic);

extern void TimedTask_DeactivateTask(TimedTask_TaskType *timeTaskPtr);

extern void TimedTask_DeleteTask(TimedTask_TaskType *timeTaskPtr);

/* To be called by the OS Timer ISR */
extern void TimedTask_OsTimerTick(void);

#endif /* TimedTask_h */
