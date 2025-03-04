/******************************************************************************
* File: FSA.h
*
* Purpose:
*   Implementation for a fixed size allocator (FSA). 
*
* Author:
*   Yana GLazer
*
******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /*for size_t*/

typedef struct fsa fsa_t;

/*******************************************************************************
* Suggesting number of bytes for memory allocation. 
* Parameters:
*	block_size- size of single block
*	num_blocks- number of block needed
*	
* Return:
*	returns number of required bytes for memory allocation
* Complexity:
*	O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t block_size, size_t num_blocks);

/* the client will do external malloc and pass memory block to init, */
/* the init will take the block and will initiate it to fsa */
/* memory_size should be return value from FSASuggestSize */
/* any lower number will cause less blocks */

/*function will return pointer to fsa, NULL if initialization failed (memory 
*	not valid, insufficient memory)
*memory pointer is promised to be aligned from user
* Complexity: O(n)*/
fsa_t* FSAInit(void* memory, size_t memory_size, size_t block_size);

/* returns pointer to avilable memory block, o.w NULL  */
void* FSAAllocate(fsa_t* fsa);

/* return number of free_blocks. O(n) */
size_t FSACountFree(fsa_t* fsa);

/* free the given block in the fsa */
void FSAFree(fsa_t* fsa, void* block);

#endif
