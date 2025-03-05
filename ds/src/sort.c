#include <stdlib.h> /*calloc*/
#include <string.h> /*memset*/
#include "sort.h"

/******************************************************************************/
static void Swap(int *a, int *b);
static int FindMax(int arr[], size_t size);
static void CountingSortDigits(int arr[], size_t size, int digits_num);
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
	/*set in the begining i_min to i=0*/
	size_t i_min = 0, i = 1;
	
	/*search minimum element*/
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
/*only for non-negative ints*/
/*over write input array*/
void CountingSort(int arr[], size_t size)
{
	size_t max = 0;
	size_t i = 0, out_idx = 0;
	
	int *count_array = NULL;
	int *output_array = NULL;
	
	/*find input range*/
	max = FindMax(arr, size);
	
	/*create countArray range size, initialized to 0*/
	count_array = (int*)calloc(max + 1, sizeof(int));
	if (NULL == count_array)
	{
		return;
	}
	
	/*count how many times each elemnt appears in array*/
	for (i = 0; i < size; ++i)
	{
		++count_array[arr[i]];
	}
	
	/*cumulative sum*/
	for (i = 1; i < max + 1; ++i)
	{
		count_array[i] += count_array[i-1];
	}
	
	output_array = (int*)malloc(size * sizeof(int));
	if (NULL == output_array)
	{
		return;
	}
	
	/*create output array*/
	for (i = size; i > 0 ; --i)
	{
		out_idx = --count_array[arr[i]];
		output_array[out_idx] = arr[i];
	}

	
	memcpy(arr, output_array, size * sizeof(int));
	free(count_array);
	free(output_array);
}
/******************************************************************************/
void RadixSort(int arr[], size_t size)
{
	size_t max = FindMax(arr, size);
	int digits_num = 1;
	
	/*counting sort to every digit*/
	for (digits_num = 1; max/digits_num > 0 ; digits_num *= 10)
	{
		CountingSortDigits(arr, size, digits_num);
	}
}


/******************************************************************************/
static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/******************************************************************************/
static int FindMax(int arr[], size_t size)
{
	int max = arr[0];
	size_t i = 0;
	
	for (i = 1; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	return max;
}
/******************************************************************************/

static void CountingSortDigits(int arr[], size_t size, int digits_num)
{
	size_t i = 0;
	size_t numItemsBefore = 0, count = 0;
	int num = 0;
	
	int count_array[10] = {0}; /*sorting one digit every time*/
	int *output_array = NULL;
	
	/*Store count of occurrences*/
	/*counting sort on the array based on the unit place digits*/
	for (i = 0; i < size; ++i)
	{
		++count_array[(arr[i] / digits_num) % 10];
	}
	
	/*cumulative sum*/
	for (i = 0; i < 10 ; ++i)
	{
		count = count_array[i];
		count_array[i] = numItemsBefore;
		numItemsBefore += count;
	}
	
	output_array = (int*)malloc(size * sizeof(int));
	if (NULL == output_array)
	{
		return;
	}
	/*create output array*/
	for (i = 0; i < size ; ++i)
	{
		num = (arr[i] / digits_num) % 10;
		output_array[count_array[num]] = arr[i];
		++count_array[num];
	}

	
	memcpy(arr, output_array, size * sizeof(int));
	free(output_array);
}
