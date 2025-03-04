/*******************************************************************************
* File: fsa_test.c
*
* Purpose:
*   Test suite for fsa.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h>						/* printf */
#include <stdlib.h>						/* malloc, free */
#include <string.h>						/* memset */

#include "fsa.h"						/* own header */

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
static int TestFSASuggestSize(void);
static int TestFSAInit(void);
static int TestFSAAllocate(void);
static int TestFSACountFree(void);
static int TestFSAFree(void);
static int TestFSAIntegrated(void);


/******************************************************************************/

static int TestFSASuggestSize(void)
{
	int status = 0;

	printf("Testing FSA Suggest Size...");

	status |= TEST_CHECK(
					(sizeof(size_t) + 5 * sizeof(size_t)) == FSASuggestSize(5, 5),
					"Suggested size did not match expected for block_size=5, num_blocks=5");

	status |= TEST_CHECK(
					(sizeof(size_t) + 5 * sizeof(size_t)) == FSASuggestSize(8, 5),
					"Suggested size did not match expected for block_size=8, num_blocks=5");

	status |= TEST_CHECK(
					sizeof(size_t) == FSASuggestSize(0, 5),
					"Suggested size did not match expected; should be header size only");

	status |= TEST_CHECK(
					sizeof(size_t) == FSASuggestSize(5, 0),
					"Suggested size did not match expected; should be header size only for zero blocks");

	TEST_RESULT(status);
	return status;
}

static int TestFSAInit(void)
{
	int status = 0;
	void* memory = NULL;
	fsa_t* fsa = NULL;
	size_t block_size = 16;
	size_t num_blocks = 10;
	size_t memory_size = 0;

	printf("Testing FSA Init...\t");

	/* Test with valid parameters */
	memory_size = FSASuggestSize(block_size, num_blocks);
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);
		status |= TEST_CHECK(num_blocks == FSACountFree(fsa),
						"FSAInit didn't initialize all blocks as free");

		free(memory);
		memory = NULL;
	}

	/* Test with insufficient memory size - FSA should succeed but with fewer blocks */
	memory_size = FSASuggestSize(block_size, num_blocks);
	memory = malloc(memory_size - 5);

	if (NULL != memory)
	{
		/* Memory for 9 blocks instead of 10 */
		fsa = FSAInit(memory, memory_size - 5, block_size);
		status |= TEST_CHECK(num_blocks - 1 == FSACountFree(fsa),
					"FSAInit with reduced memory should initialize fewer blocks");

		free(memory);
		memory = NULL;
	}

	/* Test with insufficient memory size */
	memory_size = 5;
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);
		status |= TEST_CHECK(NULL == fsa,
						"FSAInit should failed with insufficient memory size");

		free(memory);
		memory = NULL;
	}

	/* Test with NULL memory */
	fsa = FSAInit(NULL, memory_size, block_size);
	status |= TEST_CHECK(NULL == fsa, "FSAInit should fail with NULL memory");

	/* Test with zero block size */
	memory_size = FSASuggestSize(0, num_blocks);
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, 0);
		status |= TEST_CHECK(NULL == fsa, "FSAInit should fail with zero block size");

		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

static int TestFSAAllocate(void)
{
	int status = 0;
	void* memory = NULL;
	fsa_t* fsa = NULL;
	size_t block_size = 32;
	size_t num_blocks = 5;
	size_t memory_size = 0;
	void* blocks[5] = {NULL};
	int i = 0;

	printf("Testing FSA Allocate...\t");

	/* Initialize FSA */
	memory_size = FSASuggestSize(block_size, num_blocks);
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);

		/* Allocate all blocks */
		for (i = 0; i < (int)num_blocks; ++i)
		{
			blocks[i] = FSAAllocate(fsa);
			status |= TEST_CHECK(NULL != blocks[i], "FSAAllocate failed to allocate block");

			/* Check that each allocated block is different */
			if (i > 0 && NULL != blocks[i] && NULL != blocks[i-1])
			{
				status |= TEST_CHECK(blocks[i] != blocks[i-1],
								"FSAAllocate allocated the same block twice");
			}
		}

		/* Verify no more blocks are available */
		status |= TEST_CHECK(NULL == FSAAllocate(fsa),
						"FSAAllocate should return NULL when no blocks are left");

		/* Verify count is zero */
		status |= TEST_CHECK(0 == FSACountFree(fsa),
						"FSACountFree should return 0 after all blocks are allocated");

		free(memory);
		memory = NULL;
	}

	/* Test with NULL FSA */
	status |= TEST_CHECK(NULL == FSAAllocate(NULL),
		"FSAAllocate should return NULL with NULL FSA");

	TEST_RESULT(status);
	return status;
}

static int TestFSACountFree(void)
{
	int status = 0;
	void* memory = NULL;
	fsa_t* fsa = NULL;
	size_t block_size = 16;
	size_t num_blocks = 8;
	size_t memory_size = 0;
	void* blocks[8] = {NULL};
	int i = 0;

	printf("Testing FSA Count Free...");

	/* Initialize FSA */
	memory_size = FSASuggestSize(block_size, num_blocks);
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);

		/* Initial count should be equal to num_blocks */
		status |= TEST_CHECK(num_blocks == FSACountFree(fsa),
						"FSACountFree should return num_blocks after initialization");

		/* Allocate blocks one by one and check count */
		for (i = 0; i < (int)num_blocks; ++i)
		{
			blocks[i] = FSAAllocate(fsa);
			status |= TEST_CHECK(num_blocks - (i + 1) == FSACountFree(fsa),
							"FSACountFree returned incorrect count after allocation");
		}

		free(memory);
		memory = NULL;
	}
	(void)blocks;

	/* Test with NULL FSA */
	status |= TEST_CHECK(0 == FSACountFree(NULL),
					"FSACountFree should return 0 with NULL FSA");

	TEST_RESULT(status);
	return status;
}

