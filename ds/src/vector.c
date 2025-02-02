#include <stdlib.h>/*malloc etc.*/
#include <stdio.h> /*printf*/
#include <string.h>/*memcpy*/
#include <assert.h>/*assert*/
#include "vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5

struct vector
{
	size_t element_size;
	size_t size; /*current size*/
	size_t capacity;
	void *head_vector;
};

/* Allocating memory for vector type and vector data*/
vector_t* VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *p_vector = (vector_t*)calloc(1, sizeof(vector_t));
	p_vector->head_vector = (void*)calloc(capacity * GROWTH_FACTOR, element_size);
	
	if (p_vector == NULL || p_vector->head_vector == NULL)
	{
		printf("Allocation Failed.\n");
		return NULL;
	}
	
	p_vector->element_size = element_size;
	p_vector->size = 0;
	p_vector->capacity = capacity * GROWTH_FACTOR;
	
	return (p_vector);
}

/*Freeing memory*/
void VectorDestroy(vector_t* vector)
{
	assert(NULL != vector);
	
	free(vector->head_vector);
	vector->head_vector = NULL;
	
	free(vector);
	vector = NULL;
}

/*Returning pointer of the element in given index of the vector*/
/*does'nt increase size!*/
void* VectorAccessElement(const vector_t* vector, size_t index)
{
	assert(NULL != vector && index < vector->capacity);
	
	return ((char*)vector->head_vector + index * vector->element_size);
}

int VectorPushBack(vector_t* vector, const void* data)
{
	assert(NULL != vector && NULL != data);
	
	if (vector->size == vector->capacity)
	{
		if (1 == VectorReserve(vector, GROWTH_FACTOR * vector->capacity))
		{
			return 1;
		}
	}
	
	memcpy((char*)vector-> head_vector + vector->size*vector->element_size, 
			data, vector->element_size);
			
	++vector->size;
			
	return 0;
}

/*Removing last element*/
void VectorPopBack(vector_t* vector)
{
	assert(NULL != vector && vector->size > 0);
	--vector->size;
}

/*Returns the capacity of the vector*/
size_t VectorCapacity(const vector_t* vector)
{
	assert(NULL != vector);
	return (vector->capacity);
}

/*Returns the size of the vector (number of current element)*/
size_t VectorSize(const vector_t* vector)
{
	assert(NULL != vector);
	return (vector->size);
}

/*Increase capacity of vector to new_capacity if it bigger then current capacity*/
/*Return value- capacity increased = 0, not = 1, allocation problem = 2*/
int VectorReserve(vector_t* vector, size_t new_capacity)
{
	assert(NULL != vector);
	
	if (new_capacity > vector->capacity)
	{
		vector->head_vector = (void*)realloc(vector->head_vector, new_capacity*vector->element_size);
		
		if (NULL == vector->head_vector)
		{
			printf("Reallocation Failed.\n");
			return 2;
		}
		
		vector->capacity = new_capacity;
		return 0;
	}
	
	return 1;
}


/*If vector size is less than shrink factor capacity, shrink capacity*/
/* 1 - Not shrinked, 0- Shrinked*/

int VectorShrink(vector_t* vector)
{
	assert(NULL != vector);
	
	if ((vector->size / vector->capacity) < SHRINK_FACTOR)
	{
		vector->capacity *= SHRINK_FACTOR;
		return 0;
	}
	
	return 1;
}







