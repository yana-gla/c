/******************************************************************************/
/*                          Author Yana Glazer                                */
/*                           Date 21/02/2025                                  */
/*                          Reviewed by ____                                  */
/******************************************************************************/

#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

#include "sorted_ll.h"

typedef struct p_queue p_queue_t; 

p_queue_t *PQCreate(is_before_t is_before);
void PQDestroy(p_queue_t *queue);
int PQIsEmpty(const p_queue_t* p_queue);
void PQRemove(p_queue_t *p_queue, match_func_t is_match, void *param);
int PQEnqueue(p_queue_t *p_queue, void *data);
void PQDequeue(p_queue_t* p_queue);
void *PQPeek(const p_queue_t* p_queue);
size_t PQCount(const p_queue_t* p_queue);
void PQClear(p_queue_t *queue);


#endif /*P_QUEUE_H*/
