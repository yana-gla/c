#include <stack.h>


void SortStack(stack_t *stack)
{
	
	size_t size = Size(stack);
	int num = 0;
	
	stack_t *stack_h = Create(size, sizeof(int));
	
	while (!IsEmpty(stack))
	{
		num = *(int*)Peek(stack);
		Pop(stack);
		Push(stack_h, &num);
	}
	
	while (!IsEmpty(stack_h))
	{
		num = *(int*)Peek(stack_h);
		Pop(stack_h);
		
		if (!IsEmpty(stack) num  )
		Push(stack, &num);
		
		
	}
}
