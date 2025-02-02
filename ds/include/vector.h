#ifndef __VECTOR_H__
#define __VECTOR_H__


typedef struct vector vector_t;


vector_t* VectorCreate(size_t element_size, size_t capacity); /*Tested*/
void VectorDestroy(vector_t* vector);
void* VectorAccessElement(const vector_t* vector, size_t index); /*Tested*/
int VectorPushBack(vector_t* vector, const void* data); /*Tested*/
void VectorPopBack(vector_t* vector); /*Tested*/
size_t VectorCapacity(const vector_t* vector); /*Tested*/
size_t VectorSize(const vector_t* vector); /*Tested*/
int VectorReserve(vector_t* vector, size_t new_capacity); /*Tested*/
int VectorShrink(vector_t* vector); /*Tested*/


#endif /* VECTOR_H */
