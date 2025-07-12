/*******************************************************************************
 * File: singly_ll.c							
 * 										
 * Description: 
 *		Implementation of linked list data structure and functionality
 *																
 * History: 									
 *		Date: 03/02/2025, reviewed by 						
 *										
 * Author:									
 *		Yana Glazer	
 *
 * Code Reviewd:
 *		Daniel Micha	04/02/2025					
 *										
 ******************************************************************************/
#include <stdlib.h>   /*malloc*/
#include <assert.h>  /*assert*/
#include "singly_ll.h"

static slist_itr_t NodeToItr(node_t* node);
static node_t* ItrToNode(slist_itr_t itr);
static int count_fun(void* data, void* counter);

struct node /*link list element*/
{
	void* data;    /*data*/
	node_t* next; /*ptr to next node*/
};

struct slist
{
	node_t* head;  /*ptr to head node*/
	node_t* tail; /*ptr to tail node*/
};

/******************************************************************************/
/*Creates list and dummy node tail
 No parameters, returns pointer to list, O(1) */
slist_t* ListCreate()
{
	slist_t *list = (slist_t*)malloc(sizeof(slist_t));
	node_t* dummy_tail = NULL;
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	dummy_tail = (node_t*)malloc(sizeof(node_t));
	
	if(NULL == dummy_tail)
	{
		free(list);
		return (NULL);
	}
	
	/*Initialize Data tail to ptr to list, next to NULL*/
	dummy_tail->data = list;
	dummy_tail->next = NULL;
	
	list->tail = dummy_tail;
	list->head = dummy_tail;
	
	return (list);
}

/******************************************************************************/
/*Function recives pointer to list and returns Itr to the first node.         */
/*O(1)                                                                        */ 
slist_itr_t ListItrBegin(const slist_t* list)
{
	assert(NULL != list);
	return (NodeToItr(list->head));
}

/******************************************************************************/
/*Function gets iterator and returns iterator to next node, O(1)              */
slist_itr_t ListItrNext(slist_itr_t itr)
{
	node_t* node = ItrToNode(itr);
	assert(NULL != itr);
	return (NodeToItr(node->next));
}

/******************************************************************************/
/* Function gets pointer to list and returns iterator to Dummy tail*//*fix- UNB?*/
/*O(1)                                                                        */
slist_itr_t ListItrEnd(slist_t* list)
{	
	assert(NULL != list);
	return(NodeToItr((list->tail)));
}

/******************************************************************************/
/*Function gets iterator and returns his data                                 */ 
/*O(1)                                                                        */
void* ListGetData(slist_itr_t itr)
{
	assert(NULL != itr);
	return(ItrToNode(itr)->data);
}

/******************************************************************************/
/*Function gets iterator and pointer to data,
  Sets data in the current node*/
void ListSetData(slist_itr_t itr, const void* data)
{
	node_t* node = ItrToNode(itr);
	assert(NULL != itr && NULL != data);
	node->data = (void*)data;
}

/******************************************************************************/
/*Function gets 2 iterators, Returns 1 if they Equal, 0 if Not Equal*/
int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2)
{
	assert(NULL != itr1 && NULL != itr2);
	return (itr1 == itr2); 
}

/******************************************************************************/
/*Function gets iterator and data, inserts new node (with new data) before given*/ 
/*itr. Returns Same Iterator (new node)                                       */
/*O(1)                                                                        */
slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data)
{
	node_t* node_in = NULL;
	node_t* node_itr = ItrToNode(itr);
	slist_t* list = NULL;
	
	assert(NULL != data);
	
	/*allocating new node*/
	node_in = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == node_in)
	{
		return (NULL);
	}
	
	/*copying current node to new next node */
	node_in->data = node_itr->data; 
	node_in->next = node_itr->next;
	
	/*updating new data in current node*/
	node_itr->data = (void*)data;
	
	/*updating next field in current node to new node*/
	node_itr->next = node_in;

	/*if itr pointed to dummy tail (dummy tail turn to new node*/
	/*updating list*/	
	if (NULL == node_in->next)
	{
		list = node_in->data;
		list->tail = node_in;
	}
	
	return (itr);
}

