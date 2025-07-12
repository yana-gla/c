#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


int main (void)
{
	int n = 5;
	int *arr_mlc = (int*)malloc(sizeof(int)*n);
	/*
	for (int i=0; i < n; ++i)
	{
		arr_mlc[i] = 5;
	}
	*/
	
	if (NULL == arr_mlc) 
	{
		printf ("error\n");
		return 0;
	}
	
	/*printf ("pointer of arr_mlc before free is %p\n", arr_mlc);*/
	
	if (*arr_mlc == 0) printf ("Yana\n");
	
	free(arr_mlc);
	
	/* *arr_mlc = 8;*/
	
	/*
	int *pn = &n;
	free(pn);
	*pn = 10;
	*/
	
	/*	
	if (*arr_mlc != 0) 
	{
		"This prints Q5";
	}
	*/
	
	int arr[10] = {0};
	/*printf ("11'th member in the array is %d", arr_10[10]);*/
	
	/*arr[10] = 9;*/
	
	return 0;	

}
