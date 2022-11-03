#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	queue_t q;

    q = queue_create();
	TEST_ASSERT(q != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

/* Delete */
void test_queue_delete(void)
{
	queue_t q;
	int data = 3;
	int delete = 5;

	q = queue_create();
	queue_enqueue(q, &data);
	queue_enqueue(q, &delete);
	queue_delete(q, &delete);
}

/* Callback function that increments items */
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42) {
        queue_delete(q, data);
    }
    else {
        *a += 1;
    }
    printf("\n");
}

void test_iterator(void)
{
	struct queue *p;
	int value[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
	size_t i;

	/* Initialize the queue and enqueue items */
	p = queue_create();
	for (i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
	    queue_enqueue(p, &value[i]);
	    printf("value[%zu] is: %d\n", i, value[i]);
	}


	/* Increment every item of the queue, delete item '42' */
	queue_iterate(p, iterator_inc);
   
   assert(value[0] == 2);
   //assert(queue_length(q) == 9);
}



int main(void)
{
	test_create();
	test_queue_simple();

	return 0;
}
