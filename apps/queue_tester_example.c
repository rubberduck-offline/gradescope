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

	TEST_ASSERT(queue_create() != NULL);
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


void test_size(void){
    //int *ptr;
    int data1=3;
    int data2=5;
    queue_t q;
    fprintf(stderr, "*** TEST enqueue ***\n");
    q=queue_create();
    queue_enqueue(q, &data1);
    queue_enqueue(q, &data2);
    TEST_ASSERT(queue_length(q)==2);
}
void test_null_size(){
    queue_t q;
    int * ptr;
    fprintf(stderr, "*** TEST null delete ***\n");
    q=NULL;
    TEST_ASSERT(queue_length(q)==-1);
}
void test_empty_delete(){
    queue_t q;
    int data=3;
    fprintf(stderr, "*** TEST empty delete ***\n");
    q=queue_create();
    
    TEST_ASSERT(queue_delete(q, &data)==-1);
}

void test_null_dequeue(void){
    queue_t q;
    int * ptr;
    fprintf(stderr, "*** TEST null delete ***\n");
    q=NULL;
    TEST_ASSERT(queue_dequeue(q, (void **)ptr)==-1);
}

void test_empty_dequeue(void){
    queue_t q;
    int * ptr;
    fprintf(stderr, "*** TEST null delete ***\n");
    q=queue_create();
    TEST_ASSERT(queue_dequeue(q, (void **)ptr)==-1);
}
void test_null_data_enqueue(void){
    queue_t q;
    q=queue_create();
    fprintf(stderr, "*** TEST null data enqueue ***\n");
    TEST_ASSERT(queue_enqueue(q, NULL)==-1);
}

void test_null_function_iterate(void){
    queue_t q;
    q=queue_create();
    fprintf(stderr, "*** TEST null function iterate ***\n");
    TEST_ASSERT(queue_iterate(q, NULL)==-1);
}

void test_non_empty_destroy(void){
    queue_t q;
    int data=3;
    q=queue_create();
    queue_enqueue(q, &data);
    fprintf(stderr, "*** TEST non_empty_destroy***\n");
    TEST_ASSERT(queue_destroy(q)==-1);
}
int main(void)
{
	test_create();
	test_queue_simple();
    test_size();
    test_null_size();
    test_empty_delete();
    test_null_dequeue();
    test_empty_dequeue();
    test_null_data_enqueue();
    test_null_function_iterate();
    test_non_empty_destroy();
	return 0;
}
