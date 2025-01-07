#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


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

int StrCmp(const char *str_1, const char *str_2)
{	
	assert (NULL != str_1);
	assert (NULL != str_2);
	
	while('\0' != *str_1 && *str_1 == *str_2)
	{
		++str_1;
		++str_2;
	}
	return *str_1 - *str_2;
}

char *strcpy(char *restrict dst, const char *restrict src)
{
	size_t i = 0;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	while ('\0' != *(src + i) )
	{
		*(dst + i) = *(src + i); // too many actions because use of i
		++i;
	}
	
	*(dst+i) = '\0';
	
	return dst;
}

//ToTest
char *strncpy(char *dst, const char *restrict src, size_t dsize)
{	
	size_t i = 0;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	for (; i < dsize ; ++i)
	{
		*(dst + i) = *(src + i);
	}
	
	while ('\0' != *(dst + i))
	{
		*(dst + i) = '\0';
		++i;
	}
	
	return dst;	
}

//test i < n
int strncmp(const char* s1, const char* s2, size_t n)
{
	size_t i = 0;
	
	assert (NULL != s1);
	assert (NULL != s2);
	
	while('\0' != *s1 && *s1 == *s2 && i < n)
	{
		++s1;
		++s2;
		++i;
	}
	return *(s1-1) - *(s2-1);
}


int IsPldrm(const char *str)
{	
	int left = 0;
	int right = StrLen(str) - 1;
	
	while (left < right)
	{
		if (str[left] != str[right])
		{
			return 0;
		}
		
		left++;
		right--;
	}
	return 1;
}

int strcasecmp(const char *str_1, const char *str_2)
{
	assert (NULL != str_1);
	assert (NULL != str_2);
	
	while('\0' != tolower(*str_1) && tolower(*str_1) == tolower(*str_2))
	{
		++str_1;
		++str_2;
	}
	
	return tolower(*str_1) - tolower(*str_2);
}

char *strchr(const char *s, int c)
{
	assert (NULL != s);
	
	while ('\0' !=  *s && *s != c) 
	{
		++s;
	}
	
	return *(s) == c ? s : NULL;
}

char *strdup(const char *s)
{
	assert (NULL != s);
	char *d_s = (char*)malloc(sizeof(s)+1);
	assert (NULL != d_s);
	
	strcpy(d_s, s);

	return d_s;
}

char *strcat(char *restrict dst, const char *restrict src)
{	
	assert (NULL != dst);
	assert (NULL != src);
	
	int len_dst = StrLen(dst);
	
	strcpy(dst+len_dst, src);
	
	return dst;
}

char *strncat(char *restrict dst, const char *src, size_t ssize)
{
	assert (NULL != dst);
	assert (NULL != src);
	
	int len_dst = StrLen(dst);
	
	strncpy(dst+len_dst, src, ssize);
	
	return dst;
}

char *strstr(const char *haystack, const char *needle)
{	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	if ('\0' == *needle) return haystack;
	
	while ('\0' != *haystack && strncmp(haystack, needle, StrLen(needle)) != 0 )
	{
		++haystack;
	}
	
	return *haystack == '\0' ? NULL : haystack;
}

size_t strspn(const char *s, const char *accept)
{
	size_t i = 0;
	
	assert (NULL != s);
	assert (NULL != accept);
	
	while ((*s+1) != '\0' && 0 == strncmp(s+i, accept+i, 1))  
	{
		++i;
	}
	
	return i;
}

int c_dig(int num)
{	
	while (abs(num) > 0)
	{
	  if (num % 10 == 7) return 0;
	
	  num/=10;
	}
	
	return 1;
}

//reverse rang and negative
void BOOM_p(int from, int to)
{

	while (from <= to)
	{
		if (from % 7 == 0) printf ("BOOM ");
		else if (c_dig(from) == 0) printf ("BOOM ");
		else printf("%d ", from);
		
		++from;
	}
	printf("\n");
}


void *ToOneSpace(*char str)
{
	char *dst = str;
	
	while (' ' == *str && ' ' == *(str+1))
	{
		++str;
	}
	
	strcpy(dst+1, str+1);
}
		
char *white_s(*str)
{
	assert(NULL != str);
	
	size_t right = strlen(str)-1;
	char* runner = str;
	
	//eating initial spaces
	while (' ' == *str)
	{
		++str;
	}
	
	runner = str;
	
	//changing middle spaces to one space
	while ('\0'== *runner)
	{
		ToOneSpace(runner);
		++runner;
	}
		
	//eating final spaces
	if (' ' == *(runner)) *runner = '\0';

}
	
	
	
	


int main (void)
{
	char str1[7] = "abcde", str2[]= "cd", str3[5] = "poi";
	/*char *str3 = (char*)malloc(sizeof(str1+str2)+1);*/
	
	//printf("len of yana is %ld", StrLen(str1));
	//printf("compare is %d\n", StrCmp(str1, str2));
	//printf("%s\n", str3);
	//printf("%s\n", strcat(str1, str2));
	//printf("%s\n", strncat(str3, str2, 1));
	//printf("%s\n", strstr(str1, str2));
	
	//printf("%ld\n", strspn(str1, str2));
	
	int from = 0, to = 20;
	BOOM_p(from, to);
	
	//strdup
	//free	

	
	//free(d_s);
	
	
	return 0;
	
}




