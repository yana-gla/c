/******************************************************************************
* File: queue_test.c
*
* Purpose:
*   Test suite for queue.h
*
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include <assert.h>                     /* assert */
#include "queue.h"						/* own header */

#define PASS_FORMAT	"\x1b[1;36m"
#define UNFORMAT	"\x1b[1;0m"
#define FAIL_FORMAT "\x1b[1;31m"

static int TestQueueCreateDestroy(void)
{
	queue_t* queue = NULL;
	int status = 0;

	printf("Testing Queue Create/Destroy...");
	queue = QueueCreate();
	if (NULL == queue)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Queue creation returned NULL\n" UNFORMAT);
		return 1;
	}

	if (0 == QueueIsEmpty(queue))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected empty queue, but got non-empty\n" UNFORMAT);
		status = 1;
	}
	
	if (0 != QueueSize(queue))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0, but got %lu\n" UNFORMAT,
				(unsigned long)QueueSize(queue));
		status = 1;
	}

	QueueDestroy(queue);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestQueueEnqueueDequeue()
{
	queue_t* queue = NULL;
	int val = 42;
	int status = 0;

	printf("Testing Queue Enqueue/Dequeue...");
	queue = QueueCreate();

	if (0 != QueueEnqueue(queue, &val))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Enqueue operation not successful" UNFORMAT);
		status = 1;
	}

	if (1 != QueueSize(queue))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected size 1, but got %lu\n" UNFORMAT,
				(unsigned long)QueueSize(queue));
		status = 1;
	}

	if (val != *(int*)QueuePeek(queue))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected data %d, but got %d\n" UNFORMAT,
				val, *(int*)QueuePeek(queue));
		status = 1;
	}

	QueueDequeue(queue);
	if (0 != QueueSize(queue))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected size 0, but got %lu\n" UNFORMAT,
				(unsigned long)QueueSize(queue));
		status = 1;
	}

	QueueDestroy(queue);
	if (0 == status)
	{
		printf(PASS_FORMAT "PASSED\n" UNFORMAT);
	}
	return status;
}

static int TestQueueAppend()
{
	queue_t* queue1 = NULL;
	queue_t* queue2 = NULL;
	int values1[] = {1, 2, 3};
	int values2[] = {4, 5, 6};
	int expected[] = {1, 2, 3, 4, 5, 6};
	size_t i = 0;
	int status = 0;

	printf("Testing Queue Append...");
	queue1 = QueueCreate();
	queue2 = QueueCreate();
	
	for (i = 0; i < 3; ++i)
	{
		QueueEnqueue(queue1, &values1[i]);
		QueueEnqueue(queue2, &values2[i]);
	}
	QueueAppend(queue1, queue2);

	if (6 != QueueSize(queue1))
	{
		printf(FAIL_FORMAT "\n\tFAILED: After append, expected size 6, but got %lu\n" UNFORMAT,
					(unsigned long)QueueSize(queue1));
		status = 1;
	}
	if (0 != QueueSize(queue2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: After append, expected size 0, but got %lu\n" UNFORMAT,
					(unsigned long)QueueSize(queue2));
		status = 1;
	}
	
	for (i = 0; i < 6; ++i)
	{
		if (expected[i] != *(int*)QueuePeek(queue1))
		{
			printf(FAIL_FORMAT "\n\tFAILED: Expected data %d at element %lu, but got %d\n" UNFORMAT,
					expected[i], (unsigned long)i, *(int*)QueuePeek(queue1));
			status = 1;
		}
		QueueDequeue(queue1);
	}

	QueueDestroy(queue1);
	QueueDestroy(queue2);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

int main(void)
{	
	int status = 0;

	status |= TestQueueCreateDestroy();
	status |= TestQueueEnqueueDequeue();
	status |= TestQueueAppend();
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
	else
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	return 0;
}

