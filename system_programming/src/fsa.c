#include <stdlib.h> /*NULL*/
#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define METADATA_SIZE sizeof(fsa_t)
#define ROUND_UP_TWS(size)  (size & (WORD_SIZE - 1)) == 0 ? \
								size : ((size & ~(WORD_SIZE - 1)) +  WORD_SIZE) 
								/*TWS = to word size, rounds up 8, 16, 32..*/

struct fsa 
{
	size_t off_free_block; /*holds offset from begining to free block, 
							not necasirily to first*/
};


/******************************************************************************/
size_t FSASuggestSize(size_t block_size, size_t num_blocks)
{
	size_t rounded_block_size = ROUND_UP_TWS(block_size);
	return ((rounded_block_size * num_blocks) + METADATA_SIZE);
}

/******************************************************************************/
fsa_t* FSAInit(void* memory, size_t memory_size, size_t block_size)
{
	size_t num_blocks = 0, i = 1;
	size_t *runner = memory;
	int runner_increment = 0;
	
	/*initialization fail if memory not valid, insufficient memory*/
	if ((NULL == memory) ||
		 block_size == 0 || /*division by block_size*/
		 (memory_size < (ROUND_UP_TWS(block_size) + METADATA_SIZE)))
		 				 /*ensures at least one block, line 45*/
	{
		return NULL;
	}

	/*round up block size to word size*/
	block_size = ROUND_UP_TWS(block_size);
	num_blocks = (memory_size - METADATA_SIZE) / block_size;
	runner_increment = block_size / WORD_SIZE;
	
	*runner++ = METADATA_SIZE; /*off_free_block*/
	
	/*update in each block offset of next free block, except the last one*/
	while (i < num_blocks)
	{
		*runner = METADATA_SIZE + block_size * i++;
		runner += runner_increment;
	}
	/*last block sign with 0*/
	*runner = 0;
	
	return ((fsa_t*)memory);
}

/******************************************************************************/
void* FSAAllocate(fsa_t* fsa)
{
	size_t *free_block = NULL;
	
	/*check if there is avilable blocks*/
	if (NULL != fsa && 0 != fsa->off_free_block )
	{
		/*update address of free block*/
		free_block = (size_t*)((char*)fsa + fsa->off_free_block);
		
		/*update new next free block*/
		fsa->off_free_block = *free_block;
	}
	
	return ((void*)free_block);
}

/******************************************************************************/
size_t FSACountFree(fsa_t* fsa)
{
	size_t counter = 0;
	size_t *pointer = (size_t*)fsa;
	
	if (NULL == fsa)
	{
		return 0;
	}
	
	while (0 != *pointer)
	{
		++counter;
		pointer = (size_t*)((char*)fsa + *pointer);
	}
	
	return counter;
}

/******************************************************************************/
void FSAFree(fsa_t* fsa, void* block)
{
	if (NULL == fsa || NULL == block)
	{
		return;
	}
	
	*(size_t*)block = fsa->off_free_block;
	fsa->off_free_block =(size_t)((char*)block - (char*)fsa);
}



