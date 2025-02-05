#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "singly_ll.h"
#include "queue.h"

struct Queue
{
    slist_t* list;
};

queue_t* QueueCreate(void)
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return (NULL);
	}
	
	queue->list = ListCreate();
	
	if (NULL == queue->list)
	{
		free(queue);
		return (NULL);
	}
	
	return (queue);
}

void QueueDestroy(queue_t* queue)
{
	assert(NULL != queue);
	
	ListDestroy(queue->list);
	
	free(queue);
	queue = NULL;
}

int QueueEnqueue(queue_t* queue, void* data)
{
	slist_itr_t itr = ListItrEnd(queue->list);
	
	assert(NULL != queue && NULL != data);
	
	if (itr != ListInsertBefore(itr, data))          /*check*/
	{
		return 1;
	}
	
	return 0;
}

void QueueDequeue(queue_t* queue)
{
	slist_itr_t itr = ListItrBegin(queue->list);
	assert(NULL != queue);
	
	ListRemove(itr);                               /*check return*/
}
void* QueuePeek(const queue_t* queue)
{
	slist_itr_t itr = ListItrBegin(queue->list);
	assert(NULL != queue);
	return (ListGetData(itr));
}

size_t QueueSize(const queue_t* queue)
{
	assert(NULL != queue);
	return (ListCount(queue-> list));
}

int QueueIsEmpty(const queue_t* queue)
{
	assert(NULL != queue);
	return (ListIsEmpty(queue-> list));
}
queue_t* QueueAppend(queue_t* queue_dst, queue_t* queue_src)
{
	assert(NULL != queue_dst && NULL != queue_src);
	ListAppend(queue_dst-> list, queue_src-> list);
	return (queue_dst);
}


