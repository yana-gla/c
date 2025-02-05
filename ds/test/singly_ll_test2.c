/*
*	Writer : Ofir Hasson	
*
*	Reviewed by: 
*	02/02/2025
*/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "singly_ll.h" 

typedef struct
{
	int x;
	char str[50];
}s_t;

int AddInt(void* data, const void* param);
int IsMatchInt(void* data1, const void* data2);
int IsMatchStruct(void* data1, const void* data2);
int AddIntToStruct(void* data, const void* param);
void CheckListTypes();
void CheckListStructs();
void SuccessPrint();

int main()
{
	CheckListTypes();
	CheckListStructs();
	SuccessPrint();
	return (0);
}

void CheckListTypes()
{
	/* check create*/
	slist_t* list = ListCreate();
	
	/* check begin*/
	slist_itr_t iterator= ListItrBegin(list);
	
	int a = 1, b = 2, c = 3, d = 4, e = 5;
	slist_itr_t start_iterator = iterator;
	
	/* check empty */
	assert(1 == ListIsEmpty(list));
	
	/* check insert and next*/
	assert(1 == *(int*)ListItrGetData(ListInsertBefore(iterator,&a)));
	iterator = ListItrNext(iterator);
	assert(2 == *(int*)ListItrGetData(ListInsertBefore(iterator,&b)));
	iterator = ListItrNext(iterator);
	assert(3 == *(int*)ListItrGetData(ListInsertBefore(iterator,&c)));
	iterator = ListItrNext(iterator);
	
	/* check count */
	assert(3 == ListCount(list));
	
	/* check not empty */
	assert(0 == ListIsEmpty(list));
	
	/* check equals */
	assert(1 == ListItrIsEqual(iterator,iterator));
	assert(0 == ListItrIsEqual(iterator,start_iterator));
	
	/* check insert */
	assert(4 == *(int*)ListItrGetData(ListInsertBefore(iterator,&d)));
	iterator = ListItrNext(iterator);
	assert(5 == *(int*)ListItrGetData(ListInsertBefore(iterator,&e)));
	
	/* check count */
	assert(5 == ListCount(list));
	
	/* check begin after changes*/
	assert(1 == *(int*)ListItrGetData(ListItrBegin(list)));
	
	/* check find and end*/
	assert(5 == *(int*)ListItrGetData(ListFind(start_iterator, ListItrEnd(list), IsMatchInt, &e)));
	
	/* check data change */
	ListItrSetData(iterator,&d);
	assert(4 == *(int*)ListItrGetData(iterator));
	
	/* check for each */
	ListForEach(start_iterator, iterator, AddInt, &e);
	assert(9 == *(int*)ListItrGetData(iterator));
	
	/* check remove */
	assert(NULL == ListItrGetData(ListRemove(iterator)));
	iterator = ListRemove(start_iterator);
	assert(7 == *(int*)ListItrGetData(iterator));
	
	/* check destroy*/
	ListDestroy(list);
}

void CheckListStructs()
{
	slist_t* list = ListCreate();
	s_t s1 = {1, "a"};
	s_t s2 = {2, "aa"};
	s_t s3 = {3, "aaa"};
	s_t s4 = {4, "aaaa"};
	s_t s5 = {5, "aaaaa"};
	int n = 5;
	
	/* check begin*/
	slist_itr_t iterator= ListItrBegin(list);
	
	slist_itr_t start_iterator = iterator;
	
	/* check empty */
	assert(1 == ListIsEmpty(list));
	
	/* check insert and next*/
	assert(1 == ((s_t*)ListItrGetData(ListInsertBefore(iterator,&s1))) -> x);
	iterator = ListItrNext(iterator);
	assert(0 == strcmp("aa",((s_t*)ListItrGetData(ListInsertBefore(iterator,&s2))) -> str));
	iterator = ListItrNext(iterator);
	assert(3 == ((s_t*)ListItrGetData(ListInsertBefore(iterator,&s3))) -> x);
	iterator = ListItrNext(iterator);
	
	/* check count */
	assert(3 == ListCount(list));
	
	/* check not empty */
	assert(0 == ListIsEmpty(list));
	
	/* check equals */
	assert(1 == ListItrIsEqual(iterator,iterator));
	assert(0 == ListItrIsEqual(iterator,start_iterator));
	
	/* check insert */
	assert(4 == ((s_t*)ListItrGetData(ListInsertBefore(iterator,&s4))) -> x);
	iterator = ListItrNext(iterator);
	assert(0 == strcmp("aaaaa",((s_t*)ListItrGetData(ListInsertBefore(iterator,&s5))) -> str));
	
	/* check count */
	assert(5 == ListCount(list));
	
	/* check begin after changes*/
	assert(1 == (((s_t*)ListItrGetData(ListItrBegin(list))) -> x));
	
	/* check find and end*/
	assert(2 == ((s_t*)ListItrGetData(ListFind(start_iterator, ListItrEnd(list), IsMatchStruct, &s2))) -> x);
	
	/* check data change */
	ListItrSetData(iterator,&s1);
	assert(1 == ((s_t*)ListItrGetData(iterator)) -> x);
	
	/* check for each */
	ListForEach(start_iterator, iterator, AddIntToStruct, &n);
	assert(6 == ((s_t*)ListItrGetData(iterator)) -> x);
	
	/* check remove */
	assert(NULL == ListItrGetData(ListRemove(iterator)));
	iterator = ListRemove(start_iterator);
	assert(7 == ((s_t*)ListItrGetData(iterator)) -> x);
	
	/* check destroy*/
	ListDestroy(list);
}

int AddInt(void* data, const void* param)
{
	*(int*)data += *(int*)param;
	return (0);
}

int IsMatchInt(void* data1, const void* data2)
{
	return(*(int*)data1 == *(int*)data2);
}

int IsMatchStruct(void* data1, const void* data2)
{
	return((((s_t*)data1) -> x == ((s_t*)data2) -> x) && (0 == strcmp(((s_t*)data1) -> str, ((s_t*)data2) -> str)));
}

int AddIntToStruct(void* data, const void* param)
{
	((s_t*)data) -> x += *(int*)param;
	return (0);
}

void SuccessPrint()
{
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
}






