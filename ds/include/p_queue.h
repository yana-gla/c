/******************************************************************************
*                          Author Yana Glazer                                *                           Date 21/02/2025                                 *                          Reviewed by ____         
*                
* 								Purpose:
*   Implementation of a priority queue, ordering is defined by user-defined
*   comparator function. Data is saved and passed by reference only.
*******************************************************************************/

#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

typedef struct p_queue p_queue_t; 

typedef int (*cmp_func_t) (const void* data1, const void* data2);
typedef int (*is_match_t) (const void* data, const void* param);

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


#endif /*P_QUEUE_H*/
