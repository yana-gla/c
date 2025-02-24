/*******************************************************************************
* File: task_test.c
*
* Purpose:
*   Test suite for task.h
*
* Author:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h>						/* printf */
#include <string.h>						/* strcmp */
#include "task.h"						/* own header */

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


/***************************** Core Test Function *****************************/

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

/* Test function prototypes */
static int TestTaskCreate(void);
static int TestTaskTime(void);
static int TestTaskRun(void);
static int TestTaskCleanup(void);

/* Test helper functions */
static ssize_t DummyJob(void* params);
static ssize_t PeriodicJob(void* params);
static void DummyCleanup(void* params);

/* Test parameters */
static int g_job_counter = 0;
static int g_cleanup_counter = 0;
static int g_periodic_interval = 5;


/**************************** Test Implementation *****************************/

static ssize_t DummyJob(void* params)
{
	(void)params;
	++g_job_counter;
	return (-1);
}

static ssize_t PeriodicJob(void* params)
{
	(void)params;
	++g_job_counter;
	return g_periodic_interval;
}

static void DummyCleanup(void* params)
{
	(void)params;
	++g_cleanup_counter;
}

static int TestTaskCreate(void)
{
	int status = 0;
	task_t* task1 = NULL;
	task_t* task2 = NULL;
	time_t curr_time = time(NULL);
	ssize_t interval = 0;

	printf("Testing Task Create...\t");

	/* Test basic creation */
	task1 = TaskCreate(curr_time, DummyJob, NULL, DummyCleanup, NULL, interval);
	status |= TEST_CHECK(NULL != task1, "Task creation failed");

	/* Test initialized time */
	status |= TEST_CHECK(curr_time == TaskGetTime(task1), "Time not set correctly");

	/* Test UID uniqueness */
	task2 = TaskCreate(curr_time, DummyJob, NULL, DummyCleanup, NULL, interval);
	status |= TEST_CHECK(0 == CompareUID(TaskGetUID(task1), TaskGetUID(task2)),
							"UIDs not unique");

	TaskDestroy(task1);
	TaskDestroy(task2);

	TEST_RESULT(status);
	return status;
}

static int TestTaskTime(void)
{
	int status = 0;
	task_t* task = NULL;
	time_t curr_time = time(NULL);
	time_t new_time = curr_time + 100;
	ssize_t interval = 0;

	printf("Testing Task Time Get/Set...");

	task = TaskCreate(curr_time, DummyJob, NULL, DummyCleanup, NULL, interval);

	/* Test time getter */
	status |= TEST_CHECK(curr_time == TaskGetTime(task), "Initial time incorrect");

	/* Test time setter */
	TaskSetTime(task, new_time);
	status |= TEST_CHECK(new_time == TaskGetTime(task), "Time update failed");

	TaskDestroy(task);

	TEST_RESULT(status);
	return status;
}

static int TestTaskRun(void)
{
	int status = 0;
	task_t* task = NULL;
	time_t curr_time = time(NULL);
	ssize_t interval = 0;

	printf("Testing Task Run...\t");

	/* Test one-time task */
	g_job_counter = 0;
	task = TaskCreate(curr_time, DummyJob, NULL, DummyCleanup, NULL, interval);
	status |= TEST_CHECK(-1 == TaskRun(task), "One-time task return value wrong");
	status |= TEST_CHECK(1 == g_job_counter, "Job not executed");
	TaskDestroy(task);

	/* Test periodic task */
	g_job_counter = 0;
	task = TaskCreate(curr_time, PeriodicJob, NULL, DummyCleanup, NULL, interval);
	status |= TEST_CHECK(g_periodic_interval == TaskRun(task),
		"Periodic task return value wrong");
	status |= TEST_CHECK(1 == g_job_counter, "Periodic job not executed");
	TaskDestroy(task);

	TEST_RESULT(status);
	return status;
}

static int TestTaskCleanup(void)
{
	int status = 0;
	task_t* task = NULL;
	time_t curr_time = time(NULL);
	ssize_t interval = 0;

	printf("Testing Task Cleanup...\t");

	g_cleanup_counter = 0;
	task = TaskCreate(curr_time, DummyJob, NULL, DummyCleanup, NULL, interval);

	TaskCleanUp(task);
	status |= TEST_CHECK(1 == g_cleanup_counter, "Cleanup not executed");

	TaskDestroy(task);

	TEST_RESULT(status);
	return status;
}

int main(void)
{
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestTaskCreate();
	status |= TestTaskTime();
	status |= TestTaskRun();
	status |= TestTaskCleanup();

	PrintTestSummary(status);
	return (status);
}

