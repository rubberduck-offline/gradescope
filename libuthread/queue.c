#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"
#include <assert.h>

struct QNode 
{
	void *data;
	struct QNode *next;
};
// typedef struct QNode QNode;

struct queue {
	/*
	 * queue_t - Queue type
	 *
	 * A queue is a FIFO data structure. Data items are enqueued one after the
	 * other.  When dequeueing, the queue must returned the oldest enqueued item
	 * first and so on.
	 *
	 * Apart from delete and iterate operations, all operations should be O(1).
	 */	
	struct QNode *first;
	struct QNode *last;
	int size;
};
// typedef struct queue queue;

queue_t queue_create(void)
{
	/*
	 * queue_create - Allocate an empty queue
	 *
	 * Create a new object of type 'struct queue' and return its address.
	 *
	 * Return: Pointer to new empty queue. NULL in case of failure when allocating
	 * the new queue.
	 */

	struct queue *q = malloc(sizeof(struct queue));

	if (q) {
        q->first = NULL;
        q->last = NULL;
        q->size = 0;
        return q;
    }
    return NULL;
}

int queue_destroy(queue_t queue)
{
	/*
	 * queue_destroy - Deallocate a queue
	 * @queue: Queue to deallocate
	 *
	 * Deallocate the memory associated to the queue object pointed by @queue.
	 *
	 * Return: -1 if @queue is NULL or if @queue is not empty. 0 if @queue was
	 * successfully destroyed.
	 */

	if (!queue | (queue->size > 0)) {
		//printf("This should not be running...\n");
		return -1;
	} 

	//printf("Free memory...\n");
	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/*
	 * queue_enqueue - Enqueue data item
	 * @queue: Queue in which to enqueue item
	 * @data: Address of data item to enqueue
	 *
	 * Enqueue the address contained in @data in the queue @queue.
	 *
	 * Return: -1 if @queue or @data are NULL, or in case of memory allocation error
	 * when enqueing. 0 if @data was successfully enqueued in @queue.
	 */
	struct QNode *new_node;
	new_node = malloc(sizeof(struct queue));
	if(!new_node | !data) {
		return -1;
	}
	
	new_node->data = data;
	new_node->next = NULL;
	if ((queue->size == 0) | !queue) {
		queue->first = new_node;
		queue->last = queue->first;
	} else if (queue->size > 0) {
		queue->last->next = new_node;
		queue->last = new_node;
	}
	queue->size++;

	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/*
	 * queue_dequeue - Dequeue data item
	 * @queue: Queue in which to dequeue item
	 * @data: Address of data pointer where item is received
	 *
	 * Remove the oldest item of queue @queue and assign this item (the value of a
	 * pointer) to @data.
	 *
	 * Return: -1 if @queue or @data are NULL, or if the queue is empty. 0 if @data
	 * was set with the oldest item available in @queue.
	 */
	if ((queue == NULL) | (data == NULL) | (queue->size == 0)) {
		return -1;
	}

	if (queue->first == queue->last) {
		queue->last = NULL;
	}

	struct QNode *temp;
	*data = queue->first->data;
	temp = queue->first;
	queue->first = queue->first->next;
	queue->size--;
	free(temp);

	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/*
	 * queue_delete - Delete data item
	 * @queue: Queue in which to delete item
	 * @data: Data to delete
	 *
	 * Find in queue @queue, the first (ie oldest) item equal to @data and delete
	 * this item.
	 *
	 * Return: -1 if @queue or @data are NULL, of if @data was not found in the
	 * queue. 0 if @data was found and deleted from @queue.
	 */
	// printf("queue->first->data is %p \n", queue->first->data);
	// printf("data is %p \n", data);

	// printf("queue->first is %p \n", queue->first);
	// printf("queue->last is %p \n", queue->last);



	if ((queue == NULL) | (data == NULL)) {
		return -1;
	}

	// printf("data to delete: %p\n", data);
	struct QNode *currentNode = queue->first;
	struct QNode *previousNode = NULL;
	while (currentNode != NULL) 
	{
		if (currentNode->data == data) {
			// printf("data is found \n");
			/* If reaches last node*/
			if (currentNode->next == NULL) {
				currentNode = NULL;
			} else {
				currentNode = currentNode->next;
				previousNode->next = currentNode;
			}
			queue->size--;
			//printf("data deleted\n");
			return 0;
		}
		previousNode = currentNode;
		currentNode = currentNode->next;

	}
	

	return -1;
}

/*
 * queue_func_t - Queue callback function type
 * @queue: Queue to which item belongs
 * @data: Data item
 *
 * Function to be run on each item using queue_iterate(). The current item is
 * received as @data.
 */
int queue_iterate(queue_t queue, queue_func_t func)
{
	 // * queue_iterate - Iterate through a queue
	 // * @queue: Queue to iterate through
	 // * @func: Function to call on each queue item
	 // *
	 // * This function iterates through the items in the queue @queue, from the oldest
	 // * item to the newest item, and calls the given callback function @func on each
	 // * item. The callback function receives the current data item as parameter.
	 // *
	 // * Note that this function should be resistant to data items being deleted
	 // * as part of the iteration (ie in @func).
	 // *
	 // * Return: -1 if @queue or @func are NULL, 0 otherwise.
	
	if ((queue == NULL) | (func == NULL)) {
		return -1;
	}

	struct QNode *currentNode = queue->first;
	while (currentNode != NULL) {

		func(queue, currentNode->data);
	
		currentNode = currentNode->next;
	}

	return 0;
}

int queue_length(queue_t queue)
{
	
	 // * queue_length - Queue length
	 // * @queue: Queue to get the length of
	 // *
	 // * Return the length of queue @queue.
	 // *
	 // * Return: -1 if @queue is NULL. Length of @queue otherwise.
	 
	if (queue == NULL) {
		return -1;
	}

	return queue->size;
}

// // Unit Tests
// void test_create(void)
// {
//     queue_t q;

//     q = queue_create();
//     assert(q != NULL);
// }

// void test_queue_simple(void)
// {
//     queue_t q;
//     int data = 3, *ptr;


//     q = queue_create();
//     queue_enqueue(q, &data);
//     queue_dequeue(q, (void*)&ptr);
//     assert(ptr == &data);
// }

//  Callback function that increments items 
// static void iterator_inc(queue_t q, void *data)
// {
//     int *a = (int*)data;
//     printf("*a has value: %d\n", *a);

//     if (*a == 42) {
//         queue_delete(q, data);
//     }
//     else {
//         *a += 1;
//         printf("*a incremented to value: %d\n", *a);
//     }
//     printf("\n");
// }


