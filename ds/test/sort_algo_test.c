/*
*	Writer : Ofir Hasson
*
*	Reviewed by: 
*	Reviewed date: 
*/



#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* rand,qsort */
#include <string.h> /* memcmp */
#include <time.h> /* time */

#include "sort_algo.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

#define SIZE 5000

typedef void (*sort_func)(int*,size_t);
typedef int (*search_func)(int* arr, size_t size, int n);

static void TestAlgorithm(sort_func sort_alg , char* name);
static void TestSearch(search_func search_alg, char* name);
static void TestMergeSort();
/*static void TestQuickSort();*/
/*static void TestQuickSortNoOpt();*/
/*static void TestQuickSortOpt();*/

static void CopyArr(int* dst_arr, int* src_arr, size_t size);
static void generateRandomArray(int* arr, size_t size);
static void generateRandomArray1_100(int* arr, size_t size);
static void generateRandomArray1_100WithNegatives(int* arr, size_t size);
static int IntsCmp(const void *a, const void *b);

int main(void)
{
	printf("Beginning arr_sorts.c tests...\n\n");
	
	TestAlgorithm(BubbleSort , "BubbleSort");
	TestAlgorithm(SelectionSort, "SelectionSort");
	TestAlgorithm(InsertionSort, "InsertionSort");
	TestAlgorithm(CountingSort, "CountingSort");
	TestAlgorithm(CountingSort, "NegativeCountingSort");
	TestAlgorithm(RadixSort, "RadixSort");
	
	TestMergeSort();
/*	TestQuickSort();*/


	return (0);
}

static void TestMergeSort()
{
	int arr[SIZE] = {0};
	int arr1[SIZE] = {0};
	
	clock_t start_t, end_t;
   	double total_t;
   	
   	printf("MergeSort test:\n");
   	
    srand(time(NULL));
    
	generateRandomArray(arr, SIZE);
    
	CopyArr(arr1,arr,SIZE);
	
    start_t = clock();
	MergeSort(arr, SIZE);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   	printf("Total time of the MergeSort: %f\n", total_t);
   	
   	start_t = clock();
	qsort(arr1, SIZE, sizeof(arr1[0]), IntsCmp);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Total time of the qsort: %f\n", total_t);
	
	if(0 != memcmp(arr,arr1,SIZE * sizeof(arr1[0])))
	{
		printf(RED "\n\tMergeSort FAILED!\n\n" UNFORMAT);
	}
	else
	{
		printf(GREEN "\n\tMergeSort PASSED!\n\n" UNFORMAT);
	}

}

/*static void TestQuickSort()*/
/*{*/
/*	TestQuickSortNoOpt();*/
/*	TestQuickSortOpt();*/
/*}*/

#pragma GCC push_options
#pragma GCC optimize ("O0")

/*static void TestQuickSortNoOpt()*/
/*{*/
/*	int arr[SIZE] = {0};*/
/*	int arr1[SIZE] = {0};*/
/*	*/
/*	clock_t start_t, end_t;*/
/*   	double total_t;*/
/*   	*/
/*   	printf("QuickSort test:\n");*/
/*   	*/
/*    srand(time(NULL));*/
/*    */
/*	generateRandomArray(arr, SIZE);*/
/*    */
/*	CopyArr(arr1,arr,SIZE);*/
/*	*/
/*    start_t = clock();*/
/*	QuickSort(arr, SIZE, sizeof(arr[0]), IntsCmp);*/
/*	end_t = clock();*/
/*	*/
/*	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;*/
/*   	printf("Total time of the QuickSort (No optimization): %f\n", total_t);*/
/*   	*/
/*   	start_t = clock();*/
/*	qsort(arr1, SIZE, sizeof(arr1[0]), IntsCmp);*/
/*	end_t = clock();*/
/*	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;*/
/*	printf("Total time of the qsort (No optimization): %f\n", total_t);*/
/*	*/
/*	if(0 != memcmp(arr,arr1,SIZE * sizeof(arr1[0])))*/
/*	{*/
/*		printf(RED "\n\tQuickSort FAILED!\n\n" UNFORMAT);*/
/*	}*/
/*	else*/
/*	{*/
/*		printf(GREEN "\n\tQuickSort PASSED!\n\n" UNFORMAT);*/
/*	}*/

/*}*/

#pragma GCC pop_options

#pragma GCC push_options
#pragma GCC optimize ("O3")

