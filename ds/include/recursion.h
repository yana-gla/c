/*******************************************************************************
* File: recursion.h
*
* Purpose:
*   Implementation of recursive Fibonacci, Flip SLL, Stack sort and standard
*	String functions
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   Shavit Gilis
*
*Date: 17/03/2025
*Last Update: 18/03/2025
*******************************************************************************/
#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /*size_t*/
#include "stack.h" /*own header for stack implementation*/

typedef struct Node Node;
struct Node{
	Node *next;
	void *data;
};

/*Fibonacci*/
size_t FibonacciIterative(int element_index);
size_t FibonacciRecrusive(int i);

/*FlipList*/
Node *FlipList(Node *head);

/*SortStack*/
/*O(n^2*)*/
stack_t *SortStack(stack_t *stack);

/*String*/
int Strlen(const char *string);
int Strcmp(const char *str1, const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strcat(char *dest, const char *src);
char *Strstr(const char *haystack, const char *needle);

#endif /* RECURSION_H */
