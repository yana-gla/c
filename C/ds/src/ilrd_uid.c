#include <unistd.h>     /*for pid_t function*/
#include <string.h>    /*memcmp, memcpy*/
#include <ifaddrs.h>  /*getifaddrs, freeifaddrs*/
#include "ilrd_uid.h" 
/******************************************************************************/
static void GetIP(char *ip_addr);

ilrd_uid_t bad_id = {0};

ilrd_uid_t CreateUID(void)
{
	/*new id*/
	ilrd_uid_t id = {0};
	
	/*counter*/
	static size_t counter = 0; 
	id.counter= ++counter;
	
	id.pid = getpid();
	id.time = time(NULL);
	GetIP((char*)&id.ip_addr);
	
	return id;
}

int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second)
{
	return ( (first.counter == second.counter) && 
			(first.pid == second.pid) &&
			(first.time == second.time) &&
			(0 == memcmp(&first.ip_addr, &second.ip_addr, 14))  );
}

/******************************************************************************/
/*                          Static Function                                   */
/******************************************************************************/


static void GetIP(char *ip_addr)
{
	struct ifaddrs *ifap = NULL, *ifa = NULL;
		
	if (-1 == getifaddrs(&ifap))
	{
		return;
	}
	
	for (ifa = ifap ; NULL != ifa ; ifa = ifa->ifa_next)
	{
		if ((NULL != ifa->ifa_addr) && (ifa->ifa_flags == 69699)
									   && (ifa->ifa_addr->sa_family == AF_INET))
		{
			memcpy(ip_addr, &(ifa->ifa_addr->sa_data), 14);
			break; 
		}
	}
	freeifaddrs(ifap);
}
/******************************************************************************/

