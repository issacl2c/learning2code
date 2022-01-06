//
//  Hash.c
//  issacl2c
//
//  Created by Issac on 27/12/21.
//

#include "Hash.h"
#include "math.h"   // for square root function
#if HASH_TYPE == STRING_HASH_TYPE
#include "string.h"
#endif

HASH_TABLE HashTablePtr = NULL;


/*------------------------------------------------------*/
/* Demo function for Hash                               */
/* Expects:                                             */
/* Returns:                                             */
/*------------------------------------------------------*/
void Hash_Demo(void)
{
    unsigned int operation = 0;
    Hash_KeyType key;
#if HASH_TYPE == STRING_HASH_TYPE
    key = (char *)malloc(sizeof(char) * HASH_MAX_KEY_SIZE);
#endif
    unsigned int tableSize, attr = 0;
    HASH_POSITION myHashEntryPtr = NULL;
    printf("OPEN HASH DEMO APPLICATION\n\n");
    printf("This implements an open hash table. The Keys are integer keys\n\n");
    while(1)
    {
        printf("Choose the operation you would like to perform:\
              \n1: Initialize a Hash Table\
              \n2: Insert Entry\
              \n3: Find Entry With Key\
              \n4: Delete Entry with Key\
              \n5: Print Hash Table\
              \n6: Exit Operation\n\n");
        
        scanf("%d", &operation);
        
        if (operation == 6)
            break;
        
        switch (operation)
        {
            case 1:
                printf("Enter the Hash table Size\n");
                scanf("%d", &tableSize);
                HashTablePtr = Hash_Table_Init(tableSize);
                printf("Hash Table initialized. Ptr = %x, Table Size = %d\n", (int)((void *)HashTablePtr), HashTablePtr->tableSize);
                break;
            case 2:
                printf("Enter the key and attribute\n");
#if HASH_TYPE == STRING_HASH_TYPE
                scanf("%s %d",key, &attr);
#else
                scanf("%d %d",&key,&attr);
#endif
                Hash_Table_Insert(key, attr, HashTablePtr);
                break;
            case 3:
                printf("Enter the key to find the entry\n");
#if HASH_TYPE == STRING_HASH_TYPE
                scanf("%s", key);
#else
                scanf("%d", &key);
#endif
                myHashEntryPtr = Hash_Table_Find(key, HashTablePtr);
                if (myHashEntryPtr != NULL)
                {
#if HASH_TYPE == STRING_HASH_TYPE
                printf("ENTRY FOUND: Ptr = %x, Key = %s, Attribute = %d\n\n", (int)((void *)myHashEntryPtr), myHashEntryPtr->key, myHashEntryPtr->attr);
#else
                printf("ENTRY FOUND: Ptr = %x, Key = %d, Attribute = %d\n\n", (int)((void *)myHashEntryPtr), myHashEntryPtr->key, myHashEntryPtr->attr);
#endif
                }
                else
                {
                    printf("ENTRY DOES NOT EXIST\n\n");
                }
                break;
            case 4:
                printf("Enter the key to Delete the Entry\n");
#if HASH_TYPE == STRING_HASH_TYPE
                scanf("%s", key);
#else
                scanf("%d", &key);
#endif
                Hash_Table_Delete(key, HashTablePtr);
                break;
            case 5:
                Hash_Utility_PrintHash(HashTablePtr);
                break;
            case 6:
                break;
            default:
                printf("ERROR :@Hash Demo: Invalid Input\n\n");
                break;
        }
    }
}

