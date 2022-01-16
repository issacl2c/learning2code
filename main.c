//
//  main.c
//  issacl2c
//
//  Created by Issac on 12/12/21.
//

#include <stdio.h>
#include "./DataStructures/BinaryTree.h"
#include "./DataStructures/Hash.h"
#include "./DataStructures/Heap.h"
#include "./DataStructures/Stack.h"
#include "./DesignProblems/IcecreamCone.h"
#include "./DesignProblems/MatrixRotation.h"
#include "./DesignProblems/Sorts.h"
#include "./DesignProblems/ReaderWriter.h"

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
                \n4: Stack Demo Application\
                \n5: Ice Cream Cone Store Aplication\
                \n6: Matrix Rotation Application\
                \n7: Sorts Application\
                \n8: Reader Writer Demo Application\
                \n9: Exit Operation\n\n");
        
        scanf("%d", &application);
        
        if (application == 9)
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
                Stack_Demo();
                break;
            case 5:
                printf("------------------ICE CREAM STORE DEMO-------------------\n. How many customers can enter the store? \n");
                scanf("%d", &customers);
                IcecreamCone_Store(customers);
                break;
            case 6:
                MatrixRotation_Demo();
                break;
            case 7:
                Sorts_Demo();
                break;
            case 8:
                ReaderWriter_Demo();
                break;
            case 9:
                printf("Thank you, bye bye!! \n\n");
                break;
            default:
                break;
        }
    }

    
    return 0;
}


