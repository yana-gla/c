#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

typedef struct vector vector_t;

vector_t* VectorCreate(size_t element_size, size_t capacity);   
void VectorDestroy(vector_t* vector);
void* VectorAccessElement(const vector_t* vector, size_t index);   
int VectorPushBack(vector_t* vector, const void* data);   
void VectorPopBack(vector_t* vector);   
size_t VectorCapacity(const vector_t* vector);   
size_t VectorSize(const vector_t* vector);   
int VectorReserve(vector_t* vector, size_t new_capacity);   
int VectorShrink(vector_t* vector);   

#endif /* VECTOR_H */
