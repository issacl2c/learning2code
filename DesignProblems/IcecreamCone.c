//
//  IcecreamCone.c
//  issacl2c
//
//  Created by Issac on 06/01/22.
//

#include "IcecreamCone.h"
#include <stdio.h>
#include <stdlib.h>     // we need the standard library functions including rand()
#include <pthread.h>    // we need some threads, mutexes.
#include <semaphore.h>  // we need semaphore.
#include "Queue.h"      // we  need the Queue data type

/* Static variables */
static volatile unsigned int            CustomerCount           = 0;
static volatile unsigned int            CustomerID              = 0;
static volatile unsigned int            CloseShop               = 0;

static unsigned int                     maxManagerQSize         = MANAGER_QUEUE_SIZE;
static unsigned int                     maxConesPerCustoemr     = MAX_CONES_PER_CUSTOMER;
static Queue_ListType                   *OfficeQueue;
static Queue_ListType                   *CashierQueue;

static pthread_mutex_t                  managerQueue;
static pthread_mutex_t                  cashierQueue;
static pthread_mutex_t                  customerQueue;
static pthread_mutex_t                  customerID;

static sem_t                            *managersOffice;
static sem_t                            *workerInQueue;
static sem_t                            *cashiersOffice;
static sem_t                            *conesForPayment;
/*------------------------------------------------------*/
/* Ice Cream Store Manager Function                     */
/* Manages the quality of the cones                     */
/* Has a queue of workers waiting for approval          */
/* Expects:                                             */
/* 1. What kind of queue size do I have today?          */
/* Returns:                                             */
/* Nothing                                              */
/*------------------------------------------------------*/
static void *IcecreamCone_Manager(void *param)
{
    OfficeQueue = NULL;
    volatile IcecreamCone_ConeType   *ConeForEvaluation;

    
    OfficeQueue = Queue_List_Init(OfficeQueue); /* Create a Queue for my beloved workers */
    
    sem_unlink("managersOffice");
    managersOffice = sem_open("managersOffice", O_CREAT|O_EXCL, 0666, (int)(*((int *)param)));   /* Create sem for size Queue */
    if (managersOffice == SEM_FAILED)
    {
        printf("Failed to create managersOffice semaphore\n");
        pthread_exit(1);
    }
    pthread_mutex_init(&managerQueue, NULL);            /* Initialize my office for mutual exclusivity */
    pthread_mutex_init(&customerQueue, NULL);           /* Customer is king - don't disturb them */
    
    sem_unlink("workerInQueue");
    workerInQueue = sem_open("workerInQueue", O_CREAT|O_EXCL, 0666, 0);              /* I'm ready for workers */
    if (workerInQueue == SEM_FAILED)
    {
        printf("Failed to create workerInQueue semaphore\n");
        pthread_exit(1);
    }
    while (CustomerCount > 0)                            /* As long as we have customers, I'm here */
    {
        sem_wait(workerInQueue);                         /* Wait for a worker */
        
        if (CloseShop == 0)                              /* Cashier says go home */
        {
            pthread_mutex_lock(&managerQueue);                      /* lock my queue */
            ConeForEvaluation = Queue_List_Extract(OfficeQueue);  /*Show me what you made! */
            pthread_mutex_unlock(&managerQueue);                    /* Unlock my queue */
            
            ConeForEvaluation->qualityAccepted = (boolean)(rand() % 2); // My decisions are anyways random..Good luck!
            ConeForEvaluation->qualityCheckDone = 1;
            
            printf("\n Manager: QC done for Customer: %d, Cone %d. RESULT: %d ! \n", ConeForEvaluation->customerNum, ConeForEvaluation->coneNum, ConeForEvaluation->qualityAccepted);
            
            sem_post(managersOffice);                              /* one more person can enter now */
        }
        else
        {
            printf(" Manager: Time to go home. All customers done\n");
            break;
        }

    }

    pthread_exit(0);                            // Apparently this also returns the function!
}

