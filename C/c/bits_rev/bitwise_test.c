#include <stddef.h>
#include "bitwise.h"
#include <stdio.h>



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
      
      PrntFltBts1(f);
      PrntFltBts2(f);
      
    return 0;		
}

