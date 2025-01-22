#include <stdio.h>

/*Revweied by Yonatan 14.01.25 */
/*Changes been made 18.01.25 */

void Print(int x)
{
	printf("%d\n", x);
}

typedef struct
{
	int x;
	void (*fptr)(int); 

}print_me;

int main(void)
{
	int i = 0; 
	print_me arr[10]; 
	
	for( ; i < 10; ++i)
	{
		arr[i].x = i;
		arr[i].fptr = Print;
		arr[i].fptr(arr[i].x); 
	}
	
	return 0;
}

	
	
	
	
