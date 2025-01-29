#include <stddef.h> /*for size_t*/
#include <limits.h> /*UCHAR_MAX, CHAR_BIT*/
#include <assert.h> /*assert*/
#include "bit_arr.h"

#define BIT_ARR_BYTES   sizeof(bit_arr_t) /*8*/
#define NUM_BITS_ARR    BIT_ARR_BYTES * CHAR_BIT /*64*/


static unsigned char LUT_CNT[UCHAR_MAX + 1] = {0}; /*val 0-8*/ 
static unsigned char LUT_MRR[UCHAR_MAX + 1] = {0}; /*val 0 - 255 */

static unsigned char MirrorByte(unsigned char num)
{
	num = (0x0f & num) << 4 | (0xf0 & num) >> 4 ;
	num = (0x33 & num) << 2 | (0xcc & num ) >>  2;
	num = (0x55 & num) << 1 | (0xaa & num ) >> 1;
	
	return (num);
}

static void InitLutMirror()
{
	int i = 0;
	for (i = 0 ; UCHAR_MAX + 1 > i ; ++i)
	{
		LUT_MRR[i] = MirrorByte((unsigned char) i);
	}
}

static int is_off_lut_mirr()
{
	return (!LUT_MRR[1]);
}


bit_arr_t BitArrayMirrorLut(bit_arr_t arr)
{
	size_t i = 0;
	bit_arr_t result = 0;
	
	if (is_off_lut_mirr())
	{
		InitLutMirror();
	}
	
	for (i = 0 ; BIT_ARR_BYTES > i ; ++i)
	{
		result <<= BIT_ARR_BYTES;
		result |= LUT_MRR[arr & 0xff];
		arr >>= BIT_ARR_BYTES;
	}
	
	return result;
}

static int CountBitsByte(unsigned char byte)
{
    byte = ( byte & 0x55) + ( (byte >> 1) & 0x55);
    byte = ( byte & 0x33) + ( (byte >> 2) & 0x33);
    byte = ( byte & 0x0f) + ( (byte >> 4) & 0x0f);
    
    return byte;
}

static void InitLutCount()
{
	int i = 0;

	for (i = 0 ; UCHAR_MAX + 1 > i ; ++i)
	{
		LUT_CNT[i] = CountBitsByte((unsigned char)i);
	}
} 

static int is_off_lut_count()
{
	return (!LUT_CNT[1]) ;
}

size_t BitArrCountOnLut(bit_arr_t arr)
{
	size_t num_on = 0;
	
	if (is_off_lut_count())
	{
		InitLutCount();
	}
	while (0 < arr)
	{
		num_on += LUT_CNT[(arr&0xff)];
		arr >>= CHAR_BIT;
	}
	
	return (num_on);
}





bit_arr_t BitArraySetOn(bit_arr_t arr, size_t k)
{
	assert (k <= NUM_BITS_ARR);
	
	return (arr | 1 <<k );
}

bit_arr_t BitArraySetOff(bit_arr_t arr, size_t k) /*check*/
{
	assert (k <= NUM_BITS_ARR);
	
	return (arr & ~(1 << k));
}

bit_arr_t BitArraySetAll(bit_arr_t bit_arr)
{
	return (~0);
	(void) bit_arr;
}

/*Set 0 all bitarray*/
bit_arr_t BitArrayResetAll(bit_arr_t bit_arr)
{
	return (0);
	(void) bit_arr;
}

bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val)
{
	assert (k <= NUM_BITS_ARR && ((val == 0) | (val == 1)));
	
	bit_arr &= ~(1 << k);
	return (bit_arr |= val << k) ;
}

int BitArrGetVal(bit_arr_t bit_arr, size_t k)
{
	assert (k <= NUM_BITS_ARR);
	
	return ((bit_arr >> k) & 1);

}

bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k)
{
	assert (k <= NUM_BITS_ARR);
	
	return (bit_arr ^ (1 << k));
}


bit_arr_t BitArrRotateL(bit_arr_t bit_arr, size_t val)
{
	val &= 0x3f;
	return (bit_arr << val | bit_arr >> (NUM_BITS_ARR - val));
}

bit_arr_t BitArrRotateR(bit_arr_t bit_arr, size_t val)
{
	val &= 0x3f;
	return (bit_arr >> val | bit_arr << (NUM_BITS_ARR - val));
}


bit_arr_t BitArrayMirror64(bit_arr_t arr)
{
	arr = ((0x00000000ffffffff&arr)<< 32 | (0xffffffff00000000&arr)>>32 );
	arr = ((0x0000ffff0000ffff&arr)<< 16 | (0xffff0000ffff0000&arr)>> 16);
	arr = ((0x00ff00ff00ff00ff&arr)<<8 | (0xff00ff00ff00ff00&arr)>>8);
	arr = ((0x0f0f0f0f0f0f0f0f&arr)<<4 | (0xf0f0f0f0f0f0f0f0&arr)>>4);
	arr = ((0x3333333333333333&arr)<<2 | (0xcccccccccccccccc&arr)>>2);
	arr = ((0x5555555555555555&arr)<<1 | (0xaaaaaaaaaaaaaaaa&arr)>>1);
	
	return (arr);
}


/*static unsigned char MirrorByte(unsigned char num)*/

bit_arr_t BitArrayMirror(bit_arr_t arr)
{
	bit_arr_t result = 0;
	size_t i = 0;
	
	for (i = 0 ; BIT_ARR_BYTES > i ; ++i)
	{
		result <<= BIT_ARR_BYTES;
		result |= MirrorByte(arr & 0xff);
		arr >>= BIT_ARR_BYTES;
	}	
	
	return result;
}


size_t BitArrCountOn(bit_arr_t arr)
{
	size_t bits_on = 0;
	
	while (0 < arr)
	{
		bits_on += CountBitsByte(arr&0xff);
		arr >>= CHAR_BIT;
	}
	
	return (bits_on);
}
	

size_t BitArrCountOn64(bit_arr_t arr)
{
	arr = ( ((arr&0xaaaaaaaaaaaaaaaa)>>1) + (arr&0x5555555555555555));
	arr = ( ((arr&0xcccccccccccccccc)>>2) + (arr&0x3333333333333333));
	arr = ( ((arr&0xf0f0f0f0f0f0f0f0)>>4) + (arr&0x0f0f0f0f0f0f0f0f));
	arr = ( ((arr&0xff00ff00ff00ff00)>>8) + (arr&0x00ff00ff00ff00ff));
	arr = ( ((arr&0xffff0000ffff0000)>>16) + (arr&0x0000ffff0000ffff));
	arr = ( ((arr&0xffffffff00000000)>>32) + (arr&0x00000000ffffffff)); 
	return arr;
}

size_t BitArrCountOff(bit_arr_t arr)
{
	return (NUM_BITS_ARR - BitArrCountOn(arr));
}

char *BitArrayToString(const bit_arr_t arr, char *buffer)
{

	int i = NUM_BITS_ARR - 1;
	bit_arr_t bit = 0;
	char *buffer_start = buffer;
	
	assert(buffer != NULL);
	
	for (i = i ; i >= 0; --i)
	{
			bit = ((arr>>i) & 1);
			*buffer++ = bit + '0';
	}
	
	*buffer = '\0';
	
	return (buffer_start);
}




