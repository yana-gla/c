/*******************************************************************************
* File: vsa_test.c
*
* Purpose:
*   Test suite for vsa.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h>						/* printf */
#include <stdlib.h>						/* malloc, free */

#include "vsa.h"						/* own header */

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
static int TestVSAInit(void);
static int TestVSAAllocate(void);
static int TestVSALargestBlock(void);
static int TestVSAFree(void);
static int TestVSAIntegrated(void);


/******************************************************************************/

static int TestVSAInit(void)
{
	int status = 0;
	void* memory = NULL;
	vsa_t* vsa = NULL;
	size_t memory_size = 0;
	size_t largest_block = 0;

	printf("Testing VSA Init...\t");

	/* Test with valid parameters */
	memory_size = 96;
	largest_block = memory_size - (2 * sizeof(size_t));
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		status |= TEST_CHECK(largest_block == VSALargestBlock(vsa),
						"VSAInit didn't inialize with correct block size");

		free(memory);
		memory = NULL;
	}

	/* Test with unaligned memory size */
	memory_size = 100; /* Largest block size should match prev test*/
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		status |= TEST_CHECK(largest_block == VSALargestBlock(vsa),
						"VSAInit didn't inialize with correct block size for unaligned memory block");

		free(memory);
		memory = NULL;
	}

	/* Test with insufficient memory size */
	memory_size = 10;
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		status |= TEST_CHECK(NULL == vsa, "VSAInit should fail on insufficient memory size");

		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

static int TestVSAAllocate(void)
{
	int status = 0;
	void* memory = NULL;
	vsa_t* vsa = NULL;
	size_t memory_size = 88;
	void* blocks[4] = {0};
	size_t block_sizes[] = {8, 8, 16, 16};
	size_t i = 0;

	printf("Testing VSA Allocate...\t");

	/* Initialize VSA */
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);

		/* Allocate all blocks */
		for (i = 0; i < sizeof(blocks) / sizeof(blocks[0]) ; ++i)
		{
/*			printf ("\ni is %ld\n", i);*/
			blocks[i] = VSAAllocate(vsa, block_sizes[i]);
/*			printf("\n %ld %ld\n", *((long*)memory), *((long*)memory+2));*/
			
			status |= TEST_CHECK(NULL != blocks[i], "VSAAllocate failed to allocate block");

			/* Check that each allocated block is different */
			if (i > 0 && NULL != blocks[i] && NULL != blocks[i-1])
			{
				status |= TEST_CHECK(blocks[i] != blocks[i-1],
								"VSAAllocate allocated the same block twice");
			}
		}
		
		/* Verify no more blocks are available */
		status |= TEST_CHECK(NULL == VSAAllocate(vsa, block_sizes[0]),
						"VSAAllocate should return NULL when no blocks are left");

		/* Verify largest block is zero */
		status |= TEST_CHECK(0 == VSALargestBlock(vsa),
						"VSALargestBlock should return 0 after all space is allocated");
		
		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

static int TestVSALargestBlock(void)
{
	int status = 0;
	void* memory = NULL;
	vsa_t* vsa = NULL;
	size_t memory_size = 88;
	size_t largest_block = 0;
	void* blocks[4] = {0};
	size_t block_sizes[] = {8, 8, 16, 16};
	size_t i = 0;

	printf("Testing VSA Largest Block...");

	/* Initialize VSA */
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		largest_block = memory_size - (2 * sizeof(size_t));

		/* Allocate all blocks */
		for (i = 0; i < sizeof(blocks) / sizeof(blocks[0]) ; ++i)
		{
			blocks[i] = VSAAllocate(vsa, block_sizes[i]);
			status |= TEST_CHECK(NULL != blocks[i], "VSAAllocate failed to allocate block");

			/* Verify that largest block is correct */
			largest_block -= (block_sizes[i] + (
								(block_sizes[i] == largest_block) ? (0) : (sizeof(size_t))));
			status |= TEST_CHECK(largest_block == VSALargestBlock(vsa),
							"VSALargestBlock did not match expected value after allocation");
		}

		/* Verify largest block is zero */
		status |= TEST_CHECK(0 == VSALargestBlock(vsa),
						"VSALargestBlock should return 0 after all space is allocated");

		/* Verify consecutive freed blocks give correct largest block */
		largest_block = sizeof(size_t) + block_sizes[2] + block_sizes[3];
		VSAFree(blocks[0]); /* extra free (non-consecutive) */
		VSAFree(blocks[2]);
		VSAFree(blocks[3]);
		status |= TEST_CHECK(largest_block == VSALargestBlock(vsa),
						"VSALargestBlock returned incorrect value when adjacent blocks freed");

		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

static int TestVSAFree(void)
{
	int status = 0;
	void* memory = NULL;
	vsa_t* vsa = NULL;
	size_t memory_size = 96;
	void* block1 = NULL;
	void* block2 = NULL;
	void* block3 = NULL;
	size_t largest_before_alloc = 0;
	size_t largest_after_alloc = 0;
	size_t largest_after_free = 0;

	printf("Testing VSA Free...\t");

	/* Initialize VSA */
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		largest_before_alloc = VSALargestBlock(vsa);

		/* Allocate multiple blocks */
		block1 = VSAAllocate(vsa, 8);
		block2 = VSAAllocate(vsa, 16);
		block3 = VSAAllocate(vsa, 8);

		largest_after_alloc = VSALargestBlock(vsa);

		/* Test freeing single block */
		VSAFree(block3);
		largest_after_free = VSALargestBlock(vsa);
		status |= TEST_CHECK(largest_after_free > largest_after_alloc,
						"VSAFree failed to increase available space");

		/* Test re-allocating after free */
		block3 = VSAAllocate(vsa, 8);
		status |= TEST_CHECK(NULL != block2,
						"Failed to re-allocate freed block");

		/* Test freeing multiple blocks */
		VSAFree(block2);
		VSAFree(block3);
		status |= TEST_CHECK(VSALargestBlock(vsa) > largest_after_free,
						"Multiple VSAFree operations failed to coalesce adjacent blocks");

		/* Test freeing all blocks should restore original largest block size */
		VSAFree(block1);
		status |= TEST_CHECK(VSALargestBlock(vsa) == largest_before_alloc,
						"VSAFree all blocks failed to restore original block size");

		free(memory);
		memory = NULL;
	}

	TEST_RESULT(status);
	return status;
}

