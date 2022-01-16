//
//  Stack.c
//  issacl2c
//
//  Created by Issac on 16/01/22.
//

#include "Stack.h"
#include "stdlib.h"
#include "stdio.h"

static Stack_ElementType *StackPtr = NULL;

/*------------------------------------------------------*/
/* Pop Element from Stack                               */
/* Expects:                                             */
/* 1: Pointer to the stack                              */
/* Returns:                                             */
/* Element that is popped                               */
/*------------------------------------------------------*/
STACK_OBJECT_TYPE Stack_Pop(Stack_ElementType *stackPtr)
{
    STACK_OBJECT_TYPE returnObject = 0;
    Stack_ElementType *tempPtr;
    if (stackPtr != NULL)
    {
        if (stackPtr->nextPtr != NULL)
        {
            returnObject = stackPtr->nextPtr->object;
            tempPtr = stackPtr->nextPtr->nextPtr;
            free(stackPtr->nextPtr);
            stackPtr->nextPtr = tempPtr;
        }
        else
        {
            printf("\nERROR @ STACK POP: NULL STACK\n");
        }
    }
    else
    {
        printf("\nERROR @ STACK POP: NULL STACK\n");
    }
    return returnObject;
}

/*------------------------------------------------------*/
/* Push Element into Stack                              */
/* Expects:                                             */
/* 1: Pointer to the stack                              */
/* 2: element to be pushed                              */
/* Returns:                                             */
/*------------------------------------------------------*/
void Stack_Push(Stack_ElementType *stackPtr, STACK_OBJECT_TYPE object)
{
    Stack_ElementType *tempPtr = NULL;
    
    if (stackPtr == NULL)
    {
        stackPtr = (Stack_ElementType *)malloc(sizeof(struct Stack_Element_T));
        stackPtr->nextPtr = (Stack_ElementType *)malloc(sizeof(struct Stack_Element_T));
        stackPtr->nextPtr->nextPtr = NULL;
        stackPtr->nextPtr->object = object;
    }
    else
    {
        tempPtr = stackPtr->nextPtr;
        stackPtr->nextPtr = (Stack_ElementType *)malloc(sizeof(struct Stack_Element_T));
        stackPtr->nextPtr->object = object;
        stackPtr->nextPtr->nextPtr = tempPtr;
    }
}

/*------------------------------------------------------*/
/* Stack Demo Application                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
void Stack_Demo(void)
{
    unsigned int operation = 0, object = 0;
    printf("STACK DEMO APPLICATION\n\n");
    printf("This implements a simple stqack. The objects are integers\n\n");
    
    StackPtr = (Stack_ElementType *)malloc(sizeof(struct Stack_Element_T));
    
    while(1)
    {
        printf("Choose the operation you would like to perform:\
               \n1: Push into Stack\
               \n2: Pop Stack\
               \n3: Exit Operation\n\n");
        
        scanf("%d", &operation);
        
        if (operation == 3)
            break;
        
        switch (operation)
        {
            case 1:
                printf("Enter the integer object \n");
                scanf("%d", &object);
                Stack_Push(StackPtr, object);
                break;
            case 2:
                object = Stack_Pop(StackPtr);
                printf("Object Popped: %d\n", object);
                break;
            case 3:
                break;
            default:
                printf("ERROR :@Stack Demo: Invalid Input\n\n");
                break;
        }
    }
}
