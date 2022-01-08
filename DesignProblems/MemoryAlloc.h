//
//  MemoryAlloc.h
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

/* Problem statement:
 - Implement a simple malloc() and free() for a generic architecture and OS
 
 ASSUMPTIONS
 ------------
 - We are operating within the process space. There is a HEAP top defined, which can be obtained using HEAP_TOP.
 */

/* Demonstrated Result:
 - Keep two trees: one for allocated memory blocks, and one for free memory blocks.
    -WHY?
        -- free tree requires searching for "best fit". The key of this tree is the "free size".
        -- Allocated tree requires searching for the pointer. The key of this tree is the pointer.
        -- both searches happen at O(logn) time.
 - Each time an allocation is requested, scan the free tree for best fit.
        -- pop it out, place it in the allocated tree, with the pointer as the key.
 - If nothing is found, then - take new memory from the HEAP_TOP and insert into allocated tree.
 
 for a good reference point: look here: https://danluu.com/malloc-tutorial/
 My solution is better than the above link in 2 aspects:
 --> the implementation of trees makes searching more efficient.
 --> The free block sizes are split to use only the required sections.
 
 Improvements:
 --> Make it thread safe.
 
 Testing:
 --> Need to test by replacing the C library stock functions. not done.
 */

/* Exported types */
typedef struct MemoryAlloc_Tree_T
{
    unsigned int key;
    unsigned int attr;
    struct MemoryAlloc_Tree_T *leftPtr;
    struct MemoryAlloc_Tree_T *rightPtr;
}MemoryAlloc_TreeType;

/* Extern stuff */
#define HEAP_TOP(size) sbrk(size)

extern void *MemoryAlloc_malloc(unsigned int size);

extern void MemoryAlloc_free(void *memPtr);


#ifndef MemoryAlloc_h
#define MemoryAlloc_h

#include <stdio.h>

#endif /* MemoryAlloc_h */