/*------------------------------------------------------*/
/* Initialize a Hash Table                              */
/* Expects:                                             */
/* 1: Size of the Hash Table                            */
/* Returns:                                             */
/* Pointer to the initialized Hash Table                */
/*------------------------------------------------------*/
HASH_TABLE Hash_Table_Init(unsigned int tableSize)
{
    HASH_TABLE hashTablePtr =  NULL;
    
    if (tableSize < HASH_MIN_SIZE)
    {
        printf("#ERROR: @Hash_Table_init(): Minimum Hash size not met");
    }
    else
    {
        hashTablePtr = (HASH_TABLE)malloc( sizeof(Hash_TableType)); // allocate the hash table root
        
        tableSize = Hash_Utility_NextPrime(tableSize);  // Table size should be prime.
        hashTablePtr->tableSize = tableSize;
        hashTablePtr->table = (HASH_POSITION)malloc( sizeof(Hash_EntryListType) * tableSize ); // allocate the lists
        
        unsigned int i = 0;
        
        for (i = 0; i < tableSize; i++)
        {
            hashTablePtr->table[i].nextPtr = NULL;  /* Sentinel node for the list @ position */
        }
    }
    
    return hashTablePtr;
}

/*------------------------------------------------------*/
/* Insert an entry to a Hash Table                      */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 2: Value for the entry                               */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/*------------------------------------------------------*/
void Hash_Table_Insert(Hash_KeyType key, Hash_AttrType attr, HASH_TABLE hashTablePtr)
{
    HASH_POSITION hashEntryPos = Hash_Table_Find(key, hashTablePtr);
#if HASH_TYPE == STRING_HASH_TYPE
    HASH_POSITION hashEntryHead = &(hashTablePtr->table[Hash_StringHash(key, hashTablePtr->tableSize)]);
#else
    HASH_POSITION hashEntryHead = &(hashTablePtr->table[Hash_IntHash(key, hashTablePtr->tableSize)]);
#endif
    
    if ( hashEntryPos == NULL )
    {
        hashEntryPos = (HASH_POSITION)malloc(sizeof(Hash_EntryListType));
#if HASH_TYPE == STRING_HASH_TYPE
        hashEntryPos->key = (char *)malloc(sizeof(char) * HASH_MAX_KEY_SIZE);
        (void)strcpy(hashEntryPos->key, key);
#else
        hashEntryPos->key = key;
#endif
        hashEntryPos->attr = attr;
        hashEntryPos->nextPtr = hashEntryHead->nextPtr;
        hashEntryHead->nextPtr = hashEntryPos;
    }
    
}

/*------------------------------------------------------*/
/* Delete an entry from a Hash Table                    */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/*------------------------------------------------------*/
void Hash_Table_Delete(Hash_KeyType key, HASH_TABLE hashTablePtr)
{
    HASH_POSITION hashEntryPos = Hash_Table_Find(key, hashTablePtr);
#if HASH_TYPE == STRING_HASH_TYPE
    HASH_POSITION hashEntryHead = &(hashTablePtr->table[Hash_StringHash(key, hashTablePtr->tableSize)]);
#else
    HASH_POSITION hashEntryHead = &(hashTablePtr->table[Hash_IntHash(key, hashTablePtr->tableSize)]);
#endif
    
    if ( hashEntryPos != NULL )
    {
        while ( hashEntryHead->nextPtr != hashEntryPos)
        {
            hashEntryHead = hashEntryHead->nextPtr;
        }
        hashEntryHead->nextPtr = hashEntryPos->nextPtr;
        free(hashEntryPos);
    }
}

/*------------------------------------------------------*/
/* Find an entry in the Hash Table                      */
/* Expects:                                             */
/* 1: Key for the entry                                 */
/* 3: Pointer to the hash table                         */
/* Returns:                                             */
/* Pointer to the entry in the Hash table               */
/*------------------------------------------------------*/
HASH_POSITION Hash_Table_Find(Hash_KeyType key, HASH_TABLE hashTablePtr)
{
    HASH_POSITION hashTableEntryPtr = NULL;
    
    if (hashTablePtr != NULL)
    {
#if HASH_TYPE == STRING_HASH_TYPE
        unsigned int hashIndex = Hash_StringHash(key, hashTablePtr->tableSize);
#else
        unsigned int hashIndex = Hash_IntHash(key, hashTablePtr->tableSize);
#endif
        hashTableEntryPtr = hashTablePtr->table[hashIndex].nextPtr;
        
        while (hashTableEntryPtr != NULL)  // Parse through the list
        {
#if HASH_TYPE == STRING_HASH_TYPE
            if (strcmp(hashTableEntryPtr->key, key) != 0)
#else
            if (hashTableEntryPtr->key != key)
#endif
            {
                hashTableEntryPtr = hashTableEntryPtr->nextPtr;
            }
            else
            {
                break;
            }
        }
        
    }
    return hashTableEntryPtr;
}

