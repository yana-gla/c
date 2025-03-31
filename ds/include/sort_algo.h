/******************************************************************************
* File: sort.h
*
* Purpose: 
*   Implementation of sorting algorithm (sort from smallest to largest)
*
* Author:
*   Yana GLazer 04/03/2025
* 	Adding  MergeSort, QuickSort 29/03/2025
*
******************************************************************************/

#ifndef __SORT_ALGO_H__
#define __SORT_ALGO_H__

#include <stddef.h>


/*cmp func for q_sort*/
typedef int(*compare_func)(const void*, const void*);
/******************************************************************************
* BubbleSort
* comparison-based
* Time Complexity (worst):  O(n2)
* Space Complexity (worst): O(1)
******************************************************************************/
void BubbleSort(int arr[], size_t size);


/******************************************************************************
* SelectionSort
* comparison-based
* Time Complexity (worst):  O(n2)
* Space Complexity (worst): O(1)
******************************************************************************/
void SelectionSort(int arr[], size_t size);

/******************************************************************************
 *InsertionSort
 *comparison-based
 ******************************************************************************/
void InsertionSort(int arr[], size_t size);
/******************************************************************************/

void CountingSort(int arr[], size_t size);

void RadixSort(int arr[], size_t size);

int MergeSort(int *arr_to_sort, size_t num_elements);

void QuickSort(void *arr, size_t arr_size, size_t element_size, compare_func compare);

#endif /*SORT_ALGO*/
