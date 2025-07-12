/*Changed after Reviewd by Omri 02/02/2025*/
/*Changed after mentors review  08/02/2025*/

#include <stdlib.h>/*malloc etc.*/
#include <stdio.h> /*printf*/
#include <string.h>/*memcpy*/
#include <assert.h>/*assert*/
#include "vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5
#define MIN_CAPACITY 8
#define MAX(a, b) ((a > b) ? a : b)

struct vector
{
	size_t element_size;
	size_t size;        /*current size*/
	size_t capacity;
	void *head_vector;
};

/* Allocating memory for vector type and vector data*/
vector_t* VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *p_vector = (vector_t*)malloc(sizeof(vector_t));
	if (NULL == p_vector)
	{
		return NULL;
	}
	
	capacity = MAX(MIN_CAPACITY, capacity);
	
	p_vector->head_vector = (void*)calloc(capacity, element_size);
	
	if (NULL == p_vector->head_vector)
	{
		free (p_vector);
		return NULL;
	}
	
	p_vector->element_size = element_size;
	p_vector->size = 0;
	p_vector->capacity = capacity;
	
	return p_vector;
}

/*Freeing memory*/
void VectorDestroy(vector_t* vector)
{
	assert(NULL != vector);
	
	free(vector->head_vector);
	vector->head_vector = NULL;
	
	memset(vector, 0, sizeof(*vector));

	free(vector);
}

/*Returning pointer of the element in given index of the vector*/
/*Does'nt increase size*/
void* VectorAccessElement(const vector_t* vector, size_t index)
{
	assert(NULL != vector);
	
	if (index >= vector->size)
	{
		return NULL;
	}
	
	return ((char*)vector->head_vector + (index * vector->element_size));
}

/*0- Pushed, 1 - allocation failed */
int VectorPushBack(vector_t* vector, const void* data)
{
	/*void *tmp_head = NULL;*/
	
	assert(NULL != vector && NULL != data);
	
	if (vector->size == vector->capacity)
	{
		if (2 == VectorReserve(vector, GROWTH_FACTOR * vector->capacity))
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
	
	if (vector->size / vector->capacity < SHRINK_FACTOR)
	{
		if (2 == VectorShrink(vector))
		{
			return ;
		}
	}
	
	return;
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

/*Increase capacity of vector to new_capacity if it bigger than the current
  capacity of the vector.
  Return value- capacity increased = 0, not = 1, allocation problem = 2*/
int VectorReserve(vector_t* vector, size_t new_capacity)
{
	void *temp_head = NULL;
	assert(NULL != vector);
	
	if (new_capacity > vector->capacity)
	{
		temp_head = (void*)realloc(vector->head_vector, new_capacity * vector->element_size);
		
		if (NULL == temp_head)
		{
			return 2;
		}
		vector->head_vector = temp_head;
		
		vector->capacity = new_capacity;
		return 0;
	}
	
	return 1;
}


/*If vector size is less than shrink factor capacity, shrink capacity*/
/*0- Shrinked,  1 - Not shrinked, , 2- realocation failed*/

int VectorShrink(vector_t* vector)
{
	void *temp_head = NULL;
	size_t new_capacity = MAX(vector->size * GROWTH_FACTOR, MIN_CAPACITY);
	
	assert(NULL != vector);
	
	if (new_capacity < vector->capacity)
	{
		temp_head = (void*)realloc(vector->head_vector, new_capacity * vector->element_size);
		if (NULL == temp_head)
		{
			return 2;
		}
		vector->head_vector = temp_head;
		vector->capacity = new_capacity;
		return 0;
	}
	
	return 1;
}







