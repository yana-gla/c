#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include "heap.h" /*own header*/
#include "heap_p_queue.h" /*own header*/

struct p_queue{
	heap_t *heap;
};

p_queue_t *PQCreate(cmp_func_t cmp_func)
{
	p_queue_t *p_queue = NULL;
	
	assert(NULL != cmp_func);
	
	p_queue = (p_queue_t*)malloc(sizeof(p_queue_t));
	if(NULL == p_queue)
	{
		return NULL;
	}
	
	p_queue->heap= HeapCreate(cmp_func);
	if(NULL == p_queue->heap)
	{
		free(p_queue);
		p_queue = NULL;
		return NULL;
	}
	
	return p_queue;
}
/*Remove entirely the priority queue from memory*/
void PQDestroy(p_queue_t *p_queue)
{
	assert(NULL != p_queue);
	
	HeapDestroy(p_queue->heap);
	p_queue->heap= NULL; /*like memset*/
	/*memset(p_queue, 0, sizeof(p_queue_t));*/
	
	free(p_queue);
	p_queue = NULL;
}

int PQIsEmpty(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return HeapIsEmpty(p_queue->heap);
}

/*Remove single element matching (function) param.
 Enables to remove elemnt not 
 according priority*/
void *PQRemove(p_queue_t *p_queue, is_match_t is_match, void *param)
{
	assert (NULL != p_queue);
	assert (NULL != is_match);
	
	return HeapRemove(p_queue->heap, is_match, param);
}

/*When success returns 0, O.W 1*/
int PQEnqueue(p_queue_t *p_queue, void *data)
{
	assert (NULL != p_queue);
	
	return HeapPush(p_queue->heap, data);
}

void PQDequeue(p_queue_t* p_queue)
{
	assert (NULL != p_queue);

	HeapPop(p_queue->heap);
}

void *PQPeek(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);

	return HeapPeek(p_queue->heap);
}

size_t PQCount(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	
	return HeapSize(p_queue->heap);
}
/*Remove all elemnts but keeps the queue*/
void PQClear(p_queue_t *p_queue)
{
	assert(NULL != p_queue);
	while (!PQIsEmpty(p_queue))
	{
		PQDequeue(p_queue);
	}
}

