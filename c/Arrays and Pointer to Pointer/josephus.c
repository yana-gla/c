#include <stdio.h>    
#include <stdlib.h>/*is it used?*/


int josephus_n(int arr[], int n)
{		
	/*solution according to recrusive formula*/
	/*W = (W(n-1)+2) mod n;*/
	
	int winner = 0; 
	int i = 1;
	
	(void)arr;
	
	while (i <= n)
	{
		winner = (winner + 2) % i;
		++i;
	}
	
	return winner;
}


int josephus_n2(int arr[], int n) 
{
	int i = 0;
	arr[n-1] = 0;
	
	for (  ; i < n-1 ; ++i)
	{
		arr[i] = i+1;
	}
	
	i = 0;
	
	while (arr[i] != i)
	{
		arr[i] = arr[arr[i]];
		i = arr[i];
	}
	
	return (i);
}
	
	
int josephus_n_logn(int arr[], int n)
{		
		int i = 1;
		int sword = 1; /*sword 1 = killing, sword 0 = passing*/
		int num_alive = n;
		
		while(num_alive > 1)
		{
			if (arr[i] == 0 && sword == 1)
			{
				arr[i] = 1;
				--num_alive;
	 			sword = 0; /*killing current solider*/
			}
						
			else if (arr[i] == 0 && sword == 0)
			{
				sword = 1;
			}			
			
			i = (i+1) % n;
		}
		
		/*iterate to find winner*/
		for (i = 0; i < n; ++i)
		{
				if (arr[i] == 0)
				{
						break;		
				}
		}
		
		return i;
}

int main(void)
{
	 	/*0 is alive solider*/
		int arr[5] = {0};
		
		printf("winner nlogn solution %d\n", josephus_n_logn(arr, 5));
		printf("winner n solution %d\n" ,josephus_n(arr, 5));
		printf("winner n2 solution %d\n" ,josephus_n2(arr, 5));

		return 0;		
}
		
