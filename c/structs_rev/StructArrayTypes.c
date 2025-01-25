#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> /*SCHAR_MAX 127*/
#include "StructArrayTypes.h"

/*
void intToStr(int num, char *str) {/*sprintf
    int i = 0;
    int j = 0;
    char temp = '\0';
    
    /*if num is negative
    int sign = num;

    if (num < 0)
        num = -num;

    while (num > 0) {
      
        str[i++] = num % 10 + '0';
      	num /= 10;
    } 

    if (sign < 0) {
        str[i++] = '-';
    }

    str[i] = '\0';

    /* Reverse- j left, i right
   i -= 1;
    while (j < i)
    {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        ++j, --i;
    }
}
*/


/* Print Function */
void PrntInt(element_t *ptr_strct)
{
	printf("%d\n", *(int*)&ptr_strct->ptr_data);	
}

void PrntFlt(element_t *ptr_strct)
{
	printf("%.3f\n", *(float*)&(ptr_strct->ptr_data));
}

void PrntStr(element_t *ptr_strct)
{
	printf("%s\n", (char*)(ptr_strct->ptr_data));
}


/* Add Function */
state_t AddInt(element_t *ptr_strct, int num)
{
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}
	
	*(int*)&(ptr_strct -> ptr_data) += num;
	
	return (SUCCESS);
}

state_t AddFlt(element_t *ptr_strct, int num)
{
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}
	*(float*)&(ptr_strct -> ptr_data) += num;
	
	return (SUCCESS);
}

state_t AddStr(element_t *ptr_strct, int num)
{
	char str_num[10] = "";
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}
      
	sprintf(str_num, "%d", num);
	/*intToStr(num, str_num); /*str_num will return num as string*/
	strcat((char*)(ptr_strct -> ptr_data), str_num);
	
	return (SUCCESS);
}


/* Clean Function */
void ClnStr(element_t *ptr_strct)
{
	free(ptr_strct -> ptr_data);
}
	
void EmptyFnct(element_t *ptr_strct)
{
	(void)ptr_strct;
}


/* Init Function */
state_t InitInt(element_t *ptr_strct, int x)
{
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}
	*(int*)&ptr_strct -> ptr_data = x;
	ptr_strct -> p_prnt = PrntInt;
	ptr_strct -> p_add = AddInt;
	ptr_strct -> p_cln = EmptyFnct;
	
        return (SUCCESS);
}

state_t InitFlt(element_t *ptr_strct, float flt)
{
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}
	*(float*)&ptr_strct -> ptr_data = flt;
	ptr_strct -> p_prnt = PrntFlt;
	ptr_strct -> p_add = AddFlt;
	ptr_strct -> p_cln = EmptyFnct;
	
	return (SUCCESS);
}

state_t InitStr(element_t *ptr_strct, char *str)
{
	
	ptr_strct -> ptr_data = (char*)calloc(SCHAR_MAX, sizeof(char)); /*The string that will hold the str & the add */
	if (NULL == ptr_strct -> ptr_data)
	{
	    printf ("Memory allocation failed.\n");
	    return (FAIL);
	}
	if (NULL == ptr_strct)
	{
	    return (FAIL);
	}

	strcpy((char*)(ptr_strct -> ptr_data), str);
	
	ptr_strct -> p_prnt = PrntStr;
	ptr_strct -> p_add = AddStr;
	ptr_strct -> p_cln = ClnStr;
	
	return (SUCCESS);
}




	


