/******************************************************************************
* File: hash_table.c
*
* Purpose:
*  Implement Hash DS
*
* Author:
*   Yana Glazer
* 
*Date:
*	24/03/2025
*
* Code Reviewd by:
*	Yonatan Fainer
*
******************************************************************************/
#include  <stddef.h> /*offsetof*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memset*/
#include <assert.h> /*assert*/
#include "doubly_ll.h" /*own header*/
#include "hash_table.h" /*own header*/

struct ht_table
{
	ht_hash_func_t hash_func;
	ht_match_func_t match_func;
	size_t capacity;
	dlist_t* buckets[1]; /* Array of linked lists serving as buckets */
};

typedef struct 
{
    void* key;
    void* data;
}ht_item_t;

typedef struct
{
	ht_action_func_t action_func;
	void* param; /*q*/
}action_wrp_t;

typedef struct 
{
	ht_match_func_t match_func;
	void *key;
}match_wrp_t;

static void DestroyLists(ht_table_t* ht, size_t i);
static void DestroyOneItem(ht_item_t *item);
static void DestroyItems(dlist_t *dlist);
static int InitBuckets(ht_table_t* table);
static size_t GetIndex(ht_table_t* table, void* key);
static ht_item_t *CreateItem(void* key, void* value);
static dlist_itr_t HTSearch(dlist_t *list, void* key, ht_match_func_t match_func);
static int HTWrprMatch(const void *item, const void *params);
static int HTWrprAct(void *item, void *wrp_params);


/******************************************************************************/
ht_table_t* HTCreate(ht_match_func_t match_func,
					 ht_hash_func_t hash_func,
					 size_t capacity)
{
	ht_table_t *table = NULL;
	
	assert(NULL != match_func);
	assert(NULL != hash_func);
	
	table = (ht_table_t*)malloc(offsetof(ht_table_t, buckets) + capacity * sizeof(dlist_t*));
	if (NULL == table)
	{
		return NULL;
	}
	
	/*Init Fields*/
	if (0 != InitBuckets(table)) /*failure in creating dll lists*/
	{
		memset(table, 0, sizeof(ht_table_t));
		free(table);
		table = NULL;
		
		return NULL;
	}
	table->hash_func = hash_func;
	table->match_func = match_func;
	table->capacity = capacity;
	
	return table;
}

/******************************************************************************/
void HTDestroy(ht_table_t* table)
{
	assert (NULL != table);
	
	/*free lists and items*/
	DestroyLists(table, table->capacity);
	
	/*free table*/
	memset(table, 0, sizeof(ht_table_t));
	free(table);
	table = NULL;
}

/******************************************************************************/
int HTInsert(ht_table_t* table, void* key, void* value)
{
	size_t idx = 0;
	dlist_itr_t itr = DLLItrEnd(table->buckets[0]);
	ht_item_t *item = NULL;
	
	assert(NULL != table);
	assert(NULL != key);
	
	item = CreateItem(key, value);
	if (NULL == item)
	{
		return 1;
	}
	
	/*get idx*/
	idx = GetIndex(table, key);
	
	itr = DLLPushFront(table->buckets[idx], item);
	if (DLLItrIsEqual(itr, DLLItrEnd(table->buckets[idx]) )) /*if failed to push*/
	{
		DestroyOneItem(item);
		item = NULL;
		
		return 1;
	}
	
	return 0;
}

/******************************************************************************/
void HTRemove(ht_table_t* table, void* key)
{
	size_t idx = 0;
	dlist_t *list = NULL;
	dlist_itr_t itr = NULL, end = NULL;
	ht_item_t *item = NULL;
	
	assert(NULL != table);
	assert(NULL != key);
	
	idx = GetIndex(table, key); 
	list = table->buckets[idx];
	
	end = DLLItrEnd(list);
	itr = HTSearch(list, key, table->match_func);
	item = DLLGetData(itr);
	
	/*if key in Hash*/
	if (!DLLItrIsEqual(itr, end))
	{
		DestroyOneItem(item);
		item = NULL;
		DLLRemove(itr);
		itr = NULL;
	}
}

/******************************************************************************/
void* HTFind(const ht_table_t* table, void* key)
{
	size_t idx = 0;
	dlist_t *list = NULL;
	dlist_itr_t itr = NULL, end = NULL;
	ht_item_t *item = NULL;
	
	assert(NULL != table);
	assert(NULL != key);
	
	idx = GetIndex((ht_table_t*)table, key); 
	list = table->buckets[idx];
	end = DLLItrEnd(list);
	
	itr = HTSearch(list, key, table->match_func);
	if (DLLItrIsEqual(itr, end))/*if not found*/
	{
		return NULL;
	}
	
	/*move element to front, fast access, frequently searched*/
	item = (ht_item_t*)DLLGetData(itr);
	DLLRemove(itr);
	DLLPushFront(list, item);
	
	return item->data;
}
/******************************************************************************/

