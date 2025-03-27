/*******************************************************************************
* File: heap_test.c
*
* Purpose:
*   Test suite for heap.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcpy, srcmp, etc */
#include <math.h> /* fabs */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert.h */

#include "heap.h" /* own header */

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

/* Basic Tests Prototypes*/
static int TestHeapCreateDestroy(void);
static int TestHeapPeekPushPop(void);
/*static int TestHeapRemove(void);*/

/* Basic Test Helpers */
static int CompareInts(const void* first, const void* second);
static int MatchInts(const void* data, void* params);

/* Additional Test Prototypes */
static int TestHeapEdgeCases(void);
static int TestHeapDifferentDataTypes(void);
static int TestHeapStressTest(void);

/* Additional Test Helpers */
static int CompareStrings(const void* first, const void* second);
static int MatchStrings(const void* data, void* params);
static int CompareFloats(const void* first, const void* second);
static int MatchFloats(const void* data, void* params);

typedef struct person
{
	char name[50];
	int age;
} person_t;

static int ComparePersonsByAge(const void* first, const void* second);
static int MatchPersonsByName(const void* data, void* params);


/*** Basic Helpers ************************************************************/

static int CompareInts(const void* first, const void* second)
{
	assert(NULL != first);
	assert(NULL != second);

	if (*(int*)first < *(int*)second)
	{
		return (-1);
	}
	else if (*(int*)first > *(int*)second)
	{
		return (1);
	}

	return (0);
}

static int MatchInts(const void* data, void* params)
{
	assert(NULL != data);
	assert(NULL != params);

	return (*(int*)data == *(int*)params);
}


/*** Additional Helpers ********************************************************/

static int CompareStrings(const void* first, const void* second)
{
	int result = 0;
	
	assert(NULL != first);
	assert(NULL != second);
	
	result = strcmp((char*)first, (char*)second);
	
	if (result < 0)
	{
		return (-1);
	}
	else if (result > 0)
	{
		return (1);
	}
	
	return (0);
}

static int MatchStrings(const void* data, void* params)
{
	assert(NULL != data);
	assert(NULL != params);
	
	return (0 == strcmp((char*)data, (char*)params));
}

static int CompareFloats(const void* first, const void* second)
{
	assert(NULL != first);
	assert(NULL != second);
	
	if (*(float*)first < *(float*)second)
	{
		return (-1);
	}
	else if (*(float*)first > *(float*)second)
	{
		return (1);
	}
	
	return (0);
}

static int MatchFloats(const void* data, void* params)
{
	const float epsilon = 0.00001f;
	float diff = 0.0f;
	
	assert(NULL != data);
	assert(NULL != params);
	
	diff = fabs(*(float*)data - *(float*)params);
	return (diff < epsilon);
}

static int ComparePersonsByAge(const void* first, const void* second)
{
	assert(NULL != first);
	assert(NULL != second);
	
	if (((person_t*)first)->age < ((person_t*)second)->age)
	{
		return (-1);
	}
	else if (((person_t*)first)->age > ((person_t*)second)->age)
	{
		return (1);
	}
	
	return (0);
}

static int MatchPersonsByName(const void* data, void* params)
{
	assert(NULL != data);
	assert(NULL != params);
	
	return (0 == strcmp(((person_t*)data)->name, (char*)params));
}


/******************************************************************************/

static int TestHeapCreateDestroy(void)
{
	heap_t* heap = NULL;
	int status = 0;

	printf("Testing Heap Create/Destroy...");
	heap = HeapCreate(CompareInts);
	status |= TEST_CHECK(NULL != heap, "HeapCreate failed to create new heap");

	status |= TEST_CHECK(1 == HeapIsEmpty(heap), "HeapIsEmpty should return true on new heap");
	status |= TEST_CHECK(0 == HeapSize(heap), "HeapSize should return 0 on new heap");

	HeapDestroy(heap);

	TEST_RESULT(status);
	return status;
}

static int TestHeapPeekPushPop(void)
{
	heap_t* heap = NULL;
	int status = 0;
	int values[] = {5, 3, 7, 2, 4, 6, 8};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;

	printf("Testing Heap Push/Peek/Pop...");

	heap = HeapCreate(CompareInts);
	if (NULL == heap)
	{
		status |= TEST_CHECK(0, "Failed to initialize heap");
		TEST_RESULT(status);
		return (status);
	}

	/* Test Push */
	for (i = 0; i < n_values; ++i)
	{
		status |= TEST_CHECK(0 == HeapPush(heap, &values[i]),
						"HeapPush should return 0 on success");
	}

	status |= TEST_CHECK(0 == HeapIsEmpty(heap),
					"HeapIsEmpty should return false after pushes");
	status |= TEST_CHECK(n_values == HeapSize(heap),
					"HeapSize should return correct number after pushes");

	/* Test Peek */
	status |= TEST_CHECK(&values[3] == HeapPeek(heap),  /* 2 should be the highest priority */
					"HeapPeek should return highest priority element");

	/* Test Pop */
	HeapPop(heap);
	status |= TEST_CHECK(n_values - 1 == HeapSize(heap),
					"HeapSize should decrease after HeapPop");
	status |= TEST_CHECK(&values[1] == HeapPeek(heap),  /* 3 should be next */
					"HeapPeek should return new highest priority element after pop");

	/* Pop all elements and verify empty state */
	for (i = 0; i < n_values - 1; ++i)
	{
		HeapPop(heap);
	}

	status |= TEST_CHECK(1 == HeapIsEmpty(heap),
					"HeapIsEmpty should return true after popping all elements");
	status |= TEST_CHECK(0 == HeapSize(heap),
					"HeapSize should be 0 after popping all elements");

	HeapDestroy(heap);

	TEST_RESULT(status);
	return (status);
}

