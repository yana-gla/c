/******************************************************************************/
/*                          Author Yana Glazer                                */
/*                           Date 21/02/2025                                  */
/*                      Reviewed by Yonatan Fainer 23/02/2025                 */
/*                           Last Update 23/02/2025                           */
/*                                                                            */
/*Purpose: Generate unique identifier based on counter, process ID, time and  */
/*								 IP address                                   */
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
	char ip_addr[14];
}ilrd_uid_t;

/*Bad UID value*/
extern ilrd_uid_t bad_id;

/*******************************************************************************
* CreateUID
* Function creates new UID
*
* Parameters: void
*
* Returns: (ilrd_uid_t) new uid
* 	
*Complecity: O(1)
*******************************************************************************/
ilrd_uid_t CreateUID(void);
/*******************************************************************************
* CompareUID
* Function compare 2 UID. 
*
* Parameters: 2 UID to compare
*
* Returns: Equal returns 1, Not equal returns 0.
* 	
*Complecity: O(1)
*******************************************************************************/
int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second);

#endif /*ILRD_UID_H*/
