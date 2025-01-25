#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StructArrayTypes.h"

#define ARR_LEN 3

static void PrntArr(element_t *ptr_strct);
static state_t AddArr(element_t *ptr_strct, int num);
static void CleanArr(element_t *ptr_strct);

int main(void)
{
	int x = 3;
	float f = 2.7;
	char str[] = "Amber The Sweetest Cavalier"; /*Amber is my dog*/
	
	int int_to_add = 0;
	
	element_t strct_arr[ARR_LEN] = {0}; /*initilizing strtct array*/
	
	if (SUCCESS != InitInt(&strct_arr[0], x))
	{
	    return (FAIL);
	}
	
	if (SUCCESS != InitFlt(&strct_arr[1], f))
	{
	    return (FAIL);
	}
	
	if (SUCCESS != InitStr(&strct_arr[2], str))
	{
	    return (FAIL);
	}
    
	PrntArr(strct_arr);
	
	printf("\n");
	printf("Enter integer number to add\n");
	scanf("%d", &int_to_add);
	printf("\n");
	
	if (SUCCESS != AddArr(strct_arr, int_to_add))
	{
	    return (FAIL);
	}
	
	PrntArr(strct_arr);
	
	CleanArr(strct_arr);
	
	return (SUCCESS);
}
	
static void PrntArr(element_t *ptr_strct)
{
	
	int i = 0;
	for (; i < ARR_LEN ; ++i)
	{
		ptr_strct[i].p_prnt(&ptr_strct[i]);
	}
}

static state_t AddArr(element_t *ptr_strct, int num)
{
	int i = 0;

	for ( i= 0 ; i < ARR_LEN ; ++i)
	{
		if (SUCCESS != ptr_strct[i].p_add(&ptr_strct[i] ,num))
		{
		    return (FAIL);
		}
	}	
	
	return (SUCCESS);
}

static void CleanArr(element_t *ptr_strct)
{
	int i = 0;
	
	for ( ; i <  ARR_LEN ; ++i)
	{
		ptr_strct[i].p_cln(&ptr_strct[i]);
	}
}



