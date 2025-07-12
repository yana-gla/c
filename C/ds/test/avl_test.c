/*******************************************************************************
* File: avl_test.c
*
* Purpose:
*	Test suite for avl.h
*
* Performance Metrics Explanation:
*	This test file measures several key performance aspects of the AVL tree:
*
*   Operation Timing:
*		- Insertion Time: Time to add new nodes while maintaining balance
*		- Search Time: Time to find existing nodes in the tree
*		- Removal Time: Time to delete nodes and rebalance the tree
*		- Re-insertion Time: Time to add previously removed nodes
*
*   Balance Metrics:
*   	- Final Tree Height: Actual height of the tree after all operations
*   	- Theoretical Max Height: The maximum expected height (1.44*log2(n+2))
*   		for an AVL tree with n nodes
*   	- Height/log(n) Ratio: How the tree height compares to the logarithm of
*   		the number of nodes. In a perfectly balanced binary tree, this would
*   		approach 1.0. Values between 1.0-1.5 indicate good balance.
*
*	Scaling Performance:
*		Shows how tree performance changes with increasing number of nodes.
*		This helps verify that operations maintain O(log n) complexity as the
*		tree grows. A well-balanced AVL tree should show only modest increases
*		in operation times even as the tree size increases significantly.
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <time.h> /* clock_t, clock(), CLOCKS_PER_SEC */
#include <assert.h> /* assert */

#include "avl.h" /* own header */

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
static int TestAVLCreateDestroy(void);
static int TestAVLInsertRemove(void);
static int TestAVLForEach(void);
static int AVLStressTest(void);
static int AVLScalingTest(void);

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

	/* printf("\nAction Count: %2lu\t Current: %2d",
								g_action_count, *(int*)p_int); */

	--g_action_count;

	return (0);
}

static double LogBase2(double value)
{
	double result = 0.0;
	double temp = value;

	while (temp >= 2.0)
	{
		temp /= 2.0;
		result += 1.0;
	}

	/* Add fractional part approximation */
	if (temp > 1.0)
	{
		double fraction = temp - 1.0;
		if (fraction >= 0.5) result += 0.585;
		else if (fraction >= 0.25) result += 0.321;
		else result += 0.152;
	}

	return result;
}


/******************************************************************************/

static int TestAVLCreateDestroy(void)
{
	avl_t* avl_tree = NULL;
	int status = 0;

	printf("Testing AVL Create/Destroy...");

	avl_tree = AVLCreate(CompareInts);
	status |= TEST_CHECK(NULL != avl_tree, "Failed to initialize AVL tree");

	status |= TEST_CHECK(1 == AVLIsEmpty(avl_tree),
					"Newly initialized AVL tree should be empty");
	status |= TEST_CHECK(0 == AVLHeight(avl_tree),
					"Newly initialized AVL tree height should be zero");
	status |= TEST_CHECK(0 == AVLCount(avl_tree),
					"Newly initialized AVL tree count should be zero");

	AVLDestroy(avl_tree);

	TEST_RESULT(status);
	return (status);
}

