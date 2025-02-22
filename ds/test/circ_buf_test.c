/******************************************************************************
* File: circ_buf_test.c
*
* Purpose:
*   Test suite for circ_buf.h
*
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include <stddef.h>						/* size_t */
#include <aio.h>						/* ssize_t */
#include <string.h>						/* strncmp */
#include "circ_buf.h"					/* own header */

#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

static int TestBufCreateDestroy(void)
{
	int status = 0;
	circ_buf_t* buf = NULL;
	size_t capacity = 100;

	printf("Testing Buf Create/Destroy...");
	buf = BufCreate(capacity);
	if (NULL == buf)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Buf creation returned NULL\n"UNFORMAT);
		return 1;
	}

	if (1 != BufIsEmpty(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected empty buffer, but got non-empty\n" UNFORMAT);
		status = 1;
	}

	if (capacity != BufFreeSpace(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected free space in buffer to match capacity\n" UNFORMAT);
		status = 1;
	}

	if (0 != BufSize(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected size to be 0, but got %lu\n" UNFORMAT,
				(unsigned long)BufSize(buf));
		status = 1;
	}

	BufDestroy(buf);
	if (0 == status)
	{
		printf(PASS_FORMAT "\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestBufWrite(void)
{
	int status = 0;
	circ_buf_t* buf = NULL;
	size_t capacity = 10;
	char* data = "Hello, World!";
	ssize_t n_bytes_expected = 5;
	ssize_t n_bytes_to_write = 5;
	ssize_t n_bytes_written = 0;

	printf("Testing Buf Write...");
	buf = BufCreate(capacity);
	if (NULL == buf)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Buf creation returned NULL\n"UNFORMAT);
		return 1;
	}

	n_bytes_written = BufWrite(buf, data, n_bytes_to_write);
	if (n_bytes_written != n_bytes_expected)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected %lu bytes written, but got %lu\n" UNFORMAT,
				(unsigned long)n_bytes_expected, (unsigned long)n_bytes_written);
		status = 1;
	}

	if (n_bytes_written != (ssize_t)BufSize(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Buffer size doesn't match bytes written\n" UNFORMAT);
		status = 1;
	}

	n_bytes_to_write = 7;
	n_bytes_expected = 5;  /* Only 5 bytes of free space left */
	n_bytes_written = BufWrite(buf, data, n_bytes_to_write);
	if (n_bytes_written != n_bytes_expected)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected %lu bytes written, but got %lu\n" UNFORMAT,
				(unsigned long)n_bytes_expected, (unsigned long)n_bytes_written);
		status = 1;
	}

	if (0 != BufFreeSpace(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected buffer to be full, but %lu bytes available\n" UNFORMAT,
				(unsigned long)BufFreeSpace(buf));
		status = 1;
	}

	BufDestroy(buf);
	if (0 == status)
	{
		printf(PASS_FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

static int TestBufRead(void)
{
	int status = 0;
	circ_buf_t* buf = NULL;
	size_t capacity = 10;
	char* write_data = "Hello, World!";
	char read_data[11] = {0};  
	ssize_t n_bytes_to_write = 5;
	ssize_t n_bytes_to_read = 0;
	ssize_t n_bytes_read = 0;

	printf("Testing Buf Read...");
	buf = BufCreate(capacity);
	if (NULL == buf)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Buf creation returned NULL\n"UNFORMAT);
		return 1;
	}

/*	 Test reading from empty buffer */
	n_bytes_read = BufRead(buf, read_data, 1);

	if (0 != n_bytes_read)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected 0 bytes read from empty buffer, but got %lu\n" UNFORMAT,
				(unsigned long)n_bytes_read);
				fflush(stdout);

		status = 1;
	}

	 /*Write some data and verify read */
	if (n_bytes_to_write != BufWrite(buf, write_data, n_bytes_to_write))
	{

		printf(FAIL_FORMAT "\n\tFAILED: Could not write test data to buffer\n" UNFORMAT);
		fflush(stdout);
		status = 1;
	}

	n_bytes_to_read = 3;
	n_bytes_read = BufRead(buf, read_data, n_bytes_to_read);
	if (n_bytes_read != n_bytes_to_read)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected %lu bytes read, but got %lu\n" UNFORMAT,
				(unsigned long)n_bytes_to_read, (unsigned long)n_bytes_read);
				fflush(stdout);
		status = 1;
	}

	if (0 != strncmp(write_data, read_data, n_bytes_read))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Read data doesn't match written data\n" UNFORMAT);
		fflush(stdout);
		status = 1;
	}

	if (2 != BufSize(buf))
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected 2 bytes remaining, but got %lu\n" UNFORMAT,
				(unsigned long)BufSize(buf));
				fflush(stdout);
		status = 1;
	}

	n_bytes_to_read = 5;
	n_bytes_read = BufRead(buf, read_data, n_bytes_to_read);
	if (2 != n_bytes_read)
	{
		printf(FAIL_FORMAT "\n\tFAILED: Expected 2 bytes read, but got %lu\n" UNFORMAT,
				(unsigned long)n_bytes_read);
				fflush(stdout);
		status = 1;
	}

	BufDestroy(buf);
	if (0 == status)
	{
		printf(PASS_FORMAT "\t\tPASSED\n" UNFORMAT);
	}
	return status;
}

int main(void)
{	
	int status = 0;

	status |= TestBufCreateDestroy();
	status |= TestBufWrite();
	status |= TestBufRead();	

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

