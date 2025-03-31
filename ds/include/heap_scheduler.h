/******************************************************************************
* File: scheduler.h
*
* Purpose:
*   Implementation of scheduler.
*	The scheduler enables serial execution of operation (tasks) at predetermined
*	time intervals.
*	It should allow for the addition of new tasks, and the removal of
*	irrelevant ones as well.
*
* Author: Yana Glazer
*	24/02/2025
*Reviwed by: Corine Bracha
*	27/03/25
******************************************************************************/
#ifndef __HEAP_SCHEDULER_H__
#define __HEAP_SCHEDULER_H__

#include "ilrd_uid.h"

typedef struct scheduler scheduler_t;

typedef ssize_t (*job_t)(void* params);
typedef void (*cleanup_t)(void* params);

/* O(1) */
scheduler_t* SchedCreate(void);

/* O(n) */
void SchedDestroy(scheduler_t* scheduler);

/* add task to scheduler, O(n) */
ilrd_uid_t SchedAddTask(scheduler_t* scheduler,
                        size_t time,    /* absolute time */
                        job_t job_func,    
                        void* job_params,
                        cleanup_t cleanup_func,
                        void* cleanup_params,
                        size_t interval);
 
/* find task by UID
 * send pointer to task to TaskDestroy()
 * remove task by its uid, O(n) */
int SchedRemoveTaskByUID(scheduler_t* scheduler, ilrd_uid_t uid);

/* set start_time to current global time (once), O(1) */
int SchedStart(scheduler_t* scheduler);

/* stop executing any more tasks in given scheduler, O(1)*/
void SchedStop(scheduler_t* scheduler);

/* clear scheduler, O(n)*/
void SchedClear(scheduler_t* scheduler);

/* checks if scheduler is empty */
int SchedIsEmpty(scheduler_t* scheduler);

/* how many tasks in scheduler */
size_t SchedCount(scheduler_t* scheduler);

#endif



