/******************************************************************************/
/*Author Yana Glazer
Reviewd by Liel
*******************************************************************************/

#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*calloc*/
#include "stack.h"

struct stack
{
	void *data;        /*ptr to the stack*/
	size_t index;     /*index to element on stack*/
	size_t type_size; /*size of single element*/
	size_t capacity; /*capacity of stack*/
};
	
/*Alloction for stack struct and data base*/ 
stack_t *Create(size_t capacity, size_t element_size)
{
	stack_t *stk = (stack_t*) calloc(1 ,sizeof(stack_t));
	stk->data = (void*) calloc(capacity, element_size);
	
	if (NULL == stk || NULL == stk->data)
	{
		printf("Allocation of stack Failed.\n");
		return NULL;
	}

	stk->index = 0;
	stk->type_size = element_size;
	stk->capacity = capacity;
	
	return (stk);
}

/*freeing the allocation from create function*/
/*The function does'nt handle NULL pointer*/
void Destroy(stack_t* stk)
{
	free(stk->data);	
	stk->data = NULL;
	
	free(stk);
	stk = NULL;
}

/*remove element from the stack*/
/*The function does'nt handle NULL pointer*/
/*                            Pop beyond Zero index*/                              
void Pop(stack_t* stk)
{
	--(stk->index);
}

/*add element to the stack*/
/*The function does'nt handle NULL pointers*/
/*                           Pushing beyond capacity */ 
void Push(stack_t* stk, const void* val)
{	
	
	memcpy((char*) (stk -> data) + (stk->index) * (stk->type_size),
	                                                  val, stk->type_size) ;
	++(stk -> index);
}	

/*function returns pointer to the top element of the stack*/
/*The function does'nt handle NULL pointer*/
void *Peek(const stack_t* stk)
{
	return (char*)(stk -> data) + (stk -> index - 1) * (stk -> type_size);
}

/* true/ false function fo empyy */ 
int IsEmpty(const stack_t* stk)
{
	return (stk->index == 0 ? 1 : 0);
}

/*function returns the current index on the stack*/
/*The function does'nt handle NULL pointer*/
size_t Size(const stack_t* stk)
{
	return (stk->index);
}

/*the function returns the total capacity / size of the stack */
/*The function does'nt handle NULL pointer*/
size_t Capacity(const stack_t* stk)
{
	return (stk->capacity);
}





