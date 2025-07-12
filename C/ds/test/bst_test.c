/*******************************************************************************
* File: bst_test.c
*
* Purpose:
*   Test suite for bst.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "bst.h" /* own header */

/* Macros for test formatting */
#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

/* Core macro to perform checks and print error messages */
#define TEST_CHECK(condition, message) \
	Check((condition), (message), __FILE__, __LINE__)

/* Macro to print final test status */
#define TEST_RESULT(status) \
	do { \
		if (0 == (status)) \
		{ \
			printf(PASS_FORMAT "\tPASSED\n" UNFORMAT); \
		} \
	} while (0)

/* Global variables */
static int g_total_checks = 0;
static int g_failed_checks = 0;

/* Summarize testing */
static void PrintTestSummary(int status)
{
	printf("\n%s ======= Test Summary =======%s\n", BOLD_FORMAT, UNFORMAT);
	printf("┌──────────────────┬─────────┐\n");
	printf("│ Total checks     │ %7d │\n", g_total_checks);
	printf("│ Failed checks    │ %7d │\n", g_failed_checks);
	printf("└──────────────────┴─────────┘\n");
	if (0 != status)
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	else
	{
		printf(PASS_FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
}


/***************************** CORE TEST FUNCTION *****************************/

/* Core check function with formatted output */
static int Check(
	int condition,			/* Test condition to evaluate */
	const char* message,	/* Error message if test fails */
	const char* file,		/* Source file where check occurred */
	int line				/* Line number where check occurred */
);

/* Core check function implementation */
static int Check(int condition, const char* message, const char* file, int line)
{
	++g_total_checks;

	if (!condition)
	{
		printf(FAIL_FORMAT "\n   FAILED: %s\n   └────File: %s; \tLine: %d\n" UNFORMAT,
						message, file, line);
		++g_failed_checks;
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* Tests Prototypes*/
static int TestBSTCreateDestroy(void);
static int TestBSTInsertRemove(void);
static int TestBSTIterators(void);
static int TestBSTFind(void);
static int TestBSTForEach(void);

/* Test Helper Prototypes */
static int CompareInts(const void* num1, const void* num2);
static int DummyAction(void* p_int, void* params);

/* Test Helper Global Vars */
static size_t g_action_count;


/*************************** Test Helper Functions ****************************/

static int CompareInts(const void* num1, const void* num2)
{
	assert(NULL != num1);
	assert(NULL != num2);

	return ((*(int*)num1 == *(int*)num2) ? (0) :
					((*(int*)num1 < *(int*)num2) ? (-1) : (1)));
}

static int DummyAction(void* p_int, void* params)
{
	(void)params;

	assert(NULL != p_int);

	if (0 == g_action_count)
	{
		return (1);
	}

	--g_action_count;

	return (0);
}


/******************************************************************************/

static int TestBSTCreateDestroy(void)
{
	bst_t* bst = NULL;
	int status = 0;

	printf("Testing BST Create/Destroy...");

	bst = BSTCreate(CompareInts);
	status |= TEST_CHECK(NULL != bst, "Failed to initialize BST");

	status |= TEST_CHECK(1 == BSTIsEmpty(bst), "Newly initialized BST should be empty");

	BSTDestroy(bst);

	TEST_RESULT(status);
	return (status);
}

static int TestBSTInsertRemove(void)
{
	bst_t* bst = NULL;
	int status = 0;

	printf("Testing BST Insert/Remove...");

	bst = BSTCreate(CompareInts);
	if (NULL != bst)
	{
		int values[] = {5, 1, 3, 4, 10, 20, 30, 7, 0, 2};
		size_t n_values = 10;
		size_t i  = 0;

		for (i = 0; i < n_values; ++i)
		{
			BSTInsert(bst, &values[i]);
		}

		TEST_CHECK(0 == BSTIsEmpty(bst),
				"BSTIsEmpty should return false after inserts");
		TEST_CHECK(n_values == BSTCount(bst),
				"BSTCount should return correct number after inserts");

		/* Test removing leaf */
		BSTRemove(BSTFind(bst, &values[9])); /* removing 2 */
		--n_values;

		TEST_CHECK(n_values == BSTCount(bst),
				"BSTCount should return correct number after removing leaf");

		/* Test removing node with 1 child */
		BSTRemove(BSTFind(bst, &values[4])); /* removing 10 */
		--n_values;

		TEST_CHECK(n_values == BSTCount(bst),
				"BSTCount should return correct number after removing node w/1 child");

		/* Test removing node with 2 children */
		BSTRemove(BSTFind(bst, &values[1])); /* removing 1 */
		--n_values;

		TEST_CHECK(n_values == BSTCount(bst),
				"BSTCount should return correct number after removing node w/2 children");
	}

	BSTDestroy(bst); /* should free items */

	TEST_RESULT(status);
	return (status);
}

static int TestBSTIterators(void)
{
	bst_t* bst = NULL;
	bst_itr_t begin, end, current, next, prev;
	/* Values to insert in the tree */
	int values[] = {50, 25, 75, 10, 30, 60, 85, 5, 15, 27, 40, 55, 70, 80, 90};
	/* Same values, but already in sorted order for validation */
	int sorted_values[] = {5, 10, 15, 25, 27, 30, 40, 50, 55, 60, 70, 75, 80, 85, 90};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;
	int status = 0;

	printf("Testing BST Iterators...");

	bst = BSTCreate(CompareInts);
	status |= TEST_CHECK(NULL != bst, "Failed to initialize BST");

	/* Test iterator behavior on empty tree */
	begin = BSTItrBegin(bst);
	end = BSTItrEnd(bst);
	status |= TEST_CHECK(BSTIsSameItr(begin, end),
			"Begin and End iterators should be the same for empty tree");

	/* Insert values */
	for (i = 0; i < n_values; ++i)
	{
		BSTInsert(bst, &values[i]);
	}

	/* Test iterator traversal - forward (in-order) */
	begin = BSTItrBegin(bst);
	end = BSTItrEnd(bst);
	status |= TEST_CHECK(!BSTIsSameItr(begin, end),
			"Begin and End iterators should be different for non-empty tree");

	current = begin;
	i = 0;
	while (!BSTIsSameItr(current, end))
	{
		int* value_ptr = (int*)BSTGetData(current);
		status |= TEST_CHECK(NULL != value_ptr, "Failed to get data from iterator");
		status |= TEST_CHECK(sorted_values[i] == *value_ptr,
				"Iterator traversal not giving values in sorted order");

		next = BSTItrNext(current);

		/* Test that prev of next is current, unless next is end */
		if (!BSTIsSameItr(next, end))
		{
			prev = BSTItrPrev(next);
			status |= TEST_CHECK(BSTIsSameItr(prev, current),
					"Prev of Next should be Current");
		}

		current = next;
		++i;
	}

	status |= TEST_CHECK(i == n_values,
			"Iterator didn't traverse all elements");

	/* Test iterator traversal - backward */
	current = BSTItrPrev(end); /* Last element */
	i = n_values - 1;

	while (!BSTIsSameItr(current, begin))
	{
		int* value_ptr = (int*)BSTGetData(current);
		status |= TEST_CHECK(NULL != value_ptr, "Failed to get data from iterator");
		status |= TEST_CHECK(sorted_values[i] == *value_ptr,
				"Backward iterator traversal not giving values in reverse sorted order");

		current = BSTItrPrev(current);
		--i;
	}

	/* Check first element */
	status |= TEST_CHECK(sorted_values[0] == *(int*)BSTGetData(current),
			"First element should match smallest value in tree");

	BSTDestroy(bst);

	TEST_RESULT(status);
	return (status);
}

static int TestBSTFind(void)
{
	bst_t* bst = NULL;
	int values[] = {42, 15, 88, 6, 27, 53, 101, 1, 10, 20, 30, 45, 65, 95, 120};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;
	int not_in_tree = 99;
	bst_itr_t found = {0}, end = {0};
	int status = 0;

	printf("Testing BST Find...\t");

	bst = BSTCreate(CompareInts);
	status |= TEST_CHECK(NULL != bst, "Failed to initialize BST");

	end = BSTItrEnd(bst);

	/* Test find on empty tree */
	found = BSTFind(bst, &values[0]);;
	status |= TEST_CHECK(BSTIsSameItr(found, end),
			"Find on empty tree should return end iterator");

	/* Insert values */
	for (i = 0; i < n_values; ++i)
	{
		BSTInsert(bst, &values[i]);
	}

	/* Test finding each value */
	for (i = 0; i < n_values; ++i)
	{
		found = BSTFind(bst, &values[i]);

		status |= TEST_CHECK(!BSTIsSameItr(found, end),
				"Find should locate existing element");

		if (!BSTIsSameItr(found, end))
		{
			int* value_ptr = (int*)BSTGetData(found);
			status |= TEST_CHECK(NULL != value_ptr, "Failed to get data from iterator");
			status |= TEST_CHECK(*value_ptr == values[i],
					"Find returned iterator to wrong element");
		}
	}

	/* Test finding value not in the tree */
	found = BSTFind(bst, &not_in_tree);
	status |= TEST_CHECK(BSTIsSameItr(found, end),
			"Find on non-existent element should return end iterator");

	/* Test after removing an element */
	BSTRemove(BSTFind(bst, &values[5])); /* Remove 53 */

	found = BSTFind(bst, &values[5]);
	status |= TEST_CHECK(BSTIsSameItr(found, end),
			"Find after remove should return end iterator");

	BSTDestroy(bst);

	TEST_RESULT(status);
	return (status);
}

static int TestBSTForEach(void)
{
	bst_t* bst = NULL;
	int values[] = {50, 25, 75, 10, 30, 60, 85, 5, 15, 27, 40, 55, 70, 80, 90};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;
	bst_itr_t begin = {0}, end = {0}, mid1 = {0}, mid2 = {0};
	int return_value = 0;
	int status = 0;

	printf("Testing BST ForEach...\t");

	bst = BSTCreate(CompareInts);
	status |= TEST_CHECK(NULL != bst, "Failed to initialize BST");

	/* Insert values */
	for (i = 0; i < n_values; ++i)
	{
		BSTInsert(bst, &values[i]);
	}

	begin = BSTItrBegin(bst);
	end = BSTItrEnd(bst);

	/* Test action that stops after first iteration */
	g_action_count = 0; /* This will cause to return 1 on first call */
	return_value = BSTForEach(begin, end, DummyAction, NULL);

	status |= TEST_CHECK(1 == return_value,
			"ForEach should return non-zero when action returns non-zero");

	/* Get values from specific positions to test partial range */
	mid1 = BSTFind(bst, &values[3]); /* Find 10 */
	mid2 = BSTFind(bst, &values[11]); /* Find 55 */

	/* Test partial range */
	g_action_count = 10; /* More than enough for this range */
	return_value = BSTForEach(mid1, mid2, DummyAction, NULL);

	status |= TEST_CHECK(0 == return_value,
			"ForEach on partial range should succeed");

	/* Test empty range */
	g_action_count = 1;
	return_value = BSTForEach(begin, begin, DummyAction, NULL);
	status |= TEST_CHECK(0 == return_value,
			"ForEach on empty range should succeed without calling action");
	status |= TEST_CHECK(1 == g_action_count,
			"Action shouldn't be called for empty range");

	BSTDestroy(bst);

	TEST_RESULT(status);
	return (status);
}

int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestBSTCreateDestroy();
	status |= TestBSTInsertRemove();
	status |= TestBSTIterators();
	status |= TestBSTFind();
	status |= TestBSTForEach();

	PrintTestSummary(status);
	return (status);
}

