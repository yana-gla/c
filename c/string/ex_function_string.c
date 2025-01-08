#include <stddef.h>                     /* For size_t type definition */
#include <assert.h>                     /* For assert macro */
#include <stdlib.h>                     /* For malloc */
#include <ctype.h>                      /* For tolower function */
#include <errno.h>
#include "string.h"  

int C_Dig(int num)
{	
	while (abs(num) > 0)
	{
	  if (num % 10 == 7) return 0;
	
	  num/=10;
	}
	
	return 1;
}

//reverse range and negative
void Boom_p(int from, int to)
{

	while (from <= to)
	{
		if (from % 7 == 0) printf ("BOOM ");
		else if (C_Dig(from) == 0) printf ("BOOM ");
		else printf("%d ", from);
		
		++from;
	}
	printf("\n");
}


char *del_white(char *str)
{
    char *str_cpy = (char*)malloc(StrLen(str) + 1);
    char *str_cpy_strt = str_cpy;

    
    while(' ' == *str && '\0' != *str)
    {
        ++str;
    }
    
    str_cpy_strt = 
    
    *str_cpy = *str;
    ++str_cpy;
    
    while ('\0' != *(str+1) )
    {
        if (*str == ' ' && *(str+1) == ' ')
        {
            ++str;
        }
        
        else 
        {
            *str_cpy = *str;
            ++str_cpy;
            ++str;
        }
    }
    
    if (*str == ' ')
    {
        *str_cpy = '\0';
    }
    
        
    return cpy_start;
      
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