/*------------------------------------------------------*/
/* Ice Cream Store Cashier Function                     */
/* Accepts payments.                                    */
/* Tell the customer to buzz off                        */
/* Expects:                                             */
/* Nothing                                              */
/* Returns:                                             */
/* Nothing                                              */
/*------------------------------------------------------*/
static void *IcecreamCone_Cashier(void *param)
{
    CashierQueue = Queue_List_Init(CashierQueue);            /* Create a Queue for my beloved customers */
    volatile IcecreamCone_ConeType   *ConeForEvaluation = NULL;
    sem_unlink("cashiersOffice");
    sem_unlink("conesForPayment");
    cashiersOffice = sem_open("cashiersOffice", O_CREAT|O_EXCL, 0666, 1);             // I can handle one customer at a time.
    conesForPayment = sem_open("conesForPayment", O_CREAT|O_EXCL, 0666, 0);           // I also need a customer to start!
    
    while (CustomerCount > 0)
    {
        sem_wait(conesForPayment);
        if (CloseShop == 0)
        {
            pthread_mutex_lock(&cashierQueue);
            ConeForEvaluation = Queue_List_Extract(CashierQueue);  /* Show me the money! */
            ConeForEvaluation->paymentAccepted = 1;
            pthread_mutex_unlock(&cashierQueue);
            printf("\n Cashier: Processed payment for Customer: %d, Cone %d ! \n", ConeForEvaluation->customerNum, ConeForEvaluation->coneNum);
            sem_post(cashiersOffice);
        }
        else
        {
            break;
        }

    }
    printf("\n Cashier: All payments completed. I'm done! \n");
    
    pthread_exit(0);                            // Apparently this also returns the function!
}


/*------------------------------------------------------*/
/* Ice Cream Store Worker Function                      */
/* Makes a cone, takes it for approval, returns back    */
/* Expects:                                             */
/* 1. Cone Pointer                                      */
/* Returns:                                             */
/*                                                      */
/*------------------------------------------------------*/
static void *IcecreamCone_Worker(void *param)
{
    volatile IcecreamCone_ConeType *myCone = (IcecreamCone_ConeType *)param;
    
    myCone->qualityAccepted = 0;                        // Create the cone.
    myCone->paymentAccepted = 0;
    myCone->qualityCheckDone = 0;

    
    sem_wait(managersOffice);                          // wait for managers office
    pthread_mutex_lock(&managerQueue);                  // Lock the Queue
    Queue_List_Insert(OfficeQueue, myCone);   // Insert into Queue
    sem_post(workerInQueue);
    pthread_mutex_unlock(&managerQueue);
    printf("\n Worker: Customer %d Cone %d Waiting for manager approval \n", myCone->customerNum, myCone->coneNum);
    
    while (myCone->qualityAccepted == 0)                // wait meaninglessly till boss approves.
    {
        if (myCone->qualityCheckDone == 1)
        {
            myCone->qualityCheckDone = 0;
            sem_wait(managersOffice);                          // wait for managers office
            pthread_mutex_lock(&managerQueue);                  // Lock the Queue
            Queue_List_Insert(OfficeQueue, myCone);   // Insert into Queue
            sem_post(workerInQueue);
            pthread_mutex_unlock(&managerQueue);
        }
    }
    
    printf("\n Worker: Customer %d Cone %d Quality accepted! \n", myCone->customerNum, myCone->coneNum);
    
    pthread_exit(0);                                        // Apparently this also returns the function!
}

