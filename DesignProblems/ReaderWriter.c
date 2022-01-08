//
//  ReaderWriter.c
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

#include "ReaderWriter.h"
#include <semaphore.h>  // we need semaphore here.
#include <pthread.h>    // we need some threads, mutexes.

static volatile unsigned int        TestArray[READERWRITER_ARRAYSIZE] = {1,1};
static volatile unsigned int        ReadersIn = 0;
static volatile unsigned int        ReadersOut = 0;
static volatile unsigned int        ModifyCounter = 0;
static volatile unsigned int        WriterWaiting = 0;


static pthread_mutex_t  In;
static pthread_mutex_t  Out;

static sem_t            *ReadWriteSem;

static void *writer(void *param)
{
    while (ModifyCounter < READERWRITER_MAX_MODIFICATIONS)
    {
        pthread_mutex_lock(&In);        /* Writer is IN */
        pthread_mutex_lock(&Out);       /* No one can get out now, let me assess the read Queue */
        
        if (ReadersIn == ReadersOut)    /* See if there are no pending readers */
        {
            pthread_mutex_unlock(&Out); /* No use locking when no one is inside.. */
        }
        else
        {
            /* some folks are still reading. */
            WriterWaiting = 1;          /* Writer is waiting, guys */
            pthread_mutex_unlock(&Out); /* Get out - all you pending readers */
            sem_wait(ReadWriteSem);     /* I'll just wait here to be allowed to write.. */
            WriterWaiting = 0;          /* No longer waiting! */
        }
        /* no one can get in here - modify the data structures */
        printf("\nWriter %d About to Modify the Array\n", (int)param  );
        for (unsigned int i = 0; i < READERWRITER_ARRAYSIZE; i++)
        {
            TestArray[i] += 1;
        }
        ModifyCounter++;
        pthread_mutex_unlock(&In);  /* Someone else can get in now...*/
    }
    pthread_exit(0);
}

static void *reader(void *param)
{
    unsigned int result = 0;
    static unsigned int previousValue = 0;
    
    while (ModifyCounter < READERWRITER_MAX_MODIFICATIONS)
    {
        pthread_mutex_lock(&In);                    /* Let me In, I'm a Reader */
        ReadersIn++;                                /* Register myself as an active reader */
        pthread_mutex_unlock(&In);                  /* I don't need exclusive access */
        
        if (previousValue != TestArray[0])  /* I got a new value */
        {
            /* We are now in the safe reading section */
            switch ( (int)param )
            {
            case (READERWRITER_READOP_ADD):
            {
                result = TestArray[0] + TestArray[1];
                break;
            }
            case (READERWRITER_READOP_MUL):
            {
                result = TestArray[0] * TestArray[1];
                break;
            }
            case (READERWRITER_READOP_EXP):
            {
                result = TestArray[0];
                for (unsigned int i = 0; i < TestArray[1]; i++)
                {
                    result = result * TestArray[0];
                }
                break;
            }
            default:
                break;
            }
            printf("\n Reader %d Result after operation on %d, %d = %d \n", (int)param, TestArray[0], TestArray[1], result);
            
            previousValue = TestArray[0];
        }

        /* we are done */
        pthread_mutex_lock(&Out);       /* I want to get out */
        ReadersOut++;
        if (ReadersOut == ReadersIn)    /* I'm the last Reader */
        {
            if (WriterWaiting == 1)     /* Writer is waiting */
            {
                sem_post(ReadWriteSem); /* Signal the writer to begin writing */
            }
        }
        pthread_mutex_unlock(&Out);     /* I'm out.. */
    }
    
    pthread_exit(0);
}

void ReaderWriter_Demo(void)
{
    pthread_attr_t genericAttr;
    pthread_attr_init (&genericAttr);
 
    printf("\n---------------READER_WRITER SHOW BEGINS-------------------\n");
    
    sem_unlink("ReadWriteSem");
    ReadWriteSem = sem_open("ReadWriteSem", O_CREAT|O_EXCL, 0666, 1);   /* Create the read-write semaphore */
    
    /* Initialize the MUTEXES */
    pthread_mutex_init(&In, NULL);
    pthread_mutex_init(&Out, NULL);
    
    /* Spawn the readers */
    pthread_t readers[READERWRITER_NUM_READERS];
    for (unsigned int i = 0; i < READERWRITER_NUM_READERS; i++)
    {
        pthread_create(&(readers[i]), &genericAttr, reader, (void *)i);
    }
    
    /* Spawn the writers */
    pthread_t writers[READERWRITER_NUM_WRITERS];
    for (unsigned int i = 0; i < READERWRITER_NUM_WRITERS; i++)
    {
        pthread_create(&(writers[i]), &genericAttr, writer, (void *)i);
    }
    
    /* Join everyone */
    for (unsigned int i = 0; i < READERWRITER_NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (unsigned int i = 0; i < READERWRITER_NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }
    
    printf("\n---------------READER_WRITER SHOW OVER-------------------\n");
    
    
}

