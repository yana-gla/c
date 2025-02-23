#include <stdio.h> /* For printf */
#include <assert.h> /* For assert */
#include "p_queue.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

int amount_of_tests = 0;

int TestPQEnqueueDequeue();
int TestPQClearRemove();
int TestPQCountEmpty();
static int CompareFunc(const void* first, const void* second);
int MatchFunc(const void* first, const void* second);

int main(void)
{
	int result = 0;
	result += TestPQEnqueueDequeue();
	result += TestPQCountEmpty();
	result += TestPQCountEmpty();
	
	if (result == amount_of_tests)
	{
		printf(GREEN "\n🫡️ All tests completed successfully 🫡️\n\n" UNFORMAT);
	}
	
	else
	{
		printf(RED "\nFAILED tests! Check your program!\n" UNFORMAT);
	}
	return (0);
}

/*Prioratize by value*/
static int CompareFunc(const void* first, const void* second)
{
	return (*(int*) first - *(int*) second);
}


int MatchFunc(const void* first, const void* second)
{
	return (*(int*) first == *(int*) second);
}

int TestPQClearRemove()
{
	int a = 1;
	int b = 2;
	int c = 1;
	int d = 16;
	int h = -5;
	p_queue_t* queue = NULL;
	
	++amount_of_tests;
	
	queue = PQCreate(CompareFunc);
	PQEnqueue(queue, &d);
	PQEnqueue(queue, &a);
	PQEnqueue(queue, &b);
	PQEnqueue(queue, &c);
	
	if (PQIsEmpty(queue) != 0)
	{
		printf(RED "Failed TestPQClearRemove. Got %d and expected 0\n" UNFORMAT, PQIsEmpty(queue)); 
		return (-1); 	
	}
	
	PQClear(queue);
	
	if (PQIsEmpty(queue) != 1)
	{
		printf(RED "Failed TestPQClearRemove. Got %d and expected 1\n" UNFORMAT, PQIsEmpty(queue)); 
		return (-1); 	
	}
	
	PQEnqueue(queue, &d);
	PQEnqueue(queue, &a);
	PQEnqueue(queue, &b);
	PQEnqueue(queue, &c);
	
	PQRemove(queue, MatchFunc, &b);
	
	if (PQCount(queue) != 3)
	{
		printf(RED "Failed TestPQClearRemove. Got %lu and expected 3\n" UNFORMAT, PQCount(queue)); 
		return (-1); 	
	}
	
	PQRemove(queue, MatchFunc, &a);
	
	if (PQCount(queue) != 2)
	{
		printf(RED "Failed TestPQClearRemove. Got %lu and expected 2\n" UNFORMAT, PQCount(queue)); 
		return (-1); 	
	}
	
	PQEnqueue(queue, &h);
	
	if (*(int*) PQPeek(queue) != -5)
	{
		printf(RED "Failed TestPQClearRemove. Got %d and expected -5\n" UNFORMAT, *(int*) PQPeek(queue)); 
		return (-1); 
	}
	
	printf(GREEN "TestPQClearRemove tests completed successfully\n" UNFORMAT);
	return (1);
}

int TestPQCountEmpty()
{
	int a = 1;
	int b = 2;
	p_queue_t* queue = NULL;
	
	++amount_of_tests;
	
	queue = PQCreate(CompareFunc);
	PQEnqueue(queue, &a);
	PQEnqueue(queue, &b);
	
	if (PQCount(queue) != 2)
	{
		printf(RED "Failed TestPQCountEmpty. Got %lu and expected 2\n" UNFORMAT, PQCount(queue)); 
		return (-1); 	
	}
	
	PQDequeue(queue);
	
	if (PQCount(queue) != 1)
	{
		printf(RED "Failed TestPQCountEmpty. Got %lu and expected 2\n" UNFORMAT, PQCount(queue)); 
		return (-1); 	
	}
	
	if (PQIsEmpty(queue) != 0)
	{
		printf(RED "Failed TestPQCountEmpty. Got %d and expected 0\n" UNFORMAT, PQIsEmpty(queue)); 
		return (-1); 	
	}
	
	PQDequeue(queue);
	
	if (PQIsEmpty(queue) != 1)
	{
		printf(RED "Failed TestPQCountEmpty. Got %d and expected 1\n" UNFORMAT, PQIsEmpty(queue)); 
		return (-1); 	
	}
	
	PQDestroy(queue);
	
	printf(GREEN "TestPQCountEmpty tests completed successfully\n" UNFORMAT);
	return (1);
}

int TestPQEnqueueDequeue()
{
	int a = 1;
	int b = 2;
	int c = 1;
	int d = 16;
	p_queue_t* queue = NULL;
	
	++amount_of_tests;
	
	queue = PQCreate(CompareFunc);
	PQEnqueue(queue, &d);
	PQEnqueue(queue, &a);
	PQEnqueue(queue, &b);
	PQEnqueue(queue, &c);
	
	if (*(int*) PQPeek(queue) != 1)
	{
		printf(RED "Failed TestPQEnqueueDequeue. Got %d and expected 1\n" UNFORMAT, *(int*) PQPeek(queue)); 
		return (-1); 
	}
	
	PQDequeue(queue);
	
	if (*(int*) PQPeek(queue) != 1)
	{
		printf(RED "Failed TestPQEnqueueDequeue. Got %d and expected 1\n" UNFORMAT, *(int*) PQPeek(queue));
		return (-1);   
	}
	PQDequeue(queue);
	
	if (*(int*) PQPeek(queue) != 2)
	{
		printf(RED "Failed TestPQEnqueueDequeue. Got %d and expected 2\n" UNFORMAT, *(int*) PQPeek(queue));
		return (-1);   
	}
	PQDequeue(queue);
	
	if (*(int*) PQPeek(queue) != 16)
	{
		printf(RED "Failed TestPQEnqueueDequeue. Got %d and expected 16\n" UNFORMAT, *(int*) PQPeek(queue));
		return (-1);   
	}
	
	PQDestroy(queue);
	
	printf(GREEN "\n\nTestPQEnqueueDequeue tests completed successfully\n" UNFORMAT);
	return (1);
}


