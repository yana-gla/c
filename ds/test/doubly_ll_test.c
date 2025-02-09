/******************************************************************************
* File: doubly_ll_test.c
*
* Purpose:
*   Test suite for doubly_ll.h
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include "doubly_ll.h"					/* own header */

#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

/*****************************************************************************/

static int g_total_checks = 0;
static int g_failed_checks = 0;

/* Test Prototypes */
static int TestDLLCreateDestroy(void);

/* Other Function Prototypes */
/*
static int IsMatch(void* data1, void* data2);
static int AddInt(void* data, void* param);
*/
/*****************************************************************************/

static int TestDLLCreateDestroy(void)
{
	dlist_t* list = NULL;
	int status = 0;
	
	printf("Testing DLL Create/Destroy...");
	list = DLLCreate();
	
	++g_total_checks;	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}
	
	++g_total_checks;
	if (0 == DLLIsEmpty(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected empty list, but got non-empty\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
/*	
	++g_total_checks;
	if (0 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0, but got %lu\n" UNFORMAT, 
			   (unsigned long)ListCount(list));
		++g_failed_checks;
		status = 1;
	}
*/	
	DLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestDLLIterators(void)
{
	dlist_t* list = NULL;
	dlist_itr_t itr1 = NULL;
	dlist_itr_t itr2 = NULL;
	int val = 42;
	int status = 0;

	printf("Testing DLL Iterators...");
	list = DLLCreate();
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	itr1 = DLLItrEnd(list);
	++g_total_checks;
	if (DLLItrEnd(list) == DLLInsertBefore(list, itr1, &val))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before end failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	itr1 = DLLItrBegin(list);
	itr2 = DLLItrEnd(list);
	++g_total_checks;
	if (0 != DLLItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Begin and End iterators should not be equal\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	itr1 = DLLItrNext(itr1);
	++g_total_checks;
	if (1 != DLLItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Next of Begin should equal End\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	DLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestDLLInsertRemove(void)
{
	dlist_t* list = NULL;
	dlist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	int status = 0;
	
	printf("Testing DLL Insert/Remove...");
	list = DLLCreate();
	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		return 1;
	}

	itr = DLLItrEnd(list);
	++g_total_checks;
	if (DLLItrEnd(list) == DLLInsertBefore(list, itr, &val1))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before end failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	++g_total_checks;
	if (1 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 1, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}
	
	itr = DLLItrBegin(list);
	++g_total_checks;
	if (DLLItrEnd(list) == DLLInsertBefore(list, itr, &val2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before begin failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	++g_total_checks;
	if (2 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 2, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	itr = DLLItrBegin(list);
	itr = DLLRemove(itr);
	++g_total_checks;
	if (1 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 1 after remove, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	itr = DLLItrBegin(list);
	itr = DLLRemove(itr);
	++g_total_checks;
	if (0 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0 after remove, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	DLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestDLLDataAccess(void)
{
	dlist_t* list = NULL;
	dlist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	int status = 0;

	printf("Testing DLL Data Access...");
	list = DLLCreate();
	
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	itr = DLLItrEnd(list);
	itr = DLLInsertBefore(list, itr, &val1);
	++g_total_checks;
	if (val1 != *(int*)DLLGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected data %d, but got %d\n" UNFORMAT,
			   val1, *(int*)DLLGetData(itr));
		++g_failed_checks;
		status = 1;
	}

	DLLSetData(itr, &val2);
	++g_total_checks;
	if (val2 != *(int*)DLLGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: After SetData expected %d, but got %d\n" UNFORMAT,
			   val2, *(int*)DLLGetData(itr));
		++g_failed_checks;
		status = 1;
	}
	
	DLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestDLLPushPop(void)
{
	dlist_t* list = NULL;
	dlist_itr_t itr = NULL;
	int val1 = 42;
	int val2 = 24;
	int val3 = 99;
	void* popped_data = NULL;
	int status = 0;
	
	printf("Testing DLL Push/Pop Ops...");
	list = DLLCreate();
	
	++g_total_checks;	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}
	
	/* Test PushFront */
	itr = DLLPushFront(list, &val1);
	++g_total_checks;
	if (DLLItrEnd(list) == itr)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PushFront failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* Test PushBack */
	itr = DLLPushBack(list, &val2);
	++g_total_checks;
	if (DLLItrEnd(list) == itr)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PushBack failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	/* Verify count after pushes */
	++g_total_checks;
	if (2 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 2, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}
	
	/* Test order of elements */
	itr = DLLItrBegin(list);
	++g_total_checks;
	if (val1 != *(int*)DLLGetData(itr))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Front element expected %d, but got %d\n" UNFORMAT,
			   val1, *(int*)DLLGetData(itr));
		++g_failed_checks;
		status = 1;
	}
	
	/* Add one more element for multiple pop tests */
	DLLPushBack(list, &val3);
	
	/* Test PopFront */
	popped_data = DLLPopFront(list);
	++g_total_checks;
	if (val1 != *(int*)popped_data)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PopFront expected %d, but got %d\n" UNFORMAT,
			   val1, *(int*)popped_data);
		++g_failed_checks;
		status = 1;
	}
	
	/* Test PopBack */
	popped_data = DLLPopBack(list);
	++g_total_checks;
	if (val3 != *(int*)popped_data)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PopBack expected %d, but got %d\n" UNFORMAT,
			   val3, *(int*)popped_data);
		++g_failed_checks;
		status = 1;
	}
	
	/* Verify count after pops */
	++g_total_checks;
	if (1 != DLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 1 after pops, but got %lu\n" UNFORMAT,
			   (unsigned long)DLLCount(list));
		++g_failed_checks;
		status = 1;
	}
	
	DLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

int main(void)
{	
	int status = 0;

	status |= TestDLLCreateDestroy();
	status |= TestDLLIterators();
	status |= TestDLLInsertRemove();
	status |= TestDLLDataAccess();
	status |= TestDLLPushPop();

	printf("\n%s ======= Test Summary =======%s\n", BOLD_FORMAT, UNFORMAT);
	printf("┌──────────────────┬─────────┐\n");
	printf("│ Total checks     │ %7d │\n", g_total_checks);
	printf("│ Failed checks    │ %7d │\n", g_failed_checks);
	printf("└──────────────────┴─────────┘\n");
	if (0 == status)
	{
		printf(PASS_FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
	else
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	return 0;
}

