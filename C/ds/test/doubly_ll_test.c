#include <stdio.h> /* For printf */
#include <assert.h> /* For assert */
#include <string.h>
#include "doubly_ll.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define UNFORMAT "\x1b[1;0m"

/*static void Test();*/
static char* ListToString(dlist_t* lst, char* str);
static int MatchInts(const void* data1, const void* data2);
static void TestCreateAndDestroy(void);
static void TestInsertAndRemove(void);
static void TestFindAndMultiFind(void);
static int BiggerInts(const void* data1, const void* data2);
static void TestSplice(void);
static int AddInt(void* data, void* param);
static void TestForEach(void);

int main(void)
{
	printf(BLUE"Beginning doubly_ll.c tests...\n\n"UNFORMAT);

	TestCreateAndDestroy();
	TestInsertAndRemove();
	TestFindAndMultiFind();
	TestSplice();
	TestForEach();

	return (0);
}

/*
*	DLLItrBegin
*	DLLItrEnd
*	DLLGetData
*	DLLItrNext
*/
static char* ListToString(dlist_t* lst, char* str)
{
	dlist_itr_t curr = DLLItrBegin(lst);
	char* ptr_str = str;
	
	while(DLLItrEnd(lst) != curr)
	{
		*ptr_str = *(int*)DLLGetData(curr) + '0';
		++ptr_str;
		curr = DLLItrNext(curr);
	}
	
	*ptr_str = '\0';
	
	return (str);
}

/*
*	DLLCreate
*	DLLDestroy
*/
static void TestCreateAndDestroy()
{
	dlist_t* list = DLLCreate();
	
	printf(BLUE"Beginning create and destroy tests:\n"UNFORMAT);
	
	if(NULL == list)
	{
		printf(RED"\t\tTestCreateAndDestroy : Fail to create list\n"UNFORMAT);
	}
	else
	{
		DLLDestroy(list);
		printf(GREEN"\t\tTestCreateAndDestroy : PASSED!\n"UNFORMAT);
	}
}

