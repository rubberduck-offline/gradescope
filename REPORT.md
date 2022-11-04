# User Thread Library

## Summary

The goal of this project is to build a basic user-level thread library `libuthread.a` for Linux. This library provides a complete interface for applications to creat and run independent threads concurrently. It is able to create new threads, schedule the execution threads in a round-robin fashion, and provide a thread synchronization API (ECS 150_Project #2 - User-level thread library).

## Implementation

The implementation of this program has three main parts:

1. Implementing a queue container for system programming
2. Implementing the thread management API `uthread.c` using internal context API `context.c` for applications to create, terminate, or manipulate threads
3. Implementing the semaphore API `sem.c` to control the access to common resources by multiple threads


### Queue API

A queue object, `struct queue`, is defined in this API to handle thread scheduling. It is implemented using a singly linked list. A singly linked list allows an arbitrary number of thread and fast access to the first element. This singly linked list contains a void pointer `*data` and a struct pointer `struct QNode *next`. `*data` later stores the actutal thread ctx and `struct QNode *next` points to the next tcb object in queue. 

All queue related operations: create, destory, enqueue, dequeue, etc, are defined in this API.

User thread library does not have access to this private data sturcture. The library has access to queue size from `queue_length()`.

`queue_iterate()` provides a generic way to call a custom function provided by the caller on each item currently enqueued in the queue.

All operations apart from `iterate` and `delete` are in O(1).


### Uthread API



### Semaphore API




### Reference program and testing

`libuthread/Makefile` compiles all `.c` files into `.o` outputs and links to the `libuthread.a`. Provided `apps/Makefile` generates executables for testing the implemented APIs.

## License

This work is distributed under the [GNU All-Permissive
License](https://spdx.org/licenses/FSFAP.html).

Copyright 2022, Aileen, ECS150