/*static void TestQuickSortOpt()*/
/*{*/
/*	int arr[SIZE] = {0};*/
/*	int arr1[SIZE] = {0};*/
/*	*/
/*	clock_t start_t, end_t;*/
/*   	double total_t;*/
/*   	*/
/*   	printf("QuickSort test:\n");*/
/*   	*/
/*    srand(time(NULL));*/
/*    */
/*	generateRandomArray(arr, SIZE);*/
/*    */
/*	CopyArr(arr1,arr,SIZE);*/
/*	*/
/*    start_t = clock();*/
/*	QuickSort(arr, SIZE, sizeof(arr[0]), IntsCmp);*/
/*	end_t = clock();*/
/*	*/
/*	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;*/
/*   	printf("Total time of the QuickSort: %f\n", total_t);*/
/*   	*/
/*   	start_t = clock();*/
/*	qsort(arr1, SIZE, sizeof(arr1[0]), IntsCmp);*/
/*	end_t = clock();*/
/*	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;*/
/*	printf("Total time of the qsort: %f\n", total_t);*/
/*	*/
/*	if(0 != memcmp(arr,arr1,SIZE * sizeof(arr1[0])))*/
/*	{*/
/*		printf(RED "\n\tQuickSort FAILED!\n\n" UNFORMAT);*/
/*	}*/
/*	else*/
/*	{*/
/*		printf(GREEN "\n\tQuickSort PASSED!\n\n" UNFORMAT);*/
/*	}*/

/*}*/

#pragma GCC pop_options

static void TestSearch(search_func search_alg, char* name)
{
	int arr[SIZE] = {0};
	int first = 0 , last = SIZE-1, middle = SIZE / 2; 
	int tmp = 1000;
	int result = 0;
	size_t i = 0;
   	
   	printf("%s test:\n",name);
   	
    for (i = 0; i < SIZE; ++i) 
    {
        arr[i] = i;
    }
	
	if(first != search_alg(arr,SIZE, arr[first]))
	{
		++result;
		printf(RED "\n\t%s FAILED! expected result %d, but got %d\n\n" UNFORMAT, name,first,search_alg(arr,SIZE, arr[first]));
	}
	
	if(last != search_alg(arr,SIZE, arr[last]))
	{
		++result;
		printf(RED "\n\t%s FAILED! expected result %d, but got %d\n\n" UNFORMAT, name,last,search_alg(arr,SIZE, arr[last]));
	}
	
	if(middle != search_alg(arr,SIZE, arr[middle]))
	{
		++result;
		printf(RED "\n\t%s FAILED! expected result %d, but got %d\n\n" UNFORMAT, name,middle,search_alg(arr,SIZE, arr[middle]));
	}
	
	if(tmp != search_alg(arr,SIZE, arr[tmp]))
	{
		++result;
		printf(RED "\n\t%s FAILED! expected result %d, but got %d\n\n" UNFORMAT, name,tmp,search_alg(arr,SIZE, arr[tmp]));
	}
	
	if(0 == result)
	{
		printf(GREEN "\n\t%s PASSED!\n\n" UNFORMAT, name);
	}
	
}

static void TestAlgorithm(sort_func sort_alg , char* name)
{
	int arr[SIZE] = {0};
	int arr1[SIZE] = {0};
	
	clock_t start_t, end_t;
   	double total_t;
   	
   	printf("%s test:\n",name);
   	
    srand(time(NULL));
    if(sort_alg == CountingSort)
    {
    	generateRandomArray1_100(arr, SIZE);
    }
    else if(sort_alg == CountingSort && strcmp("NegativeCountingSort", name))
    {
    	generateRandomArray1_100WithNegatives(arr, SIZE);
    }
    else
    {    
	    generateRandomArray(arr, SIZE);
    }
	CopyArr(arr1,arr,SIZE);
	
    start_t = clock();
	sort_alg(arr,SIZE);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   	printf("Total time of the %s: %f\n",name, total_t);
   	
   	start_t = clock();
	qsort(arr1, SIZE, sizeof(arr1[0]), IntsCmp);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Total time of the qsort: %f\n", total_t);
	
	if(0 != memcmp(arr,arr1,SIZE * sizeof(arr1[0])))
	{
		printf(RED "\n\t%s FAILED!\n\n" UNFORMAT, name);
	}
	else
	{
		printf(GREEN "\n\t%s PASSED!\n\n" UNFORMAT, name);
	}

}

static int IntsCmp(const void *a, const void *b) 
{
    return (*(int*)a - *(int*)b);
}

static void generateRandomArray(int* arr, size_t size) 
{
	size_t i = 0;
    for (i = 0; i < size; ++i) 
    {
        arr[i] = rand() % 10000;
    }
}

static void generateRandomArray1_100(int* arr, size_t size) 
{
	size_t i = 0;
    for (i = 0; i < size; ++i) 
    {
        arr[i] = (rand() % 100) + 1;
    }
}

static void generateRandomArray1_100WithNegatives(int* arr, size_t size) 
{
	size_t i = 0;
    for (i = 0; i < size; ++i) 
    {
        arr[i] = (rand() % 100) + 1;
        if(i % 2)
        {
        	arr[i] = -arr[i];
        }
    }
}

static void CopyArr(int* dst_arr, int* src_arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0 ; i < size ; ++i)
	{
		dst_arr[i] = src_arr[i];
	}
}



