/*
*	DLLPushFront
*	DLLPushBack
*	DLLPopFront
*	DLLPopBack
*	DLLIsEmpty
*	DLLCount
*/
static void TestInsertAndRemove()
{
	size_t i = 0;
	int values_front[] = {3,2,1};
	int values_back[] = {4,5,6};
	size_t size_values = 3;
	dlist_t* list = DLLCreate();
	char str[50];
	int result = 0;
	
	printf(BLUE"Beginning insert and remove tests:\n"UNFORMAT);
	
	if(NULL == list)
	{
		printf(RED"\t\tTestInsertAndRemove : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	
	for(i = 0 ; i < size_values ; ++i)
	{
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list, &values_front[i])));
		assert(values_back[i] == *(int*)DLLGetData(DLLPushBack(list, &values_back[i])));
	}
	
	ListToString(list, str);
	
	if (0 != strcmp("123456",ListToString(list, str)))
	{
		printf(RED"\t\tTestInsertAndRemove : Expected list : 123456 , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	if(6 != DLLCount(list))
	{
		printf(RED"\t\tTestInsertAndRemove : Expected list size : 6 , but got : %lu\n"UNFORMAT,DLLCount(list));
		result = 1;
	}
	if(!result)
	{
		printf(GREEN"\t\tTestInsertAndRemove : INSERT PASSED!\n"UNFORMAT);
	}
	
	result = 0;
	
	for(i = 0 ; i < size_values ; ++i)
	{
		assert((int)i + 1 == *(int*)DLLPopFront(list));
		assert((int)(6 - i) == *(int*)DLLPopBack(list));
	}
	
	if(!DLLIsEmpty(list))
	{
		printf(RED"\t\tTestInsertAndRemove : Expected empty : 1 , but got : %d\n"UNFORMAT,DLLIsEmpty(list));
		result = 1;
	}
	if(0 != DLLCount(list))
	{
		printf(RED"\t\tTestInsertAndRemove : Expected list size : 0 , but got : %lu\n"UNFORMAT,DLLCount(list));
		result = 1;
	}
	if(!result)
	{
		printf(GREEN"\t\tTestInsertAndRemove : REMOVE PASSED!\n"UNFORMAT);
	}
	
	DLLDestroy(list);
}

/*
*	DLLFind
*	DLLMultiFind
*/
static void TestFindAndMultiFind()
{
	size_t i = 0;
	int values_front[] = {3,2,1};
	int values_back[] = {4,5,6};
	size_t size_values = 3;
	int match_data = 4, match_data1 = 0;
	int find1 = 0, find2 = 0, *find3 = 0;
	dlist_t* list = DLLCreate();
	dlist_t* list1 = DLLCreate();
	dlist_t* list2 = DLLCreate();
	dlist_t* list3 = DLLCreate();
	int result = 0;
	char str[50];
	
	printf(BLUE"Beginning find and multifind tests:\n"UNFORMAT);
	
	if(NULL == list)
	{
		printf(RED"\t\tTestFindAndMultiFind : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list1)
	{
		printf(RED"\t\tTestFindAndMultiFind : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list2)
	{
		printf(RED"\t\tTestFindAndMultiFind : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list3)
	{
		printf(RED"\t\tTestFindAndMultiFind : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	
	for(i = 0 ; i < size_values ; ++i)
	{
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list, &values_front[i])));
		assert(values_back[i] == *(int*)DLLGetData(DLLPushBack(list, &values_back[i])));
	}
	
	find1 = *(int*)DLLGetData(DLLFind(DLLItrBegin(list),DLLItrEnd(list),MatchInts, &match_data));
	find2 = *(int*)DLLGetData(DLLFind(DLLItrBegin(list),DLLItrNext(DLLItrBegin(list)),MatchInts, &values_front[size_values-1]));
	find3 = DLLGetData(DLLFind(DLLItrBegin(list),DLLItrEnd(list),MatchInts, &match_data1));
	
	if(4 != find1)
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected 4 , but got : %d\n"UNFORMAT, find1);
		result = 1;
	}
	if(1 != find2)
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected 1 , but got : %d\n"UNFORMAT, find2);
		result = 1;
	}
	if(find3)
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected NULL , but got non null\n"UNFORMAT);
		result = 1;
	}
	if(!result)
	{
		printf(GREEN"\t\tTestFindAndMultiFind : FIND PASSED!\n"UNFORMAT);
	}
	
	assert(0 == DLLMultiFind(DLLItrBegin(list),DLLItrEnd(list),BiggerInts, &values_front[size_values-1], list1));
	assert(0 == DLLMultiFind(DLLItrBegin(list),DLLItrEnd(list),BiggerInts, &values_back[size_values-1], list2));
	assert(0 == DLLMultiFind(DLLItrBegin(list2),DLLItrEnd(list2),BiggerInts, &values_front[size_values-1], list3));
	
	result = 0;
	
	if (0 != strcmp("23456",ListToString(list1, str)))
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected list : 23456 , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	ListToString(list2, str);
	if(!DLLIsEmpty(list2))
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected empty , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	ListToString(list3, str);
	if(!DLLIsEmpty(list3))
	{
		printf(RED"\t\tTestFindAndMultiFind : Expected empty , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	if(!result)
	{
		printf(GREEN"\t\tTestFindAndMultiFind : MULTIFIND PASSED!\n"UNFORMAT);
	}
	
	DLLDestroy(list);
	DLLDestroy(list1);
	DLLDestroy(list2);
	DLLDestroy(list3);
}

/*
*	DLLSplice
*/
static void TestSplice()
{
	size_t i = 0;
	int values_front[] = {3,2,1};
	int values_back[] = {4,5,6};
	size_t size_values = 3;
	int result = 0;
	dlist_t* list = DLLCreate();
	dlist_t* list1 = DLLCreate();
	dlist_t* list2 = DLLCreate();
	dlist_t* list3 = DLLCreate();
	dlist_itr_t itr = NULL;
	char str[50];
	
	printf(BLUE"Beginning splice tests:\n"UNFORMAT);
	
	if(NULL == list)
	{
		printf(RED"\t\tTestSplice : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list1)
	{
		printf(RED"\t\tTestSplice : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list2)
	{
		printf(RED"\t\tTestSplice : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	if(NULL == list3)
	{
		printf(RED"\t\tTestSplice : Fail to create list\n"UNFORMAT);
		result = 1;
	}
	
	for(i = 0 ; i < size_values ; ++i)
	{
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list, &values_front[i])));
		assert(values_back[i] == *(int*)DLLGetData(DLLPushBack(list, &values_back[i])));
	}
	
	itr = DLLItrBegin(list);
	for(i = 0 ; i < size_values ; ++i)
	{
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list1, &values_front[i])));
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list2, &values_front[i])));
		assert(values_front[i] == *(int*)DLLGetData(DLLPushFront(list3, &values_front[i])));
		assert(values_back[i] == *(int*)DLLGetData(DLLPushBack(list1, &values_back[i])));
		itr = DLLItrNext(itr);
	}
	
	DLLSplice(itr, DLLItrBegin(list1), DLLItrEnd(list1));
	if (0 != strcmp("123123456456",ListToString(list, str)))
	{
		printf(RED"\t\tTestSplice : Expected list : 123123456456 , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	DLLSplice(DLLItrBegin(list), DLLItrBegin(list2), DLLItrEnd(list2));
	if (0 != strcmp("123123123456456",ListToString(list, str)))
	{
		printf(RED"\t\tTestSplice : Expected list : 123123123456456 , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	DLLSplice(DLLItrEnd(list), DLLItrBegin(list3), DLLItrEnd(list3));
	if (0 != strcmp("123123123456456123",ListToString(list, str)))
	{
		printf(RED"\t\tTestSplice : Expected list : 123123123456456123 , but got : %s\n"UNFORMAT,str);
		result = 1;
	}
	
	if(!result)
	{
		printf(GREEN"\t\tTestSplice : SPLICE PASSED!\n"UNFORMAT);
	}
	
	DLLDestroy(list);
	DLLDestroy(list1);
	DLLDestroy(list2);
	DLLDestroy(list3);
	
}

static int AddInt(void* data, void* param)
{
	*(int*)data += *(int*)param;
	return (0);
}

/*
*	DLLForEach
*/
static void TestForEach()
{
	dlist_t* list = DLLCreate();
	int a = 1, b = 2, c = 3, d = 4, g = 1;
	char buff[5];
	
	printf(BLUE"Beginning for each tests:\n"UNFORMAT);
	
	DLLPushBack(list, &a);
	DLLPushBack(list, &b);
	DLLPushBack(list, &c);
	DLLPushBack(list, &d);
	
	DLLForEach(DLLItrBegin(list), DLLItrEnd(list), AddInt, &g);
	ListToString(list, buff);
	
	if (strcmp(buff, "2345"))
	{
		printf(RED"\t\tTestForEach: Received %s and expected 1234\n"UNFORMAT, buff);
		return;
	}
	
	DLLForEach(DLLItrNext(DLLItrBegin(list)), DLLItrEnd(list), AddInt, &g);
	ListToString(list, buff);
	
	if (strcmp(buff, "2456"))
	{
		printf(RED"\t\tTestForEach: Received %s and expected 2456\n"UNFORMAT, buff);
		return;
	}
	
	DLLForEach(DLLItrBegin(list), DLLItrPrev(DLLItrEnd(list)), AddInt, &g);
	ListToString(list, buff);
	
	if (strcmp(buff, "3566"))
	{
		printf(RED"\t\tTestForEach: Received %s and expected 3566\n"UNFORMAT, buff);
		return;
	}
	
	printf(GREEN"\t\tTestForEach: FOREACH PASSED!\n"UNFORMAT);
	DLLDestroy(list);
}
	
static int MatchInts(const void* data1, const void* data2)
{
	return (*(int*)data1 == *(int*)data2);
}

static int BiggerInts(const void* data1, const void* data2)
{
	return (*(int*)data1 > *(int*)data2);
}

















