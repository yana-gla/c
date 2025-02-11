/******************************************************************************
* File: sorted_ll.h
*
* Purpose:
*   <insert file purpose here>
*
*
******************************************************************************/

#ifndef __SORTED_LL_H__
#define __SORTED_LL_H__

#include "doubly_ll.h" 

typedef struct srt_ll srt_ll_t; /* list type */
typedef struct srt_itr srt_itr_t; /* iterator type */

struct srt_itr
{
	dlist_itr_t itr;
	
	#ifndef NDEBUG
	srt_ll_t *sr_list;
	#endif
	
};

/*******************************USER FUNCTION TYPEDEF************************/

/* is the left value before the right value (sorted) */
typedef int(*is_before_t)(const void* data_list, const void* data_user); 
/*+ before
0 equal
- after
*/

/*
typedef extern int (*match_func_t) (const void* first, const void* second);
typedef extern int (*action_func_t) (void* data, void* param);
*/

/******************************************************************************/
srt_ll_t* SrtLLCreate(is_before_t is_before); 

void SrtLLDestroy(srt_ll_t* list); 

srt_itr_t SrtLLItrBegin(const srt_ll_t* list);

srt_itr_t SrtLLItrEnd(const srt_ll_t* list);

srt_itr_t SrtLLItrNext(srt_itr_t itrs);

srt_itr_t SrtLLItrPrev(srt_itr_t itrs);

/* Boolean check if list is empty - O(1)*/
int SrtLLIsEmpty(const srt_ll_t* list);

/* boolean check if the iterators point to the same node - O(1)*/
int SrtLLItrIsEqual(srt_itr_t itr1, srt_itr_t itr2);

/* insert a new node with data by sorted order - O(n)*/
srt_itr_t SrtLLInsert(srt_ll_t* list, void* data);

/* remove the node pointed by itr O(1)*/
srt_itr_t SrtLLRemove(srt_itr_t);

void* SrtLLPopFront(srt_ll_t*);

void* SrtLLPopBack(srt_ll_t*);

/* O(n) */
size_t SrtLLCount(const srt_ll_t*);

void* SrtLLGetData(srt_itr_t);/*O(1)*/

/* O(n) fined the firs node that has the data, otherwise return 'to'. */
srt_itr_t SrtLLFind(srt_ll_t* sr_list, void* data);

/* retur 'to' if not found, otherwise return the iterator of node than match the function find if*/
srt_itr_t SrtLLFindIf(srt_itr_t from, srt_itr_t to, match_func_t is_match, void* data);

/* O(n) */
int SrtLLForEach(srt_itr_t from, srt_itr_t to, action_func_t action, void* param);

/* merge the nodes from src into dst (the list 'src' will be empty by the end) O(n) */
srt_ll_t* SrtLLMerge(srt_ll_t* dst, srt_ll_t* src);


#endif /*SORTED_LL*/
