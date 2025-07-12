#include "binary_search.h"

int BinIterSearch(int arr[], int size, int target)
{
	int l = 0, r = size -1, m = 0; /*left, right, middle*/
	
	while (l <= r)
	{
		m = (l + r) / 2;
		
		if (arr[m] == target)
		{
			return m;
		}
		if (target > arr[m])
		{
			l = m + 1;
		}
		else 
		{
			r = m -1;
		}
	}
	return -1;
}


static int HelperBinRecSearch(int arr[], int target, int l, int r)
{
	int m = (l + r) /2;
	
	if (l > r)
	{
		return -1;
	}
	
	if (arr[m] == target)
	{
		return m;
	}
	if (target > arr[m])
	{
		return HelperBinRecSearch(arr, target, m + 1, r);
	}
	
	return HelperBinRecSearch(arr, target, l, m-1);
}

int BinRecSearch(int arr[], int size, int target)
{
	int l = 0, r = size -1;
	
	return HelperBinRecSearch(arr, target, l, r);
}
