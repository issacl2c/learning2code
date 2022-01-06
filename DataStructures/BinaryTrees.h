//
//  BinaryTrees.h
//  issacl2c
//
//  Created by Issac on 12/12/21.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>

typedef struct BinaryTreeNode_T
{
    unsigned int        key;                // Key of the node
    unsigned int        attr;               // Data in the node
    BinTreeNodeType     *rightNodePtr;      // Pointer to the right node
    BinTreeNodeType     *leftNodePtr;       // Pointer to the left node
}BinTreeNodeType;

typedef BinTreeNodeType *BINARY_TREE;

/* Tree Function Declarations */

/*------------------------------------------------------*/
/* Insert Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be inserted                        */
/* 2: Attribute of node                                 */
/* 3: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
extern BINARY_TREE BinTree_InsertNode(unsigned int key, unsigned int attr, BINARY_TREE treePtr);


/*------------------------------------------------------*/
/* Delete Node into a Binary Tree                       */
/* Expects:                                             */
/* 1: Key of node to be deleted                         */
/* 2: Tree HEAD pointer                                 */
/* Returns:                                             */
/* Tree HEAD Pointer                                    */
/*------------------------------------------------------*/
extern BINARY_TREE BinTree_DeleteNode(unsigned int key, BINARY_TREE treePtr);




#endif /* BinaryTree_h */
