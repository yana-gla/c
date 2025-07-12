#include <stdio.h>
#include <string.h>
#include <limits.h>

int FlipDigitsNum(int num)
{
	int sign = 1;
	int rev_num = 0;
	
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	
	while (num > 0)
	{
		rev_num = rev_num * 10 + num % 10;
		num /= 10;
	}
	
	return sign * rev_num;
}


unsigned char MirrorBitsByte(unsigned char byte)
{
	byte = (0x0f & byte) << 4 | (0xf0 & byte) >> 4 ;
	byte = (0x33 & byte) << 2 | (0xcc & byte) >>  2;
	byte = (0x55 & byte) << 1 | (0xaa & byte) >> 1;
	
	return byte;
}

int FlipBit( int val, unsigned int n)
{
	return ( (1 << n) ^ val);
}

int CountBitsOn(unsigned char byte)
{
    byte = (byte & 0x55) + ((byte & 0xaa)>>1);
    byte = (byte & 0x33) + ((byte & 0xcc)>>2);
    byte = (byte & 0x0f) + ((byte & 0xf0)>>4);
    
    return byte;
}

int CountBitsOnNew(unsigned char byte)
{
    byte = ( byte & 0x55) + ((byte & 0xaa)>>1);
    byte = ( byte & 0x33) +  ((byte & 0xcc)>>2);
    byte = ( byte & 0x0f) +  ((byte & 0xf0)>>4);
    
    return byte;
}

char RotateLeft(char byte, unsigned int nbits)
{
	nbits = 0x7 & nbits; /*modulu 8*/
	return ((byte << nbits) | (byte >> (CHAR_BIT - nbits)));
}

void SwapPtr(int **num1, int **num2)
{
	int *tmp_ptr = *num1;
	*num1 = *num2;
	*num2 = tmp_ptr;
}

int StrLen(char const *str)
{
	const char *rnr = str;
	
	while ('\0' != *rnr)
	{
		++rnr;
	}
	
	return (rnr-str);
}

int StrCmp(const char *str1, const char *str2)
{
	
	while (('\0' != *str1) && (*str1 == *str2))
	{
		++str1, ++str2;
	}
	
	return (*str1 - *str2);
}


char *StrCpy(char *dest, const char *src)
{
	char *rnr = dest; 
	
	while ('\0' != *src)
	{
		*rnr++ = *src++;
	}
	
	*dest = '\0'; 
	
	return dest;
}

char *StrNCpy(char *dest, const char *src, int n)
{
	char *des_start = dest; 
	
	while (('\0' != *src) && (n > 0))
	{
		*dest++ = *src++;
		--n;
	}
	
	while (n > 0)
	{
		*dest++ = '\0';
		--n;
	}
	
	return des_start;
}	

char *StrCat (char *dest, const char *src)
{
	StrCpy(dest + StrLen(dest), src);
	return (dest);
	
} 

unsigned long GetNFibonacciElement2(unsigned int n)
{
	unsigned int  i = 0 ;
	unsigned long a0= 0, a1 = 1;
	
	for ( i = 0; i < n ; ++i)
	{
		a1 = a0 + a1;
		a0 = a1 - a0;
	}
	
	return a0;
}

char *IntToString (int num, char *str)
{
	sprintf(str, "%d", num);
	return (str);
}

int MultBy8 (int num)
{
	return (num << 3);
}

void Swap1(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

/*dont work if it the same pointer*/
void Swap2(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1 ^ *ptr2;
	*ptr2 = *ptr1 ^ *ptr2;
	*ptr1 = *ptr1 ^ *ptr2;
}


void Swap3(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1 + *ptr2;
	*ptr2 = *ptr1 - *ptr2;
	*ptr1 = *ptr1 - *ptr2;
}






int main()
{
	
	int a = 5, b = 6;
	int* p1 = &a, *p2 = &b;
	char str1[5] = "yana", str2[3] = "ya", str3[8] = ""; 
	
	printf("Flip num -230 is %d\n", FlipDigitsNum(-230));
	printf("Flip num 1000 is %d\n\n", FlipDigitsNum(1000));
	
	printf("Mirror byte of 0 is %d\n", MirrorBitsByte(0));
	printf("Mirror byte of 123 is (222) %d\n", MirrorBitsByte(123));
	printf("Mirror byte of 255 is (255) %d\n\n",MirrorBitsByte(255));
	
	printf("Flip bit is %d (127)\n\n", FlipBit(123, 2));
	
	printf("Num bits in 71 is (4) %d\n\n", CountBitsOn(71));
	
	
	printf("RotateLeft bit is %d (111)\n", FlipBit(123, 2));
	
	printf("before : p1 - %d , p2 - %d\n",*p1, *p2);
	SwapPtr(&p1, &p2);
	printf("after : p1 - %d , p2 - %d\n",*p1, *p2);
	
	printf("len of yana is %d\n", StrLen("Yana"));

	printf ("StrCmp %d\n", StrCmp(str1, str2));
	printf ("strcmp %d\n", strcmp(str1, str2));
	printf ("StrCpy %s\n", StrCpy(str3, str2));
	printf ("StrNCpy %s\n", StrCpy(str3, str2));
	printf ("StrCpy %s\n\n", StrCat(str1, str2));
	
	printf ("Fibonacci 3 %ld\n", GetNFibonacciElement2(3));
	printf ("Fibonacci 5 %ld\n", GetNFibonacciElement2(5));
	printf ("Fibonacci 7 %ld\n", GetNFibonacciElement2(7));
	
	
	
	
	printf ("IntToString %s\n", IntToString (5, str3));
	printf("Mult 3 by 8 is-> %d\n\n", MultBy8(3));
	
	printf("a and b before Swap1 %d %d\n", a, b);
	Swap1(&a, &b);
	printf("a and b after Swap1 %d %d\n", a, b);
	Swap2(&a, &b);
	printf("a and b after Swap2 %d %d\n", a, b);
	Swap3(&a, &b);
	printf("a and b after Swap2 %d %d\n", a, b);
	
	return 0;
}
	
	
	
	
