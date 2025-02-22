/******************************************************************************/
/*                          Author Yana Glazer                                */
/*                           Date 21/02/2025                                  */
/*                          Reviewed by ____                                  */
/******************************************************************************/
#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <sys/types.h> /*for pid_t type, signed int*/
#include <time.h> /*for time, time- long int*/

/*Modifying this struct may cause unexpected behavior or memory corruption*/
typedef struct{
	size_t counter;
	pid_t pid;
	time_t time;
	unsigned int ip_addr;
}ilrd_uid_t;

/*Bad UID value*/
extern ilrd_uid_t bad_id;


/*Function creates new UID*/
ilrd_uid_t CreateUID(void);

/*Function compare 2 UID. Equal returns 1, Not equal returns 0*/
int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second);

#endif /*ILRD_UID_H*/
