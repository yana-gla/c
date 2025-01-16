#include <stdio.h>

void Print(int x)
{
	printf("%d\n", x);
}

typedef struct Print
{
	int x;
	void (*fptr)(int);

}print_me;

int main(void)
{
	size_t i = 0;
	print_me arr[10];
	
	for( ; i < 10; ++i)
	{
		arr[i].x = i;
		arr[i].fptr = &Print;
		arr[i].fptr(arr[i].x);
	}
	
	return 0;
}

	
	
	
	
