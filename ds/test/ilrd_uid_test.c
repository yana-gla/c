/*******************************************************************************
* File: ilrd_uid_test.c
*
* Purpose:
*   Test suite for ilrd_uid.h
*   
* Taken from:
*   Shani Zuniga
*
*******************************************************************************/

#include <stdio.h>						/* printf */
#include <unistd.h>						/* sleep */
#include "ilrd_uid.h"					/* own header */

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


/******************************CORE*TEST*FUNCTION******************************/

/* Core check function with formatted output */
int Check(
	int condition,			/* Test condition to evaluate */
	const char* message,	/* Error message if test fails */
	const char* file,		/* Source file where check occurred */
	int line				/* Line number where check occurred */
);

/* Core check function implementation */
int Check(int condition, const char* message, const char* file, int line)
{
	++g_total_checks;

	if (!condition)
	{
		printf(FAIL_FORMAT "\n  FAILED: %s\n   └────File: %s; \tLine: %d\n" UNFORMAT,
			   message, file, line);
		++g_failed_checks;
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* Tests Prototypes*/
static int TestUIDCreate(void);
static int TestUIDInvalid(void);
static int TestUIDComparison(void);
static int TestUIDUniqueness(void);
static int TestUIDTimeComponent(void);

/******************************************************************************/

static int TestUIDCreate(void)
{
	int status = 0;
	ilrd_uid_t uid = { 0 };

	printf("Testing UID Create...\t");
	
	uid = CreateUID();
	status |= TEST_CHECK(0 != uid.time, "UID time component should not be zero");
	status |= TEST_CHECK(0 != uid.pid, "UID pid component should not be zero");
	status |= TEST_CHECK(0 < uid.counter, "UID counter component should be positive");
	status |= TEST_CHECK('\0' != uid.ip_addr, "UID ip_addr should not be empty");

	TEST_RESULT(status);
	return status;
}

static int TestUIDInvalid(void)
{
	int status = 0;
	ilrd_uid_t uid = { 0 };
	
	printf("Testing Invalid UID...\t");
	
	uid = CreateUID();
	status |= TEST_CHECK(1 == CompareUID(bad_id, bad_id), 
						"Invalid UID should match itself");
	status |= TEST_CHECK(0 == CompareUID(uid, bad_id), 
						"Valid UID should not match invalid UID");
	
	TEST_RESULT(status);
	return status;
}

static int TestUIDComparison(void)
{
	int status = 0;
	ilrd_uid_t uid1 = { 0 };
	ilrd_uid_t uid2 = { 0 };
	ilrd_uid_t uid_copy = { 0 };
	
	printf("Testing UID Comparison...");
	
	uid1 = CreateUID();
	uid2 = CreateUID();
	uid_copy = uid1;
	
	status |= TEST_CHECK(1 == CompareUID(uid1, uid1), 
						"UID should match itself");
	status |= TEST_CHECK(1 == CompareUID(uid1, uid_copy), 
						"UID should match its copy");
	status |= TEST_CHECK(0 == CompareUID(uid1, uid2), 
						"Different UIDs should not match");
	
	TEST_RESULT(status);
	return status;
}

static int TestUIDUniqueness(void)
{
	int status = 0;
	ilrd_uid_t uids[10] = { {0} };
	int i = 0;
	int j = 0;
	int is_unique = 1;

	printf("Testing UID Uniqueness...");

	/* Generate 10 UIDs */
	for (i = 0; i < 10; ++i)
	{
		uids[i] = CreateUID();
	}

	/* Check that all UIDs are unique */
	for (i = 0; i < 10; ++i)
	{
		for (j = i + 1; j < 10; ++j)
		{
			if (1 == CompareUID(uids[i], uids[j]))
			{
				is_unique = 0;
				break;
			}
		}
	}

	status |= TEST_CHECK(1 == is_unique,
						"All generated UIDs should be unique");

	TEST_RESULT(status);
	return status;
}

static int TestUIDTimeComponent(void)
{
	int status = 0;
	ilrd_uid_t uid1 = { 0 };
	ilrd_uid_t uid2 = { 0 };

	printf("Testing UID Time Component...");

	uid1 = CreateUID();
	sleep(1);  /* Sleep to ensure different time */
	uid2 = CreateUID();

	status |= TEST_CHECK(uid1.time != uid2.time,
						"UIDs created at different times should have different time components");
	status |= TEST_CHECK(uid1.time < uid2.time,
						"Later UID should have greater time value");

	TEST_RESULT(status);
	return status;
}

int main(void)
{	
	int status = 0;
	g_total_checks = 0; g_failed_checks = 0;

	status |= TestUIDCreate();
	status |= TestUIDInvalid();
	status |= TestUIDComparison();
	status |= TestUIDUniqueness();
	status |= TestUIDTimeComponent();

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

