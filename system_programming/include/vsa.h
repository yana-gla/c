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

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/*******************************************************************************
* VSAInit
* Creates new variable size allocator
* 
* Parameters:
* 	memory - pointer to allocated memory for vsa
* 	memory_size - size of allocated memory in bytes
*
* Returns:
* 	pointer to created vsa
* 	NULL if vsa is NULL or not enough memory
*
* Time Complexity: O(1)
*******************************************************************************/
vsa_t* VSAInit(void* memory, size_t memory_size);

/*******************************************************************************
* VSAAllocate
* Allocates requested sized block from vsa
*
* Parameters:
*	vsa - pointer to vsa
*	memory_size - Requested memory size
*
* Returns:
* 	On success- pointer to allocated block
* 	NULL if allocation did'nt happen due lack of space
*
* Time Complexity: O(n), n- number of allocated blocks in vsa
*******************************************************************************/
void* VSAAllocate(vsa_t* vsa, size_t memory_size);

/*******************************************************************************
* VSALargestBlock
* Returns size of largest free block in vsa
*
* Parameters:
* 	vsa - pointer to vsa
*
* Returns:
* 	size of largest free block (0 is full vsa)
*
* Time Complexity: O(n), n- number of allocated blocks in vsa
*******************************************************************************/
size_t VSALargestBlock(vsa_t* vsa);

/*******************************************************************************
* VSAFree
* Free prevoiusly allocated block in vsa
*
* Parameters:
* 	block - pointer to prevoiusly allocated block in vsa
*
* Returns: void
*
* Time Complexity: O(1)
*******************************************************************************/
void VSAFree(void* block);

#endif /*__VSA_H__*/

