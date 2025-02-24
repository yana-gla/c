#include <stdio.h>


void Find2MissingNumber(int arr[], int arr_size)
{
	int n = arr_size + 2;
	int sum = 0, sum_arr = 0, sum_missing = 0;
	int sq_sum = 0, sq_sum_arr = 0, sq_sum_missing = 0;
	int i = 0;
	
	
	/*sum of arithmetic sequence sum = n(n+1)/2)*/
	/*	sum_num = n*(1 + n)/2;*/
	/*n(n+1)(2n+1)/6*/
	for (i = 1; i <= n ; ++i)
	{
		sum += i;
		sq_sum += i*i;
	}
	
	for (i = 0 ; i < arr_size ; ++i)
	{
		sum_arr += arr[i];
		sq_sum_arr += arr[i] * arr[i];
	}
	
	sum_missing = sum - sum_arr;
	sq_sum_missing = sq_sum - sq_sum_arr;
	
	for (i=1 ; (sum_missing - i)*(sum_missing - i) + i*i != sq_sum_missing; ++i);
	
	printf("Missing numbers are: %d and %d.\n", i, sum_missing-i);
}

void Find2MissingNumberXor(int arr[], int arr_size)
{
	int xor_all = 0;
	int p = 0, q = 0;
	int i = 0, n = arr_size + 2;
	
	for (i = 1; i <= n ; ++i)
	{
		xor_all ^= i;
	}
	
	for (i = 0 ; i < arr_size ; ++i)
	{
		xor_all ^= arr[i];
	}
	
	/*right most set bit*/
	xor_all = xor_all & (~(xor_all-1)); 
	
	for (i = 0; i < arr_size ; ++i)
	{
		if ((arr[i] & xor_all) == xor_all)
		{
			p ^= arr[i];
		}
		else
		{
			q ^= arr[i];
		}
	}
	
	for (i = 1; i <= n ; ++i)
	{
		if ((i & xor_all) == xor_all)
		{
			p ^= i;
		}
		else
		{
			q ^= i;
		}
	}
	
	printf("Missing numbers are: %d and %d.\n", p, q);
	
}


int main(void)
{
	int arr[] = {2, 3, 5};
	
	Find2MissingNumber(arr, 3);
	Find2MissingNumberXor(arr, 3);
	
	return 0;
}
