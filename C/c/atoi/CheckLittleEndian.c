#include <stdio.h>

#define CHECK_LITTLE_ENDIAN() (*(short*)"\0\1" == 0x0100)

int CheckLittleEndian()
{
  unsigned int x = 1;
  char *c = (char*) &x;
  return (int)*c;
}


int main()
{
	printf("CheckLittleEndian function is %d\n", CheckLittleEndian());
	printf("CHECK_LITTLE_ENDIAN MAKRO is %d\n", CHECK_LITTLE_ENDIAN() );

	return 0;
}
