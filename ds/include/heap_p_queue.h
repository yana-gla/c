/*******************************************************************************
*                          Author Yana Glazer                                *                           Date 27/03/2025                                 *                          Reviewed by ____         
*                
* 								Purpose:
*  Implementation of a priority queue, with Heap DS, ordering is defined by 
*  user-defined comparator function. Data is saved and passed by reference only.
*******************************************************************************/
#ifndef __HEAP_P_QUEUE_H__
#define __HEAP_P_QUEUE_H__

#include <stddef.h>

typedef struct p_queue p_queue_t; 

typedef int (*cmp_func_t) (const void* data1, const void* data2);
typedef int (*is_match_t) (const void* data, void* param);

p_queue_t *PQCreate(cmp_func_t cmp_func);
void PQDestroy(p_queue_t *queue);
int PQIsEmpty(const p_queue_t* p_queue);
void *PQRemove(p_queue_t *p_queue, is_match_t is_match, void *param);
int PQEnqueue(p_queue_t *p_queue, void *data);
void PQDequeue(p_queue_t* p_queue);
/*returns pointer to data of the first element to dequeue, first element in queue*/
void *PQPeek(const p_queue_t* p_queue);
size_t PQCount(const p_queue_t* p_queue);
void PQClear(p_queue_t *queue);

#endif /*HEAP_P_QUEUE_H*/