static int TestAVLInsertRemove(void)
{
	avl_t* avl_tree = NULL;
	int status = 0;

	printf("Testing AVL Insert/Remove...");

	avl_tree = AVLCreate(CompareInts);
	if (NULL != avl_tree)
	{
		int values[] = {5, 1, 3, 4, 10, 20, 30, 7, 0, 2};
		int sequential[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		size_t n_values = 10;
		int i = 0;

		/* Test basic insert */
		for (i = 0; i < (int)n_values; ++i)
		{
			status |= TEST_CHECK(0 == AVLInsert(avl_tree, &values[i]),
							"AVLInsert should return 0 on success");
		}

		status |= TEST_CHECK(0 == AVLIsEmpty(avl_tree),
						"AVLIsEmpty should return false after inserts");
		status |= TEST_CHECK(n_values == AVLCount(avl_tree),
						"AVLCount should return correct number after inserts");

		/* Test if tree is balanced after inserts */
		status |= TEST_CHECK(4 == AVLHeight(avl_tree),
						"AVLHeight should be 4 after balanced inserts");

		/* Test removing leaf */
		status |= TEST_CHECK(&values[9] == AVLContains(avl_tree, &values[9]), /* 2 */
						"AVLContains should detect existing value in the tree");

		AVLRemove(avl_tree, &values[9]); /* removing 2 */
		--n_values;

		status |= TEST_CHECK(n_values == AVLCount(avl_tree),
						"AVLCount should return correct number after removing leaf");
		status |= TEST_CHECK(NULL == AVLContains(avl_tree, &values[9]),
						"AVLContains should indicate removed value is not in the tree");

		/* Test removing node with 1 child */
		status |= TEST_CHECK(&values[5] == AVLContains(avl_tree, &values[5]), /* 20 */
						"AVLContains should detect existing value in the tree");

		AVLRemove(avl_tree, &values[5]); /* removing 20 */
		--n_values;

		status |= TEST_CHECK(n_values == AVLCount(avl_tree),
						"AVLCount should return correct number after removing node w/1 child");
		status |= TEST_CHECK(NULL == AVLContains(avl_tree, &values[5]),
						"AVLContains should indicate removed value is not in the tree");

		/* Test removing node with 2 children */
		status |= TEST_CHECK(&values[1] == AVLContains(avl_tree, &values[1]), /* 1 */
						"AVLContains should detect existing value in the tree");

		AVLRemove(avl_tree, &values[1]); /* removing 1 */
		--n_values;

		status |= TEST_CHECK(n_values == AVLCount(avl_tree),
						"AVLCount should return correct number after removing node w/2 children");
		status |= TEST_CHECK(NULL == AVLContains(avl_tree, &values[1]),
						"AVLContains should indicate removed value is not in the tree");

		/* Balance test with sequential insertions (should trigger rotations) */
		AVLDestroy(avl_tree);
		avl_tree = AVLCreate(CompareInts);
		assert(NULL != avl_tree);

		/* Insert increasing sequence (1-10) - should trigger left rotations */
		for (i = 0; i < 10; ++i)
		{
			AVLInsert(avl_tree, &sequential[i]);
		}

		status |= TEST_CHECK(4 == AVLHeight(avl_tree),
						"AVLHeight should be 4 after sequential increasing inserts (balance check)");
		status |= TEST_CHECK(10 == AVLCount(avl_tree),
						"AVLCount should be 10 after sequential inserts");

		AVLDestroy(avl_tree);
		avl_tree = AVLCreate(CompareInts);
		assert(NULL != avl_tree);

		/* Insert decreasing sequence (10-1) - should trigger right rotations */
		for (i = 9; i >= 0; --i)
		{
			AVLInsert(avl_tree, &sequential[i]);
		}

		status |= TEST_CHECK(4 == AVLHeight(avl_tree),
						"AVLHeight should be 4 after sequential decreasing inserts (balance check)");
		status |= TEST_CHECK(10 == AVLCount(avl_tree),
						"AVLCount should be 10 after sequential inserts");
	}

	AVLDestroy(avl_tree);

	TEST_RESULT(status);
	return (status);
}

static int TestAVLForEach(void)
{
	avl_t* avl_tree = NULL;
	int status = 0;
	int values[15] = {0};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;

	printf("Testing AVL ForEach...\t");

	avl_tree = AVLCreate(CompareInts);
	if (NULL == avl_tree)
	{
		status |= TEST_CHECK(0, "Failed to initialize AVL tree");
		TEST_RESULT(status);
		return (status);
	}

	/* Insert values into tree */
	for (i = 0; i < n_values; ++i)
	{
		values[i] = ((int)i + 1);
		AVLInsert(avl_tree, &values[i]);
	}

	/* Test pre-order traversal */
	g_action_count = n_values;
	status |= TEST_CHECK(0 == AVLForEach(avl_tree, DummyAction, NULL, PRE_ORDER),
						"AVLForEach should succeed with PRE_ORDER traversal");
	status |= TEST_CHECK(0 == g_action_count,
						"Action should be performed on all nodes in PRE_ORDER");

	/* Test in-order traversal */
	g_action_count = n_values;
	status |= TEST_CHECK(0 == AVLForEach(avl_tree, DummyAction, NULL, IN_ORDER),
						"AVLForEach should succeed with IN_ORDER traversal");
	status |= TEST_CHECK(0 == g_action_count,
						"Action should be performed on all nodes in IN_ORDER");

	/* Test post-order traversal */
	g_action_count = n_values;
	status |= TEST_CHECK(0 == AVLForEach(avl_tree, DummyAction, NULL, POST_ORDER),
						"AVLForEach should succeed with POST_ORDER traversal");
	status |= TEST_CHECK(0 == g_action_count,
						"Action should be performed on all nodes in POST_ORDER");

	/* Test early termination */
	g_action_count = 0; /* Will cause DummyAction to return non-zero on first call */
	status |= TEST_CHECK(1 == AVLForEach(avl_tree, DummyAction, NULL, IN_ORDER),
						"AVLForEach should return non-zero when action fails");

	AVLDestroy(avl_tree);

	TEST_RESULT(status);
	return (status);
}

static int AVLStressTest(void)
{
	avl_t* avl_tree = NULL;
	int status = 0;
	int values[100000] = {0};
	size_t i = 0;
	size_t n_values = 100000;
	size_t theoretical_max_height = 0;

	/* Performance measurement variables */
	clock_t start_time = 0;
	clock_t end_time = 0;
	double insertion_time = 0.0;
	double search_time = 0.0;
	double removal_time = 0.0;
	double reinsertion_time = 0.0;
	double avg_insert_time = 0.0;
	double avg_search_time = 0.0;
	double avg_remove_time = 0.0;

	/* Balance metrics */
	size_t final_height = 0;
	double height_to_nodes_ratio = 0.0;

	printf("Running AVL Stress Test...");

	avl_tree = AVLCreate(CompareInts);
	if (NULL == avl_tree)
	{
		status |= TEST_CHECK(0, "Failed to initialize AVL tree");
		TEST_RESULT(status);
		return (status);
	}

	/* Initialize values */
	for (i = 0; i < n_values; ++i)
	{
		values[i] = i;
	}

	/* Insert values in order and measure time */
	start_time = clock();
	for (i = 0; i < n_values; ++i)
	{
		AVLInsert(avl_tree, &values[i]);
	}
	end_time = clock();
	insertion_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	avg_insert_time = insertion_time / n_values;

	status |= TEST_CHECK(n_values == AVLCount(avl_tree),
					"AVLCount should return correct number after stress test inserts");

	/* For an AVL tree, max height is approximately 1.44*log2(n+2) */
	theoretical_max_height = (size_t)(1.44 * (LogBase2((double)n_values + 2.0)));
	status |= TEST_CHECK(AVLHeight(avl_tree) <= theoretical_max_height,
					"AVLHeight should not exceed theoretical maximum for AVL trees");

	/* Check all values exist and measure search time */
	start_time = clock();
	for (i = 0; i < n_values; ++i)
	{
		status |= TEST_CHECK(&values[i] == AVLContains(avl_tree, &values[i]),
						"AVLContains should find all inserted values");
	}
	end_time = clock();
	search_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	avg_search_time = search_time / n_values;

	/* Remove half the values and measure time */
	start_time = clock();
	for (i = 0; i < n_values; i += 2)
	{
		AVLRemove(avl_tree, &values[i]);
	}
	end_time = clock();
	removal_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	avg_remove_time = removal_time / (n_values / 2);

	status |= TEST_CHECK(n_values / 2 == AVLCount(avl_tree),
					"AVLCount should return correct number after removing half");

	/* Check correct values exist */
	for (i = 0; i < n_values; ++i)
	{
		int expected = (i % 2 == 0) ? 0 : 1;
		status |= TEST_CHECK(
			((expected) ? (&values[i]) : (NULL)) == AVLContains(avl_tree, &values[i]),
			"AVLContains should correctly identify removed/existing values");
	}

	/* Re-insert removed values and measure time */
	start_time = clock();
	for (i = 0; i < n_values; i += 2)
	{
		AVLInsert(avl_tree, &values[i]);
	}
	end_time = clock();
	reinsertion_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	status |= TEST_CHECK(n_values == AVLCount(avl_tree),
					"AVLCount should return correct number after re-insertion");

	/* Check all values exist again */
	for (i = 0; i < n_values; ++i)
	{
		status |= TEST_CHECK(&values[i] == AVLContains(avl_tree, &values[i]),
						"AVLContains should find all values after re-insertion");
	}

	/* Calculate additional metrics */
	final_height = AVLHeight(avl_tree);
	height_to_nodes_ratio = (double)final_height / (LogBase2((double)n_values));

	/* Print performance metrics */
	if (0 == status)
	{
		printf("\n%s ======= Performance Metrics =======%s\n", BOLD_FORMAT, UNFORMAT);
		printf("┌──────────────────────┬───────────────┬───────────────┐\n");
		printf("│ Operation            │ Total Time    │ Avg Time/Op   │\n");
		printf("│                      │ (seconds)     │ (microseconds)│\n");
		printf("├──────────────────────┼───────────────┼───────────────┤\n");
		printf("│ %6lu Insertions    │ %11.6f   │ %11.3f   │\n",
					n_values, insertion_time, avg_insert_time * 1000000.0);
		printf("│ %6lu Searches      │ %11.6f   │ %11.3f   │\n",
					n_values, search_time, avg_search_time * 1000000.0);
		printf("│ %6lu Removals      │ %11.6f   │ %11.3f   │\n",
					n_values / 2, removal_time, avg_remove_time * 1000000.0);
		printf("│ %6lu Re-insertions │ %11.6f   │ %11.3f   │\n",
					n_values / 2, reinsertion_time, (reinsertion_time / (n_values / 2)) * 1000000.0);
		printf("└──────────────────────┴───────────────┴───────────────┘\n");

		printf("\n%s ======= Balance Metrics =======%s\n", BOLD_FORMAT, UNFORMAT);
		printf("┌─────────────────────┬─────────┐\n");
		printf("│ Metric              │ Value   │\n");
		printf("├─────────────────────┼─────────┤\n");
		printf("│ Final tree height   │ %7lu │\n", final_height);
		printf("│ Theoretical max     │ %7lu │\n", theoretical_max_height);
		printf("│ Height/log(n) ratio │ %7.2f │\n", height_to_nodes_ratio);
		printf("└─────────────────────┴─────────┘\n");
	}

	AVLDestroy(avl_tree);

	return (status);
}

static int AVLScalingTest(void)
{
	/* Test sizes for scaling tests */
	size_t test_sizes[] = {/*100, 500, 1000, */5000, 10000};
	size_t num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
	size_t size_idx = 0;
	int status = 0;

	printf("Running AVL Scaling Tests...\n");

	printf("%s ======= Scaling Performance =======%s\n", BOLD_FORMAT, UNFORMAT);
	printf("┌─────────┬───────────┬───────────┬───────────┬───────────┬───────────┐\n");
	printf("│  Size   │ Insertion │  Search   │  Removal  │   Height  │ Height /  │\n");
	printf("│         │  (sec)    │  (sec)    │  (sec)    │           │ Log Ratio │\n");
	printf("├─────────┼───────────┼───────────┼───────────┼───────────┼───────────┤\n");

	for (size_idx = 0; size_idx < num_sizes; ++size_idx)
	{
		avl_t* avl_tree = NULL;
		size_t n_values = test_sizes[size_idx];
		int* values = NULL;
		size_t i = 0;
		clock_t start_time = 0;
		double insertion_time = 0.0;
		double search_time = 0.0;
		double removal_time = 0.0;
		size_t tree_height = 0;
		double log_height = 0.0;
		double height_ratio = 0.0;

		/* Allocate memory for values */
		values = (int*)malloc(n_values * sizeof(int));
		if (NULL == values)
		{
			status |= TEST_CHECK(0, "Failed to allocate memory for values");
			continue;
		}

		/* Initialize values */
		for (i = 0; i < n_values; ++i)
		{
			values[i] = i;
		}

		/* Create tree */
		avl_tree = AVLCreate(CompareInts);
		if (NULL == avl_tree)
		{
			free(values);
			status |= TEST_CHECK(0, "Failed to initialize AVL tree");
			continue;
		}

		/* Measure insertion time */
		start_time = clock();
		for (i = 0; i < n_values; ++i)
		{
			AVLInsert(avl_tree, &values[i]);
		}
		insertion_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;

		/* Measure search time */
		start_time = clock();
		for (i = 0; i < n_values; ++i)
		{
			AVLContains(avl_tree, &values[i]);
		}
		search_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;

		/* Measure removal time (remove half) */
		start_time = clock();
		for (i = 0; i < (n_values / 2); ++i)
		{
			AVLRemove(avl_tree, &values[i]);
		}
		removal_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;

		/* Get height metrics */
		tree_height = AVLHeight(avl_tree);
		log_height = LogBase2((double)n_values);
		height_ratio = (log_height > 0.0) ? ((double)tree_height / log_height) : 0.0;

		/* Print results for this size */
		printf("│ %7lu │ %9.6f │ %9.6f │ %9.6f │ %9lu │ %9.2f │\n",
			n_values, insertion_time, search_time, removal_time,
			tree_height, height_ratio);

		/* Clean up */
		AVLDestroy(avl_tree);
		free(values);
	}

	printf("└─────────┴───────────┴───────────┴───────────┴───────────┴───────────┘\n");

	return (status);
}

int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestAVLCreateDestroy();
	status |= TestAVLInsertRemove();
	status |= TestAVLForEach();

	status |= AVLStressTest();
	status |= AVLScalingTest();
	
	PrintTestSummary(status);
	return (status);
}

