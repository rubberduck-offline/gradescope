#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

// #include "uthread.h"

struct semaphore {
    /* TODO Phase 3 */
    int count;
    queue_t wq;
};

sem_t sem_create(size_t count)
{
    /* TODO Phase 3 */
    struct semaphore *sem = malloc(sizeof(struct semaphore));
    sem->count = count;
    sem->wq = queue_create();
    return sem;
}

int sem_destroy(sem_t sem)
{
    /* TODO Phase 3 */
    free(sem);
    return 0;
}

int sem_down(sem_t sem)
{
    /* TODO Phase 3 */
    /* Decrement by one, or block if already 0 */
    // if sem->count > 0, decrement by one
    if (sem->count > 0) {
        sem->count -= 1;
    } else {
        queue_enqueue(sem->wq, uthread_current());
        uthread_block();
    }

    // no need for while loop
    
    // while (sem->count == 0) {
    //     /* Block self */
    //     // enqueue current_thread to waiting queue
    //     uthread_block();

    // }
    
    return 0;
}

int sem_up(sem_t sem)
{
    /* TODO Phase 3 */
    /* Increment by one, and wake up one of the waiting
     * threads if any*/
    if (queue_length(sem->wq) == 0) {
        // nothing in the wl
        sem->count += 1;
    } else {
        struct uthread_tcb *next_thread;
        queue_dequeue(sem->wq, (void**)&next_thread);
        uthread_unblock(next_thread);
    }


    
    return 0;
}
