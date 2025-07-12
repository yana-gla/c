#include <stdio.h>


union numbers
{
	int i;
	float f;
	double d;
	};
	
struct X 
{
	int i;
	char c;
	double d;
	short s;
};

struct card 
{
	unsigned int suit :2;
	unsigned int face_value : 4;
} ;

int main()
{
		printf ("%ld\n", sizeof(union  numbers));
		printf ("%ld\n", sizeof(struct X));
		printf ("%ld\n", sizeof(struct card));
		
		return 0;
}


