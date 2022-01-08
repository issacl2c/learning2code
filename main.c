//
//  main.c
//  issacl2c
//
//  Created by Issac on 12/12/21.
//

#include <stdio.h>
#include <pthread.h>
#include "./DataStructures/BinaryTree.h"
#include "./DataStructures/Hash.h"
#include "./DataStructures/Heap.h"
#include "./DesignProblems/IcecreamCone.h"
#include "./DesignProblems/MatrixRotation.h"
#include "./DesignProblems/Sorts.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello. This is Issac learning to code! \n\n");
    // Welcome over
    
    unsigned int application;
    unsigned int customers;
    while (1)
    {
        printf("Choose the Application:\
                \n1: Binary Tree Demo Application\
                \n2: Hash Table Demo Application\
                \n3: Heap Demo Application\
                \n4: Ice Cream Cone Store Aplication\
                \n5: Matrix Rotation Application\
                \n6: Sorts Application\
                \n7: Exit Operation\n\n");
        
        scanf("%d", &application);
        
        if (application == 7)
        {
            printf("Thank you, bye bye!! \n\n");
            break;
        }
        switch (application)
        {
            case 1:
                BinaryTree_Demo();
                break;
            case 2:
                Hash_Demo();
                break;
            case 3:
                Heap_Demo();
                break;
            case 4:
                printf("------------------ICE CREAM STORE DEMO-------------------\n. How many customers can enter the store? \n");
                scanf("%d", &customers);
                IcecreamCone_Store(customers);
                break;
            case 5:
                MatrixRotation_Demo();
                break;
            case 6:
                Sorts_Demo();
                break;
            case 7:
                printf("Thank you, bye bye!! \n\n");
                break;
            default:
                break;
        }
    }

    
    return 0;
}


