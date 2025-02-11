/******************************************************************************
* File: sorted_ll_test.c
*
* Purpose:
*   Test suite for sorted_ll.h
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include "sorted_ll.h"					/* own header */

#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

/*****************************************************************************/

static int g_total_checks = 0;
static int g_failed_checks = 0;

/* Test Prototypes */
static int TestSrtLLCreateDestroy(void);
static int TestSrtLLIterators(void);
static int TestSrtLLInsertRemove(void);
static int TestSrtLLDataAccess(void);
static int TestSrtLLPop(void);
static int TestSrtLLForEach(void);
static int TestSrtLLFind(void);
static int TestSrtLLFindIf(void);
/*static int TestSrtLLMerge(void);*/

/* Other Function Prototypes */
static int IntComparator(const void* first, const void* second);
static int IsMatch(const void* data1, const void* data2);
static int AddInt(void* data, void* param);

/*****************************************************************************/

/* is_before_t function to determine least to greatest ordering of ints */
static int IntComparator(const void* first, const void* second)
{
/*	return ((*(int*)first == *(int*)second) ? (0) :*/
/*					((first < second) ? (-1) : (1)));*/
	
	if (*(int*)second < *(int*)first)
		{
			return 1;
		}
		else if (*(int*)second > *(int*)first)
		{
			return -1;
		}
		return 0;
}

static int IsMatch(const void* first, const void* second)
{
	return (*(int*)first == *(int*)second);
}

static int AddInt(void* data, void* param)
{
	*(int*)data += *(int*)param;
	return 0;
}

/*****************************************************************************/

