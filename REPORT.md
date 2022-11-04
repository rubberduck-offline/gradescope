# User Thread Library

## Summary

The goal of this project is to build a basic user-level thread library 
`libuthread.a` for Linux. This library provides a complete interface for 
applications to creat and run independent threads concurrently. It is able to 
create new threads, schedule the execution threads in a round-robin fashion, 
and provide a thread synchronization API (ECS 150_Project #2 - User-level
thread library).

## Implementation

The implementation of this program has three main parts:

1. Implementing a queue container for system programming
2. Implementing the thread management API `uthread.c` using internal context 
API `context.c` for applications to create, terminate, or manipulate threads
3. Implementing the semaphore API `sem.c` to control the access to common 
resources by multiple threads


### Queue API

A queue object, `struct queue`, is defined in this API `queue.c` to handle 
thread scheduling. It is implemented using a singly linked list. A singly linked
 list allows an arbitrary number of threads and enables fast access to the first
  element in the queue. This singly linked list contains a void pointer `*data` 
  and a struct pointer `struct QNode *next`. `*data` later stores the actutal 
  thread user `context (uctx)` and `struct QNode *next` points to the next tcb 
  object in queue. 

All queue related operations: create, destory, enqueue, dequeue, etc, are 
defined in this API.

User thread library does not have access to this private data sturcture. The 
library has access to queue size from `queue_length()`.

`queue_iterate()` provides a generic way to call a custom function provided by 
the caller on each item currently enqueued in the queue.

All operations apart from `iterate` and `delete` are in O(1).


### Uthread API

Most of the thread management is implemented in Uthread API `uthread.c`.

An object `struct uthread_tcb` consist with a state, a pointer to stack, and a `uthread_ctx_t *uctx` pointer to store the thread execution content. 

A ready queue `ready_q` is created in serve as a container for thread 
scheduling. At `uthread_create()`, a new thread is enqueued into this FIFO 
queue. It is then dequeued and executed by `uthread_ctx_switch()` when 
`uthread_yield()` is called. 

A void pointer declared in the queue allows it to pickup any data type that is 
passed to it. All data manipulation is achieved through modifying pointers, in 
most cases, dereferencing a pointer to pointer (i.e. `queue_dequeue(ready_q, (void**)&next_thread);`).

`uthread_run()` runs an idle thread. This thread runs a while loop to keep track
 if there are still threads in the ready queue. If the queue is not empty, it 
 calls yeild on thread to perform switching, else it breaks out the while loop 
 and frees memory from the queue object.

`uctx` is initialized through function `uthread_ctx_init()` given by the 
internal context API `context.c`. Switch between two execution contexts and 
stack allocation for new thread is also achieved using the internal context API.


### Semaphore API

Semaphore is implemented using the skeleton code given in lecture slides. 
Instead of the while loop approach, it is developed with if-else condition 
because there isn't a spin lock in this project.

Each semaphore object `sem` has maintains its internal count and its own waiting
 queue `wq`.

The waiting queue schedules the semaphores. Semaphores take affect on the actual
 user thread ready queue through accessing uthread API functions 
 `uthread_block()` and `uthread_unblock()` in `sem_up` and `sem_down`.

### Reference and Testing

Reference:
* Lecture slides and Office Hours

`libuthread/Makefile` compiles all `.c` files into `.o` outputs and links to 
the `libuthread.a`. Provided `apps/Makefile` generates executables for testing 
the implemented APIs.

Performed unit test on `libuthread/queue.c` using `apps/queue_tester_example.c`.

## Partner Work Division

### Aileen
* 100% `libuthread/queue.c` implementation
* 100% `libuthread/uthread.c` implementation
* 100% `libuthread/sem.c` implementation
* 100% `libuthread/Makefile` implemention
* 100% `REPORT.md`

### Randy
* Resource collection
* 100% `libuthread/preempt.c` implemention
* 100% `apps/test_preempt.c` implemention
* Input to `libuthread/sem.c`: First attempt copied straight from lecture 
slides, code does not work. Second attempt built upon Aileen's code, passes 
`sem_simple.c` test case. Work wasn't submit since both worked in parallel and 
Aileen's code passed⋅

## License

This work is distributed under the [GNU All-Permissive
License](https://spdx.org/licenses/FSFAP.html).

Copyright 2022, Aileen and Randy, UC DAVIS ECS150
