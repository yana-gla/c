/******************************************************************************
* File: scheduler.h
*
* Purpose:
*   <insert file purpose here>
*
* Author:
*   
*
******************************************************************************/

#ifndef __TASK_H__
#define __TASK_H__



#include <sys/types.h>     /* for ssize_t */
#include <time.h>         /*for time_t*/
#include "ilrd_uid.h"

typedef struct task task_t;

/* task to perform -> return the next time the task should run.
 * if there is no next run, return 0
 */
typedef ssize_t (*job_func_t)(void* params);

/* cleanup after the last interval of task (if needed) */
typedef void (*cleanup_func_t)(void* params);


/*Function Creates New Task and set it with user pararmeters*/
/*Returns pointer to task on success, on Failure NULL*/
task_t* TaskCreate(time_t time,    /* absolute time */   /* for add task in scheduler*/
                    job_func_t job_func,
                    void* job_params,
                    cleanup_func_t cleanup_func,
                    void* cleanup_params,
                    ssize_t interval); 

/* Free resources associated with given task */
void TaskDestroy(task_t* task); /* for remove task in scheduler*/

/* Retrieves time associated with given task */
time_t TaskGetTime(task_t* task); /* for start scheduler (peek)*/

/* Sets the time associated with given task */
void TaskSetTime(task_t* task, time_t time); /* for start scheduler (periodic task)*/

/* Retrieves UID associated with given task */
ilrd_uid_t TaskGetUID(task_t* task); /* for add task in scheduler*/

/* Runs task job function - return is the interval, -1 if non-periodic (overwrite bulit-in interval) */
ssize_t TaskRun(task_t* task); /* for start scheduler */

/* Runs task cleanup function */
void TaskCleanUp(task_t* task); /* for start scheduler and stop scheduler */

ssize_t GetInterval(task_t* task);

void SetInterval(task_t* task, ssize_t interval);

#endif


