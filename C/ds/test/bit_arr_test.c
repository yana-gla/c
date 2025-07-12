#include <stdio.h> /*printf*/
#include <stddef.h> /*for size_t*/
#include <limits.h> /*UCHAR_MAX CHAR_BIT*/
#include <assert.h> /*assert*/
#include "bit_arr.h"

#define BIT_ARR_BYTES   sizeof(bit_arr_t) /*8*/
#define NUM_BITS_ARR    BIT_ARR_BYTES * CHAR_BIT /*64*/

int main()
{
	bit_arr_t arr = 10;  /*1010*/
	bit_arr_t arr2 = 39; /*0010 0111*/
	bit_arr_t arr3 =  100; /*1100100*/
	char buffer[NUM_BITS_ARR + 1] ="" ;
	int val = 64;
	
	
	printf("SetOn should print 11 %lu\n", BitArraySetOn(arr, 0));
	printf("SetOn should print 14 %lu\n", BitArraySetOn(arr, 2));
	
	printf("SetOff should print 8 %lu\n", BitArraySetOff(arr, 1));
	printf("SetOff should print 2 %lu\n", BitArraySetOff(arr, 3));
	printf("\n");
	
	printf("Set all is %lu\n", BitArraySetAll(arr));
	printf("Reset all is %lu\n", BitArrayResetAll(arr));
	
	
	printf("BitArrSetBit is %lu\n", BitArrSetBit(arr, 1, 0));
	printf("BitArrSetBit is %lu\n", BitArrSetBit(arr, 0, 1));
	printf("BitArrSetBit is %lu\n\n", BitArrSetBit(arr, 0, 1));
	
	printf("BitArrGetVal is %d\n", BitArrGetVal(arr, 0));
	printf("BitArrGetVal is %d\n", BitArrGetVal(arr, 1));
	
	printf("BitArrFlip is 8 %lu\n", BitArrFlip(arr, 1));
	printf("BitArrFlip is 14 %lu\n", BitArrFlip(arr, 2));
	
	printf("BIT_ARRAY_SIZE is %lu\n", BIT_ARR_BYTES);
	printf("NUM_BITS size is %lu\n", NUM_BITS_ARR);
	
	printf("BitArrRotateL is %lu\n",BitArrRotateL(arr2, 2));
	printf("BitArrRotateR is %lu\n\n",BitArrRotateR(arr2, 2));
	
	printf("Mirror64 is    %lu\n", BitArrayMirror64(arr));
	printf("Mirror is      %lu\n\n", BitArrayMirrorLut(arr));
	printf("MirrorLut is   %lu\n\n", BitArrayMirrorLut(arr));
	
	
	printf("CountOn64 bits is %lu\n", BitArrCountOn64(arr));
	printf("CountOn bits is %lu\n", BitArrCountOn(arr));
	printf("CountOnLUT_CNT is bits is %lu\n", BitArrCountOnLut(arr));
	printf("CountOnLUT_CNT is bits is %lu\n", BitArrCountOnLut(arr3));
	
	
	printf("CountOff bits is %lu\n", BitArrCountOff(arr));

	/*printf("size of buffer is %lu\n", sizeof(buffer));*/
	
	printf("To string bits is %s\n", BitArrayToString(arr, buffer));
	
	printf("val is %d\n", val & 0x3f);
	

	return 0;
	
}


