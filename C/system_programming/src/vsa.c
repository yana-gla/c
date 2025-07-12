#include <assert.h> /*assert*/ 
#include "vsa.h" /*own header*/

#define WORD_SIZE sizeof(size_t)
#define METADATA_SIZE sizeof(vsa_t)
#define ROUND_DOWN_TWS(size) size & ~(WORD_SIZE - 1) /*TWS = to word size,
													 rounds down 33->32..*/
#define ROUND_UP_TWS(size)  (size + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1)
#define MAX(a,b) ((a > b) ? a : b)
#define ABS(x) ((x > 0) ? x : (-x))
#define NEXT_META(adr) ((long*)((char*)adr + WORD_SIZE + (ABS(*adr))))
#define END ((long)-1) /*end value in memory*/

struct vsa{
	long block_size;
};

static void VSADefrag(long *free_memory);

/******************************************************************************/

vsa_t* VSAInit(void* memory, size_t memory_size)
{
	/*round down memory to word size*/
	memory_size = ROUND_DOWN_TWS(memory_size);
	
	if (NULL == memory || memory_size < 2 * METADATA_SIZE) /*2 for start and end META*/
	{
		return NULL;
	}
	
	/*free memory ahead*/
	*(long*)memory = memory_size - 2 * METADATA_SIZE;
	
	/*in the end zero free memory, symbol with END*/
	*(long*)((char*)memory + memory_size - METADATA_SIZE) = END;
	
	return (vsa_t*)memory;
}

/******************************************************************************/

void* VSAAllocate(vsa_t* vsa, size_t memory_size)
{
	long *runner = (long*)vsa, *free_block = NULL;
	long next_free_space = 0;
	int not_found = 1;
	memory_size = ROUND_UP_TWS(memory_size);

	assert(NULL != vsa);
	assert(0 < memory_size);/*check if neccasery*/
	
	while (not_found && (END != *runner))
	{
		if (*runner >= 0)
		{
			VSADefrag(runner); /*combine free consecutive blocks (until first negative)*/
		}

		next_free_space = *runner - memory_size;
		if (next_free_space >= 0)
		{
			/*pointer to free block*/
			free_block = (long*)((char*)runner + METADATA_SIZE); 
			/*update occupancy current block*/
			*runner = -memory_size;
			not_found = 0;
		}
		if(next_free_space > 0)
		{
			/*update after the block, amount of free space*/
			*(long*)((char*)free_block + memory_size) = next_free_space - METADATA_SIZE;
		}
		/*jump to next metadata*/
		runner = NEXT_META(runner); 
	}
	return free_block;
}
/******************************************************************************/

/*should be long*/
size_t VSALargestBlock(vsa_t* vsa)
{
	long max_size = 0;
	long *runner = (long*)vsa;
	
	assert(NULL != vsa);

	while (END != *runner)
	{
		if (*runner >= 0)
		{
			VSADefrag(runner);
		}

		max_size = MAX(*runner, max_size);
	
		/*jump to next metadata*/
		runner = NEXT_META(runner); 
	}
	return (size_t)max_size;
}
/******************************************************************************/

void VSAFree(void* block)
{
	long *meta_block = (long*)((char*)block - METADATA_SIZE);
	
	if (NULL == block)
	{
		return;
	}
	
	*meta_block = ABS(*meta_block);
}
/*******************************   Static function   **************************/

/*Merges Free consecutive blocks*/
static void VSADefrag(long *free_memory)
{
	long *next_block = NULL;
	
	if (0 > *free_memory)
	{
		return;
	}
	
	next_block = (long*)((char*)free_memory + METADATA_SIZE + *free_memory);
	
	while (*next_block >= 0)
	{
		*free_memory += *next_block + METADATA_SIZE;
		next_block =(long*)((char*)next_block + METADATA_SIZE + *next_block);
	}
}

/******************************************************************************/
