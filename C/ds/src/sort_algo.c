#include <stdlib.h> /*calloc*/
#include <string.h> /*memset*/
#include "sort_algo.h"

#define GET_ELEMENT(arr, index, element_size) (((char*)arr) + (index*element_size))

/******************************************************************************/
static int Bubble(int arr[], size_t size);
static void Swap(int *a, int *b);
static int FindMax(int arr[], size_t size);
static void CountingSortDigits(int arr[], size_t size, int digits_num);
static void QuickSortHelper(void *arr, size_t start, size_t end, size_t element_size, compare_func compare);
static size_t Partition(void *arr, size_t start, size_t end, size_t element_size, compare_func compare);
static void SwapVoid(void *a, void *b, size_t element_size);
static void HelperMergeSort(int *arr, size_t num_elements, int helper_arr[]);
static void Merge(int arr_l[], size_t nl, int arr_r[], size_t nr, int helper_arr[]);
static void SwapSmallest(int arr[], size_t size);
/******************************************************************************/
void BubbleSort(int arr[], size_t size)
{
	int not_sorted = 1;
	
	while (not_sorted && size > 1)
	{
		not_sorted = Bubble(arr, size--);
	}
}
/******************************************************************************/
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
int MergeSort(int *arr_to_sort, size_t num_elements)
{
	int *helper_arr = (int*)malloc(num_elements *sizeof(int));
	if (NULL == helper_arr)
	{
		return -1;
	}
	HelperMergeSort(arr_to_sort, num_elements, helper_arr);
	free(helper_arr);
	return 0;
}

/******************************************************************************/
void QuickSort(void *arr, size_t arr_size, size_t element_size, compare_func compare)
{
	QuickSortHelper(arr, 0, arr_size - 1, element_size, compare);
}
/******************************************************************************/


/*******************************  Static function  ****************************/
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

/******************************************************************************/
static void Merge(int arr_l[], size_t nl, int arr_r[], size_t nr, int helper_arr[])
{
	size_t il = 0, ir = 0, ih = 0;
	
	while (il < nl && ir < nr)
	{
		helper_arr[ih++] = (arr_l[il] < arr_r[ir]) ? arr_l[il++] : arr_r[ir++];
	}
	
	/*left elemnts*/
	while (il < nl)
	{
		helper_arr[ih++] = arr_l[il++];
	}
	while (ir < nr)
	{
		helper_arr[ih++] = arr_r[ir++];
	}

}

static void HelperMergeSort(int *arr, size_t num_elements, int helper_arr[])
{
	size_t left = num_elements/2, right = num_elements - left; /*odd & even*/
	
	if (num_elements <= 1) /*one item array is sorted*/
	{
		return;
	}
	HelperMergeSort(arr, left, helper_arr); /*calling left part*/
	HelperMergeSort(arr + left, right, helper_arr); /*calling right part*/ 
	Merge(arr, left, (arr + left), right, helper_arr);		
	memcpy(arr, helper_arr, num_elements * sizeof(int));
	
}

/******************************************************************************/
static void SwapVoid(void *a, void *b, size_t element_size)
{
	void *temp = malloc(element_size);
	if (NULL == temp)
	{
		return;
	}
	memcpy(temp, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, temp, element_size);	
	free(temp);
}

static void QuickSortHelper(void *arr, size_t start, size_t end, size_t element_size, compare_func compare)
{
	size_t pivot_idx = 0;
	
	if (end <= start) /*array of size 1 is sorted*/
	{
		return;
	}
	
	pivot_idx = Partition(arr, start, end, element_size, compare);
	
	if (pivot_idx > start)
	{
		 /*Recursively sort [start, pivot_index)*/
		QuickSortHelper(arr, start, pivot_idx - 1, element_size, compare);
	}
	
	
	/*Recursively sort [pivot_index + 1, end) */
	QuickSortHelper(arr, pivot_idx + 1, end, element_size, compare);
}
       
static size_t Partition(void *arr, size_t start, size_t end, size_t element_size, compare_func compare)
{
	size_t pivot = end ; /*pivot is the last element*/
	void *pivot_ref = GET_ELEMENT(arr, pivot, element_size);
	void *curr_ref = NULL, *i_ref = NULL;
	size_t i = start, j = start; /*j runs on all the array, i is the index of all the elemnts which smaller than pivot*/
	
	for (j = start ; j < end ; ++j)
	{
		curr_ref = GET_ELEMENT(arr, j, element_size);
		/*if curr is smaller than pivot swap*/
		if (compare(curr_ref, pivot_ref) < 0) 
		{
			i_ref = GET_ELEMENT(arr, i, element_size);
			SwapVoid(curr_ref, i_ref, element_size);
			++i;
		}
	}
	/*move pivot to the right place*/
	SwapVoid(pivot_ref, 
			 GET_ELEMENT(arr, i, element_size), element_size);
	
	return i;
}
/******************************************************************************/
