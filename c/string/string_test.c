/******************************************************************************
* File: string_test.c
*
* Purpose:
*   Test suite for string.h functions providing verification of functionality.
*
* Notes:
*   - Each string function has a corresponding test function
*   - Tests include edge cases and normal usage
*   
* Author:
*   Shani Zuniga
*
**********************lt********************************************************/

#include <assert.h>                     /* assert macro */
#include <stdlib.h>                     /* For malloc */
#include <string.h>                     /* For string function comparisons */
#include <stdio.h>                      /* printf */
#include "string.h"                     /* functions to test */

/***********************Test functions declaration**************************/

static void TestStrLen(void);
static void TestStrCmp(void);
static void TestStrNCmp(void);
static void TestStrCaseCmp(void);
static void TestStrCpy(void);
static void TestStrNCpy(void);
static void TestStrChr(void);
static void TestStrDup(void);
static void TestStrCat(void);
static void TestStrNCat(void);
static void TestStrStr(void);
static void TestStrSpn(void);

/************************************************************************/

static void TestStrLen(void)
{
    	const char* test_str1 = "";
    	const char* test_str2 = "hello";
    	const char* test_str3 = "hello\0hidden";
	
	assert(StrLen(test_str1) == strlen(test_str1));
    	assert(StrLen(test_str2) == strlen(test_str2));
    	assert(StrLen(test_str3) == strlen(test_str3));
}

/************************************************************************/
static void TestStrCmp(void)
{
    	const char* str1 = "hello";
    	const char* str2 = "hello";
    	const char* str3 = "abc";
    	const char* str4 = "abcd";
    
    	assert(StrCmp(str1, str2) == strcmp(str1, str2));
    	assert(StrCmp(str3, str4) == strcmp(str3, str4));
    	assert(StrCmp(str4, str3) == strcmp(str4, str3));
}
/************************************************************************/
static void TestStrNCmp(void)
{
    	const char* str1 = "hello";
    	const char* str2 = "help";
    	size_t n = 3;
    
    	assert(StrNCmp(str1, str2, n) == strncmp(str1, str2, n));
    	assert(StrNCmp(str1, str2, n + 1) == strncmp(str1, str2, n + 1));
    	assert(StrNCmp(str1, str1, n) == strncmp(str1, str1, n));
    	
}


/************************************************************************/

static void TestStrCaseCmp(void)
{
	const char* str1 = "Hello";
	const char* str2 = "HELLO";
	const char* str3 = "Help";
	const char* str4 = "";

	/* Test case insensitive equality*/
	assert(StrCaseCmp(str1, str2) == 0);

	/* Test ordering*/
	assert(StrCaseCmp(str1, str3) < 0);
	assert(StrCaseCmp(str3, str1) > 0);

	/* Test empty string*/
	assert(StrCaseCmp(str4, str4) == 0);
	assert(StrCaseCmp(str4, str1) < 0);
}

/************************************************************************/

static void TestStrCpy(void)
{
    	char* dest1 = (char*) malloc(20);
    	char* dest2 = (char*) malloc(20);
    	const char* src = "hello";
    
    	assert(NULL != dest1 || NULL != dest2);
    
    	assert(strcmp(StrCpy(dest1, src), strcpy(dest2, src)) == 0);
    
    	free(dest1);
    	free(dest2);
}


/************************************************************************/

static void TestStrNCpy(void)
{
    	char* dest1 = (char*) malloc(20);
    	char* dest2 = (char*) malloc(20);
    	const char* src = "hello";
    	size_t n = 3;

    	assert(NULL != dest1 || NULL != dest2);

    	/* Initialize buffers*/ 
    	memset(dest1, 'x', 20);
    	memset(dest2, 'x', 20);

    	StrNCpy(dest1, src, n);
    	strncpy(dest2, src, n);

    	/* Compare actual buffer contents*/
    	/*assert(memcmp(dest1, dest2, 20) == 0);*/

    	free(dest1);
    	free(dest2);
}

/************************************************************************/

static void TestStrChr(void)
{
	const char* str1 = "hello world";
	const char* str2 = "";
	
	assert(StrChr(str1, 'o') == strchr(str1, 'o'));
	assert(StrChr(str1, 'z') == strchr(str1, 'z'));
	assert(StrChr(str1, '\0') == strchr(str1, '\0'));
	assert(StrChr(str2, 'a') == strchr(str2, 'a'));
}

