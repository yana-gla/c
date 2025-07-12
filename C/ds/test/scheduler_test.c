#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "scheduler.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

typedef struct
{
    scheduler_t* sched;
    ilrd_uid_t uid;
} remove_task_params_t;

void TestStartStop();
void TestNoneRecurringTask();
ssize_t TaskPrint(void* param);
ssize_t TaskStop(void* param);
ssize_t TaskPrintNoneRecurring(void* param);
void TestRemovingTask();
void Cleanup(void* param);
void TestRemovingTaskDynamically();
ssize_t TaskRemove(void* param);

int main(void)
{
	TestRemovingTask();
    TestStartStop();
    TestNoneRecurringTask();
    TestRemovingTaskDynamically();
    printf(GREEN "\n✅ All tests completed successfully! ✅\n" UNFORMAT);
    return 0;
}

ssize_t TaskPrint(void* param)
{
    printf("Task executed with value: %d\n", *(int*)param);
    ++*(int*)param;
    return (1);
}

ssize_t TaskPrintNoneRecurring(void* param)
{
    printf("Task executed with value: %d\n", *(int*)param);
    ++*(int*)param;
    return (-1);
}

ssize_t TaskStop(void* param)
{
    printf("Stopping scheduler...\n");
    SchedStop((scheduler_t*)param);
    return -1;
}

void Cleanup(void* param)
{
    printf("Cleaning up task with value: %d\n", *(int*)param);
}

void TestStartStop()
{
    scheduler_t* sched;
    int task1;
    int task2;
    time_t now;
    
    printf("\n--- Testing Start and Stop ---\n");
    sched = SchedCreate();
    assert(sched != NULL);
    
    task1 = 1;
    task2 = -1; /* This task stops the scheduler */
    now = time(NULL);
    
    SchedAddTask(sched, now + 1, TaskPrint, &task1, Cleanup, &task1, 5);
    SchedAddTask(sched, now + 4, TaskStop, sched, Cleanup, &task2, 1);
    
    SchedStart(sched);
    
    SchedClear(sched);
    printf("Count: %ld\n", SchedCount(sched));
    assert(SchedIsEmpty(sched) == 1);
    
    now = time(NULL);
    SchedAddTask(sched, now + 1, TaskPrint, &task1, Cleanup, &task1, 2);
    SchedAddTask(sched, now + 6, TaskStop, sched, Cleanup, &task2, 1);
    
    printf("Count: %ld\n", SchedCount(sched));
    
    SchedStart(sched);
    SchedClear(sched);
    
    SchedDestroy(sched);
}

void TestRemovingTask()
{
	scheduler_t* sched = SchedCreate();
	ilrd_uid_t uid;
	int task1 = 1;
	uid = SchedAddTask(sched, 1, TaskPrint, &task1, Cleanup, &task1, 1);
	printf("Count: %ld\n", SchedCount(sched));
	
	printf("TEST ID: %ld\n", uid.counter);
    printf("TEST PID: %d\n", uid.pid);
	SchedRemoveTaskByUID(sched, uid);
	
	printf("Count: %ld\n", SchedCount(sched));
	
	SchedDestroy(sched);

}

void TestNoneRecurringTask()
{
    scheduler_t* sched;
    int task1;
    time_t now;
    
    printf("\n--- Testing Recurring Task Time Change ---\n");
    sched = SchedCreate();
    assert(sched != NULL);
    
    task1 = 2;
    now = time(NULL);
    
    SchedAddTask(sched, now + 1, TaskPrintNoneRecurring, &task1, Cleanup, &task1, 2);
    assert(!SchedIsEmpty(sched));
    
    SchedStart(sched);
    
    SchedDestroy(sched);
}

void TestRemovingTaskDynamically()
{
    scheduler_t* sched = SchedCreate();
    int task1 = 1000, task2 = 2000, task3 = 3000;
    remove_task_params_t remove_params;
    assert(sched != NULL);

    printf("\n--- Testing Dynamic Task Removal ---\n");

    remove_params.uid = SchedAddTask(sched, time(NULL) + 5 , TaskPrint, &task1, Cleanup, &task1, 1);
    remove_params.sched = sched;

    SchedAddTask(sched, time(NULL) + 3, TaskRemove, &remove_params, Cleanup, &task2, 1);

    SchedAddTask(sched, time(NULL) + 10, TaskPrint, &task3, Cleanup, &task3, 1);
     SchedAddTask(sched, time(NULL) + 15, TaskStop, sched, Cleanup, &task2, 1);

    printf("Initial Task Count: %ld\n", SchedCount(sched));
    SchedStart(sched);
    printf("Final Task Count: %ld\n", SchedCount(sched));

    SchedDestroy(sched);

}

ssize_t TaskRemove(void* param)
{
    remove_task_params_t* params = (remove_task_params_t*)param;
    printf("Removing Task with ID: %ld\n", params->uid.counter);
    SchedRemoveTaskByUID(params->sched, params->uid);
    return -1; 
}


