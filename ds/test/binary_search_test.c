#include <stdio.h> /*printf*/

#include "binary_search.h"







int main(void)
{
	int arr_even[6] = {1, 3, 5, 6 ,7, 8};
	int arr_n_even[5] = {1, 3, 5, 6 ,7};
	int arr_neg[7] = {-21, -19, -12, -2, -1 ,0, 9};
	int arr_one[1] = {5};
		
	printf("start test BinIterSearch:\n");
	printf("index is (5) %d.\n", BinIterSearch(arr_even, 6, 8));
	printf("index is (-1) %d.\n", BinIterSearch(arr_even, 6, 0));
	
	printf("index is (1) %d.\n", BinIterSearch(arr_n_even, 5, 3));
	printf("index is (-1) %d.\n", BinIterSearch(arr_n_even, 5, -10));
	
	printf("index is (1) %d.\n", BinIterSearch(arr_neg, 7, -19));
	printf("index is (-1) %d.\n", BinIterSearch(arr_neg, 7, 10));
	
	printf("index is (0) %d.\n", BinIterSearch(arr_one, 1, 5));
	printf("index is (-1) %d.\n", BinIterSearch(arr_one, 1, 0));
	
	
	printf("\nstart test BinRecSearch:\n");
	printf("index is (5) %d.\n", BinRecSearch(arr_even, 6, 8));
	printf("index is (-1) %d.\n", BinRecSearch(arr_even, 6, 0));
	
	printf("index is (1) %d.\n", BinRecSearch(arr_n_even, 5, 3));
	printf("index is (-1) %d.\n", BinRecSearch(arr_n_even, 5, -10));
	
	printf("index is (1) %d.\n", BinRecSearch(arr_neg, 7, -19));
	printf("index is (-1) %d.\n", BinRecSearch(arr_neg, 7, 10));
	
	printf("index is (0) %d.\n", BinRecSearch(arr_one, 1, 5));
	printf("index is (-1) %d.\n", BinRecSearch(arr_one, 1, 0));
	
	
	
	
	
	return 0;
}
