#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include "sorted_ll.h" /*own header for sotred list implementation*/
#include "p_queue.h" /*own header*/

struct p_queue{
	srt_ll_t *list;
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
	p_queue->list = SrtLLCreate(cmp_func);
	if(NULL == p_queue->list)
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
	SrtLLDestroy(p_queue->list);
	p_queue->list = NULL;
	free(p_queue);
	p_queue = NULL;
}

int PQIsEmpty(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return SrtLLIsEmpty(p_queue->list);
}


/*Remove single element*/
void PQRemove(p_queue_t *p_queue, is_match_t is_match, void *param)
{
	srt_itr_t itr = {0};
	
	assert (NULL != p_queue);
	assert (NULL != is_match);
	
	itr = SrtLLFindIf(SrtLLItrBegin(p_queue->list), SrtLLItrEnd(p_queue->list), is_match, (void*)param);
	SrtLLRemove(itr);
	
}

/*When success returns 0, O.W 1*/
/*when sorted list fail to insert, it returns itr to last node*/
int PQEnqueue(p_queue_t *p_queue, void *data)
{
	srt_itr_t itr = {0};
	assert (NULL != p_queue);
	itr = SrtLLInsert(p_queue->list, data);
	return SrtLLItrIsEqual(itr, SrtLLItrEnd(p_queue->list));
}

void PQDequeue(p_queue_t* p_queue)
{
	assert(p_queue);
	SrtLLPopFront(p_queue->list);
}

void *PQPeek(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return SrtLLGetData(SrtLLItrBegin(p_queue->list));
}

size_t PQCount(const p_queue_t* p_queue)
{
	assert(NULL != p_queue);
	return SrtLLCount(p_queue->list);
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

