#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

#define RUNNING 0
#define READY 1        /* ready to schedule */
#define BLOCKED 2     /* waiting to join */
#define EXIT 3        /* thread is dead */

//queue_t prev_q; // may not need this
queue_t ready_q;


/*
 * Tread Control Block*
 * uthread_tcb - Internal representation of threads called TCB (Thread Control
 * Block)
 */
struct uthread_tcb {
    /* TODO Phase 2 */

    int state; /* running, ready, blocked, exit */
    void *stack;
    uthread_ctx_t *uctx; /* typedef ucontext_t uthread_ctx_t */
    
};
// struct uthread_tcb* idle;
struct uthread_tcb* current_thread;

/*
 * uthread_current - Get currently running thread
 *
 * Return: Pointer to current thread's TCB
 */
struct uthread_tcb *uthread_current(void)
{
    /* TODO Phase 2/4 */

    return current_thread;
}

void uthread_yield(void) // context switch, enqueue/dequeue
{
//     /*
//      * uthread_yield - Yield execution
//      *
//      * This function is to be called from the currently active and running thread in
//      * order to yield for other threads to execute.
//      */

    // 1. enque the curernt thread to the ready q
    // 2. grab the next availbe thread from the redy q
    // 3. current thread = next
    // 4. make the context switch
    // printf("got in yield\n");
    queue_enqueue(ready_q, current_thread); // enqueue current_thread (idle)
    struct uthread_tcb *prev_thread;
    struct uthread_tcb *next_thread;
    queue_dequeue(ready_q, (void**)&next_thread); // dequeue ready queue to get the head
    prev_thread = current_thread;
    current_thread = next_thread;
    uthread_ctx_switch(((struct uthread_tcb*)prev_thread)->uctx, ((struct uthread_tcb*)next_thread)->uctx);

}

void uthread_exit(void)
{
    /*
     * uthread_exit - Exit from currently running thread
     *
     * This function is to be called from the currently active and running thread in
     * order to finish its execution.
     *
     * This function shall never return.
     */
    // printf("exit\n");
    // struct uthread_tcb *prev_thread;
    struct uthread_tcb *next_thread;
    queue_dequeue(ready_q, (void**)&next_thread); // dequeue ready queue to get the head
    // prev_thread = current_thread;
    // current_thread = next_thread;
    uthread_ctx_switch(((struct uthread_tcb*)current_thread)->uctx, ((struct uthread_tcb*)next_thread)->uctx);

}

int uthread_create(uthread_func_t func, void *arg) // init
{
     // * uthread_create - Create a new thread
     // * @func: Function to be executed by the thread
     // * @arg: Argument to be passed to the thread
     // *
     // * This function creates a new thread running the function @func to which
     // * argument @arg is passed.
     // *
     // * Return: 0 in case of success, -1 in case of failure (e.g., memory allocation,
     // * context creation).
    // printf("inside create\n");
    struct uthread_tcb *new_thread = (struct uthread_tcb*)malloc(sizeof(struct uthread_tcb));
    new_thread->stack = uthread_ctx_alloc_stack();
    new_thread->uctx = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));
    uthread_ctx_init(new_thread->uctx, new_thread->stack, func, arg);
    queue_enqueue(ready_q, new_thread);


     return 0;
}

int uthread_run(bool preemp, uthread_func_t func, void *arg) // create obj, create, enqueue
{
    
     // * uthread_run - Run the multithreading library
     // * @preempt: Preemption enable
     // * @func: Function of the first thread to start
     // * @arg: Argument to be passed to the first thread
     // *
     // * This function should only be called by the process' original execution
     // * thread. It starts the multithreading scheduling library, and becomes the
     // * "idle" thread. It returns once all the threads have finished running.
     // *
     // * If @preempt is `true`, then preemptive scheduling is enabled.
     // *
     // * Return: 0 in case of success, -1 in case of failure (e.g., memory allocation,
     // * context creation).
     

    if (preemp) {
        printf("testing: preemptive scheduling is enabled.\n");
    }
    ready_q = queue_create();
    struct uthread_tcb* idle = (struct uthread_tcb*)malloc(sizeof(struct uthread_tcb));
    // idle->state = 1;
    idle->uctx = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));
    idle->stack = uthread_ctx_alloc_stack();
    current_thread = idle;
    //queue_enqueue(ready_q, current_thread);
    uthread_create(func, arg);
    while(queue_length(ready_q) >= 1) {
        uthread_yield();
    }

    queue_destroy(ready_q);

    


    return 0;
}


void uthread_block(void)
{
    /* TODO Phase 4 */
    // change the state
    current_thread->state = BLOCKED;

    struct uthread_tcb *prev_thread;
    struct uthread_tcb *next_thread;
    queue_dequeue(ready_q, (void**)&next_thread); // dequeue ready queue to get the head
    prev_thread = current_thread;
    current_thread = next_thread;
    uthread_ctx_switch(((struct uthread_tcb*)prev_thread)->uctx, ((struct uthread_tcb*)next_thread)->uctx);
}

void uthread_unblock(struct uthread_tcb *uthread)
{
    /* TODO Phase 4 */
    // change the state
    current_thread->state = READY;
    // uthread here is the dequeue from waiting queue
    // enqueue this thread to the ready queue
    queue_enqueue(ready_q, uthread);

}

// Testing
// void hello(void *arg)
// {
//     (void)arg;

//     printf("Hello world!\n");
// }

// int main(void)
// {
//     uthread_run(false, hello, NULL);

//     return 0;
// }