static int TestHeapRemove(void)
{
	heap_t* heap = NULL;
	int status = 0;
	int values[] = {5, 3, 7, 2, 4, 6, 8};
	size_t n_values = sizeof(values) / sizeof(values[0]);
	size_t i = 0;
	int target_value = 0;
	void* removed_value = NULL;

	printf("Testing Heap Remove...\t");

	heap = HeapCreate(CompareInts);
	if (NULL == heap)
	{
		status |= TEST_CHECK(0, "Failed to initialize heap");
		TEST_RESULT(status);
		return (status);
	}

	/* Insert values */
	for (i = 0; i < n_values; ++i)
	{
		HeapPush(heap, &values[i]);
	}

	/* Test remove existing value */
	target_value = 4;
	removed_value = HeapRemove(heap, MatchInts, &target_value);
	status |= TEST_CHECK(&values[4] == removed_value,
					"HeapRemove should return pointer to removed value");
	status |= TEST_CHECK(n_values - 1 == HeapSize(heap),
					"HeapSize should decrease after HeapRemove");

	/* Test remove non-existent value */
	target_value = 999;  /* Value not in heap */
	removed_value = HeapRemove(heap, MatchInts, &target_value);
	status |= TEST_CHECK(NULL == removed_value,
					"HeapRemove should return NULL when value not found");
	status |= TEST_CHECK(n_values - 1 == HeapSize(heap),
					"HeapSize should remain unchanged when removing non-existent value");

	/* Test remove highest priority element */
	target_value = 2;  /* Highest priority value */
	removed_value = HeapRemove(heap, MatchInts, &target_value);
	status |= TEST_CHECK(&values[3] == removed_value,
					"HeapRemove should return pointer to highest priority value");
	status |= TEST_CHECK(n_values - 2 == HeapSize(heap),
					"HeapSize should decrease after removing highest priority element");
	status |= TEST_CHECK(&values[1] == HeapPeek(heap),  /* 3 should be new highest */
					"Heap should maintain priority after removing highest element");

	/* Remove all remaining elements using HeapRemove */
	for (i = 0; i < n_values; ++i)
	{
		target_value = values[i];
		HeapRemove(heap, MatchInts, &target_value);
	}

	status |= TEST_CHECK(1 == HeapIsEmpty(heap),
					"HeapIsEmpty should return true after removing all elements");

	HeapDestroy(heap);

	TEST_RESULT(status);
	return (status);
}

static int TestHeapEdgeCases(void)
{
	heap_t* heap = NULL;
	int status = 0;
	int single_value = 42;
	
	printf("Testing Heap Edge Cases...");
	heap = HeapCreate(CompareInts);

	/* Test heap with one element */
	status |= TEST_CHECK(0 == HeapPush(heap, &single_value),
					"HeapPush should succeed with one element");
	status |= TEST_CHECK(1 == HeapSize(heap),
					"HeapSize should return 1 after pushing one element");
	status |= TEST_CHECK(&single_value == HeapPeek(heap),
					"HeapPeek should return the single element");
	
	HeapPop(heap);
	status |= TEST_CHECK(0 == HeapSize(heap),
					"HeapSize should return 0 after popping the single element");
	status |= TEST_CHECK(1 == HeapIsEmpty(heap),
					"HeapIsEmpty should return true after popping the single element");
	
	HeapDestroy(heap);
	
	TEST_RESULT(status);
	return (status);
}

