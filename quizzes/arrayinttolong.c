#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/



long *SumIntParirsToLOngs1(int ints[], size_t NumOfElements)
{
	size_t i = 0;
	long *longs = (long*)ints;
	
	for (i = 0 ; i < NumOfElements/2 ; ++i)
	{
		longs[i] = (long)ints[i*2] + ints[i*2 + 1];
	}
	
	return longs;
	
}


long *SumIntParirsToLOngs2(int ints[], size_t NumOfElements)
{
	size_t i = 0;
	long *longs = (long*)ints;
	long sum = 0;
	
	
	for (i = 0 ; i < NumOfElements-1 ; ints += 2, i+=2)
	{	
		sum = (long)(*ints) + *(ints+1);
		memcpy(ints, &sum, sizeof(long));/*to, from, size bytes*/
	}
	
	return longs;
	
}






int main(void)
{
	int i = 0;
	
	int arr1[6] = {1, 6, 456, -3, 8, 12};
	int arr2[6] = {1, 6, 456, -3, 8, 12};
	long *longs1 = SumIntParirsToLOngs1(arr1, 6);
	long *longs2 = SumIntParirsToLOngs2(arr2, 6);
	
	for (i = 0; i < 3; ++i)
	{
		printf ("%ld ", *(longs1 + i));
	} 
	printf ("\n");
	
	for (i = 0; i < 3; ++i)
	{
		printf ("%ld ", *(longs2 + i));
	} 
	printf ("\n");
	return 0;
}
