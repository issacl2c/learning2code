//
//  ReaderWriter.h
//  issacl2c
//
//  Created by Issac on 07/01/22.
//

/* Demonstrate a simple reader-writer semaphore sharing algorithm, with FAIRNESS
    - emphasis on the PENDING reader !
    - Avoid starving the writer, also allow writer to write a new value.
 
 Reference for this example is here: https://arxiv.org/pdf/1309.4507.pdf
 
 Points to NOTE:
 -> the driver code here is not very good IN THAT it can't demonstrate fairness in output (outputs may show writer bias).
 -> BUT, in real life, this is what will happen:
    --> If there is a writer, and N readers:
        -> Writers and readers compete equally for the right to "ENTER" the critical section.
        -> When a reader enters:
            -> A reader enters and registers itself, and allows others to enter.
            -> Whenever a value is present, any number of readers have the preference to read.
        -> When a writer enters:
            -> It checks if there are any pending readers. (PREFERENCE to a pending READER)
            -> It signals readiness to write to the pending readers.
            -> no new "readers" may now enter.
            -> the existing readers exit the CRITICAL section after reading.
            -> the last reader to exit, signals the writer to start writing.
 */

#ifndef ReaderWriter_h
#define ReaderWriter_h

#include <stdio.h>

/* DEFINES */
#define READERWRITER_NUM_READERS (3)            /* Number of readers */
#define READERWRITER_NUM_WRITERS (1)            /* Number of writers */
#define READERWRITER_ARRAYSIZE (2)              /* Test Array Size */
#define READERWRITER_MAX_MODIFICATIONS (10)     /* Max number of modifications allowed before program exits */

/* Operations performed by the reader on the array elements */
#define READERWRITER_READOP_ADD         (0)
#define READERWRITER_READOP_MUL         (1)
#define READERWRITER_READOP_EXP         (2)

/* Exported functions */
extern void ReaderWriter_Demo(void);



#endif /* ReaderWriter_h */
