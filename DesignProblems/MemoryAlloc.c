//
//  MemoryAlloc.c
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

#include "MemoryAlloc.h"
#include "unistd.h"
#include "stdlib.h"

#define FREE_TREETYPE   (0)
#define ALLOC_TREETYPE  (1)

/* Data Structures */
MemoryAlloc_TreeType *FreeMemoryTree = NULL;
MemoryAlloc_TreeType *AllocatedMemoryTree = NULL;



/* Functions */
/* Insert to either tree */
static MemoryAlloc_TreeType *MemoryAlloc_Tree_Insert(void *memPtr, unsigned int memSize, MemoryAlloc_TreeType *treePtr, unsigned int treeType)
{
    unsigned int key, attr;
    if (treeType == FREE_TREETYPE)
    {
        key = memSize;
        attr =(unsigned int)memPtr;
    }
    else
    {
        key = (unsigned int)memPtr;
        attr =memSize;
    }
    if (treePtr == NULL)
    {
        /* Fresh tree - start */
        treePtr = (MemoryAlloc_TreeType *)memPtr;
        if (treeType == FREE_TREETYPE)
        {
            treePtr->key = key;
            treePtr->attr = attr;
        }
        else
        {
            treePtr->key = key;
            treePtr->attr = attr;
        }
        treePtr->leftPtr = NULL;
        treePtr->rightPtr = NULL;
    }
    else
    {
        if (treePtr->key > key)
        {
            treePtr->leftPtr = MemoryAlloc_Tree_Insert((void *)key, attr, treePtr->leftPtr, treeType);
        }
        else if (treePtr->key < key)
        {
            treePtr->rightPtr = MemoryAlloc_Tree_Insert((void *)key, attr, treePtr->rightPtr, treeType);
        }
        else
        {
            printf("ERROR : duplicate entries @ tree insert. ");
        }
    }
    return treePtr;
}

/* Searching the allocated tree */
static MemoryAlloc_TreeType *MemoryAlloc_Tree_FindDelete(unsigned int key, unsigned int *attr, MemoryAlloc_TreeType *treePtr)
{
    MemoryAlloc_TreeType *treeRet = treePtr;
    if (treeRet != NULL)
    {
        if (treeRet->key > key)
        {
            treeRet->leftPtr = MemoryAlloc_Tree_FindDelete(key, attr, treeRet->leftPtr);
        }
        else if (treeRet->key < key)
        {
            treeRet->rightPtr = MemoryAlloc_Tree_FindDelete(key, attr, treeRet->rightPtr);
        }
        else
        {
            /* THis is the node */
            *attr = treePtr->attr;
            MemoryAlloc_TreeType *tmp_TreePtr;
            unsigned int tmpAttr;
            /* Delete this node */
            if ( (treeRet->leftPtr != NULL)
                && (treeRet->rightPtr != NULL) )
            {
                /* Find minimum of the right tree */
                tmp_TreePtr = treeRet->rightPtr;
                while (tmp_TreePtr->leftPtr != NULL)
                {
                    tmp_TreePtr = tmp_TreePtr->leftPtr;
                }
                
                /* found the min. now replace the node with it */
                treeRet->key = tmp_TreePtr->key;
                treeRet->attr = tmp_TreePtr->attr;
                
                /* delete this found node */
                treeRet->rightPtr = MemoryAlloc_Tree_FindDelete(treePtr->key, &tmpAttr, treeRet->rightPtr);
            }
            else
            {
                tmp_TreePtr = treeRet;
                if (treeRet->rightPtr == NULL)
                {
                    treeRet = treePtr->leftPtr;
                }
                if (treeRet->leftPtr == NULL)
                {
                    treeRet = treePtr->leftPtr;
                }
                /* no free is necessary, we are working with free itself! */
            }
        }
    }
    return treeRet;
}

/* Searching the free tree */
static void *MemoryAlloc_Tree_GetFreeSlot(unsigned int size, MemoryAlloc_TreeType *treePtr)
{
    void *memPtr = NULL;
    MemoryAlloc_TreeType *tmpTreePtr = treePtr;
    MemoryAlloc_TreeType *greaterParent = NULL;
    unsigned int tempAttr, tempKey;
    
    /* Objective : Find a suitable size (best fit) and use only as much as necessary */
    while ( tmpTreePtr != NULL)
    {
        if (size > tmpTreePtr->key)
        {
            tmpTreePtr = tmpTreePtr->rightPtr;
        }
        else if (size < tmpTreePtr->key)
        {
            greaterParent = tmpTreePtr;
            tmpTreePtr = tmpTreePtr->leftPtr;
        }
        else
        {
            greaterParent = tmpTreePtr;
            break;
        }
    }
    tmpTreePtr = greaterParent;
    if (greaterParent != NULL)
    {
        /* Now, delete thie entry allocate only what is necessary */
        tempKey = tmpTreePtr->key;
        tempAttr = tmpTreePtr->attr;
        memPtr = (void *)tempAttr;
        tmpTreePtr = MemoryAlloc_Tree_FindDelete(tmpTreePtr->key, &tempAttr, tmpTreePtr);
        
        /* Now insert the necessary free block */
        if (tempKey - size > 0)
        {
            tempAttr = tempAttr + (tempKey-size);
            tempKey = tempKey - size;
            treePtr = MemoryAlloc_Tree_Insert(memPtr, tempKey, treePtr, FREE_TREETYPE);
        }
    }

    return memPtr;
}

void *MemoryAlloc_malloc(unsigned int size)
{
    void *memPtr = NULL;
    MemoryAlloc_TreeType *memTree = NULL;
    unsigned int memSize = size + sizeof(struct MemoryAlloc_Tree_T);
    
    /* find for free entry in the free tree */
    memPtr = MemoryAlloc_Tree_GetFreeSlot(memSize, FreeMemoryTree);
    
    if (memPtr == NULL)
    {
        /* IF none, allocate newly */
        memPtr = HEAP_TOP(memSize);
        /* Insert to allocated Tree */
        memTree = MemoryAlloc_Tree_Insert(memPtr, (unsigned int)memSize, AllocatedMemoryTree, ALLOC_TREETYPE);
    }
    
    return memPtr;
}

void MemoryAlloc_free(void *memPtr)
{
    MemoryAlloc_TreeType *memTree;
    
    unsigned int size = 0;
    /* Find and delete the entry in the allocated tree */
    memTree = MemoryAlloc_Tree_FindDelete((unsigned int)memPtr, &size, AllocatedMemoryTree);
    
    /* Insert the entry into the free tree*/
    FreeMemoryTree = MemoryAlloc_Tree_Insert(memPtr, size, FreeMemoryTree, FREE_TREETYPE);
}
