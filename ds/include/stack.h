/*************************************************************************
Author: Yana Glazer

Implementation Data Struct STACK 

Reviwed by: Liel YIzhak 27.01.25

27/01/2025
*************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /*for size_t*/

typedef struct stack stack_t;

/*creates new stack, capacity is number of elemnts in stack,
 element size is size of single elemnt*/
stack_t *Create(size_t capacity, size_t element_size);
void Push(stack_t* , const void*); 
int IsEmpty(const stack_t*);
void Pop(stack_t*);
/*Showing without removing the top elemnt on stack*/
void *Peek(const stack_t*);
/*Returns number of element that currently in the stack*/
size_t Size(const stack_t*);

size_t Capacity(const stack_t*);
void Destroy(stack_t*); 

#endif /*closing STACK_H */
