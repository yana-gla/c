#include <stdio.h>
#include "stack.h"


struct stack {
int i;
float b;
};



int main ()
{
	struct stack_t ya ;
	stack_t *stack_ptr = NULL;
	
	int capacity = 10;
	int element_size = 4;
	
	int x = 27;
	int y = 3;
	int z = 1991;
	int *peek_ptr = NULL;
	
	stack_ptr = Create(capacity, element_size);
	
	Push(stack_ptr, &x);
	printf("One Element has been pushed to stack..\n");
	printf("Return of Is_Empy is %d\n\n", IsEmpty(stack_ptr));
	Pop(stack_ptr);
	printf("Element has been removed from stack..\n");
	printf("Return of Is_Empy is %d\n\n", IsEmpty(stack_ptr));
      
	Push (stack_ptr, &y);
	Push (stack_ptr, &z);
	printf("Two elements has been pushed to stack..\n");
	
	peek_ptr = Peek(stack_ptr);
	printf("Peek is %d\n", *(int*)peek_ptr);
	
	printf("Size of Stack is %ld\n", Size(stack_ptr));
	printf("Capacity of Stack is %ld\n", Capacity(stack_ptr));
	
	Destroy(stack_ptr);
	
	return (0);

}
