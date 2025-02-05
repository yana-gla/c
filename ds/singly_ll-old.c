#include "singly_ll.h"

struct node_t /*link list element*/
{
	/*data*/
	void* data;
	/*ptr to next node*/
	slist_itr_t next; 
};

struct slist_t
{
	slist_itr_t head; /*ptr to head node*/
};


slist_t* ListCreate()
{
	slist_t *list_p = (slist_t*)malloc(sizeof(slist_t);
	if (NULL == list_p)
	{
		printf("Allocation Failed.\n");
		return 0;
	}
	
	list_p->head = NULL;
	
	return (list_p);
}

slist_itr_t ListItrBegin(const slist_t* list)
{
	assert(NULL != list);
	return (list->head);
}

slist_itr_t ListItrNext(slist_itr_t itr)
{
	assert(NULL != list);
	return (itr->next);
}

void* ListGetData(slist_itr_t itr)
{
	assert(NULL != itr);
	return(itr->data);
}

void ListSetData(slist_itr_t itr, const void* data)
{
	assert(NULL != itr && NULL != data);
	
	itr-> data = data;
}

slist_itr_t ListItrEnd(slist_t* list)
{	
	slist_itr_t itr = NULL;
	assert(NULL != list);
	itr = list->head;
	
	while (itr != NULL )
	{
		itr = itr->next;
	}
	
	return (itr);
}

/* Equal return 1*/
int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2)
{
	assert(NULL != itr1 & NULL != itr2);
	
	return (itr1 == itr ? 1 : 0); 
}


slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data)
{
	assert(NULL != itr && NULL != data);
	
}
