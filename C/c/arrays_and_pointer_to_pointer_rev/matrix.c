#include <stdio.h>    
#include <stdlib.h>

/*Program that recives matrix from the user and calcultaes 
sum of each row */


void FreeMat(int **mat, int rows)
{
    for ( rows = rows - 1 ; rows >= 0 ; --rows)
    {
        free(mat[rows]);
    }
    
    free(mat);
}

int **AlocMatrix(int rows, int col)
{
    int i = 0;
    int **mat = (int**)calloc(rows, sizeof(int*));
    
    if (NULL == mat)
    {
        printf("Memory aloocation failed.\n");
    }
    
    for (i = 0 ; i < rows ; ++i)
    { 
        mat[i] = (int*)calloc(col, sizeof(int));
        if (NULL == mat[i])
        {
             printf("Memory aloocation failed.\n");
             FreeMat(mat, i);
             return NULL;
        }
    }
    
    return mat;
}

void ScanMatrix(int** mat, int rows, int cols)
{
      int r = 0, c = 0;
      
      for ( r = 0 ; r < rows ; ++r)
      {
          for (c = 0 ; c < cols ; ++c)
          {
              printf ("Enter number [%d, %d]\n", r, c );
              scanf ("%d", &mat[r][c]);
          }
      }
      printf("\n");
}


void SumRow(int **mat, int r, int c, int *result)
{
	int i = 0, j = 0; 
	
	for ( i = 0 ; i < r; ++i) 
	{
		for ( j = 0 ; j < c; ++j)
		{
			result[i] += mat[i][j]; 
		}
	}
}


void PrintArr(int arr[], int size)
{
      int i = 0;
      
      for (i = 0; i < size ; ++i)
	{
		printf("sum of row %d is- %d\n", i, arr[i]);
	}
}


int main(void)
{	
	int r = 0, c = 0;
	int **mat = NULL;
	int *sum_array = NULL;
	
	printf ("Enter number of rows-\n");
	scanf("%d", &r);
	
	printf ("Enter number of columns-\n");
	scanf("%d", &c);
	
	if (r == 0 || c == 0)
	{
	    printf ("Number of rows and columns can't be 0.\n");
	    return -1;
	}
	sum_array = (int*)calloc(r, sizeof(int));
	if (NULL == sum_array)
	{
	    printf("Memory aloocation failed.\n");
	}
	mat = AlocMatrix(r, c);
	ScanMatrix(mat, r, c);
	
	SumRow(mat, r, c, sum_array);
	
	PrintArr(sum_array, r);
	
	FreeMat(mat, r);

	free(sum_array);
	
	return 0;
}
	
	
	
	
	
		
