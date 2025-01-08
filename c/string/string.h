/**********************************************************************
File: string.h
Functions mirror standard string.h functionality
Author:
Yana Glazer
***********************************************************************/
#ifndef __string_h__
#define __string_h__

#include <stdio.h>  /* for size_t */
/***********************functions declaration**************************/

size_t StrLen(const char *str);
int StrCmp(const char *str_1, const char *str_2);
char *StrCpy(char *dst, const char *src);
char *StrNCpy(char *dst, const char *src, size_t dsize);
int StrNCmp(const char* s1, const char* s2, size_t n);
int StrCaseCmp(const char *str_1, const char *str_2);
char *StrChr(const char *s, int c);
char *StrdUp(const char *s);
char *StrCat(char *dst, const char *src);
char *StrNCat(char *dst, const char *src, size_t ssize);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
int C_Dig(int num);
void Boom_p(int from, int to);
int IsPldrm(const char *str);

/************************************************************************/

#endif 


