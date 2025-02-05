#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "singly_ll.h"

#define FORMAT		"\x1b[1;32m"
#define UNFORMAT	"\x1b[1;0m"


static int IsMatch(void* data1, void* data2)
{
	return *(int*)data1 == *(int*)data2;
}

static int AddInt(void* data, void* param)
{
	*(int*)data = *(int*)data + *(int*)param;
	return 0;
}


static void TestListCreateDestroy(void)
{
	slist_t* list = NULL;
	
	printf("Testing List Create/Destroy...");
	list = ListCreate();
	assert(NULL != list);
	assert(1 == ListIsEmpty(list));
	assert(0 == ListCount(list));
	
	ListDestroy(list);
	printf(FORMAT "\tPASSED\n" UNFORMAT);
}


static void TestListInsertRemove(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	
	printf("Testing List Insert/Remove...");
	list = ListCreate();
	assert(NULL != list);

	itr = ListItrEnd(list);
	assert(NULL != ListInsertBefore(itr, &val1));
	assert(1 == ListCount(list));
	
	itr = ListItrBegin(list);
	assert(NULL != ListInsertBefore(itr,  &val2));
	assert(2 == ListCount(list));

	itr = ListItrBegin(list);
	itr = ListRemove(itr);
	assert(1 == ListCount(list));

	itr = ListItrBegin(list);
	itr = ListRemove(itr);
	assert(0 == ListCount(list));

	ListDestroy(list);
	printf(FORMAT "\tPASSED\n" UNFORMAT);
}

static void TestListIterators(void)
{
	slist_t* list = NULL;
	slist_itr_t itr1 = NULL;
	slist_itr_t itr2 = NULL;
	int val = 42;

	printf("Testing List Iterators...");
	list = ListCreate();
	assert(NULL != list);

	itr1 = ListItrEnd(list);
	assert(NULL != ListInsertBefore(itr1, &val));


	itr1 = ListItrBegin(list);

	itr2 = ListItrEnd(list);

	assert(0 == ListItrIsEqual(itr1, itr2));/*check*/

	itr1 = ListItrNext(itr1);
	assert(ListItrIsEqual(itr1, itr2));

	ListDestroy(list);
	printf(FORMAT "\tPASSED\n" UNFORMAT);
}


static void TestListDataAccess(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;

	printf("Testing List Data Access...");
	list = ListCreate();
	assert(NULL != list);

	itr = ListItrEnd(list);
	itr = ListInsertBefore(itr, &val1);
	assert(val1 == *(int*)ListGetData(itr));

	ListSetData(itr, &val2);
	assert(val2 == *(int*)ListGetData(itr));
	
	ListDestroy(list);
	printf(FORMAT "\tPASSED\n" UNFORMAT);
}


static void TestListFind(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int values[] = {1, 2, 3, 4, 5};
	int target = 3;
	size_t i = 0;
	size_t n_values = 5;

	printf("Testing List Find...");
	list = ListCreate();
	assert(NULL != list);

	itr = ListItrEnd(list);
	for (i = 0; i < n_values; ++i)
	{
		itr = ListInsertBefore(itr, &values[i]);
	}

	itr = ListFind(ListItrBegin(list), ListItrEnd(list), IsMatch, &target);
	assert(NULL != itr);
	assert(target == *(int*)ListGetData(itr));

	ListDestroy(list);
	printf(FORMAT "\t\tPASSED\n" UNFORMAT);
}


static void TestListForEach(void)
{
	slist_t* list = NULL;
	slist_itr_t itr = NULL;
	int values[] = {1, 2, 3, 4, 5};
	int expected[] = {2, 3, 4, 5, 6};
	int param = 1;
	size_t i = 0;
	size_t n_values = 5;

	printf("Testing List ForEach...");
	list = ListCreate();
	assert(NULL != list);

	itr = ListItrEnd(list);
	for (i = 0; i < n_values; ++i)
	{
		itr = ListInsertBefore(itr, &values[i]);
	}

	ListForEach(ListItrBegin(list), ListItrEnd(list), AddInt, &param);

	for (i = 0; i < n_values; ++i)
	{
		assert(expected[i] == values[i]);
	}

	ListDestroy(list);
	printf(FORMAT "\t\tPASSED\n" UNFORMAT);
}

static void TestListAppend(void)
{
    slist_t* list1 = NULL;
    slist_t* list2 = NULL;
    slist_itr_t itr = NULL;
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
	int expected[] = {1, 2, 3, 4, 5, 6};
    size_t i = 0;

    printf("Testing List Append...");
    list1 = ListCreate();
    list2 = ListCreate();
    assert(NULL != list1 && NULL != list2);

    for (i = 0; i < 3; ++i)
    {
        itr = ListItrEnd(list1);
        itr = ListInsertBefore(itr, &values1[i]);	

        itr = ListItrEnd(list2);
        itr = ListInsertBefore(itr, &values2[i]);
    }

    list1 = ListAppend(list1, list2);
    assert(6 == ListCount(list1));
	assert(1 == ListIsEmpty(list2));
    
    itr = ListItrBegin(list1);
    for (i = 0; i < 6; ++i)
    {
        assert(expected[i] == *(int*)ListGetData(itr));
        itr = ListItrNext(itr);
    }

    ListDestroy(list1);
    ListDestroy(list2);
    printf(FORMAT "\t\tPASSED\n" UNFORMAT);
}



int main()
{
	TestListCreateDestroy();
	TestListInsertRemove();
	TestListIterators();
	TestListDataAccess();
	TestListFind();
	TestListForEach();
	TestListAppend();
	
	return 0;
}
