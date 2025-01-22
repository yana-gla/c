#include <limits.h> /*UCHAR*/
#include <stdlib.h> /*calloc*/
#include <stddef.h> /*NULL*/
#include <stdio.h> /*printf*/

void PrintLetters(const char *str1, const char *str2, const char *str3)
{
	int i = 0;
 	char *arr = (char*)calloc(UCHAR_MAX, sizeof(char));
 	
 	if (NULL == arr) 
 	{
 		printf("Memory allocation failed in line %d!\n", __LINE__);
 	}

 	/* Mark all chars that appear in str1 with 1*/
 	while ('\0' != *str1)
 	{
 		arr[(unsigned char)*str1] = 1;
 		++str1;
 	}
 	
 	/*If element was in str1, mark him with 2*/
 	while ('\0' != *str2)
 	{
 		if (1 == arr[(unsigned char)*str2]) /*seen before*/
 		{
 			arr[(unsigned char)*str2] = 2;
 		}
 		++str2;
 	}
 	
 	/*Mark elements with array 3 with 0*/
 	while ('\0' != *str3)
 	{
 		arr[(unsigned char)*str3] = 0;
 		++str3;
 	}
 	
 	/*print*/
 	for (i = 0; i < UCHAR_MAX ; ++i)
 	{
 		if (2 == arr[i])
 		{
 			printf("%c ", i);
 		}
 	}
 	printf("\n");
 	
 	free(arr);
 	arr = NULL;
}


int main ()
{
	printf("Expected : c d - returned : ");
	PrintLetters("abcd","bcd","b");
	
	printf("Expected : g - returned : ");
	PrintLetters("oooggg","gggggg","bd");
	
	printf("Expected :  - returned : ");
	PrintLetters("ooooooo","gggggg","og");
	
	printf("Expected : b - returned : ");
	PrintLetters("aabb","ab","a");
	
	printf("Expected :  - returned : ");
	PrintLetters("aabb","abewr","ab");


	return 0;
}
