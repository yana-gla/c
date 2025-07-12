/******************************************************************************
* File: FSA.h
*
* Purpose:
*   Implementation for a fixed size allocator (FSA). 
*
* Author:
*   Yana GLazer 02/03/25, Last changed 07/03/25
*
*Reviewd by:
	Shavit Gillis 03/03/25
	Gil Lifshitz 03/03/25
******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /*for size_t*/

typedef struct fsa fsa_t;

/*******************************************************************************
* FSASuggestSize
* Suggesting number of bytes for memory allocation. 
* Parameters:
*	block_size- size of single block
*	num_blocks- number of block needed
* Return:
*	returns number of required bytes for memory allocation
* Complexity:
*	O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t block_size, size_t num_blocks);

/*******************************************************************************
* FSAInit
* Initializing new FSA in given memory.
* Parameters:
*	memory- pointer to allocated memory by user
*	memory_size - size of allocated memory in bytes
*	block_size - size of needed blocks in bytes
* Return:
*	returns pointer to new fsa, NULL if initialization failed
* Complexity:
*	O(n), n- num of blocks
*memory pointer is promised to be aligned from user
*******************************************************************************/
fsa_t* FSAInit(void* memory, size_t memory_size, size_t block_size);

/*******************************************************************************
* FSAAllocate
* Allocate single memory block from fsa
* Parameters:
*	fsa- pointer to fsa
* Return:
*	returns pointer to avilable memory block,
	NULL if fsa NULL or there is'nt enough space
* Complexity:
*	O(1)
*******************************************************************************/
void* FSAAllocate(fsa_t* fsa);

/*******************************************************************************
* FSACountFree
* Counts number of free blocks in fsa
* Parameters:
*	fsa- pointer to fsa
* Return:
*	number of free blocks
* Complexity:
*	O(n), n- num of blocks
*******************************************************************************/
size_t FSACountFree(fsa_t* fsa);

/* free the given block in the fsa */
/*******************************************************************************
* FSAFree
* Frees given blocks in fsa, UNB double freeing or invalid pointer
* Parameters:
*	fsa- pointer to fsa
*	block- pointer to block to free
* Return:
*	void
* Complexity:
*	O(1)
*******************************************************************************/
void FSAFree(fsa_t* fsa, void* block);

#endif /* FSA_H */
