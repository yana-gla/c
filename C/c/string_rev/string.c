/******************************************************************************
* File: string.c
*
* Purpose:
*   Implementation of string manipulation functions including length calculation,
*   comparison, copying, and character searching operations.
*
* Notes:
*   - Functions mirror standard string.h functionality
*   - Error checking performed via assertions
*   
* Author:
*   Yana Glazer
*
* Review History:
*   - Functions reviewed by Nitzan Miron (Jan 8, 2025)
*
******************************************************************************/

#include <stddef.h>                     /* For size_t type definition */
#include <assert.h>                     /* For assert macro */
#include <stdlib.h>                     /* For malloc */
#include <ctype.h>                      /* For tolower function */
#include <errno.h>
#include "string.h"                     /* Own header */

/******************************************************************************
* Function Implementations
******************************************************************************/

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * calculate the length of a string
 * returns length as size_t
 */
size_t StrLen(const char *str)
{
 	const char* runner = str;

	assert (NULL != str);

	while ('\0' != *runner)
	{
		++runner;
	}
	
	return runner - str;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * compares two strings
 * returns 0 if same, returns difference of differing char values as int (str1
 * char - str2 char) if non-same char is found
 */

int StrCmp(const char *str_1, const char *str_2)
{	
	assert (NULL != str_1);
	assert (NULL != str_2);
	
	while(('\0' != *str_1) && (*str_1 == *str_2))
	{
		++str_1;
		++str_2;
	}
	return (*str_1 - *str_2);
}

/* Reviewed By:  Nitzan Miron (Jan 8, 2025)
 * copy a string from src to dest
 * returns pointer to dest
 */

char *StrCpy(char *dst, const char *src)
{
	char *dst_strt = dst;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	while ('\0' != *src)
	{
		*dst++ = *src++; 
	}
	
	*dst = '\0';
	
	return dst_strt;
}

/* Reviewed By:  Nitzan Miron (Jan 8, 2025)
 * copies a string from src to dst where at most n bytes are copied;
 * if n is greater than src length, NUL char is appended such that n bytes
 * total are written
 * returns pointer to dest
 */
/*Corrected after code review Jan 10*/
char *StrNCpy(char *dst, const char *src, size_t dsize)
{	
	char *dst_strt = dst;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	while (dsize > 0 && '\0' != *src && '\0' != *dst)
	{
	    *dst++ = *src++;
	    --dsize;
	}
	
	while (dsize > 0 && '\0' != *dst)
	{
		*dst++ = '\0';
	}
	
	return dst_strt;	
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * compares two strings up to n bytes
 * returns 0 if same, returns difference of differing char values as int (str1
 * char - str2 char) if non-same char is found}}
 */
int StrNCmp(const char* s1, const char* s2, size_t n)
{
	assert (NULL != s1);
	assert (NULL != s2);
	
	while('\0' != *s1 && *s1 == *s2 && n > 0)
	{
		++s1, ++s2, --n;
	}
	return (0 == n) ? 0 : *s1-*s2;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * compares two strings, ignoring case;
 * returns 0 if same, returns difference of differing char values as int (str1
 * char - str2 char) if non-same char is found
 */
int StrCaseCmp(const char *str_1, const char *str_2)
{
	assert (NULL != str_1);
	assert (NULL != str_2);
	
	while('\0' != *str_1 && tolower(*str_1) == tolower(*str_2))
	{
		++str_1;
		++str_2;
	}
	
	return tolower(*str_1) - tolower(*str_2);
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * locates 1st occurence of (chr) int, in str; NUL char is considered part of
 * the string
 * returns pointer to ocurrence of char if found, else returns NULL
 */
char *StrChr(const char *s, int c)
{       
	assert (NULL != s);
	
	while ('\0' !=  *s && *s != c) 
	{
		++s;
	}
	
	return *(s) == c ? (char*)s : NULL;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * returns pointer to a new string which is a duplicate of the given string
 */
char *StrDup(const char *s)
{       
	char *d_s = (char*)malloc(StrLen(s)+1);
	
	assert (NULL != s);
	
	if (NULL == d_s) return NULL;
	
	StrCpy(d_s, s);

	return d_s;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * appends src string to dest string, overwriting terminating null char, the
 * user is responsible for having enough buffer; resulting string will have a
 * new null terminator
 * returns pointer to resulting dest
 */
char *StrCat(char *dst, const char *src)
{	
	int len_dst = StrLen(dst);
	
	assert (NULL != dst);
	assert (NULL != src);
	
	StrCpy(dst+len_dst, src);
	
	return dst;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * appends src string to dest string, overwriting terminating null char, the
 * user is responsible for having enough buffer; only up to n bytes are written
 * (result may exclude null char if src contains n or more bytes)
 * returns pointer to resulting dest
 */
char *StrNCat(char *dst, const char *src, size_t ssize)
{
	char *dst_strt = dst;
	
	dst += StrLen(dst);
	
	assert (NULL != dst);
	assert (NULL != src);
	
	while ('\0' != *src && ssize > 0 )
	{
	    *dst++ = *src++;
	    --ssize;
	}
	
	*dst = '\0';
	    
	return dst_strt;
}

/* Reviewed By: Nitzan Miron (Jan 8, 2025)
 * finds the first occurrence of substring, needle, in string, haystack; null
 * bytes are not compared
 * returns pointer to beginning of substring or NULL if not found
 */
char *StrStr(const char *haystack, const char *needle)
{	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	if ('\0' == *needle) return (char*)haystack;
	
	while ('\0' != *haystack && StrNCmp(haystack, needle, StrLen(needle)) != 0 )
	{
		++haystack;
	}
	
	return *haystack == '\0' ? NULL : (char*)haystack;
}

/* Reviewed By: 
 * calculates length in bytes of initial segment of string, s, which consists
 * entirely of bytes in string, accept
 */
size_t StrSpn(const char *s, const char *accept)
{
	size_t spn = 0;
	
	assert (NULL != s);
	assert (NULL != accept);
	
	while (NULL != StrChr(accept,*s) && '\0' != *s)
	{
	    ++spn;
	    ++s;
	}
	return spn;
}


