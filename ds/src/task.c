#include <assert.h> /*assert*/
#include <stdlib.h> /*calloc*/
#include <string.h> /*memset*/
#include "task.h"


struct task
{
    time_t time; /* absolute time */
    ilrd_uid_t uid;
    job_func_t job_func;
    void* job_params;
    cleanup_func_t cleanup_func;
    void* cleanup_params;
    ssize_t interval; /* for non-periodic tasks, set interval to -1 */
};


/******************************************************************************/
task_t* TaskCreate(time_t time,    /* absolute time */   /* for add task in scheduler*/
                    job_func_t job_func,
                    void* job_params,
                    cleanup_func_t cleanup_func,
                    void* cleanup_params,
                    ssize_t interval)
{
	task_t *task = NULL;
	assert(NULL != job_func);
	
	task = (task_t*)calloc(1, sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}
	
	task->time = time;
	task->uid = CreateUID();
	task->job_func = job_func;
	task->job_params = job_params;
	task->cleanup_func = cleanup_func;
	task->cleanup_params = cleanup_params;
	task->interval = interval;
	
	return task;
}
/******************************************************************************/
void TaskDestroy(task_t* task)
{
	assert(NULL != task);
	
	memset(task, 0, sizeof(task_t));
	free(task);
	task = NULL;
}
/******************************************************************************/
time_t TaskGetTime(task_t* task)
{
	assert(NULL != task);
	return (task->time);
}
/******************************************************************************/
void TaskSetTime(task_t* task, time_t time)
{
	assert(NULL != task);
	task->time = time;
}
/******************************************************************************/
ilrd_uid_t TaskGetUID(task_t* task)
{
	assert(NULL != task);
	return (task->uid);
}
/******************************************************************************/
/* Runs task job function - return is the interval, -1 if non-periodic (overwrite bulit-in interval?) */
ssize_t TaskRun(task_t* task)
{
	assert(NULL != task);
	return (task->job_func(task->job_params));
}
/******************************************************************************/
/* Runs task cleanup function */
void TaskCleanUp(task_t* task)
{
	assert(NULL != task);
	task->cleanup_func(task->cleanup_params);
}
/******************************************************************************/
ssize_t GetInterval(task_t* task)
{
	assert(NULL != task);
	return (task->interval);
}
/******************************************************************************/
void SetInterval(task_t* task, ssize_t interval)
{
	assert(NULL != task);
	task->interval = interval;
}
/******************************************************************************/
