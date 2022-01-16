//
//  BinaryTree.h
//  issacl2c
//
//  Created by Issac on 12/12/21.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>
#include <stdlib.h>
#include "Types.h"

/* Exported Types */
typedef struct BinaryTreeNode_T
{
    unsigned int                key;                // Key of the node
    unsigned int                attr;               // Data in the node
    struct BinaryTreeNode_T     *rightNodePtr;      // Pointer to the right node
    struct BinaryTreeNode_T     *leftNodePtr;       // Pointer to the left node
}BinaryTree_NodeType;

typedef BinaryTree_NodeType *BINARY_TREE;


/* Exported Variables */
extern BINARY_TREE BinTreePtr;

/* Tree Function Declarations */

/*------------------------------------------------------*/
/* Demo function for binary tree                        */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void BinaryTree_Demo(void);


/*------------------------------------------------------*/
/* Insert Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be inserted                        */
/* 2: Attribute of node                                 */
/* 3: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
extern BINARY_TREE BinaryTree_InsertNode(unsigned int key, unsigned int attr, BINARY_TREE treePtr);


/*------------------------------------------------------*/
/* Delete Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be deleted                         */
/* 2: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
extern BINARY_TREE BinaryTree_DeleteNode(unsigned int key, BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Find node in a Binary Tree                           */
/* Expects:                                             */
/* 1: Key of node to be found                           */
/* 2: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node                                  */
/*------------------------------------------------------*/
extern BinaryTree_NodeType *BinaryTree_FindNode(unsigned int key, BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Find Minimum node in a Binary Tree                   */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node with min key                     */
/*------------------------------------------------------*/
extern BinaryTree_NodeType *BinaryTree_FindMinNode(BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Find Maximum node in a Binary Tree                   */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* pointer to the node with max key                     */
/*------------------------------------------------------*/
extern BinaryTree_NodeType *BinaryTree_FindMaxNode(BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Print nodes in a Binary Tree Pre order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
extern void BinaryTree_PreOrderPrint(BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Print nodes in a Binary Tree Post order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
extern void BinaryTree_PostOrderPrint(BINARY_TREE treePtr);

/*------------------------------------------------------*/
/* Print nodes in a Binary In Post order                */
/* Expects:                                             */
/* 1: Tree HEAD pointer                                 */
/* Returns:                                             */
/* void                                                 */
/*------------------------------------------------------*/
extern void BinaryTree_InOrderPrint(BINARY_TREE treePtr);




#endif /* BinaryTree_h */
