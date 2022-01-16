//
//  Stack.h
//  issacl2c
//
//  Created by Issac on 16/01/22.
//

/* Example of a simple stack - implemented using a linked list (singly linked)
 - operations: push to stack, pop from stack
 */

#ifndef Stack_h
#define Stack_h

#include <stdio.h>

/* Exported Types */
#define STACK_OBJECT_TYPE unsigned int

typedef struct Stack_Element_T
{
    STACK_OBJECT_TYPE       object;
    struct Stack_Element_T  *nextPtr;
}Stack_ElementType;

#define STACK (Stack_ElementType *)

/* Exported Functions */

/*------------------------------------------------------*/
/* Stack Demo Application                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Stack_Demo(void);

/*------------------------------------------------------*/
/* Pop Element from Stack                               */
/* Expects:                                             */
/* 1: Pointer to the stack                              */
/* Returns:                                             */
/* Element that is popped                               */
/*------------------------------------------------------*/
extern STACK_OBJECT_TYPE Stack_Pop(Stack_ElementType *stackPtr);

/*------------------------------------------------------*/
/* Push Element into Stack                              */
/* Expects:                                             */
/* 1: Pointer to the stack                              */
/* 2: element to be pushed                              */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Stack_Push(Stack_ElementType *stackPtr, STACK_OBJECT_TYPE object);


#endif /* Stack_h */
