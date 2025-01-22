#include <stdio.h>    
#include <stdlib.h>

int *SumRow(int *mat, int r, int c, int* sum)
{
	int i_r = 0, i_c = 0; 
	int *sum_start = sum;
	
	for ( ; i_r < r; ++i_r) 
	{
		for ( i_c =0 ;i_c < c; ++i_c)
		{
			*sum += *((mat + i_r*c) + i_c); 

		}
			++sum;
	}
	
	mat= sum_start;
	
	for (i_r = 0; i_r < r ; ++i_r)
	{
		printf("%d\n", *(mat + i_r));
	}
	
	
	return sum_start;
}



int main(void)
{	
	int arr[][3] = {{1,2,3}, {4,5,6},{7,8,9}};
	int r = 3, c = 3; /*works also if i change r, coool*/
	int *sum_array = (int*)calloc(r, sizeof(int)); 
	SumRow((int*)arr, r, c, sum_array);
	
	
	printf("size of char %ld\n", sizeof(char));
	printf("size of int %ld\n", sizeof(int));
	printf("size of array %ld\n", sizeof(arr));
	printf("size of pointer int %ld\n", sizeof(int*));
	printf("size of pointer long %ld\n", sizeof(long*));
	
	
	free(sum_array);
	return 0;
	
}
	
	
	
	
	
		
