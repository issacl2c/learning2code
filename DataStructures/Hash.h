//
//  Hash.h
//  issacl2c
//
//  Created by Issac on 27/12/21.
//
// This file implements a "open hash table". It uses open hashing algorithm with linked list implementation.

#ifndef Hash_h
#define Hash_h

#include <stdio.h>
#include <stdlib.h>
#include "Types.h"

#define INTEGER_HASH_TYPE (0)
#define STRING_HASH_TYPE (1)

#define HASH_TYPE STRING_HASH_TYPE
#define HASH_MAX_KEY_SIZE 50

/* Exported Types */
#if HASH_TYPE == STRING_HASH_TYPE
typedef char *    Hash_KeyType;
typedef unsigned int Hash_AttrType;
#else
typedef unsigned int Hash_KeyType;
typedef unsigned int Hash_AttrType;
#endif

typedef struct Hash_EntryList_T
{
    Hash_KeyType                    key;                // Key
    Hash_AttrType                   attr;               // Value @ this entry
    struct Hash_EntryList_T         *nextPtr;           // Pointer to the next entry
}Hash_EntryListType;

typedef Hash_EntryListType *HASH_POSITION;

typedef struct Hash_Table_T
{
    unsigned int                    tableSize;          // Size of the Hash Table
    Hash_EntryListType              *table;             // Array of Hash Table Entries
}Hash_TableType;

typedef Hash_TableType *HASH_TABLE;


/* Exported Variables */
extern HASH_TABLE HashTablePtr;

/* Exported Defines */
#define HASH_MIN_SIZE (1)

/* Hash Function Declarations */

/*------------------------------------------------------*/
/* Demo function for Hash                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Hash_Demo(void);

/*------------------------------------------------------*/
/* Initialize a Hash Table                              */
/* Expects:                                             */
/* 1: Size of the Hash Table                            */
/* Returns:                                             */
/* Pointer to the initialized Hash Table                */
/*------------------------------------------------------*/
extern HASH_TABLE Hash_Table_Init(unsigned int tableSize);

/*------------------------------------------------------*/
/* Insert an entry to a Hash Table                      */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 2: Value for the entry                               */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Hash_Table_Insert(Hash_KeyType key, Hash_AttrType attr, HASH_TABLE hashTablePtr);

/*------------------------------------------------------*/
/* Delete an entry from a Hash Table                    */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Hash_Table_Delete(Hash_KeyType key, HASH_TABLE hashTablePtr);

/*------------------------------------------------------*/
/* Find an entry in the Hash Table                      */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/* Pointer to the entry in the Hash table               */
/*------------------------------------------------------*/
extern HASH_POSITION Hash_Table_Find(Hash_KeyType key, HASH_TABLE hashTablePtr);

/*------------------------------------------------------*/
/* Find the Next prime number                           */
/* This is for normal integer values                    */
/* Expects:                                             */
/* Size of the Hash Table                               */
/* Returns:                                             */
/* Computed next prime                                  */
/*------------------------------------------------------*/
extern unsigned int Hash_Utility_NextPrime(unsigned int tableSize);

/*------------------------------------------------------*/
/* Utility to print a Hash table                        */
/* Expects:                                             */
/* Pointer to the hash table                            */
/* Returns:                                             */
/*------------------------------------------------------*/
extern void Hash_Utility_PrintHash(HASH_TABLE hashTablePtr);

/*------------------------------------------------------*/
/* Find the hash function                               */
/* This is for normal integer values                    */
/* Expects:                                             */
/* 1: Key                                               */
/* 2: Size of the Hash Table                            */
/* Returns:                                             */
/* Computed hash function                               */
/*------------------------------------------------------*/
extern unsigned int Hash_IntHash(unsigned int key, unsigned int tableSize);

/*------------------------------------------------------*/
/* Find the hash function                               */
/* This is for string Keys                              */
/* Expects:                                             */
/* 1: Key                                               */
/* 2: Size of the Hash Table                            */
/* Returns:                                             */
/* Computed hash function                               */
/*------------------------------------------------------*/
extern unsigned int Hash_StringHash(char *key, unsigned int tableSize);







#endif /* Hash_h */
