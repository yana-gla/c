#include <stdlib.h> /*calloc*/
#include<unistd.h> /*sleep*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/

#include "p_queue.h"
#include "scheduler.h"


struct scheduler
{  
    p_queue_t* pq;
    volatile int on;
};


static int cmp_func(const void* data1, const void* data2);
static int MatchUIDs(const void* uid1, const void* uid2);

/******************************************************************************/
scheduler_t* SchedCreate(void)
{
	scheduler_t *sched = (scheduler_t*)calloc(1, sizeof(scheduler_t));
	if(NULL == sched)
	{
		return NULL;
	}
	
	sched->pq = PQCreate(cmp_func);
	if (NULL == sched->pq)
	{
		memset(sched, 0, sizeof(scheduler_t));
		free(sched);
		sched = NULL;
		return NULL;
	}
	sched->on = 0;
	return sched;
}

/******************************************************************************/
/* O(n) */
void SchedDestroy(scheduler_t* scheduler)
{
	assert(NULL != scheduler);
	
	/*if scheduler is on, stop*/
	if (scheduler->on)
	{
		SchedStop(scheduler);
	}
	
	/*free to list*/
	SchedClear(scheduler);
	PQDestroy(scheduler->pq);
	
	
	/*free to scheduler*/
	memset(scheduler, 0, sizeof(scheduler_t));
	free(scheduler);
	scheduler = NULL;
}

/******************************************************************************/
/* add task to scheduler, O(n) */
ilrd_uid_t SchedAddTask(scheduler_t* scheduler,
                        size_t time,    /* absolute time */
                        job_func_t job_func,    
                        void* job_params,
                        cleanup_func_t cleanup_func,
                        void* cleanup_params,
                        size_t interval)
{
	task_t* task_p = NULL;
	ilrd_uid_t id_task = {0};
	
	assert(NULL != scheduler);
	assert(NULL != job_func);
	assert(NULL != cleanup_func);
	
	task_p = TaskCreate(time, job_func, job_params, cleanup_func, cleanup_params, interval);
	if (NULL == task_p)
	{
		return bad_id;
	}
	
	if (0 != PQEnqueue(scheduler->pq, task_p))
	{
		TaskDestroy(task_p);
		return bad_id;
	}
	
	id_task = TaskGetUID(task_p);
	return id_task;
}

 /******************************************************************************/
/* find task by UID
 * send pointer to task to TaskDestroy()
 * remove task by its uid, O(n) */
int SchedRemoveTaskByUID(scheduler_t* scheduler, ilrd_uid_t uid)
{
	task_t *task_p = NULL;

	assert(NULL != scheduler);

	task_p = (task_t*)PQRemove(scheduler->pq, MatchUIDs, &uid);
	if (NULL == task_p)
	{
		return 1;
	}
	
	TaskDestroy(task_p);
	return 0;
}

/******************************************************************************/
/* set start_time to current global time (once), O(1) */
/*Starts the schedular*/
/*returns 0 on success, 1 if Enqueued failed*/
/*interval from run overrides task's interval*/
int SchedStart(scheduler_t* scheduler)
{
	time_t sleep_time = 0;
	time_t task_time = 0;
	int status = 0;
	task_t *cur_task = NULL;
	ssize_t cur_interval = 0;/*returned interval from run*/ 
	
	assert(NULL != scheduler);
	
	if (scheduler->on)
	{
		return 1;
	}
	scheduler->on = 1;
	
	while (scheduler->on && !SchedIsEmpty(scheduler))
	{
		cur_task = (task_t*)PQPeek(scheduler->pq);
		task_time = TaskGetTime(cur_task);
		sleep_time = task_time - time(NULL);
		
		if (sleep_time > 0)
		{
			sleep(sleep_time);
		}

		PQDequeue(scheduler->pq);
		/*interval is according to return value from run*/
		cur_interval = TaskRun(cur_task);
		
		if (-1 == cur_interval)
		{
			TaskDestroy(cur_task);
		}
		else
		{
			TaskSetTime(cur_task, task_time + (time_t)cur_interval);
			status = PQEnqueue(scheduler->pq, cur_task);
			
			if (0 != status)
			{
				TaskDestroy(cur_task);
			}
			
		}
	}
	
	return status;
}

/******************************************************************************/
/* stop executing any more tasks in given scheduler, O(1)*/
void SchedStop(scheduler_t* scheduler)
{
	assert(NULL != scheduler);
	scheduler->on= 0;
}

/******************************************************************************/
/* clear scheduler, O(n)*/
void SchedClear(scheduler_t* scheduler)
{
	task_t *task = NULL;
	assert(NULL != scheduler);
	
	while (!SchedIsEmpty(scheduler))
	{
		task = (task_t*)PQPeek(scheduler->pq);
		TaskDestroy(task);
		PQDequeue(scheduler->pq);
	}
	
}

/******************************************************************************/
/* checks if scheduler is empty */
int SchedIsEmpty(scheduler_t* scheduler)
{
	assert(NULL != scheduler);
	return PQIsEmpty(scheduler->pq);
}

/******************************************************************************/
/* how many tasks in scheduler */
size_t SchedCount(scheduler_t* scheduler)
{
	assert(NULL != scheduler);
	return (PQCount(scheduler->pq));
}

/*************************** Static Function **********************************/


static int cmp_func(const void* task1, const void* task2)
{
	return (TaskGetTime((task_t*)task1) - TaskGetTime((task_t*)task2));
}

static int MatchUIDs(const void* uid1, const void* uid2)
{
	assert (NULL != uid1);
	assert (NULL != uid2);
	
	return CompareUID(*(ilrd_uid_t*)uid1, *(ilrd_uid_t*)uid2);
}

