/******************************************************************************
* File: sort.h
*
* Purpose:
*   Implementation of sorting algorithm (sort from smallest to largest)
*
* Author:
*   Yana GLazer 04/03/2025
*
******************************************************************************/

#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>
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



#endif /*SORT_H*/
