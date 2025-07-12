#include <string.h> /*for strncmp*/
#include "recursion.h"

/****************************  Fibonacci  *************************************/
/*0 indicates error*/
size_t FibonacciIterative(int element_index)
{
	int i = 0;
	size_t a0 = 1, a1 = 1;
	
	if (element_index < 1)
	{
		return (0);
	}
	
	while (i < element_index -1 )
	{
		a1 = a0 + a1;
		a0 = a1 - a0;
		++i;
	}
	return a0;
}

size_t FibonacciRecrusive(int i)
{
	
	if (i < 1)
	{
		return (0);
	}
	
	if (i <= 2)
	{
		return 1;
	}
	
	return (FibonacciRecrusive(i-1) + FibonacciRecrusive(i - 2));
}

/****************************  FlipList  **************************************/
Node *FlipList(Node *head)
{
	Node *new_head = NULL;
	if(NULL == head || NULL == head -> next)
	{
		return head;
	}
	/*recursion call- until the end of the list*/
	new_head = FlipList(head->next);
	
	head->next->next = head;
	head->next = NULL;
	
	return new_head;	
}

/****************************  Stack  *****************************************/
static void InsertInSortedOrder(stack_t *stack, int num)
{
	int temp = 0;
	/*Base case: stack empty / current element greater than top*/
	if (IsEmpty(stack) || num > *(int*)Peek(stack))
	{
		Push(stack, &num);
		return;
	}
	
	/*if top greater than num, remove top and recur*/
	temp = *(int*)Peek(stack);
	Pop(stack);
	InsertInSortedOrder(stack, num);
	
	Push(stack, &temp);
}


stack_t *SortStack(stack_t *stack)
{
	int top = 0;
	/*pop and remember each elemnt in a frame*/
	if (!IsEmpty(stack))
	{
		top = *(int*)Peek(stack);
		Pop(stack);
	
		/*sort remaining stack*/
		SortStack(stack);
		
		InsertInSortedOrder(stack, top);
	}
	return stack;
}

/****************************  String  ****************************************/

int Strlen(const char *string)
{
	if ('\0' == *string )
	{
		return 0;
	}
	
	return (1 + Strlen(++string));
}

int Strcmp(const char *str1, const char *str2)
{
	/*Base case- different or end of string*/
	if ((*str1 == '\0') || (*str1 != *str2))
	{
		return (*str1 - *str2);
	}
	return Strcmp(++str1, ++str2);
}

char *Strcpy(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = '\0';
		return dest;
	}
	
	*dest = *src;
	Strcpy(dest+1, src+1);

	return dest;
}

char *Strcat(char *dest, const char *src)
{
	if ('\0' == *dest)
	{
		return Strcpy(dest, src);
	}
	
	Strcat(dest + 1, src);
	return dest;
}
static char *StrstrHelper(const char *haystack, const char *needle, size_t needle_len);

char *Strstr(const char *haystack, const char *needle)
{
	size_t needle_length =	Strlen(needle);

	return StrstrHelper(haystack, needle, needle_length);
}

static char *StrstrHelper(const char *haystack,
						 const char *needle,
						 size_t needle_length)
{
	if ('\0' == *needle || 0 == strncmp(haystack, needle, needle_length))
	{
		return (char*)haystack;
	}
	if ('\0' == *haystack)
	{
		return NULL;
	}
	
	return Strstr(haystack + 1, needle);
}



