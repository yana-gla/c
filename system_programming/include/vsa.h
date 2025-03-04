/*******************************************************************************
* File: vsa.h
*
* Purpose:
*   Interface for a Variable Size Allocator (VSA) that manages memory blocks
*   within a pre-allocated memory space. Provides functionality for initializing
*   the allocator, allocating variable-sized blocks, freeing blocks, and
*   querying the largest available block size.
*
* Author:
*   Yana Glazer
*
*******************************************************************************/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> 								/* size_t */

typedef struct vsa vsa_t;

/*******************************************************************************
* VSAInit
* Initializes a new Variable Size Allocator in the provided memory space.
*
* Parameters:
* 	memory - pointer to allocated memory for the VSA
* 	memory_size - size of the provided memory in bytes
*
* Returns:
* 	pointer to initialized Variable Size Allocator
* 	NULL if initialization failed (insufficient memory size or if vsa is NULL)
*
* Complexity: O(1)
*******************************************************************************/
vsa_t* VSAInit(void* memory, size_t memory_size);

/*******************************************************************************
* VSAAllocate
* Allocates a variable sized block from the VSA
*
* Parameters:
*	vsa - pointer to the VSA
*	memory_size - desired size of block in bytes
*
* Returns:
* 	pointer to the allocated block on success
* 	NULL if no blocks of given size are available or if vsa is NULL
*
* Complexity: O(n) where n is the number of blocks
*******************************************************************************/
void* VSAAllocate(vsa_t* vsa, size_t memory_size);

/*******************************************************************************
* VSALargestBlock
* Gets size of largest free block in VSA
*
* Parameters:
* 	vsa - pointer to the VSA
*
* Returns:
* 	size of largest available block
* 	0 if no blocks available or if vsa is NULL
*
* Complexity: O(n) where n is the number of blocks
*******************************************************************************/
size_t VSALargestBlock(vsa_t* vsa);

/*******************************************************************************
* VSAFree
* Returns a previously allocated block to the VSA; undefined behavior with
* invalid pointer
*
* Parameters:
* 	block - pointer to the block to be freed
*
* Returns: void
*
* Complexity: O(1)
*******************************************************************************/
void VSAFree(void* block);

#endif

