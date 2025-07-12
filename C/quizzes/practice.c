#include <stdlib.h>
#include <stdio.h>


char *f()
{
/*	 char x = 27;*/
	 char *str = "Yana";
	 return str;
}
void question1()
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr + 2;
    ptr--;
    *ptr = 15;
    printf("%d\n", arr[1]);
}


void question4()
{
    int value = 5;
    int *p1 = &value;
    int *p2 = p1;
    *p2 = 10;
    p1 = NULL;
    printf("%d\n", value);
}

void question6()
{
    int* arr = (int*)malloc(5 * sizeof(int));
   
    char* ptr = (char*)arr;
    int i = 0;
     if (NULL == arr)
    {return;}
    for (; i < 5; i++)
    {
         ptr += sizeof(int); 
        *ptr = i; 
        printf("%d ", *arr++);
    }
    printf("%d ", *arr++);
    printf("\n");
    free(arr);
}


int question7(const int* ptr)
{
    int result = *ptr;
    
    while (0 != *ptr)
    {
        result += *ptr++;
    }
    return result;
}

void question9(char* dest, const char* src)
{
    while((*dest++ = *src++));
}

int question10(int arr[3], int size)
{
    int *p = &arr[0];
    int sum = 0;
    
	printf ("line 72 %p %p %p\n", (void*)arr, (void*)&arr[0], (void*)&arr[3]);
	printf("p is %p\n", (void*)p);
	
    while(size-- > 0)
    {

        sum += *(p + size);
        printf("sum is %d ", sum);
/*        p++;*/
    }
	printf("\n");
	printf ("sum / size is %d\n", (sum / size));
    return (sum / size);
}


int main(void)
{
	int arr0[4] = {10,20,30, 0};
	int *const arr1 = (int*)malloc(5*sizeof(int)); 
/*	int i = 0;*/
/*	int *arr2 = arr1;*/
/*	const int *arr3 = arr0;*/
	char *str = f();
	char dst[10] = "";
	char *src = "YanaGLazer";
	
	printf ("line 94 - address of arr[0] is %p, arr[3] is %p\n", (void*)&arr0[0], (void*)&arr0[3]);
	
	
	question9(dst, src);
	printf("%s\n", dst);
	
	printf("q10 is %d\n",question10(arr0, 4));
	
	
	printf("%s\n", str);
	
	if (NULL == arr1)
	{
		printf("allocation failed.\n");
	}
	
	
	
/*	arr1[0] = 0, arr1[1] = 10, arr1[2] = 20, arr1[3] = 30, arr1[4] = 40;*/
/*	*/
/*	*/
/*	for (i=0 ; i < 5 ; ++i)*/
/*	{*/
/*		printf("%d ", arr1[i]);*/
/*	}*/
/*	printf ("\n");*/
/*	int *const arr*/

	free(arr1);
/*	*/
/*	question1();*/
/*	question4();*/
/*	question6();*/
/*	*/
/*	*/

	printf("q7 is %d\n",question7(arr0));

	return 0;
}
