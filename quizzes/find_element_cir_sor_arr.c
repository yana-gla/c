#include <stddef.h>
#include <stdio.h>


int FindElementCirSortedArray(int arr[], int size, int target)
{
	size_t l = 0, r = size-1, m = 0; /* l- left, r- right, m- middle*/
	
	while (l <= r)
	{
		m = (l+r)/2;
		
		if (target == arr[m])
		{
			return m;
		}
		
		/*if left is soreted*/
		if (arr[l] <= arr[m])
		{
			if (target < arr[m] && target >= arr[l])
			
			{
				r = m - 1;
			}
			else /*(target >= arr[l] && target < arr[m] )*/
			{
				l = m + 1;
			}
		}
		else /*if right is soreted*/
		{
			if (target > arr[m] && target <= arr[r])
			{
				l = m + 1;
			}
			else
			{
				r = m - 1;
			}
		}
	}
	
	return -1;
}


int main(void)
{
	int i = 0;
	int arr[10] = {9, 15, 20, 30, 31, 50, 100, 2, 5, 8};
	int size = sizeof(arr)/ sizeof(int);

	for (i = 0; i < size; ++i)
	{
		printf ("index of %d is %d\n", arr[i] ,FindElementCirSortedArray(arr, size, arr[i]));
	}
	
	return 0;
}







