//
//  BinaryTrees.c
//  issacl2c
//
//  Created by Issac on 12/12/21.
//

#include "BinaryTree.h"

BINARY_TREE BinTreePtr = NULL;
/*------------------------------------------------------*/
/* Demo function for binary tree                        */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
void BinaryTree_Demo(void)
{
    unsigned int operation = 0;
    unsigned int key, attr = 0;
    BinaryTree_NodeType *myNodePtr = NULL;
    printf("BINARY TREE DEMO APPLICATION\n\n");
    printf("This Binary Tree is a Binary Search Tree. Each node as 1 Key and 1 Attribute\n\n");
    while(1)
    {
        printf("Choose the operation you would like to perform:\
              \n1: Insert Node\
              \n2: Find Node With Key\
              \n3: Delete Node with Key\
              \n4: Find Node with minimum value\
              \n5: Find Node with Max value\
              \n6: Print Binary Tree in Order\
              \n7: Print Binary Tree Pre-Order\
              \n8: Print Binary Tree Post-Order\
              \n7: Exit Operation\n\n");
        
        scanf("%d", &operation);
        
        if (operation == 7)
            break;
        
        switch (operation)
        {
            case 1:
                printf("Enter the Key and Attribute\n");
                scanf("%d %d", &key, &attr);
                BinTreePtr = BinaryTree_InsertNode(key, attr, BinTreePtr);
                //printf("Resulting Tree is:\n");
                break;
            case 2:
                printf("Enter the key to find the Node\n");
                scanf("%d",&key);
                myNodePtr = BinaryTree_FindNode(key, BinTreePtr);
                if (myNodePtr != NULL)
                {
                    printf("NODE FOUND: Ptr = %x, Key = %d, Attribute = %d\n\n", (int)((void *)myNodePtr), myNodePtr->key, myNodePtr->attr);
                }
                else
                {
                    printf("NODE DOES NOT EXIST\n\n");
                }
                break;
            case 3:
                printf("Enter the key to Delete the Node\n");
                scanf("%d",&key);
                myNodePtr = BinaryTree_DeleteNode(key, BinTreePtr);
                break;
            case 4:
                myNodePtr = BinaryTree_FindMinNode(BinTreePtr);
                if (myNodePtr != NULL)
                printf("MIN NODE: Ptr = %x, Key = %d, Attribute = %d\n\n", (int)((void *)myNodePtr), myNodePtr->key, myNodePtr->attr);
                break;
            case 5:
                myNodePtr = BinaryTree_FindMaxNode(BinTreePtr);
                if (myNodePtr != NULL)
                printf("MAX NODE: Ptr = %x, Key = %d, Attribute = %d\n\n", (int)((void *)myNodePtr), myNodePtr->key, myNodePtr->attr);
                break;
            case 6:
                BinaryTree_InOrderPrint(BinTreePtr);
                break;
            case 7:
                break;
            default:
                printf("ERROR :@BinaryTree_Demo: Invalid Input\n\n");
                break;
        }
    }
}

/*------------------------------------------------------*/
/* Insert Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be inserted                        */
/* 2: Attribute of node                                 */
/* 3: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
BINARY_TREE BinaryTree_InsertNode(unsigned int key, unsigned int attr, BINARY_TREE treePtr)
{
    //BINARY_TREE retTreePtr = treePtr;
    if (treePtr == NULL)
    {
        treePtr = (BINARY_TREE)(malloc(sizeof( struct BinaryTreeNode_T )));
        if (treePtr != NULL)
        {
            treePtr->key = key;
            treePtr->attr = attr;
            treePtr->leftNodePtr = NULL;
            treePtr->rightNodePtr = NULL;
        }
        else
        {
            printf("#ERROR: @BinaryTree_InsertNode: Not enough memory to insert Tree Node\n");
        }
    }
    else if (key < treePtr->key)
    {
        treePtr->leftNodePtr = BinaryTree_InsertNode(key, attr, treePtr->leftNodePtr);
    }
    else if (key > treePtr->key)
    {
        treePtr->rightNodePtr = BinaryTree_InsertNode(key, attr, treePtr->rightNodePtr);
    }
    else    //key already exists
    {
        printf("#ERROR: @BinaryTree_InsertNode: KEY with value %d already exists with attr %d\n", key, attr);
    }
    return treePtr;
}


/*------------------------------------------------------*/
/* Delete Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be deleted                         */
/* 2: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
BINARY_TREE BinaryTree_DeleteNode(unsigned int key, BINARY_TREE treePtr)
{
    BINARY_TREE tmp_treePtr;
    if (treePtr != NULL)
    {
        if (key < treePtr->key)
        {
            treePtr->leftNodePtr = BinaryTree_DeleteNode(key, treePtr->leftNodePtr);
        }
        else if (key > treePtr->key)
        {
            treePtr->rightNodePtr = BinaryTree_DeleteNode(key, treePtr->rightNodePtr);
        }
        else
        {
            /* Found the Node to delete */
            if ( (treePtr->rightNodePtr != NULL)
                && (treePtr->leftNodePtr != NULL) )
            {
                /* Two Children Case */
                tmp_treePtr = BinaryTree_FindMinNode(treePtr->rightNodePtr);
                treePtr->key = tmp_treePtr->key;
                treePtr->attr = tmp_treePtr->attr;
                treePtr->rightNodePtr = BinaryTree_DeleteNode(treePtr->key, treePtr->rightNodePtr);
            }
            else
            {
                tmp_treePtr = treePtr;
                if (tmp_treePtr->rightNodePtr == NULL)
                {
                    /* Only left Child Exists */
                    treePtr = tmp_treePtr->leftNodePtr;
                }
                if (tmp_treePtr->leftNodePtr == NULL)
                {
                    /* Only right Child Exists */
                    treePtr = tmp_treePtr->rightNodePtr;
                }
                
                free(tmp_treePtr);
            }
        }

    }
    else
    {
        printf("#ERROR: @BinaryTree_DeleteNode: Element not found\n");
    }
        
    return treePtr;
}