size_t HTCount(const ht_table_t* table)
{
	size_t i = 0;
	size_t count = 0;
	
	assert(NULL != table);
	
	for (i = 0; i < table->capacity ; ++i)
	{
		count += DLLCount((dlist_t*)table->buckets[i]);
	}
	
	return count;
}

/******************************************************************************/
int HTIsEmpty(const ht_table_t* table)
{
	size_t i = 0;
	int is_empty = 1;
	
	assert(NULL != table);
	
	for (i = 0; (i < table->capacity) && (1 == is_empty); ++i)
	{
		is_empty = DLLIsEmpty(table->buckets[i]);
	}
	
	return is_empty;
}

/******************************************************************************/
int HTForEach(ht_table_t* table, ht_action_func_t action_func, void* params)
{
	size_t i = 0;
	int status = 0;
	dlist_t *list = NULL;
	action_wrp_t act_prm = {0};
	
	assert(NULL != table);
	assert(NULL != action_func);
	
	act_prm.param = params;
	act_prm.action_func = action_func;
	
	/*perform on every list in hash*/
	for (i = 0; (i < table->capacity) && (0 == status); ++i)
	{
		list = table->buckets[i];
		status = DLLForEach(DLLItrBegin(list), DLLItrEnd(list), HTWrprAct, &act_prm);
	}
	
	return status;
}

/**************************  Static Function   ********************************/
static void DestroyLists(ht_table_t* ht, size_t end_idx)
{
	size_t i = 0;
	
	for (i = 0 ; i < end_idx ; ++i)
	{
		if (!DLLIsEmpty(ht->buckets[i]))
		{
			DestroyItems(ht->buckets[i]);
		}
		DLLDestroy(ht->buckets[i]);
		ht->buckets[i] = NULL;
	}
}

/******************************************************************************/
static void DestroyItems(dlist_t *dlist)
{
	dlist_itr_t itr = DLLItrBegin(dlist), end = DLLItrEnd(dlist);
	ht_item_t *item = NULL;

	while (!DLLItrIsEqual(itr, end))
	{
		item = (ht_item_t*)DLLGetData(itr);
		DestroyOneItem(item);

		itr = DLLItrNext(itr);
	}
}

/******************************************************************************/
static int InitBuckets(ht_table_t* table)
{
	size_t i = 0;
	int status = 0;
	
	for (i = 0; i < table->capacity ; ++i)
	{
		table->buckets[i] = DLLCreate();
		if (NULL == table->buckets[i])
		{
			status = 1;
			DestroyLists(table, i);
		}
	}
	return status;
}

/******************************************************************************/

static size_t GetIndex(ht_table_t* table, void* key)
{
	return (table->hash_func((void*)key) % table->capacity);
}

/******************************************************************************/
static ht_item_t *CreateItem(void* key, void* value)
{
	ht_item_t *item = (ht_item_t*)malloc(sizeof(ht_item_t));
	if (NULL == item)
	{
		return NULL;
	}
	item->key = key;
	item->data = value;
	
	return item;
}

/******************************************************************************/
/*Finds node with corresponding key in the list*/
static dlist_itr_t HTSearch(dlist_t *list, void* key, ht_match_func_t match_func)
{
	match_wrp_t match_key = {0};
	dlist_itr_t found = DLLItrEnd(list);
	
	match_key.match_func = match_func;
	match_key.key = key;
	
	found = DLLFind(DLLItrBegin(list), DLLItrEnd(list), HTWrprMatch, &match_key);
	
	return found;	
}

/******************************************************************************/
static int HTWrprMatch(const void *item, const void *params)
{
	match_func_t match_hash = ((match_wrp_t*)params)->match_func;
	/*first param is GetData = item*/
	void *key1 = ((ht_item_t*)item)->key;
	void* key2 = ((match_wrp_t*)params)->key;
	
	return (match_hash(key1, key2));
}

/******************************************************************************/
static void DestroyOneItem(ht_item_t *item)
{
	memset(item, 0, sizeof(ht_item_t));
	free(item);
}

/******************************************************************************/
static int HTWrprAct(void *item, void *wrp_params)
{
	action_func_t action = ((action_wrp_t*)wrp_params)->action_func;
	void *data = ((ht_item_t*)item)->data;
	void* param = ((action_wrp_t*)wrp_params)->param;
	
	return (action(data, param));
}
/******************************************************************************/
