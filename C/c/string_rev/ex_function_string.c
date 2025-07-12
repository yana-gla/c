#include <ctype.h>  
#include <stdio.h>   
#include <stdlib.h>                     /* For malloc *//* For tolower function */
#include <stddef.h>                     /* For size_t type definition */
#include <assert.h>                     /* For assert macro */
#include <errno.h>
#include <string.h>

int C_Dig(int num)
{	
	while (abs(num) > 0)
	{
	  if (num % 10 == 7) return 0;
	
	  num/=10;
	}
	
	return 1;
}

/*reverse range and negative*/
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

int IsPldrm(const char *str)
{	
	int left = 0;
	int right = strlen(str) - 1;
	
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


char *StrCpy(char *dst, char *src)
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

char *Nxt_Chr (char *str)
{
    /*char *start = str;*/
    while (*str == ' ' )/* (isalpha(*str) == 0 )*/
    {
        ++str;
    }
    
    return *str == '\0' ? str-1 : str;

}
    
    
    
char *DelSpace (char *str)
{
    char *cpy = str;
    char *rnr = str;
    int fps = 0; /*flag for con space*/
    
    assert(NULL != str);

    /*eatint initial spaces*/
    while (*str == ' ') /*(0 != isspace(*str))*/
    {
        ++str;
    }
    
    /*str begining of return string*/
    cpy = rnr = str;
    
    while ('\0' != *rnr)
    {
        if (*rnr != ' ')
        { 
            ++rnr, ++cpy;
            fps = 0;
        }
        else if (*rnr == ' ' && fps == 0)
        {   
            ++rnr, ++cpy;
            fps = 1;
        }
        
        else if (*rnr == ' ' && fps == 1)
        {
            cpy = Nxt_Chr(cpy);
            rnr = StrCpy(rnr, cpy);
            ++rnr; 
            cpy = rnr;
            fps = 0;
        }
    }

    /*eating final space*/
   while (*(rnr-1) == ' ' )
    {
        *(rnr-1) = '\0';
        --rnr;
    }
    
    return str;
}

int main (void)
{
    char str[] = "  ya      na   Gla    zer   ";
    /*printf("%s", str);*/
    
    printf("del space is |%s|\n", DelSpace(str));
  
    return 0;
}
