//
//  IcecreamCone.h
//  issacl2c
//
//  Created by Issac on 06/01/22.
 /*
  * Problem statement:
  * - in an ice-cream shop there is a Manager and a Cashier
  * - 1-10 Customers visit the shop
  * - Each customer can order 1-4 cones and spwans 1 clerk/cone
  * - Each worker creates one cone and visits the manager's office
  *   to get the approval for the quality. If the quality is bad the
  *   clerk remakes the cone and returns back later.
  * - There cannot be more than 2 clerks in the Manager's office and
  *   can attend to only one clerk at a time.
  * - Once the customer gets his/her cone, he/she exits the shop after
  *   paying the cashier.
  */

/*
 Demonstrate the result:
 - This problem is an example of multithreaded application
 - When store opens, we spawn a random number of customers. (Store --> multiple threads of customers).
 - When store opens, we also create the manager thread, who instantiates his office semaphore with count QUEUE_SIZE (2).
 - When store opens, we create a cashier thread, who instantiates a semaphore with count 1. 
 - Each customer triggers a series of actions. It is one thread.
 - Each customer can create 1-4 cones, and each cone has one clerk - there is one thread per worker (cone)
 - Customer starts to wait for the cone to be delivered by the worker. (join worker thread)
 - The worker tries to latch on to the manager's office . (semaphore of count QUEUE SIZE), and inserts himself into his queue using a critical section.
 - The manager handles a FIFO of worker requests.
    - This FIFO has length QUEUE_SIZE (2 workers)
    - The manager takes out one worker from this queue in a critical section, at a time.
    - THe processes the quality (a random decision is to be made). The outcome of this decision is to be written into the cone quality
 - The worker waits until the quality of the cone is accepted by manager, and exits itself.
 - The customer has recieved his cone, and needs to pay the cashier.
 - The cashier implements a FIFO of the customers. HE can accept one customer at a time, and accept the payment. (customer.payment = TRUE).
 - Once customer has paid the cashier, he can exit. (join all worker threads, and exit customer thread).
 - Store waits for all customers, and exits.
 */

#ifndef IcecreamCone_h
#define IcecreamCone_h

/* Some Definitions to scope the problem */
#define MAX_CUSTOMERS (10)
#define MANAGER_QUEUE_SIZE (2)
#define MAX_CONES_PER_CUSTOMER (4)

#include "Types.h"

/* Ice cream cone type */
typedef struct IcecreamCone_Cone_T
{
    unsigned int customerNum;
    unsigned int coneNum;
    boolean qualityAccepted;
    boolean paymentAccepted;
    boolean qualityCheckDone;
}IcecreamCone_ConeType;

#define QUEUE_ENTITY IcecreamCone_ConeType *

/* Exported functions */
/*------------------------------------------------------*/
/* Ice Cream Store Function                             */
/* Demonstrates the ice cream store functionality       */
/* Expects:                                             */
/* 1. Number of customers                               */
/* Returns:                                             */
/* Nothing                                              */
/*------------------------------------------------------*/
extern void IcecreamCone_Store(unsigned int numCustomers);

#endif /* IcecreamCone_h */