/*------------------------------------------------------*/
/* Find the Next prime number                           */
/* This is for normal integer values                    */
/* Expects:                                             */
/* Size of the Hash Table                               */
/* Returns:                                             */
/* Computed next prime                                  */
/*------------------------------------------------------*/
unsigned int Hash_Utility_NextPrime(unsigned int tableSize)
{
    unsigned int nextPrime = tableSize;
    unsigned int prime =0, i = 0;
    
    while (!prime)
    {
        if ( (nextPrime == 2)
            || (nextPrime == 3))
        {
            prime = 1;
            break;
        }
        if (nextPrime > 1)
        {
            if ( (nextPrime % 2 != 0)
                && (nextPrime % 3 != 0) )
            {
                if (i > 11)
                {
                    for (i = 5; i < (sqrt((double)nextPrime) + 1); i+=6)
                    {
                        if ( (nextPrime % i != 0) // divBy5
                            && (nextPrime % (i+2) != 0) )   // divBy7
                        {
                            prime = 1;
                            break;
                        }
                    }
                }
                else
                {
                    prime = 1; // 5, 7, 11
                }

            }
        }
        if (!prime)
        {
            nextPrime += 1;
        }
    }
    
    return nextPrime;
}

/*------------------------------------------------------*/
/* Find the hash function                               */
/* This is for normal integer values                    */
/* Expects:                                             */
/* 1: Key                                               */
/* 2: Size of the Hash Table                            */
/* Returns:                                             */
/* Computed hash function                               */
/*------------------------------------------------------*/
unsigned int Hash_IntHash(unsigned int key, unsigned int tableSize)
{
    unsigned int hash = 0;
    
    hash = key % tableSize;
    
    return hash;
}

/*------------------------------------------------------*/
/* Find the hash function                               */
/* This is for string Keys                              */
/* Expects:                                             */
/* 1: Key                                               */
/* 2: Size of the Hash Table                            */
/* Returns:                                             */
/* Computed hash function                               */
/* Hash function to compute is a polynomial             */
/* It uses Horner's rule to compute ASCII sum           */
/* of a given string.                                   */
/* the formula hk = ((k3) * 27 + k2) * 27 + k1.         */
/*------------------------------------------------------*/
unsigned int Hash_StringHash(char *key, unsigned int tableSize)
{
    unsigned int hash = 0;
    
    while (*key != '\0')
    {
        hash = (hash << 5u) + *key;
        key++;
    }
    
    hash = hash % tableSize;
    
    return hash;
}

/*------------------------------------------------------*/
/* Utility to print a Hash table                        */
/* Expects:                                             */
/* Pointer to the hash table                            */
/* Returns:                                             */
/*------------------------------------------------------*/
void Hash_Utility_PrintHash(HASH_TABLE hashTablePtr)
{
    unsigned int i = 0;
    HASH_POSITION hashTableEntry;
    
    if (hashTablePtr != NULL)
    {
        printf("HASH_TABLE->SIZE = %d\n", hashTablePtr->tableSize);
        for (i=0; i < hashTablePtr->tableSize; i++)
        {
            printf("HASH_TABLE->table[%d] -> ", i);
            hashTableEntry = &(hashTablePtr->table[i]);
            while (hashTableEntry->nextPtr != NULL)
            {
                hashTableEntry = hashTableEntry->nextPtr;
#if HASH_TYPE == STRING_HASH_TYPE
                printf("%s, %d -> ", hashTableEntry->key, hashTableEntry->attr);
#else
                printf("%d, %d -> ", hashTableEntry->key, hashTableEntry->attr);
#endif
            }
            printf("NULL\n");
        }
    }
}