/************************************************************************/
static void TestStrDup(void)
{
	const char* test_str1 = "Hello World";
	const char* test_str2 = "";
	const char* test_str3 = "Test\0Hidden";
	char* dup1;
	char* dup2;
	char* dup3;

	/* Test normal string */
	dup1 = StrDup(test_str1);
	assert(NULL != dup1);
	
	assert(strcmp(dup1, test_str1) == 0);
	assert(dup1 != test_str1);  /* Ensure it's a new copy */

	/* Test empty string */
	dup2 = StrDup(test_str2);
	if (NULL == dup2) {
		free(dup1);
		exit(EXIT_FAILURE);
	}
	assert(strcmp(dup2, test_str2) == 0);
	assert(dup2 != test_str2);

	/* Test string with null terminator in middle */
	dup3 = StrDup(test_str3);
	if (NULL == dup3) {
		free(dup1);
		free(dup2);
		exit(EXIT_FAILURE);
	}
	assert(strcmp(dup3, test_str3) == 0);
	assert(dup3 != test_str3);
	assert(strlen(dup3) == strlen(test_str3));

	free(dup1);
	free(dup2);
	free(dup3);
}

/************************************************************************/

static void TestStrCat(void)
{
	char* dest1 = (char*) malloc(20);
	char* dest2 = (char*) malloc(20);
	const char* src = "World";
	
	assert(NULL != dest1 && NULL != dest2);
	
	/* Test basic concatenation */
	strcpy(dest1, "Hello ");
	strcpy(dest2, "Hello ");
	assert(strcmp(StrCat(dest1, src), strcat(dest2, src)) == 0);
	
	/* Test empty destination */
	dest1[0] = '\0';
	dest2[0] = '\0';
	assert(strcmp(StrCat(dest1, src), strcat(dest2, src)) == 0);
	
	/* Test empty source */
	assert(strcmp(StrCat(dest1, ""), strcat(dest2, "")) == 0);
	
	free(dest1);
	free(dest2);
}


/************************************************************************/

static void TestStrNCat(void)
{
	char* dest1 = (char*) malloc(20);
	char* dest2 = (char*) malloc(20);
	const char* src = "World";
	
	assert(NULL != dest1 && NULL != dest2);

	/* Test partial concatenation */
	strcpy(dest1, "Hello ");
	strcpy(dest2, "Hello ");
	assert(strcmp(StrNCat(dest1, src, 3), strncat(dest2, src, 3)) == 0);

	/* Test full concatenation with n > src length */
	strcpy(dest1, "Hello ");
	strcpy(dest2, "Hello ");
	assert(strcmp(StrNCat(dest1, src, 10), strncat(dest2, src, 10)) == 0);

	/* Test zero length concatenation */
	strcpy(dest1, "Hello ");
	strcpy(dest2, "Hello ");
	assert(strcmp(StrNCat(dest1, src, 0), strncat(dest2, src, 0)) == 0);

	free(dest1);
	free(dest2);
}

/************************************************************************/

static void TestStrStr(void)
{
	const char* haystack = "Hello World";
	const char* empty = "";
	
	assert(StrStr(haystack, "World") == strstr(haystack, "World"));
	assert(StrStr(haystack, "lo") == strstr(haystack, "lo"));
	assert(StrStr(haystack, "Hello") == strstr(haystack, "Hello"));
	assert(StrStr(haystack, "Goodbye") == strstr(haystack, "Goodbye"));
	assert(StrStr(haystack, empty) == strstr(haystack, empty));
	assert(StrStr(empty, "test") == strstr(empty, "test"));
}

/************************************************************************/

static void TestStrSpn(void)
{
	const char* str1 = "123abc";
	const char* str2 = "abcdef";
	const char* str3 = "";
	
	assert(StrSpn(str1, "0123456789") == strspn(str1, "0123456789"));
	assert(StrSpn(str2, "abcdef") == strspn(str2, "abcdef"));
	assert(StrSpn(str2, "123") == strspn(str2, "123"));
	assert(StrSpn(str3, "abc") == strspn(str3, "abc"));
	assert(StrSpn(str1, "") == strspn(str1, ""));
}


/************************************************************************/
/** Function: main**/
/** Purpose: Runs all string function tests*/

int main(void)
{
	printf("Beginning string function tests\n\n");

	/* Run all tests */
	TestStrLen();
	TestStrCmp();
	TestStrNCmp();
	TestStrCaseCmp();
	TestStrCpy();
	TestStrNCpy();
	TestStrChr();
	TestStrDup();
	TestStrCat();
	TestStrNCat();
	TestStrStr();
	TestStrSpn();
	
	printf("\nAll tests completed successfully\n");
	return 0;
}