static int TestSrtLLCreateDestroy(void)
{
	srt_ll_t* list = NULL;
	int status = 0;
	
	printf("Testing SrtLL Create/Destroy...");
	list = SrtLLCreate(IntComparator);
	
	++g_total_checks;	
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	++g_total_checks;
	if (0 == SrtLLIsEmpty(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected empty list, but got non-empty\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}
	
	++g_total_checks;
	if (0 != SrtLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 0, but got %lu\n" UNFORMAT, 
			   (unsigned long)SrtLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}


static int TestSrtLLIterators(void)
{
	srt_ll_t* list = NULL;
	srt_itr_t itr1 = { 0 };
	srt_itr_t itr2 = { 0 };
	int val = 42;
	int status = 0;

	printf("Testing SrtLL Iterators...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	itr1 = SrtLLItrEnd(list);
	++g_total_checks;
	if (SrtLLItrEnd(list).itr == SrtLLInsert(list, &val).itr)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Insert before end failed\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	itr1 = SrtLLItrBegin(list);
	itr2 = SrtLLItrEnd(list);
	++g_total_checks;
	if (0 != SrtLLItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Begin and End iterators should not be equal\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	itr1 = SrtLLItrNext(itr1);
	++g_total_checks;
	if (1 != SrtLLItrIsEqual(itr1, itr2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Next of Begin should equal End\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}


static int TestSrtLLInsertRemove(void)
{
	srt_ll_t* list = NULL;
	srt_itr_t itr = { 0 };
	int values[] = {42, 17, 89, 35, 54};
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL Insert/Remove...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Test insertions */
	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		itr = SrtLLInsert(list, &values[i]);
		++g_total_checks;
		if (SrtLLItrEnd(list).itr == itr.itr)
		{
			printf(FAIL_FORMAT "\n\tFAILED: Insert returned end iterator\n" UNFORMAT);
			++g_failed_checks;
			status = 1;
		}
	}

	++g_total_checks;
	if (5 != SrtLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 5, got %lu\n" UNFORMAT,
			   (unsigned long)SrtLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	/* Test removal */
	itr = SrtLLItrBegin(list);
	itr = SrtLLRemove(itr);
	
	++g_total_checks;
	if (4 != SrtLLCount(list))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected count 4 after remove, got %lu\n" UNFORMAT,
			   (unsigned long)SrtLLCount(list));
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestSrtLLDataAccess(void)
{
	srt_ll_t* list = NULL;
	srt_itr_t itr = { 0 };
	int value = 42;
	int status = 0;

	printf("Testing SrtLL Data Access...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	itr = SrtLLInsert(list, &value);
	++g_total_checks;
	if (*(int*)SrtLLGetData(itr) != value)
	{
		printf(FAIL_FORMAT "\n\tFAILED: GetData returned wrong value\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestSrtLLPop(void)
{
	srt_ll_t* list = NULL;
	int values[] = {17, 35, 42, 54, 89};
	int* popped = NULL;
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL Pop...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Insert values */
	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		SrtLLInsert(list, &values[i]);
	}

	/* Test PopFront */
	popped = (int*)SrtLLPopFront(list);
	++g_total_checks;
	if (*popped != 17)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PopFront returned wrong value\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	/* Test PopBack */
	popped = (int*)SrtLLPopBack(list);
	++g_total_checks;
	if (*popped != 89)
	{
		printf(FAIL_FORMAT "\n\tFAILED: PopBack returned wrong value\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestSrtLLForEach(void)
{
	srt_ll_t* list = NULL;
	int values[] = {17, 35, 42, 54, 89};
	int add_value = 10;
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL ForEach...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Insert values */
	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		SrtLLInsert(list, &values[i]);
	}

	/* Test ForEach */
	status = SrtLLForEach(SrtLLItrBegin(list), SrtLLItrEnd(list), AddInt, &add_value);
	++g_total_checks;
	if (0 != status)
	{
		printf(FAIL_FORMAT "\n\tFAILED: ForEach returned non-zero status\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);

	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestSrtLLFind(void)
{
	srt_ll_t* list = NULL;
	int values[] = {17, 35, 42, 54, 89};
	int search_value = 42;
	srt_itr_t found_itr = { 0 };
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL Find...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Insert values */
	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		SrtLLInsert(list, &values[i]);
	}

	/* Test Find */
	found_itr = SrtLLFind(list, &search_value);
	++g_total_checks;
	if (*(int*)SrtLLGetData(found_itr) != search_value)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Find returned wrong value\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestSrtLLFindIf(void)
{
	srt_ll_t* list = NULL;
	int values[] = {17, 35, 42, 54, 89};
	int search_value = 42;
	srt_itr_t found_itr = { 0 };
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL FindIf...");
	list = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Insert values */
	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		SrtLLInsert(list, &values[i]);
	}

	/* Test FindIf */
	found_itr = SrtLLFindIf(SrtLLItrBegin(list), SrtLLItrEnd(list),
							IsMatch, &search_value);
	++g_total_checks;
	if (*(int*)SrtLLGetData(found_itr) != search_value)
	{
		printf(FAIL_FORMAT "\n\tFAILED: FindIf returned wrong value\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}



static int TestSrtLLMerge(void)
{
	srt_ll_t* list1 = NULL;
	srt_ll_t* list2 = NULL;
	int values1[] = {17, 42, 89};
	int values2[] = {35, 54};
	int status = 0;
	size_t i = 0;

	printf("Testing SrtLL Merge...");
	list1 = SrtLLCreate(IntComparator);
	list2 = SrtLLCreate(IntComparator);
	++g_total_checks;
	if (NULL == list1 || NULL == list2)
	{
		printf(FAIL_FORMAT "\n\tFAILED: List creation returned NULL\n" UNFORMAT);
		++g_failed_checks;
		return 1;
	}

	/* Insert values into both lists */
	for (i = 0; i < sizeof(values1) / sizeof(values1[0]); ++i)
	{
		SrtLLInsert(list1, &values1[i]);
	}
	for (i = 0; i < sizeof(values2) / sizeof(values2[0]); ++i)
	{
		SrtLLInsert(list2, &values2[i]);
	}

	/* Test Merge */
	list1 = SrtLLMerge(list1, list2);
	++g_total_checks;
	if (5 != SrtLLCount(list1))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Merged list has wrong count\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	++g_total_checks;
	if (0 != SrtLLCount(list2))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Source list not empty after merge\n" UNFORMAT);
		++g_failed_checks;
		status = 1;
	}

	SrtLLDestroy(list1);
	SrtLLDestroy(list2);
	
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}



int main(void)
{	
	int status = 0;

	status |= TestSrtLLCreateDestroy();
	status |= TestSrtLLIterators();
	status |= TestSrtLLInsertRemove();
	status |= TestSrtLLDataAccess();
	status |= TestSrtLLPop();
	status |= TestSrtLLForEach();
	status |= TestSrtLLFind();
	status |= TestSrtLLFindIf();
	status |= TestSrtLLMerge();
	
	#ifndef NDEBUG
	printf("NOT DEBUG MODE\n");
	#endif

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