static int TestHeapDifferentDataTypes(void)
{
	heap_t* string_heap = NULL;
	heap_t* float_heap = NULL;
	heap_t* struct_heap = NULL;
	int status = 0;
	
	/* Test with strings */
	char* str1 = "banana";
	char* str2 = "apple";
	char* str3 = "cherry";
	char* str4 = "date";
	char* str_arr[4] = {0};
	size_t n_strings = sizeof(str_arr) / sizeof(str_arr[0]);
	char* target_str = NULL;
	size_t i = 0;

	/* Test with floats */
	float float1 = 3.14f;
	float float2 = 1.41f;
	float float3 = 2.71f;
	float float4 = 1.73f;
	float target_float = 0.0f;
	
	/* Test with structs */
	person_t person1 = {"Alice", 30};
	person_t person2 = {"Bob", 25};
	person_t person3 = {"Charlie", 35};
	person_t person4 = {"Dave", 28};
	char target_name[50] = {0};

	/* Populate str_arr */
	str_arr[0] = str1;
	str_arr[1] = str2;
	str_arr[2] = str3;
	str_arr[3] = str4;

	printf("Testing Heap w/ Diff Types...");
	
	/* String heap tests */
	string_heap = HeapCreate(CompareStrings);
	status |= TEST_CHECK(NULL != string_heap, 
					"HeapCreate should succeed with string comparator");
	
	for (i = 0; i < n_strings; ++i)
	{
		status |= TEST_CHECK(0 == HeapPush(string_heap, str_arr[i]),
						"HeapPush should succeed with string pointers");
	}
	
	status |= TEST_CHECK(str2 == HeapPeek(string_heap),
					"HeapPeek should return highest priority string (apple)");
	
	target_str = "cherry";
	status |= TEST_CHECK(str3 == HeapRemove(string_heap, MatchStrings, target_str),
					"HeapRemove should find and remove matching string");
	
	HeapDestroy(string_heap);
	
	/* Float heap tests */
	float_heap = HeapCreate(CompareFloats);
	status |= TEST_CHECK(NULL != float_heap,
					"HeapCreate should succeed with float comparator");
	
	status |= TEST_CHECK(0 == HeapPush(float_heap, &float1), 
					"HeapPush should succeed with float");
	status |= TEST_CHECK(0 == HeapPush(float_heap, &float2), 
					"HeapPush should succeed with float");
	status |= TEST_CHECK(0 == HeapPush(float_heap, &float3), 
					"HeapPush should succeed with float");
	status |= TEST_CHECK(0 == HeapPush(float_heap, &float4), 
					"HeapPush should succeed with float");
	
	status |= TEST_CHECK(&float2 == HeapPeek(float_heap),
					"HeapPeek should return highest priority float (1.41)");
	
	target_float = 2.71f;
	status |= TEST_CHECK(&float3 == HeapRemove(float_heap, MatchFloats, &target_float),
					"HeapRemove should find and remove matching float");
	
	HeapDestroy(float_heap);
	
	/* Struct heap tests */
	struct_heap = HeapCreate(ComparePersonsByAge);
	status |= TEST_CHECK(NULL != struct_heap,
					"HeapCreate should succeed with struct comparator");
	
	status |= TEST_CHECK(0 == HeapPush(struct_heap, &person1),
					"HeapPush should succeed with struct");
	status |= TEST_CHECK(0 == HeapPush(struct_heap, &person2),
					"HeapPush should succeed with struct");
	status |= TEST_CHECK(0 == HeapPush(struct_heap, &person3),
					"HeapPush should succeed with struct");
	status |= TEST_CHECK(0 == HeapPush(struct_heap, &person4),
					"HeapPush should succeed with struct");
	
	status |= TEST_CHECK(&person2 == HeapPeek(struct_heap),
					"HeapPeek should return highest priority person (Bob, 25)");
	
	strcpy(target_name, "Charlie");
	status |= TEST_CHECK(&person3 == HeapRemove(struct_heap, MatchPersonsByName, target_name),
					"HeapRemove should find and remove matching person");
	
	HeapDestroy(struct_heap);
	
	TEST_RESULT(status);
	return (status);
}

static int TestHeapStressTest(void)
{
	heap_t* heap = NULL;
	int status = 0;
	int values[1000];
	size_t i = 0;
	size_t expected_size = 0;
	int prev_value = 0;
	int current_value = 0;
	
	printf("Testing Heap Stress...\t");
	
	heap = HeapCreate(CompareInts);
	status |= TEST_CHECK(NULL != heap,
					"HeapCreate should succeed for stress test");
	
	/* Fill heap with values */
	for (i = 0; i < 1000; ++i)
	{
		values[i] = rand() % 10000;
		status |= TEST_CHECK(0 == HeapPush(heap, &values[i]),
						"HeapPush should succeed during stress test");
	}
	
	expected_size = 1000;
	status |= TEST_CHECK(expected_size == HeapSize(heap),
					"HeapSize should return correct count after 1000 pushes");
	
	/* Verify heap property by popping in order */
	if (1 != HeapIsEmpty(heap))
	{
		prev_value = *(int*)HeapPeek(heap);
		HeapPop(heap);
		expected_size--;
		
		for (i = 0; i < 999; ++i)
		{
			if (NULL != HeapPeek(heap))
			{
				current_value = *(int*)HeapPeek(heap);
				status |= TEST_CHECK(prev_value <= current_value,
								"Heap property should be maintained during stress test");
				prev_value = current_value;
				HeapPop(heap);
				expected_size--;
				
				status |= TEST_CHECK(expected_size == HeapSize(heap),
								"HeapSize should update correctly during stress test");
			}
		}
	}
	
	status |= TEST_CHECK(1 == HeapIsEmpty(heap),
					"HeapIsEmpty should return true after popping all elements");
	
	HeapDestroy(heap);
	
	TEST_RESULT(status);
	return (status);
}


int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestHeapCreateDestroy();
	status |= TestHeapPeekPushPop();
	status |= TestHeapRemove();
	status |= TestHeapEdgeCases();
	status |= TestHeapDifferentDataTypes();
	status |= TestHeapStressTest();

	PrintTestSummary(status);
	return (status);
}

