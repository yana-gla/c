#include <stdio.h>
#include <stddef.h>

void swap (int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/*Bring 0 to Begining*/
void SortArrZeroOne(int arr[], size_t size)
{
	size_t l = 0, r = 0;
	
	for (r = 0 ;r < size ; ++ r)
	{
		if (0 == arr[r])
		{
			swap(&arr[l], &arr[r]);
			++l;
		}
	}
}

/*void SortArrZeroOne(int arr[], size_t size)*/
/*{*/
/*	size_t l = 0, r = size - 1;*/
/*	*/
/*	while (l < r)*/
/*	{*/
/*		if (1 == arr[l])*/
/*		{*/
/*			if (0 == arr[r])*/
/*			{*/
/*				swap(&arr[l], &arr[r]);*/
/*				++l, --r;*/
/*			}*/
/*			else /*if arr[r] == 1*/
/*			{*/
/*				--r; /*decrease right*/
/*			}*/
/*		}*/
/*		else /*if arr[l] == 0*/
/*		{*/
/*			++l; /*move l right*/
/*		}*/
/*			*/
/*	}*/
/*}*/

int main(void)
{
	int arr[10] = {0, 1, 0, 0, 0, 1, 0, 1, 0, 1};
	int size = sizeof(arr) / sizeof(int);
	int i = 0;
	SortArrZeroOne(arr, size);
	
	 for (i = 0; i < size; ++i)
	 {
	 	 printf("%d ", arr[i]);
	 }
     printf("\n ");
    return 0;
}
