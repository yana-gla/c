#include <stdio.h>
#include "vector.h"



int main()
{
	size_t element_size = 4, capacity = 8;
	int *idx = NULL;
	int data1 = 199, data2 = 299;
	

	vector_t *vec = VectorCreate(element_size, capacity);
	printf("Vector created..\n");
		
	printf("size is %lu\n", VectorSize(vec));
	printf("capacity is %lu\n\n", VectorCapacity(vec));
	
	idx = VectorAccessElement(vec, 1);
	*idx = 27;
	printf("%d\n", *(int*)VectorAccessElement(vec, 1));
	*(int*)VectorAccessElement(vec, 2) = 3;
	printf("%d\n", *(int*)VectorAccessElement(vec, 2));
	printf("%d\n\n", *(int*)VectorAccessElement(vec, 15));
	
	printf("size is %lu\n\n", VectorSize(vec));
	
	printf("Psuback command #1..\n");
	VectorPushBack(vec, &data1);
	printf("size is %lu\n", VectorSize(vec));
	printf("Psuback command #2..\n");
	VectorPushBack(vec, &data2);
	printf("size is %lu\n", VectorSize(vec));
	printf("Popback command..\n");
	VectorPopBack(vec);
	printf("size is %lu\n\n", VectorSize(vec));
	
	printf("Shrink command..\n");
	printf ("Return value from shrink fun %d\n", VectorShrink(vec));
	printf("Capacity is %lu\n\n", VectorCapacity(vec));
	
	printf("Reserved command to 32..\n");
	printf ("Return value from reserved fun %d\n", VectorReserve(vec, 32));
	printf("Capacity is %lu\n\n", VectorCapacity(vec));
	
	printf("Destroying vector..\n");
	VectorDestroy(vec);
	
	/*printf("Capacity is %lu\n\n", VectorCapacity(vec));*/
	
	
	
	
	
	
	
	
	
	return 0;
}