static int TestVSAIntegrated(void)
{
	int status = 0;
	void* memory = NULL;
	vsa_t* vsa = NULL;
	size_t memory_size = 192;
	void* blocks[10] = {0};
	size_t block_sizes[] = {8, 24, 8, 16, 8, 32, 8};
	size_t num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);
	size_t i = 0;
	size_t expected_largest = 0;
	size_t total_allocated = 0;
	size_t largest_freed_block = 0;

	printf("Testing VSA Integrated...");

	/* Initialize VSA */
	memory = malloc(memory_size);

	if (NULL != memory)
	{
		vsa = VSAInit(memory, memory_size);
		expected_largest = memory_size - (2 * sizeof(size_t));

		/* Test allocation pattern - fill memory partially */
		for (i = 0; i < num_blocks; ++i)
		{
			blocks[i] = VSAAllocate(vsa, block_sizes[i]);
			status |= TEST_CHECK(NULL != blocks[i],
							"VSAAllocate failed during integrated test");

			/* Each allocation reduces available space by block size + metadata */
			total_allocated += (block_sizes[i] + sizeof(size_t));
		}

		/* Test fragmentation handling - free non-adjacent blocks */
		VSAFree(blocks[1]); /* Free 24-byte block (+ metadata) */
		VSAFree(blocks[3]); /* Free 16-byte block (+ metadata) */
		VSAFree(blocks[5]); /* Free 32-byte block (+ metadata) */

		/* The largest free block should be the 32-byte block */
		largest_freed_block = 32;
		status |= TEST_CHECK(largest_freed_block == VSALargestBlock(vsa),
						"Largest block size incorrect after fragmented free");

		/* Test allocating in fragmented memory - should use largest free block */
		blocks[5] = VSAAllocate(vsa, 30); /* Should fit in the 32-byte freed space */
		status |= TEST_CHECK(NULL != blocks[5],
						"Failed to allocate block in fragmented memory");

		/* Test re-allocating when exact size block available */
		blocks[1] = VSAAllocate(vsa, 24);
		status |= TEST_CHECK(NULL != blocks[1],
						"Failed to re-allocate exact-size freed block");

		/* Test free and re-allocation pattern to verify memory stability */
		for (i = 0; i < num_blocks; ++i)
		{
			if (NULL != blocks[i])
			{
				VSAFree(blocks[i]);
				blocks[i] = NULL;
			}
		}

		/* After freeing all blocks, we should be able to allocate one large block */
		expected_largest = memory_size - (2 * sizeof(size_t));
		status |= TEST_CHECK(expected_largest == VSALargestBlock(vsa),
						"Failed to properly coalesce all free blocks");

		/* Allocate one large block (accounting for needed metadata) */
		blocks[0] = VSAAllocate(vsa, expected_largest - sizeof(size_t));
		status |= TEST_CHECK(NULL != blocks[0],
						"Failed to allocate largest possible block");

		/* Verify no more space available */
		status |= TEST_CHECK(0 == VSALargestBlock(vsa),
						"Largest block should be 0 after allocating all memory");

		/* Free the large block */
		VSAFree(blocks[0]);
		status |= TEST_CHECK(expected_largest == VSALargestBlock(vsa),
						"Failed to fully restore memory after freeing large block");

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

	status |= TestVSAInit();
	status |= TestVSAAllocate();
	status |= TestVSALargestBlock();
	status |= TestVSAFree();
	status |= TestVSAIntegrated();

	PrintTestSummary(status);
	return (status);
}