/*------------------------------------------------------*/
/* Find node in a Binary Tree                           */
/* Expects:                                             */
/* 1: Key of node to be found                           */
/* 2: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node                                  */
/*------------------------------------------------------*/
BinaryTree_NodeType *BinaryTree_FindNode(unsigned int key, BINARY_TREE treePtr)
{
    BinaryTree_NodeType *retNodePtr = treePtr;
    if (retNodePtr != NULL)
    {
        if (key < retNodePtr->key)
        {
            retNodePtr = BinaryTree_FindNode(key, retNodePtr->leftNodePtr);
        }
        else if (key > retNodePtr->key)
        {
            retNodePtr = BinaryTree_FindNode(key, retNodePtr->rightNodePtr);
        }
        else
        {
            /* Do nothing, we already have the retNodePtr in the correct node*/
        }
    }
    return retNodePtr;
}

/*------------------------------------------------------*/
/* Find Minimum node in a Binary Tree                   */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node with min key                     */
/*------------------------------------------------------*/
BinaryTree_NodeType *BinaryTree_FindMinNode(BINARY_TREE treePtr)
{
    BinaryTree_NodeType *retNodePtr = treePtr;
    
    if (retNodePtr == NULL)
    {
        printf("#ERROR: @BinaryTree_FindMinNode: Binary Tree Pointer is NULL \n");
    }
    else
    {
        while (retNodePtr->leftNodePtr != NULL)
        {
            retNodePtr = retNodePtr->leftNodePtr;
        }
    }
    return retNodePtr;
}

/*------------------------------------------------------*/
/* Find Maximum node in a Binary Tree                   */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node with max key                     */
/*------------------------------------------------------*/
BinaryTree_NodeType *BinaryTree_FindMaxNode(BINARY_TREE treePtr)
{
    BinaryTree_NodeType *retNodePtr = treePtr;
    
    if (retNodePtr == NULL)
    {
        printf("#ERROR: @BinaryTree_FindMaxNode: Binary Tree Pointer is NULL \n");
    }
    else
    {
        while (retNodePtr->rightNodePtr != NULL)
        {
            retNodePtr = retNodePtr->rightNodePtr;
        }
    }
    return retNodePtr;
}

/*------------------------------------------------------*/
/* Print nodes in a Binary Tree in order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
void BinaryTree_InOrderPrint(BINARY_TREE treePtr)
{
    if (treePtr == NULL)
    {
        printf("NULL \n");
    }
    else
    {
        BinaryTree_InOrderPrint(treePtr->leftNodePtr);
        printf("Key = %d, Attr = %d\n", treePtr->key, treePtr->attr);
        BinaryTree_InOrderPrint(treePtr->rightNodePtr);
    }
}

/*------------------------------------------------------*/
/* Print nodes in a Binary Tree Pre order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
void BinaryTree_PreOrderPrint(BINARY_TREE treePtr)
{
    while (treePtr != NULL)
    {
        /* Print node first */
        printf("Key = %d, Attr = %d\n", treePtr->key, treePtr->attr);
        BinaryTree_PreOrderPrint(treePtr->leftNodePtr);
        BinaryTree_PreOrderPrint(treePtr->rightNodePtr);
    }
}

/*------------------------------------------------------*/
/* Print nodes in a Binary Tree Post order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
void BinaryTree_PostOrderPrint(BINARY_TREE treePtr)
{
    while (treePtr != NULL)
    {
        /* Print Children */
        BinaryTree_PreOrderPrint(treePtr->leftNodePtr);
        BinaryTree_PreOrderPrint(treePtr->rightNodePtr);
        /* Print node last */
        printf("Key = %d, Attr = %d\n", treePtr->key, treePtr->attr);
    }
}
