#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc*/
#include <string.h>
#include <ctype.h> /*is_digit*/
#include <assert.h>
#include <limits.h> /*UCHAR*/
#include <stddef.h> /*NULL*/

#define IS_LITTLE_ENDIAN() (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

static void SwapChar(char *x, char *y);
static void Reverse(char* str);

/*itoa*/
char* IntToStringBase10(int num, char* buffer)
{
	int is_negative = 0;
	char *buffer_start = buffer;
	
	/*Handle 0*/
	if (num == 0)
	{
	 	*buffer++ = '0';
	 	*buffer = '\0';
	 	return buffer_start;
	}
	
	/*if num is negative*/
	if (num < 0 ) 
	{
		is_negative = 1;
		num = -num;
	}
	
	/*Building the string, will be reversed 200->002*/	
	/*if num != 0*/
	while (num > 0)
	{
		*buffer++ = num % 10 + '0';
		num /= 10;
	}
	
	if (is_negative == 1)
	{
		*buffer++ = '-';
	}
	
	*buffer = '\0';
	
	Reverse(buffer_start);
	
	return buffer_start;
}

/*atoi*/
int StringToIntBase10(const char *str)
{
	int sign = 1;
	int ones_digit = 0;
	int result = 0;
	
	while (0 != isspace(*str)) /*isspace returns non-zero, not necessarily 1 */
	{
		++str;
	}
	
	if ('-' == *str) 
	{
		sign = -1;
		++str;
	}
	
	if (isdigit(*str) == 0)
	{
	  return 0;
	}
	
	while (isdigit(*str) != 0 && '\0' != *str )
	{
		ones_digit = *str - '0';
		result = result * 10 + ones_digit;
		++str;
	}
  
	return (sign*result);
}


/*itoa*/
/*int in decimal*/
char* IntToStringAnyBase(int num, char* buffer, int base) 
{
	int is_negative = 0;
	int rem = 0; /*reminder*/
	char *buffer_start = buffer;
	
	/*Handle 0*/
	if (0 == num)
	{
	 	*buffer++ = '0';
	 	*buffer = '\0';
	 	return buffer_start;
	}
	
	/*if num is negative*/
	if (num < 0 ) 
	{
		is_negative = 1;
		num = -num;
	}
	
	/*building the string, will be reversed 200->002*/
	/*if num != 0*/
	while (num > 0)
	{
		rem = num % base;
		*buffer++ = (rem <= 9) ? rem + '0' : (rem - 10) + 'A';
		num /= base;
	}
	
	if (is_negative == 1)
	{
		*buffer++ = '-';
	}
	
	*buffer = '\0';
	
	Reverse(buffer_start);
	
	return buffer_start;
}        

static int DecVal(char c, int base)
{
    int result = -1;
    c = toupper(c);
    
    if (c >= '0' && c <= '9')
    {
        result = c - '0';
    }
    else if (c >= 'A' && c <= 'Z')
    {
      result = c - 'A' + 10;
    }

    if (result >= base)
    {
        result = -1;
    }
    
    return result;
}


/*atoi*/
/*string in base*/
int StringToIntAnyBase(const char *str, int base)
{
	int sign = 1;
	int ones_digit = 0;
	int result = 0;
	
	while (0 != isspace(*str)) /*isspace returns non-zero, not necessarily 1*/
	{
		++str;
	}
	if ('-' == *str) 
	{
		sign = -1;
		++str;
	}
		
	/*Build int*/	
	while ('\0' != *str)
	{
	    
	    ones_digit = (isdigit(*str) != 0) ? *str - '0' : toupper(*str) - 'A' + 10;
	    ones_digit = DecVal(*str, base);
	    if (ones_digit == -1) 
	    {
	        break;
	    }
	    result = result * base + ones_digit;
	    ++str;
	}
	
	return result*sign ;
}

void PrintLetters(const char *str1, const char *str2, const char *str3)
{
	int i = 0;
 	char *arr = (char*)calloc(UCHAR_MAX, sizeof(char));
 	
 	if (NULL == arr) 
 	{
 		printf("Memory allocation failed in line %d!\n", __LINE__);
 	}

 	/* Mark all chars that appear in str1 with 1*/
 	while ('\0' != *str1)
 	{
 		arr[(unsigned char)*str1] = 1;
 		++str1;
 	}
 	
 	/*If element was in str1, mark him with 2*/
 	while ('\0' != *str2)
 	{
 		if (1 == arr[(unsigned char)*str2]) /*seen before*/
 		{
 			arr[(unsigned char)*str2] = 2;
 		}
 		++str2;
 	}
 	
 	/*Mark elements with array 3 with 0*/
 	while ('\0' != *str3)
 	{
 		arr[(unsigned char)*str3] = 0;
 		++str3;
 	}
 	
 	/*print*/
 	for (i = 0; i < UCHAR_MAX ; ++i)
 	{
 		if (2 == arr[i])
 		{
 			printf("%c ", i);
 		}
 	}
 	printf("\n");
 	
 	free(arr);
 	arr = NULL;
}

void CheckLittleEndian()
{
  unsigned int x = 1;
  
  *(char*)&x == 1 ? printf("System is Little endian\n") : printf("System is Big endian\n");
}
  

/************ Static function *******/

static void SwapChar(char *x, char *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

static void Reverse(char* str)
{
	int len = strlen(str);
	char *l = str , *r = str + len - 1;
	
	while (l < r)
	{
		SwapChar(l++, r--);
	}
}

/***********************************/