static int TestFSAFree(void)
{
	int status = 0;
	void* memory = NULL;
	fsa_t* fsa = NULL;
	size_t block_size = 24;
	size_t num_blocks = 6;
	size_t memory_size = 0;
	void* blocks[6] = {NULL};
	int i = 0;

	printf("Testing FSA Free...\t");

	/* Initialize FSA */
	memory_size = FSASuggestSize(block_size, num_blocks);
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);

		/* Allocate all blocks */
		for (i = 0; i < (int)num_blocks; ++i)
		{
			blocks[i] = FSAAllocate(fsa);
		}
		status |= TEST_CHECK(0 == FSACountFree(fsa),
						"FSACountFree should return 0 after all blocks are allocated");

		/* Free blocks one by one and check count */
		for (i = 0; i < (int)num_blocks; ++i)
		{
			FSAFree(fsa, blocks[i]);
			status |= TEST_CHECK((size_t)(i + 1) == FSACountFree(fsa),
							"FSACountFree returned incorrect count after freeing block");
		}

		/* Test freeing NULL block */
		FSAFree(fsa, NULL);
		status |= TEST_CHECK(num_blocks == FSACountFree(fsa),
						"FSAFree with NULL block should not affect count");


		free(memory);
		memory = NULL;
	}

	/* Test with NULL FSA */
	FSAFree(NULL, NULL);
	status |= TEST_CHECK(1, "FSAFree with NULL FSA should not crash");

	TEST_RESULT(status);
	return status;
}

static int TestFSAIntegrated(void)
{
	int status = 0;
	void* memory = NULL;
	fsa_t* fsa = NULL;
	size_t block_size = 5;
	size_t num_blocks = 10;
	size_t memory_size = 0;
	void* blocks[10] = {NULL};
	int pattern = 0xABCDEF;
	int* int_blocks[10] = {NULL};
	int i = 0;

	printf("Testing FSA Integrated...");

	/* Initialize FSA */
	memory_size = FSASuggestSize(block_size, num_blocks); /* Should be 88 bytes on 64-bit system */
	status |= TEST_CHECK((sizeof(size_t) + 10 * sizeof(size_t)) == memory_size,
		"Memory size calculation should account for word-alignment");

	memory = malloc(memory_size);

	if (NULL != memory)
	{
		fsa = FSAInit(memory, memory_size, block_size);

		/* Allocate half the blocks and verify */
		for (i = 0; i < 5; ++i)
		{
			blocks[i] = FSAAllocate(fsa);
			int_blocks[i] = (int*)blocks[i];
			*int_blocks[i] = pattern + i;
		}

		status |= TEST_CHECK(5 == FSACountFree(fsa),
						"FSACountFree should return 5 after allocating half the blocks");

		/* Verify block contents */
		for (i = 0; i < 5; ++i)
		{
			status |= TEST_CHECK(pattern + i == *int_blocks[i],
							"Block content was corrupted");
		}

		/* Free and reallocate mixed pattern */
		FSAFree(fsa, blocks[1]);
		FSAFree(fsa, blocks[3]);
		status |= TEST_CHECK(7 == FSACountFree(fsa),
						"FSACountFree should return 7 after freeing 2 blocks");

		blocks[5] = FSAAllocate(fsa);
		blocks[6] = FSAAllocate(fsa);
		int_blocks[5] = (int*)blocks[5];
		int_blocks[6] = (int*)blocks[6];
		*int_blocks[5] = pattern + 10;
		*int_blocks[6] = pattern + 11;

		status |= TEST_CHECK(5 == FSACountFree(fsa),
						"FSACountFree should return 5 after reallocating 2 blocks");

		/* Verify original blocks still intact */
		status |= TEST_CHECK(pattern + 0 == *int_blocks[0], "Block 0 content was corrupted");
		status |= TEST_CHECK(pattern + 2 == *int_blocks[2], "Block 2 content was corrupted");
		status |= TEST_CHECK(pattern + 4 == *int_blocks[4], "Block 4 content was corrupted");
		status |= TEST_CHECK(pattern + 10 == *int_blocks[5], "Block 5 content was corrupted");
		status |= TEST_CHECK(pattern + 11 == *int_blocks[6], "Block 6 content was corrupted");

		/* Free all blocks */
		FSAFree(fsa, blocks[0]);
		FSAFree(fsa, blocks[2]);
		FSAFree(fsa, blocks[4]);
		FSAFree(fsa, blocks[5]);
		FSAFree(fsa, blocks[6]);

		status |= TEST_CHECK(num_blocks == FSACountFree(fsa),
						"FSACountFree should return num_blocks after freeing all blocks");

		/* Reallocate all blocks to verify FSA is still functional */
		for (i = 0; i < (int)num_blocks; ++i)
		{
			blocks[i] = FSAAllocate(fsa);
			status |= TEST_CHECK(NULL != blocks[i],
							"FSAAllocate failed after freeing and reallocating");
		}

		status |= TEST_CHECK(0 == FSACountFree(fsa),
						"FSACountFree should return 0 after reallocating all blocks");

		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestFSASuggestSize();
	status |= TestFSAInit();
	status |= TestFSAAllocate();
	status |= TestFSACountFree();
	status |= TestFSAFree();
	status |= TestFSAIntegrated();

	PrintTestSummary(status);
	return (status);
}

