/******************************************************************************
* File: doubly_ll.h
*
* Purpose:
*   <insert file purpose here>
*
* Author:
*   Yana Glazer
*
******************************************************************************/

#ifndef __DOUBLY_LL_H__
#define __DOUBLY_LL_H__
#include <stddef.h>

typedef struct dlist dlist_t;
typedef struct node* dlist_itr_t; 

/*******************************USER FUNCTION TYPEDEF************************/

/* 
Input: gets 2 elements to compare
Output: return TRUE or FALSE
Purpose: user must set his own comparator func for data
Complexity: o(1)
*/
typedef int (*match_func_t) (const void* first, const void* second);

/* 
Input: gets itr and param
Output: return TRUE or FALSE
Purpose: user must set his own action func for data
Complexity: o(1)
*/
typedef int (*action_func_t) (void* data, void* param);

/******************************************************************************/

dlist_t* DLLCreate();
void DLLDestroy(dlist_t* list);
size_t DLLCount(const dlist_t* list);
int DLLIsEmpty(const dlist_t* list);
/* return list->head->next */
dlist_itr_t DLLItrBegin(const dlist_t* list);
/* return list->tail */
dlist_itr_t DLLItrEnd(const dlist_t* list);
/* undefined behavior if itr is tail */
dlist_itr_t DLLItrNext(dlist_itr_t itr);
/* undefined behavior if itr is head */
dlist_itr_t DLLItrPrev(dlist_itr_t itr);
int DLLItrIsEqual(dlist_itr_t itr1, dlist_itr_t itr2);
void* DLLGetData(dlist_itr_t itr);
void DLLSetData(dlist_itr_t itr, const void* data);
/* return iterator to new node, list->tail if failed */
dlist_itr_t DLLInsertBefore(dlist_t* list, dlist_itr_t itr, void* data);

/* return iterator to next node */
dlist_itr_t DLLRemove(dlist_itr_t itr);

/* add new node containing *data* at the beginning of the list */
dlist_itr_t DLLPushFront(dlist_t* list, void* data);

/* add new node containing *data* at the end of the list */
dlist_itr_t DLLPushBack(dlist_t* list, void* data);

/* remove element from the beginning of the list
 * return the data of the popped node
 */
void* DLLPopFront(dlist_t* list);

/* remove element from the beginning of the list
 * return the data of the popped node
 */
void* DLLPopBack(dlist_t* list);

int DLLForEach(dlist_itr_t from, dlist_itr_t to, action_func_t action, void* param);

/* last spliced element = to */
dlist_itr_t DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to);

dlist_itr_t DLLFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data);

/* output holds successful compars nodes
 * return 0 if success to compare all nodes, number otherwise
 */
int DLLMultiFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data, dlist_t* output);

/******************************IN SRC FILE ***************************/


#endif
