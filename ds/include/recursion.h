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

Node *FlipList(Node *head);

/*O(n^2*)*/
stack_t *SortStack(stack_t *stack);

int Strlen(const char *string);
int Strcmp(const char *str1, const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strcat(char *dest, const char *src);
char *Strstr(const char *haystack, const char *needle);



#endif /* RECURSION_H */
