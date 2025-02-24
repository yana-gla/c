#include <stdio.h>
#include <string.h>

struct s1
{
	unsigned int *i;
	char c;
	short s;
	int *j;
};


struct s2
{
	unsigned int *i;
	int *j;
	char c;
	short s;
};

struct s3
{
	unsigned int i;
	int j;
	char c;
	short s;
};


struct b1
{
	unsigned int i : 2;
/*	unsigned char c :1 ;*/
/*	unsigned short s : 3;*/
/*	int *j;*/
/*	unsigned char x :2;*/
};

struct b2
{
	unsigned int i : 2;
	/*unsigned char c : 1 ;
	unsigned short s : 3; */
};

union 
{
	char array[7];
	int i;
	short s;

} jack1;

union 
{
	char array[4];
	int i;
	short s;

} jack2;

union 
{
	
	char a [6];
	int x;
	

} jack3;
	
	

	
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

unsigned char MirrorBitsByte(unsigned char num)
{
	num = (0x0f & num) << 4 | (0xf0 & num) >> 4 ;
	num = (0x33 & num) << 2 | (0xcc & num ) >>  2;
	num = (0x55 & num) << 1 | (0xaa & num ) >> 1;
	
	return (num);
	
}

int FlipBit( int val, unsigned int n)
{
	return ( (1 << n) ^ val);
}


int CountBitsOn(unsigned char byte)
{
    byte = ( byte & 0x55) + ( (byte >> 1) & 0x55);
    byte = ( byte & 0x33) + ( (byte >> 2) & 0x33);
    byte = ( byte & 0x0f) + ( (byte >> 4) & 0x0f);
    
    return byte;
}

char RotateLeft(char byte, unsigned int nbits)
{
	nbits = 0x7 & nbits; /*modulu 8*/
	return (byte << nbits) | (byte >> (8 - nbits));
}

void Swap1(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}


void SwapPtr(int **ptr1, int **ptr2)
{
	int *temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
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
		++str1;
		++str2;
	}
	
	return (*str1 - *str2);
}

char *StrCpy(char *dest, const char *src)
{
	char *des_start = dest; 
	
	while ('\0' != *src)
	{
		*dest++ = *src++;
	}
	
	*dest = '\0'; 
	
	return des_start;
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
	
	*dest = '\0';
	
	return des_start;
}	

char *StrCat (char *dest, const char *src)
{
	StrCpy(dest + StrLen(dest), src);
	return (dest);
	
} 

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned int  i = 0 ;
	unsigned long first = 0, second = 1, fib = 0;
	
	for ( i = 0; i <= n ; ++i)
	{
		fib = first;
		first = second;
		second += fib;
	}
	
	return (fib);
}


char *IntToString (int num, char *buffer)
{
	sprintf(buffer, "%d", num);
	return (buffer);
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

void foo()
{
	char *s1 = "hello";
	char s2[] = "hello";
	char *s3 = s1;
	printf("%lu %lu %lu %lu \n",
	sizeof(s1), sizeof(s2), strlen(s1), strlen(s2));
	/*s3 [0] = 'H';*/
	printf("%s \n", s3);
}

void foo1()
{
	size_t array [] = {0, 1, 2, 3, 4, 5}; 
	size_t val = 3;
	printf("%lu \n", val[array]);
}


int main()
{
	int a = 5, b = 6;
	int* p1 = &a, *p2 = &b;
	char str1[5] = "yana", str2[3] = "ya", str3[8] = ""; 
	
	printf("%d\n", FlipDigitsNum(-23));
	
	printf("MirrorBitsByte - %d (199)\n",MirrorBitsByte(227));
	printf("Flip bit is %d (127)\n", FlipBit(123, 2));
	
	printf("Num bits in 71 is (4) %d\n", CountBitsOn(71));
	
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
	
	printf ("Fibonacci 3 %ld\n", GetNFibonacciElement(3));
	printf ("Fibonacci 5 %ld\n", GetNFibonacciElement(5));
	printf ("Fibonacci 7 %ld\n", GetNFibonacciElement(7));
	

	
	
	printf ("IntToString %s\n", IntToString (5, str3));
	printf("Mult 3 by 8 is-> %d\n\n", MultBy8(3));
	
	printf("a and b before Swap1 %d %d\n", a, b);
	Swap1(&a, &b);
	printf("a and b after Swap1 %d %d\n", a, b);
	Swap2(&a, &b);
	printf("a and b after Swap2 %d %d\n", a, b);
	Swap3(&a, &b);
	printf("a and b after Swap2 %d %d\n", a, b);
	
	foo();
	foo1();
	
	printf("size of struct s1 is %ld\n", sizeof(struct s1));
	printf("size of struct s2 is %ld\n", sizeof(struct s2));
	printf("size of struct s3 is %ld\n", sizeof(struct s3));
	printf("size of struct b1 is %ld\n", sizeof(struct b1));
	printf("size of struct b2 is %ld\n", sizeof(struct b2));
	
	printf("size of jack1 is %ld\n", sizeof(jack1));
	printf("size of jack2 is %ld\n", sizeof(jack2));
	printf("size of jack3 is %ld\n", sizeof(jack3));
	
	
	return 0;
	
}
