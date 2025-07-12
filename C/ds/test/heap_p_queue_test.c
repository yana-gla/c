/*******************************************************************************
* File: heap_pq_test.c
*
* Purpose:
*   Test suite for heap_pq.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h> /* printf */

#include "heap_p_queue.h" /*own header*/


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
static int TestPQCreateDestroy(void);
static int TestPQEnqueueDequeue(void);
static int TestPQPeek(void);
static int TestPQClear(void);
static int TestPQRemove(void);

/* User-Defined Funcs Prototypes */
static int IntComparator(const void* first, const void* second);
static int IsMatch(const void* data1, void* data2);


/******************************************************************************/

/* cmp_func_t function to determine least to greatest ordering of ints */
static int IntComparator(const void* first, const void* second)
{
	return ((*(int*)first == *(int*)second) ? (0) :
				((*(int*)first < *(int*)second) ? (-1) : (1)));
}

static int IsMatch(const void* data1, void* data2)
{
	return (*(int*)data1 == *(int*)data2);
}

/*****************************************************************************/

static int TestPQCreateDestroy(void)
{
	p_queue_t* p_queue = NULL;
	int status = 0;

	printf("Testing PQ Create/Destroy...");
	p_queue = PQCreate(IntComparator);

	status |= TEST_CHECK(NULL != p_queue, "PQ creation returned NULL");
	status |= TEST_CHECK(1 == PQIsEmpty(p_queue), "Expected empty PQ, but got non-empty");
	status |= TEST_CHECK(0 == PQCount(p_queue), "Expected count 0, but got non-zero");

	PQDestroy(p_queue);

	TEST_RESULT(status);
	return (status);
}

static int TestPQEnqueueDequeue(void)
{
	p_queue_t* p_queue = NULL;
	int values[] = {42, 13, 54, 0, -1};
	size_t expected_size = 5;
	int status = 0;
	size_t i = 0;

	printf("Testing PQ Enqueue/Dequeue...");
	p_queue = PQCreate(IntComparator);
	status |= TEST_CHECK(NULL != p_queue, "PQ creation return NULL");

	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		status |= TEST_CHECK(-1 != PQEnqueue(p_queue, &values[i]), "Failed to insert item");
	}
	status |= TEST_CHECK(expected_size == PQCount(p_queue), "PQ not matching expected size");

	for(i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		PQDequeue(p_queue);
	}
	status |= TEST_CHECK(1 == PQIsEmpty(p_queue), "Expected empty PQ, but got non-empty");

	PQDestroy(p_queue);

	TEST_RESULT(status);
	return (status);
}

static int TestPQPeek(void)
{
	p_queue_t* p_queue = NULL;
	int values[] = {42, 0, 54, 0, -1};
	int expected[] = {-1, 0, 0, 42, 54};
	size_t expected_size = 5;
	int status = 0;
	size_t i = 0;

	printf("Testing PQ Peek...\t");
	p_queue = PQCreate(IntComparator);
	status |= TEST_CHECK(NULL != p_queue, "PQ creation return NULL");

	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		status |= TEST_CHECK(-1 != PQEnqueue(p_queue, &values[i]), "Failed to insert item");
	}
	status |= TEST_CHECK(expected_size == PQCount(p_queue), "PQ not matching expected size");

	for(i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i)
	{
		status |= TEST_CHECK(expected[i] == *(int*)PQPeek(p_queue), "PQ Peek did not return expected data");
		PQDequeue(p_queue);
	}
	status |= TEST_CHECK(1 == PQIsEmpty(p_queue), "Expected empty PQ, but got non-empty");

	PQDestroy(p_queue);

	TEST_RESULT(status);
	return (status);
}

static int TestPQClear(void)
{
	p_queue_t* p_queue = NULL;
	int values[] = {42, 0, 54, 0, -1};
	size_t expected_size = 5;
	int status = 0;
	size_t i = 0;

	printf("Testing PQ Clear...\t");
	p_queue = PQCreate(IntComparator);
	status |= TEST_CHECK(NULL != p_queue, "PQ creation return NULL");

	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		status |= TEST_CHECK(-1 != PQEnqueue(p_queue, &values[i]), "Failed to insert item");
	}
	status |= TEST_CHECK(expected_size == PQCount(p_queue), "PQ not matching expected size");

	PQClear(p_queue);
	status |= TEST_CHECK(1 == PQIsEmpty(p_queue), "Expected empty PQ, but got non-empty");

	PQDestroy(p_queue);

	TEST_RESULT(status);
	return (status);
}

static int TestPQRemove(void)
{
	p_queue_t* p_queue = NULL;
	int values[] = {42, 0, 54, 0, -1};
	int expected[] = {-1, 0, 42, 54};
	int to_remove = 0;
	size_t expected_size = 5;
	int* result = NULL;
	int status = 0;
	size_t i = 0;

	printf("Testing PQ Remove...\t");
	p_queue = PQCreate(IntComparator);
	status |= TEST_CHECK(NULL != p_queue, "PQ creation return NULL");

	for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
	{
		status |= TEST_CHECK(-1 != PQEnqueue(p_queue, &values[i]), "Failed to insert item");
	}
	status |= TEST_CHECK(expected_size == PQCount(p_queue), "PQ not matching expected size");

	result = (int*)PQRemove(p_queue, IsMatch, &to_remove);
	status |= TEST_CHECK(*result == to_remove, "Removed data does not match expected");

	for(i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i)
	{
		status |= TEST_CHECK(expected[i] == *(int*)PQPeek(p_queue), "PQ Peek after remove did not return expected data");
		PQDequeue(p_queue);
	}
	status |= TEST_CHECK(1 == PQIsEmpty(p_queue), "Expected empty PQ, but got non-empty");

	PQDestroy(p_queue);

	TEST_RESULT(status);
	return (status);
}

int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestPQCreateDestroy();
	status |= TestPQEnqueueDequeue();
	status |= TestPQPeek();
	status |= TestPQClear();
	status |= TestPQRemove();

	PrintTestSummary(status);
	return (status);
}

