#include <stdlib.h>    /*malloc*/
#include <string.h>    /*memset*/
#include <assert.h>    /*assert*/
#include <stdio.h>

/*#include "doubly_ll.h" doubly linked list*/
#include "sorted_ll.h"

/* manege structure */
struct srt_ll /*srt_ll_t*/
{
	dlist_t* dlist;
	is_before_t is_before; /*cmp function*/
};

srt_ll_t* SrtLLCreate(is_before_t is_before)
{ 
	srt_ll_t *sorted_list = NULL; 
	
	assert(NULL != is_before);
	
	sorted_list = (srt_ll_t*)malloc(sizeof(srt_ll_t));
	
	if (NULL == sorted_list)
	{
		return NULL; 
	}
	
	sorted_list->dlist = DLLCreate();
	
	if (NULL == sorted_list->dlist)
	{
		memset(sorted_list, 0, sizeof(srt_ll_t));
		free(sorted_list);
		return NULL;
	}
	
	sorted_list->is_before = is_before;
	
	return sorted_list;
}


void SrtLLDestroy(srt_ll_t* sr_list)
{
	assert(NULL != sr_list);
	
	DLLDestroy(sr_list->dlist);
	memset(sr_list, 0, sizeof(srt_ll_t));
	free(sr_list);
}

srt_itr_t SrtLLItrBegin(const srt_ll_t* sr_list)
{
	srt_itr_t itrs = {0};
	
	assert(NULL != sr_list);
	
	itrs.itr = DLLItrBegin(sr_list->dlist);
	
	#ifndef NDEBUG
	itrs.sr_list = (srt_ll_t*)sr_list;
	#endif
	
	return itrs;
}

srt_itr_t SrtLLItrEnd(const srt_ll_t* sr_list)
{
	srt_itr_t itrs = {0};
	
	assert(NULL != sr_list);
	itrs.itr = DLLItrEnd(sr_list->dlist);
	
	#ifndef NDEBUG
	itrs.sr_list = (srt_ll_t*)sr_list;
	#endif
	
	return itrs;
}

srt_itr_t SrtLLItrNext(srt_itr_t itrs)
{
	itrs.itr = DLLItrNext(itrs.itr);
	
	return itrs;
}

srt_itr_t SrtLLItrPrev(srt_itr_t itrs)
{
	itrs.itr = DLLItrPrev(itrs.itr);
	
	return itrs;
}

/* Boolean check if list is empty - O(1)*/
int SrtLLIsEmpty(const srt_ll_t* sr_list)
{
	return (DLLIsEmpty(sr_list->dlist));
}

/* boolean check if the iterators point to the same node - O(1)*/
int SrtLLItrIsEqual(srt_itr_t itr1, srt_itr_t itr2)
{
	#ifndef NDEBUG
	if (itr1.sr_list != itr2.sr_list)
	{
		return -1;
	}
	#endif
	
	return (itr1.itr == itr2.itr);
}

/* insert a new node with data by sorted order - O(n)*/
srt_itr_t SrtLLInsert(srt_ll_t* sr_list, void* data)
{
	srt_itr_t itrs = {0};
	srt_itr_t itrs_end = {0};
	
	assert((NULL != sr_list) && (NULL != data));
	
	itrs = SrtLLItrBegin(sr_list);
	itrs_end = SrtLLItrEnd(sr_list);
		
	while (!SrtLLItrIsEqual(itrs, itrs_end) && sr_list->is_before(SrtLLGetData(itrs), data) < 0 )
	{
		
		itrs = SrtLLItrNext(itrs);
	}
	
	itrs.itr = DLLInsertBefore(sr_list->dlist, itrs.itr, data);
	#ifndef NDEBUG
	itrs.sr_list = sr_list;
	#endif
	
	return itrs;
}

/* remove the node pointed by itr O(1)*/
srt_itr_t SrtLLRemove(srt_itr_t itrs)
{
	itrs.itr = DLLRemove(itrs.itr);
	return itrs;
}

void* SrtLLPopFront(srt_ll_t* sr_list)
{
	assert(NULL != sr_list);
	return DLLPopFront(sr_list->dlist);
}

void* SrtLLPopBack(srt_ll_t* sr_list)
{
	assert(NULL != sr_list);
	return DLLPopBack(sr_list->dlist);
}

/* O(n) */
size_t SrtLLCount(const srt_ll_t* sr_list)
{
	assert(NULL != sr_list);
	return DLLCount(sr_list->dlist);
}

void* SrtLLGetData(srt_itr_t itrs)/*O(1)*/
{
	return DLLGetData(itrs.itr);
}

/* O(n) fined the firs node that has the data, otherwise return 'to'. */
srt_itr_t SrtLLFind(srt_ll_t* sr_list, void* data)
{
	srt_itr_t itrs = {0};
	srt_itr_t itrs_end = {0};
	
	assert((NULL != sr_list) && (NULL != data));

	itrs = 	SrtLLItrBegin(sr_list);
	itrs_end = SrtLLItrEnd(sr_list);
	
	while(sr_list->is_before(SrtLLGetData(itrs), data) < 0 && !SrtLLItrIsEqual(itrs, itrs_end))
	{
		itrs = SrtLLItrNext(itrs);
	}
	
	return (sr_list->is_before(SrtLLGetData(itrs), data) == 0) ? itrs : itrs_end;
}

/* retur 'to' if not found, otherwise return the iterator of node than match the function find if*/
srt_itr_t SrtLLFindIf(srt_itr_t from, srt_itr_t to, match_func_t is_match, void* data)
{
	/*srt_itr_t itrs = {0};*/
	
	assert(NULL != data);
	
	#ifndef NDEBUG
	if (from.sr_list != to.sr_list)
	{
		return to;
	}
	#endif
	
	from.itr = DLLFind(from.itr, to.itr, is_match, data);
	return from;
}

/* O(n) */
int SrtLLForEach(srt_itr_t from, srt_itr_t to, action_func_t action, void* param)
{
	assert(NULL != param);
	assert(NULL != action);
	
	#ifndef NDEBUG
	if (from.sr_list != to.sr_list)
	{
		return -1;
	}
	#endif
	
	return DLLForEach(from.itr, to.itr, action, param);
}

srt_ll_t* SrtLLMerge(srt_ll_t* dst, srt_ll_t* src)
{
	srt_itr_t from = {0};    /*src*/
	srt_itr_t where = {0}; /*dst*/
	
	assert (NULL != dst);
	assert (NULL != src);
	
	where = SrtLLItrBegin(dst);
	
	/*running on source while it not empty*/
	while (!SrtLLIsEmpty(src))
	{
		from = SrtLLItrBegin(src);
		
		/*increment where while it smaller than dest*/
		while (!SrtLLItrIsEqual(where, SrtLLItrEnd(dst)) && dst->is_before(SrtLLGetData(from), SrtLLGetData(where)) > 0)
		{
			where = SrtLLItrNext(where);
		}
		
		where.itr = DLLSplice(where.itr, from.itr, SrtLLItrNext(from).itr);
	}
	
	return dst;
}