/*------------------------------------------------------*/
/* Ice Cream Store Customer Function                    */
/* Hopefully not obese. Buys a number of ice-cream cones*/
/* Waits for the cones to arrive, pays and leaves       */
/* Expects:                                             */
/* 1. How many cones can I buy today?                   */
/* Returns:                                             */
/* Nothing                                              */
/*------------------------------------------------------*/
static void *IcecreamCone_Customer(void *param)
{
    unsigned int myCones    = rand() % (int)(*((int *)param));    // choose a random value until MAX
    
    pthread_mutex_lock(&customerID);
    CustomerID++;
    unsigned int myNum      = CustomerID;             // Register myself.
    pthread_mutex_unlock(&customerID);
    
    volatile IcecreamCone_ConeType   *cones = (IcecreamCone_ConeType *)malloc(sizeof(struct IcecreamCone_Cone_T) * myCones);
    pthread_t *coneWorker = (pthread_t *)malloc(sizeof(pthread_t) * myCones);
    
    pthread_attr_t workerAttr;
    pthread_attr_init(&workerAttr);             // I don't care what the worker looks like.
    
    printf("\n\nI'm customer : %d, and I need %d cones\n", myNum, myCones);
    
    for (unsigned int worker = 0; worker < myCones; worker++)   // off you go, prepare my cones!
    {
        cones->customerNum = myNum;
        cones->coneNum = worker;
        pthread_create(&coneWorker[worker], &workerAttr, IcecreamCone_Worker, (void *)&(cones[worker]));
        printf("I'm Customer: %d and I Dispatched Cone #%d with Worker\n", myNum, worker);
    }
    
    for (unsigned int worker = 0; worker < myCones; worker++)   // tick-tock.. where are they?
    {
        pthread_join(coneWorker[worker], NULL);
    }
    
    for (unsigned int conePayment = 0; conePayment < myCones; conePayment++)   // let me pay for all
    {
        sem_wait(cashiersOffice);          // wait for cashier's office to be free.
        pthread_mutex_lock(&cashierQueue);
        Queue_List_Insert(CashierQueue, (&cones[conePayment]));
        sem_post(conesForPayment);
        pthread_mutex_unlock(&cashierQueue);
        
        while(cones[conePayment].paymentAccepted == 0)                      // wait for payment to complete.
        {
        }
        printf("I'm customer %d, I Paid for Cone #%d\n", myNum, conePayment);
        
    }
    
    pthread_mutex_lock(&customerQueue);
    CustomerCount--;                        // Get out without disturbing anyone.
    pthread_mutex_unlock(&customerQueue);
    printf("I'm customer %d, I'm leaving the store! \n", myNum);
    pthread_exit(0);                            // Apparently this also returns the function!
}

/*------------------------------------------------------*/
/* Ice Cream Store Function                             */
/* Demonstrates the ice cream store functionality       */
/* Expects:                                             */
/* 1. Number of customers                               */
/* Returns:                                             */
/* Nothing                                              */
/*------------------------------------------------------*/
void IcecreamCone_Store(unsigned int numCustomers)
{
    pthread_attr_t genericAttr;
    pthread_t customerThread[numCustomers];    // instantiate an array of customer threads
    pthread_t managerThread;                    // Manager of the store
    pthread_t cashierThread;                    // Cashier of the store
    
    CustomerCount = numCustomers;
    CustomerID    = 0;
    pthread_mutex_init(&customerID, NULL);
    
    printf("\n-------------------STORE OPEN------------------------\n");
    printf("\n------------------%d CUSTOMERS-----------------------\n", numCustomers);
    
    pthread_attr_init(&genericAttr);
    pthread_create(&managerThread, &genericAttr, IcecreamCone_Manager, &maxManagerQSize); // Create Manager
    pthread_create(&cashierThread, &genericAttr, IcecreamCone_Cashier, NULL);

    
    /* Let there be customers! */
    for (unsigned int i = 0; i < numCustomers; i++)
    {
        pthread_create(&(customerThread[i]), &genericAttr, IcecreamCone_Customer, &maxConesPerCustoemr);
    }
    
    /* Wait for all customers to exit the store */
    for (unsigned int i = 0; i < numCustomers; i++)
    {
        pthread_join(customerThread[i], NULL);
    }
    CloseShop = 1;
    sem_post(conesForPayment);      // tell cashier
    sem_post(workerInQueue);        // tell manager
    
    /* Cashier would like to leave */
    pthread_join(cashierThread, NULL);
    
    /* Manager has to go home now :( */
    pthread_join(managerThread, NULL);
    
    printf("\n-------------------STORE CLOSE------------------------\n");
}
