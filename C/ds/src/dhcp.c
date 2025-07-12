/*******************************************************************************
* File: dhcp.c
*
* Purpose:
*   Implement DHCP
	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*  
*
*Date: 01/04/2025
*Last Update: 
*******************************************************************************/
#include <stdlib.h>
#include "dhcp.h"

/*#define NUM_CHARS (4)*/

#define IP_LEN NUM_CHARS * CHAR_BIT /*32*/

/*typedef struct dhcp dhcp_t;*/
struct dhcp
{
	trie_node_t root;
	size_t mask_size;
	ip_addr_t subnet_ip;
};

typedef struct trie_node trie_node_t;
struct trie_node
{
	int is_full;	/* 1 = full, 0 = not full */
	trie_node_t* children[2];
};

enum child
{
	LEFT,
	RIGHT
}child_t;


dhcp_t* DHCPCreate(ip_addr_t subnet_ip, size_t mask_size)
{
	dhcp_t *dhcp = NULL;
	
	assert(NULL != subnet_ip);
	assert(mask_size <= 30);
	
	dhcp_t *dhcp = (dhcp_t*)malloc(sizeof(*dhcp)); /*dhcp is empty*/
	if (NULL == dhcp)
	{
		return NULL;
	}
	
	/*initialization*/
	dhcp->root = (trie_node_t*)calloc(sizeof(1, trie_node_t)); /*root is empty*/
	if (NULL == dhcp->root)
	{
		free(dhcp);
		return NULL;
	}
	dhcp->mask_size = mask_size;
	dhcp->subnet_ip = subnet_ip;
	
	
	
	/*create 3 adresses*/
	
	return dhcp;
}

status_t DHCPAllocateIP(dhcp_t* dhcp, ip_addr_t preferred_ip, ip_addr_t new_ip)
{
	
}

static ip_addr_t SubNetMask(dhcp_t dhcp)
{
	int i = 0;
	
	ip_addr_t mask = 0;
	
	for (i = 0; i < dhcp->mask_size ; ++i)
	{
		mask <<= 1;
		mask &= 1;
	}
	mask <<= IP_LEN - dhcp->mask_size;
}

static int SubNetMatch(dhcp_t dhcp, ip_addr_t preferred_ip)
{
	return (preferred_ip && SubNetMask(dhcp) ==
										 dhcp->subnet_ip  && SubNetMask(dhcp));
}

static int PreferedExist(ip_addr_t preferred_ip)
{
	
}



