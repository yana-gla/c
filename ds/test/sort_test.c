#include <stdio.h> /* For printf */
#include <assert.h> /* For assert */
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include "sort.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"
#define SIZE 5000
#define NEGATIVE_ARRAY_SIZE 5

typedef void (*SortFunction)(int*, size_t);

void TestSort(SortFunction sort_func, char* sort_name, int max_value);
/*void TestCountingSortNegative();*/
int Compare(const void *a, const void *b);
int ArraysEqual(int *arr1, int *arr2, int size);


int result;

int main(void)
{
	TestSort(BubbleSort, "Bubble Sort", 10000);
	TestSort(SelectionSort, "Selection Sort", 10000);
	TestSort(InsertionSort, "Insertion Sort", 10000);
/*	TestSort(CountingSort, "Counting Sort", 101);*/
/*	TestSort(RadixSort, "Radix Sort", 1000001);*/
/*	TestCountingSortNegative();*/

	if (0 == result)
	{
		printf(GREEN "\n🫡️🫡️🫡️🫡️🫡️🫡️ All tests completed successfully 🫡️🫡️🫡️🫡️🫡️🫡️\n" UNFORMAT);
	}
	return (0);
}

/*void TestCountingSortNegative()*/
/*{*/
/*	int arr1[NEGATIVE_ARRAY_SIZE];*/
/*	int arr2[NEGATIVE_ARRAY_SIZE];*/
/*	clock_t start, end;*/
/*	*/
/*	arr1[0] = arr2[0] = 10;*/
/*	arr1[1] = arr2[1] = -5;*/
/*	arr1[2] = arr2[2] = -90;*/
/*	arr1[3] = arr2[3] = 7;*/
/*	arr1[4] = arr2[4] = -4;*/
/*	*/
/*	start = clock();*/
/*	CountingSort(arr1, NEGATIVE_ARRAY_SIZE);*/
/*	end = clock();*/
/*	*/
/*	printf("\n-----------------------------------\n");*/
/*	printf("Counting sort negative time: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);*/
/*	*/
/*	start = clock();*/
/*	qsort(arr2, NEGATIVE_ARRAY_SIZE, sizeof(int), Compare);*/
/*	end = clock();*/
/*	*/
/*	printf("qsort time: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);*/
/*	*/
/*	if (!ArraysEqual(arr1, arr2, NEGATIVE_ARRAY_SIZE))*/
/*	{*/
/*		printf(RED "\nTestSort for Counting sort negative FAILED.\n" UNFORMAT);*/
/*		++result;	*/
/*	}*/
/*	*/
/*	else*/
/*	{*/
/*		printf(GREEN "\n🫡️ Counting sort negative PASSED 🫡️\n" UNFORMAT);*/
/*	}*/
/*	*/
/*	printf("-----------------------------------\n");*/
/*}*/

void TestSort(SortFunction sort_func, char* sort_name, int max_value)
{
	int arr1[SIZE];
	int arr2[SIZE];
	size_t i = 0;
	clock_t start, end;
	
	srand(time(NULL));
	
	for (i = 0 ; i < SIZE ; ++i) 
	{
        arr1[i] = rand() % max_value;
        arr2[i] = arr1[i];
    }


	start = clock();
	sort_func(arr1, SIZE);
	end = clock();
	
	printf("\n-----------------------------------\n");
	printf("%s time: %f seconds\n", sort_name, ((double)(end - start)) / CLOCKS_PER_SEC);
	
	start = clock();
	qsort(arr2, SIZE, sizeof(int), Compare);
	end = clock();
	
	printf("qsort time: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	
	if (!ArraysEqual(arr1, arr2, SIZE))
	{
		printf(RED "\nTestSort for %s FAILED.\n" UNFORMAT, sort_name);
		++result;	
	}
	
	else
	{
		printf(GREEN "\n🫡️ %s PASSED 🫡️\n" UNFORMAT, sort_name);
	}
	
	printf("-----------------------------------\n");
}


/* Comparison function for qsort */
int Compare(const void *a, const void *b) 
{
    return (*(int*)a - *(int*)b);
}

/* Function to check if two arrays are equal */
int ArraysEqual(int *arr1, int *arr2, int size) 
{
    return memcmp(arr1, arr2, size * sizeof(int)) == 0;
}