/******************************************************************************/
/*Function gets itr and removes its node, Returns same itr (different node)   */
/*O(1)                                                                        */ 
/*User can remove dummy tail, leads to UB                                     */
slist_itr_t ListRemove(slist_itr_t itr)
{
	node_t* node_itr = ItrToNode(itr);
	node_t* tmp = node_itr->next;
	slist_t* list = NULL;
		
	/*copying next node to current node*/
	node_itr->data = node_itr->next->data;     
	node_itr->next = node_itr->next->next;
	free(tmp);
	
	if (NULL == node_itr->next)
	{
		list = node_itr->data;
		list->tail = node_itr;
	}	
	
	return(itr);
}

/******************************************************************************/
size_t ListCount(const slist_t* list)
{
	size_t counter = 0;
	ListForEach(ListItrBegin(list), ListItrEnd((slist_t*)list), count_fun, &counter);
	return (counter);
}

/******************************************************************************/
/*Count number of elements
size_t ListCount(const slist_t* list)
{
	node_t* itr = NULL;
	size_t counter = 0;
	
	assert(NULL != list);
	
	itr = list->head->next;
	
	while (NULL != itr->next)
	{
		++counter;
		itr = itr->next;
	}
	
	return(counter);
	
}
*/

/******************************************************************************/
/*Function receives list and returns 1 if it empty, 0 if not empty*/
/*O(1)*/
int ListIsEmpty(slist_t* list)
{
	assert(NULL != list);
	return(list->head == list->tail);
}

/******************************************************************************/
/*Function gets list and delets here (freeing memory*/
/*O(1)*/
void ListDestroy(slist_t* list)
{
	node_t* current = NULL;
	node_t* next = NULL;
	
	assert(NULL != list);
	
	current = list->head;
	
	while (NULL != current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}

/******************************************************************************/
/*Function gets iterator from and to, match func and data                     */
/*If there is a match returns iterator to node, else return to                */
/*O(1)                                                                        */
slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data)
{
	assert(NULL != is_match && NULL != data);
		
	while (0 == ListItrIsEqual(from, to) && 0 == is_match(ListGetData(from), (void*)data))
	{
		from = ListItrNext(from);
	}
	
	return ( (is_match(ListGetData(from), (void*)data)) ? from : to);
}

/******************************************************************************/
/*Function gets iterator from and to, action func and a parameter             */
/*returns Status of action func                                               */
int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func,
															 const void* param)
{
	int status = 0;
	
	assert(NULL != action_func && NULL != param);
	
	while (0 == ListItrIsEqual(from, to) && 0 == status)
	{
		status = action_func(ListGetData(from), (void*)param);
		from = ListItrNext(from);
	}	
	
	return (status);
}

/******************************************************************************/
/*Appends src list to end of dest list*/
slist_t* ListAppend(slist_t* dest_list, slist_t* src_list)
{
	assert(NULL != dest_list && NULL != src_list);
	
	/*1st node of src to dummy tail dest*/
	dest_list->tail->data = src_list->head->data;
	dest_list->tail->next = src_list->head->next;
	
	/*updating tail dest (to tail src)*/
	dest_list->tail = src_list->tail;
	dest_list->tail->data = dest_list;
	
	/*upadting tail src- first real element of src*/
	src_list->head->data = src_list;
	src_list->head->next = NULL;
	src_list->tail= src_list->head;
	
	return (dest_list);
}

/******************************************************************************/
/*Static function                                                             */
static int count_fun(void* data, void* counter)
{
	assert (NULL != counter);
	++*(size_t*)counter;
	return 0;
	(void)data;
}

/******************************************************************************/
static slist_itr_t NodeToItr(node_t* node)
{
	assert(NULL != node);
	return ((slist_itr_t)node);
}

/******************************************************************************/
static node_t* ItrToNode(slist_itr_t itr)
{
	assert(NULL != itr);
	return ((node_t*)itr);
}
/******************************************************************************/

