#include "sort.h"

/******************************************************************************/
static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/******************************************************************************/
/*returns flag if there was a swap or not*/
static int Bubble(int arr[], size_t size)
{
	size_t i = 0;
	int swapped = 0;
	
	for (i = 0; i < size - 1; ++i)
	{
		if (arr[i] > arr[i+1])
		{
			Swap(&arr[i], &arr[i+1]);
			swapped = 1;
		}
	}
	
	return swapped;
}

void BubbleSort(int arr[], size_t size)
{
	int not_sorted = 1;
	
	while (not_sorted && size > 1)
	{
		not_sorted = Bubble(arr, size--);
	}
}
/******************************************************************************/
static void SwapSmallest(int arr[], size_t size)
{
	/*set in the beginig i_min to i=0*/
	size_t i_min = 0, i = 1;
	
	/*search minimun element*/
	for (i = 1; i < size ; ++i)
	{
		if (arr[i] < arr[i_min])
		{
			i_min = i;
		}
	}
	
	/*place smallest element at the begining*/
	Swap(arr, arr+i_min);
}

void SelectionSort(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size - 1; ++i)
	{
		SwapSmallest(arr + i, size - i);
	}
}
/******************************************************************************/
void InsertionSort(int arr[], size_t size)
{
	size_t i = 0, j = 0;
	int key = 0;
	
	for (i = 1; i < size ; ++i)
	{
		key = arr[i];
		 /*start comparing from adjacent element to key, key is 3- 2,1,0*/
		/*move elemnts greater than key one position right*/
		for (j = i ; j > 0 && key < arr[j - 1]; --j)
		{
			arr[j] = arr[j-1];
		}
		
		arr[j] = key;
	}
}
/******************************************************************************/
