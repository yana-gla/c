#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

typedef size_t bit_arr_t;

/*Set to 1 given index bit*/
bit_arr_t BitArraySetOn(bit_arr_t arr, size_t k);
/*Set to 0 given index bit*/
bit_arr_t BitArraySetOff(bit_arr_t arr, size_t k);
/*Set 1 all bitarray*/
bit_arr_t BitArraySetAll(bit_arr_t bit_arr);
/*Set 0 all bitarray*/
bit_arr_t BitArrayResetAll(bit_arr_t bit_arr);
/*Set to val given index bit*/
/*type of val*/
bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val);
/*Returns bit value of given index*/

int BitArrGetVal(bit_arr_t bit_arr, size_t k);
/*Flips bit of given index*/
bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k);
/*Rotates array right num times*/
bit_arr_t BitArrRotateR(bit_arr_t bit_arr, size_t val);
/*Rotates array left num times*/
bit_arr_t BitArrRotateL(bit_arr_t bit_arr, size_t val);
/*Mirrors bits in array*/
bit_arr_t BitArrayMirror(bit_arr_t arr);
bit_arr_t BitArrayMirror64(bit_arr_t arr);
bit_arr_t BitArrayMirrorLut(bit_arr_t arr);

/*Count on bits*/
size_t BitArrCountOn(bit_arr_t arr);
size_t BitArrCountOnLut(bit_arr_t arr);
size_t BitArrCountOn64(bit_arr_t arr);

/*Count off bits*/
size_t BitArrCountOff(bit_arr_t arr);
/*Returns bitarray as string*/
char *BitArrayToString(bit_arr_t arr, char *buffer);

#endif /*closing BitArray if*/
