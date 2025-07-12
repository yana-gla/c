/*******************************************************************************
* File: heap.c
*
* Purpose:
*   Implement Heap DS
	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   Sharon Salman
*
*Date: 27/03/2025
*Last Update: 30/03/2025
*******************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include "vector.h" /*own header*/
#include "heap.h" /*own header*/

#define PARENT_IDX(i) ((i-1)/2)
#define LEFT_CHILD_IDX(i) ((2*i)+1) 
#define RIGHT_CHILD_IDX(i) ((2*i)+2)

#define INITIAL_CPCTY 40 /*5 pointers*/
#define FIRST_IDX 0
#define LAST_IDX(vector) ((VectorSize(vector)) - 1)
#define EMPTY 0
#define GET_ELEMENT(vector, idx) ((VectorAccessElement(vector, idx)))

struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t* vector;
};


static void **GetElement(vector_t *vector, size_t idx);
static void HeapifyUp(heap_t *heap, size_t i);
static void HeapifyDown(heap_t *heap, size_t root_idx);
static void Swap(void **data1, void **data2);
static size_t FindIdx(heap_t *heap, int (*heap_match_func)(const void* data, void* params), void *params);
static int CompareIndxs(heap_t *heap, size_t idx1, size_t idx2);

/******************************************************************************/
heap_t* HeapCreate(int (*heap_cmp_func)(const void* first, const void* second))
{
	heap_t *heap = NULL;
	
	assert (NULL != heap_cmp_func);
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	heap->vector = VectorCreate(sizeof(void*), INITIAL_CPCTY);
	if (NULL == heap->vector)
	{
		free(heap);
		return NULL;
	}
	heap->cmp_func = heap_cmp_func;
	
	return heap;
}

/******************************************************************************/
void HeapDestroy(heap_t* heap)
{
	assert(NULL != heap);
	
	VectorDestroy(heap->vector);	
	memset(heap, 0, sizeof(heap_t));
	free(heap);
}

/******************************************************************************/
void* HeapPeek(const heap_t* heap)
{
	assert(NULL != heap);
	
	return *GetElement(heap->vector, FIRST_IDX);
}

/******************************************************************************/
size_t HeapSize(const heap_t* heap)
{
	return VectorSize(heap->vector);
}

/******************************************************************************/
int HeapIsEmpty(const heap_t* heap)
{
	return (EMPTY == HeapSize(heap));
}

/******************************************************************************/
int HeapPush(heap_t* heap, void* data)
{
	size_t i = 0;
	
	assert (NULL != heap);
	
	/*insert to left most position in the tree = last element in array*/
	if (0 != VectorPushBack(heap->vector, &data)) /*index = size-1*/
	{
		return -1;
	}
	
	/*send child index*/
	i = HeapSize(heap) - 1;
	HeapifyUp(heap, i);
	
	return 0;
}

/******************************************************************************/
void* HeapRemove(heap_t* heap, 
                int (*heap_match_func)(const void* data, void* params),
                void* params)
{
	size_t found_idx = 0;
	void **found_ptr = NULL, **last_ptr = NULL;
	void *rem_ptr = NULL;
	
	assert(NULL != heap);
	assert(heap_match_func);
	
	found_idx = FindIdx(heap, heap_match_func, params);
	/*data is not in heap*/
	if (found_idx == HeapSize(heap))
	{
		return NULL;
	}
	
	found_ptr = GetElement(heap->vector, found_idx);
	rem_ptr = *found_ptr;
	
	/*if the idx is the last one*/
	if (found_idx == LAST_IDX(heap->vector))
	{
		VectorPopBack(heap->vector);
		return rem_ptr;
	}

	last_ptr = GetElement(heap->vector, LAST_IDX(heap->vector));
	Swap(found_ptr, last_ptr);
	VectorPopBack(heap->vector);

	if(HeapSize(heap) <= 1)
	{
		return found_ptr;
	}

	if((found_idx > 0) &&
		 (CompareIndxs(heap, found_idx, PARENT_IDX(found_idx)) < 0))
	{
		HeapifyUp(heap, found_idx);
	}
	else
	{
		HeapifyDown(heap, found_idx);	
	}

	return rem_ptr;
}

/******************************************************************************/
void HeapPop(heap_t* heap)
{
	void **root = NULL, **last = NULL;
	
	assert(NULL != heap);
	assert(0 == HeapIsEmpty(heap));
	
	root = GetElement(heap->vector, FIRST_IDX);
	last = GetElement(heap->vector, LAST_IDX(heap->vector));

	/*move root to end*/
	Swap(root, last);
	/*pop root*/
	VectorPopBack(heap->vector);   
	
	if (!HeapIsEmpty(heap))
	{
		HeapifyDown(heap, FIRST_IDX);
	}
}
   
/************************ Static Function *************************************/
static void HeapifyUp(heap_t *heap, size_t i)
{
	void **child = NULL, **parent = NULL;
	
	if (0 >= i)
	{
		return;
	}

	child = GetElement((heap->vector), i);
	parent = GetElement((heap->vector), PARENT_IDX(i));
	
	if (heap->cmp_func(*parent, *child) <= 0) /*if parent higher priority*/
	{	
		return;
	}
	
	Swap(child, parent);
	HeapifyUp(heap, PARENT_IDX(i));
}

/******************************************************************************/
static void HeapifyDown(heap_t *heap, size_t root_idx)
{
	size_t child_cand_idx = root_idx;
	size_t child_l_idx = LEFT_CHILD_IDX(root_idx);
	size_t child_r_idx = RIGHT_CHILD_IDX(root_idx);
	void **child_cand = NULL, **root = NULL;
	
	/*if root has left child*/
	if ((child_l_idx <= LAST_IDX(heap->vector)) &&
				 (CompareIndxs(heap, child_l_idx, child_cand_idx) < 0))
	{
		child_cand_idx = child_l_idx;
	}
	if ((child_r_idx <= LAST_IDX(heap->vector)) &&
				 (CompareIndxs(heap, child_r_idx, child_cand_idx) < 0))
	{
		child_cand_idx = child_r_idx;
	}
	
	if (child_cand_idx != root_idx)
	{
		child_cand = GetElement(heap->vector, child_cand_idx);
		root = GetElement(heap->vector, root_idx);
		Swap(root, child_cand);
		HeapifyDown(heap, child_cand_idx);
	}
}

/******************************************************************************/
static void Swap(void **data1, void **data2)
{
	void *temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

/******************************************************************************/
static size_t FindIdx(heap_t *heap, int (*heap_match_func)(const void* data, void* params), void *params)
{
	size_t i = FIRST_IDX;
	
	for (i = FIRST_IDX; (i < HeapSize(heap)) && 
				(1 != heap_match_func(*GetElement(heap->vector, i), params)); ++i);
	
	return i;
}

/******************************************************************************/  
static void **GetElement(vector_t *vector, size_t idx)
{
	return ((void**)VectorAccessElement(vector, idx));
}
                
/******************************************************************************/
static int CompareIndxs(heap_t *heap, size_t idx1, size_t idx2)
{
	return (heap->cmp_func(*GetElement(heap->vector, idx1),
						 *GetElement(heap->vector, idx2)));	
} 
/******************************************************************************/
