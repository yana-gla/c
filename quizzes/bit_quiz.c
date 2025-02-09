#include <stdio.h>

int CountCoupleSetBits(unsigned char byte)
{
	int result = 0;
	unsigned char mask = 0x03; /*0000 0011*/
	
	while (0 < byte)
	{
		if ((byte & mask) == mask)
		{
			++result;
		}
		byte >>=1;
	}
	return result;
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
        *ptr1 += *ptr2;
        *ptr2 = *ptr1 - *ptr2;
        *ptr1 = *ptr1 - *ptr2;
}

int CountSetBits(unsigned long num)
{
	int count = 0 ;
	while (0 < num)
	{
		++count;
		num &= (num - 1);
		printf ("count is %d\n", count);
	}
	
	return count;
}


int main ()
{
	char c = 0xfe;
	unsigned char a = 0xec; /*1110 1100*/
	unsigned long b = 0x60; /*0110 0000*/
	signed char d = -4;  /* Binary: 11111100 for 8-bit signed char*/
	
	printf ("%d\n", c);
	
	c>>=1;
	printf ("%d\n", c);
	
	printf("%d\n", CountCoupleSetBits(a));
	
	printf("%d\n", CountSetBits(b));
	
	if (-1 == ~0) 
	{
        printf("One's complement\n");
    } else if (-1 == (unsigned char)0x80) 
    {
        printf("Sign-and-magnitude\n");
    } else {
        printf("Two's complement\n"); 
    }
    
    


    printf("Before shifting: %d\n", d);
    d >>= 1;
    printf("After shifting: %d\n", d);
	
	
	return 0;
}
