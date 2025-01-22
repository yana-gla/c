#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ElementType { et_str, et_int, et_dbl };

struct Element {
  enum ElementType type;
  	void        *data;
  
};


int main(void)
{

	printf ("%ld\n", sizeof(struct Element));
	struct Element *arr = malloc(sizeof(struct Element) * 3);
	arr[0].type = et_str;
	arr[0].data = strdup("String value");
	
	arr[1].type = et_int;
	arr[1].data = malloc(sizeof(int));
	*((int *)(arr[1].data)) = 5;
	
	arr[2].type = et_dbl;
	arr[2].data = malloc(sizeof(double));
	*((double *)(arr[2].data)) = 27.3;

	/* access the values.. */
	for (int i = 0; i < 3; i++) {
	  switch(arr[i].type) {
		case et_str: printf( "String: %s\n", (char *)(arr[0].data) ); break;
		case et_int: printf( "Integer: %d\n", *((int *)(arr[1].data)) ); break;
		case et_dbl: printf( "Double: %f\n", *((double *)(arr[2].data)) ); break;
	  }
	}

	/* again, ALL data was dynamically allocated, so free each item's data */
	for (int i = 0; i < 3; i++){
	  free(arr[i].data);
	  }
	/* then free the malloc'ed array */
	free(arr);
	
	printf ("%ld\n", sizeof(struct Element));
	printf ("%ld\n", sizeof(et_str ));
	printf ("%ld\n", sizeof(void * ));

return;

}
