/******************************************************************************
* File: dhcp.h
*
* Purpose:
*   <insert file purpose here>
*
* Author:
*   Yana Glazer
*
******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

/***********************************************************************************
* Function:
* 
* Purpose:
* 	-
*
* Variables:
* 	-
* 
* Return Value:
* 	-
* 
* Notes:
* 	-
*
* Complexity: O(-)
* 
***********************************************************************************/

#define NUM_CHARS (4)

enum status_t
{
	SUCCESS,
	FAILURE
}status_t;

typedef unsigned char ip_addr[NUM_CHARS] ip_addr_t;
typedef struct dhcp dhcp_t;

dhcp_t* DHCPCreate(ip_addr_t subnet_ip, size_t mask_size);

status_t DHCPAllocateIP(dhcp_t* dhcp, ip_addr_t preferred_ip, ip_addr_t new_ip);

void DHCPFreeIP(dhcp_t* dhcp, ip_addr_t ip);

size_t DHCPCountFree(const dhcp_t* dhcp);

void DHCPDestroy(dhcp_t* dhcp);


#endif
