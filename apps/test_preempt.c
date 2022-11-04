/*
 * tests the preemption
 *
 * Tests the preemption of a  thread and its successful return.
 */

#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <private.h>
#include <uthread.h>

/* This flag controls termination of the main loop. */
//volatile sig_atomic_t keep_going = 1;

void threadPreempted(void *arg)
{
    (void)arg;
    while(1){
        printf("I have not been preempted!\n");
        }
}


int main(void)
{
    int i=0;
    //uthread_run(false, threadPreempted, NULL);
    
    preempt_start(true);
    
    while (1)
        printf ("main thread: wait %d.\n ", i ++ );
    
    
    
    printf ("main thread: EXIT_SUCCESS.\n ");
    return EXIT_SUCCESS;
}
/*ref: https://www.gnu.org/software/libc/manual/html_mono/libc.html#Defining-Handlers  */
