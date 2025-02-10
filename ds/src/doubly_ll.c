#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/

#include "doubly_ll.h"

typedef struct node node_t;

struct node
{
	void* data;
	node_t* next;
	node_t* prev;
};

struct dlist
{
	node_t head;
	node_t tail;
};


static dlist_itr_t NodeToItr(node_t* node);
static node_t* ItrToNode(dlist_itr_t itr);


dlist_t* DLLCreate()
{
	dlist_t* doubly_list = (dlist_t*)malloc(sizeof(dlist_t));
	
	if (NULL == doubly_list)
	{
		return NULL;
	}
	
	doubly_list->head.data = NULL;
	doubly_list->head.next = &doubly_list->tail;
	doubly_list->head.prev =  NULL;
	
	doubly_list->tail.data = NULL;
	doubly_list->tail.next = NULL;
	doubly_list->tail.prev = &doubly_list->head;
	
	return doubly_list;
}


void DLLDestroy(dlist_t* list)
{
	node_t* curr = NULL;
	node_t* next = NULL;
	
	assert(NULL != list);
	
	curr = list->head.next;
	
	while (NULL != curr->next)
	{
		next = curr->next;
		memset(curr, 0, sizeof(node_t));
		free(curr);
		curr = next;
	}
	
	memset(list, 0, sizeof(dlist_t));
	free(list);
}

size_t DLLCount(const dlist_t* list)
{
	size_t counter = 0;
	node_t* curr = list->head.next;
	node_t* next = NULL;
	
	assert(NULL != list);
	
	while (&list->tail != curr)
	{
		++counter;
		next = curr->next;
		curr = next;
	}
	
	return counter;
}

int DLLIsEmpty(const dlist_t* list)
{
	assert(NULL != list);
	return (list->head.next == &list->tail);
	/*return !((int)DLLCount(list));*/
}

/*If succeed returns pointer to new node, fails- pointer to and done*/
dlist_itr_t DLLInsertBefore(dlist_t* list, dlist_itr_t itr, void* data)
{
	node_t *new_node = NULL;
	node_t *node_itr = ItrToNode(itr);

	assert((NULL != list) && (NULL != data));
	
	new_node = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == new_node)
	{
		return DLLItrEnd(list); /* (NodeToItr(&list->tail));*/
	}
	
	new_node->data = data;
	new_node->prev = node_itr->prev;
	new_node->next = node_itr; /*new_node->prev.next;*/
	
	node_itr->prev = new_node;
	new_node->prev->next = new_node;
	
	return NodeToItr(new_node);
}

/* return list->head->next */
dlist_itr_t DLLItrBegin(const dlist_t* list)
{
	assert(NULL != list);
	return NodeToItr(list->head.next);
}

/* return list->tail */
/*dummy node*/
dlist_itr_t DLLItrEnd(const dlist_t* list)
{
	assert(NULL != list);
	return NodeToItr((node_t*)&list->tail);
}

/* undefined behavior if itr is tail */
dlist_itr_t DLLItrNext(dlist_itr_t itr)
{
	node_t *node_itr = ItrToNode(itr);
	return NodeToItr(node_itr->next);
}

/* undefined behavior if itr is head */
dlist_itr_t DLLItrPrev(dlist_itr_t itr)
{
	node_t *node_itr = ItrToNode(itr);
	return NodeToItr(node_itr->prev);
}

int DLLItrIsEqual(dlist_itr_t itr1, dlist_itr_t itr2)
{
	return (itr1 == itr2);
}

void* DLLGetData(dlist_itr_t itr)
{
	node_t *node_itr = ItrToNode(itr);
	return (node_itr->data);
}

void DLLSetData(dlist_itr_t itr, const void* data)
{
	node_t *node_itr = ItrToNode(itr);
	assert(NULL != data);
	node_itr->data = (void*)data;
}

dlist_itr_t DLLRemove(dlist_itr_t itr)
{
	node_t *node_itr = ItrToNode(itr);
	node_t *next_node = node_itr->next;
	
	node_itr->prev->next = next_node;
	next_node->prev = node_itr->prev;
	
	memset(node_itr, 0, sizeof(node_t));
	free(node_itr);
	
	return(NodeToItr(next_node));
}

dlist_itr_t DLLPushFront(dlist_t* list, void* data)
{
	assert((NULL != list) && (NULL != data));
	return (DLLInsertBefore(list, DLLItrBegin(list), data));
	
}

dlist_itr_t DLLPushBack(dlist_t* list, void* data)
{
	assert((NULL != list) && (NULL != data));	
	return (DLLInsertBefore(list, DLLItrEnd(list), data));
}

void* DLLPopFront(dlist_t* list)
{
	dlist_itr_t first_node = NULL;
	void *data_front = NULL;
	
	assert(NULL != list);
	
	first_node = DLLItrBegin(list);
	data_front = DLLGetData(first_node); 
	
	DLLRemove(first_node);
	
	return data_front;
}

void* DLLPopBack(dlist_t* list)
{
	dlist_itr_t last_node = NULL;
	void *data_back = NULL;
	
	assert(NULL != list);
	
	last_node = DLLItrPrev(DLLItrEnd(list));
	
	data_back = DLLGetData(last_node);
	
	DLLRemove(last_node);
	
	return data_back;
}


dlist_itr_t DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to)
{
	node_t *where_node = ItrToNode(DLLItrPrev(where));
	node_t *from_node = ItrToNode(DLLItrPrev(from));
	node_t *to_node_p = ItrToNode(DLLItrPrev(to)), *to_node = ItrToNode(to);
		
	/*1 update next in one node before where (to from)*/
	where_node->next = ItrToNode(from);
	/*2 update next in node one before from (to to)*/
	from_node->next = ItrToNode(to);
	/*3 update next in one node before to (to where)*/
	to_node_p->next = ItrToNode(where);
	
	/*4 */
	to_node->prev = from_node;
	
	/*5*/
	from_node = ItrToNode(from);
	from_node->prev = where_node;
	
	/*6*/
	where_node = ItrToNode(where);
	where_node->prev = to_node_p;
	
	return NodeToItr(to_node_p);
	
}

/*status*/
int DLLMultiFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match,
				 const void* data, dlist_t* output)
{
		
	assert((NULL != output) && (NULL != data));
	
	while (!DLLItrIsEqual(from, to))
	{
		if (is_match(DLLGetData(from) ,data))
		{
			if(DLLItrIsEqual(DLLPushBack(output, DLLGetData(from)), DLLItrEnd(output))) 
			{								/*if push fails it return tail*/
				return 1;
			}

		}
		from = DLLItrNext(from); 
	}
	return 0;
}

/*status*/ 
int DLLForEach(dlist_itr_t from, dlist_itr_t to, action_func_t action, void* param)
{
	int status = 0;
	
	while(!DLLItrIsEqual(from, to) && 0 == status)
	{
		status = action(DLLGetData(from),param);
		from = DLLItrNext(from);
	}
	
	
	return status;
}


dlist_itr_t DLLFind(dlist_itr_t from, dlist_itr_t to, match_func_t is_match, const void* data)
{
	assert(NULL != data);
	
	while(!DLLItrIsEqual(from, to))
	{
		if (is_match(DLLGetData(from) ,data))
		{
			return (from);
		}
		from = DLLItrNext(from);
	}
	return to;
}



/*****************************Static function**********************************/

static dlist_itr_t NodeToItr(node_t* node)
{
	return ((dlist_itr_t)node);
}
static node_t* ItrToNode(dlist_itr_t itr)
{
	return ((node_t*)itr);
}




