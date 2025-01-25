#include <stdio.h>

typedef unsigned char uchar_t;

long Pow2(unsigned int x, unsigned int y)
{
    return (long)(x << y);
}

int IsPow2Lp(unsigned int n)
{
    /*loop*/
    if (n == 0) return 0;
    
    while (n > 1)
    {
        if ((n & 1) != 0) return 0;
        
        n >>= 1;
    }
    
    return 1;
}

int IsPow2WLp(unsigned int n)
{
    /*without loop*/
    return (0 != n && (0 == (n-1) & n));
}  

int Ads1(int num)
{
    /*Will Check carry each bit using mask*/
    int mask = 1;
    
    while (1 == (mask & num)) /*means there is carry, result this bit turn 0*/
    {
        num =  mask ^ num; /*xor suits for adding*/
        mask <<= 1; /*check next bit*/
    }
    
    return (num ^ mask);
}

void Prnt3Bits(const unsigned int arr[], size_t n)
{
    size_t i = 0;
    size_t num_bits = 0;
    unsigned int num = arr[i];
    
    for (i = 0 ; i < n ; ++i)
    {
        num_bits = 0;
      
        for(num = arr[i] ; num > 0 && num_bits <= 4; num >>= 1 )
        {
            if (1 == (1 & num))
            {
               ++num_bits;
            }
        }
        
        if (3 == num_bits)
        {
              printf ("%u ", arr[i]);
        }
    } 
    printf ("\n");
}

uchar_t ByteMirror1(uchar_t byte)
{
    uchar_t mir_byte = 0; /*mirrored byte*/
    uchar_t lsb = 0;
    int i = 0;
    
    for (i = 0 ; i < 8 ; ++i)
    {
         mir_byte <<= 1;
         lsb =  (1 & byte); /*looking on lsb of byte, if 1 ->1, if 0 -> 0*/ 
         mir_byte = mir_byte | lsb; 
         byte >>= 1;
    }
    
    return mir_byte;
}

uchar_t ByteMirror2(uchar_t b)
{
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4; 
   /* 0x0F = binary: 0000 1111, 0xF0 1111 0000 */
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   /* 0xCC = 1100 1100, 0x33 = 0011 0011 */
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   /*0xAA = 1010 1010, 0x55 = 0101 0101 */
   
   return b;
}

int Chk2_26Bit(uchar_t num)
{
    uchar_t mask = 1 << 1 | 1 << 5 ; /*00100010*/
    return !((num & mask) ^ mask); /*xor=> equal = 0 */
}


int Chk1_26Bit(uchar_t num)
{
    uchar_t mask = 1 << 1 | 1 << 5 ; /*00100010*/
    return !!(num & mask);
}

uchar_t Swap_35Bit1(uchar_t num)
{
    /*Extract 3, 5 bit*/
    uchar_t bit3 = (num >> 2) & 1 ;
    uchar_t bit5 = (num >> 4) & 1 ;
    
    num = num & (~(1 << 2));
    num = num & (~(1 << 4));
    
    num = num | (bit5 << 2); /*push 3rd bit*/
    num = num | (bit3 << 4); /*push 5rd bit*/
    
    return num;
}


uchar_t Swap_35Bit2(uchar_t num)
{

     /* Move p1'th to rightmost side */
    unsigned char bit3 =  (num >> 2) & 1;
 
    /* Move p2'th to rightmost side */
    unsigned char bit5 =  (num >> 4) & 1;
 
    /* XOR the two bits */
    unsigned char x = (bit3 ^ bit5);
 
    /* Put the xor bit back to their original positions */
    x = (x << 2) | (x << 4);
 
    /* XOR 'x' with the original number so that the
       two sets are swapped */
    return (num ^ x);
}

/*All 16 Divisable number ending with 0000*/ 
unsigned int Clsst16(const unsigned int num)
{
    unsigned int mask = ~0xF; /*Equal to 1111 1111 ... 0000  its an int, not char*/
    return (num & mask);
}

void Swap(int *x, int *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

uchar_t Cnt1BitsLp(unsigned int num)
{
    unsigned char count = 0; /*max is 32 hence char*/
    
    while (num > 0)
    {
        count += (1 & num);
        
        num >>= 1;
    }
    
    return count;
}

/*Using 'Hamming Weight'*/
uchar_t Cnt1BitsWLp(unsigned int i)
{
     i = i - ((i >> 1) & 0x55555555);        /* add pairs of bits*/
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);  /* quads */
     i = (i + (i >> 4)) & 0x0F0F0F0F;        /* groups of 8 */
     i *= 0x01010101;                        /* horizontal sum of bytes */
     return  i >> 24;               /* return just that top byte (after truncating to 32-bit even when int is wider than uint32_t)*/
}

/*TO FIX*/
/*A float that's cast to an int causes the fractional part to be truncated*/
void PrntFltBts1(float num)
{
    while (num > 0)
    { 
        printf("%d ", ((int)num&1));
        num = (int)num >> 1;
    }
        printf("\n");

/*TO FIX
/*pointer with same number of bytes int = float 32*/
void PrntFltBts2(float *fp)
{

    int i = 0;
    
    // float as an integer pointer cast
    unsigned int* ip = (unsigned int*)fp;
    unsigned int bits = *ip; /*the value*/

    for (i = 31 ; 0 <= i; --i)
    {
        printf("%d", (bits >> i) & 1);

    }
    printf("\n");
}




int main()
{
      unsigned int arr[] = {0, 7, 11, 14, 15};
      unsigned int x = -2;
      uchar_t uchr = 1;
      int y = 5, z = 10;
      int *py = &y, *pz = &z;
      float f = 65.125;
      
      
      printf("Answer Question 1 is %u, %u, %u\n", x, x<<2, x>>2);

      printf("Answer Exercises 1 is %ld\n", Pow2(2,0));
      printf("Answer Exercises 2 loop is %d\n", IsPow2Lp(0));
      printf("Answer Exercises 2 w.loop is %d\n\n", IsPow2WLp(0));
      
      printf("Answer Exercises 3 5+1 is %d\n", Ads1(5));
      printf("Answer Exercises 4 is ");
      Prnt3Bits(arr, 5);
      printf("\n");
      
      printf ("Answer ByteMirror1 is %u\n", ByteMirror1(uchr));
      printf ("Answer ByteMirror2 is %u\n", ByteMirror2(uchr));
      
      printf ("Answer Chk2_26Bit for 99 (01100011) is %d\n", Chk2_26Bit(99));
      printf("Answer Chk1_26Bit for 3 (00000011) is %d\n",Chk1_26Bit(3));
      printf("Answer Swap_35Bit1 for 4 (0000 0100) is 16 (0001 0000) %u\n",Swap_35Bit1(4));
      printf("Answer Swap_35Bit2 for 4 (0000 0100) is 16 (0001 0000) %u\n\n",Swap_35Bit2(4));
      
      printf ("Answer Clsst16 for 22 is %d\n", Clsst16(16));
      
      printf ("Before the swap y = 5, z = 10\n"); 
      Swap(py, pz);
      printf ("After the swap y = %d, z =%d This is Cool!\n\n", y, z);
      printf ("Number of On bits in 1010 1010 (170) is (loop) %d \n", Cnt1BitsLp(170));
      printf ("Number of On bits in 1010 1010 (170) is (wloop) %d \n", Cnt1BitsWLp(170));
      
      PrntFltBts1(65.125);
      /*PrntFltBts2(&f);*/
      
    return ;		
}


