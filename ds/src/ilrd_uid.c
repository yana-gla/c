#include <unistd.h>      /*for pid_t function*/
#include <string.h>     /*strcompare*/
#include <arpa/inet.h> /*ntohl*/
#include <ifaddrs.h>  /*getifaddrs, freeifaddrs*/
#include "ilrd_uid.h" 

/******************************************************************************/
static unsigned int GetIP();

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
	id.ip_addr = GetIP();
	
	return id;
}

int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second)
{
	return ( (first.counter == second.counter) && 
			(first.pid == second.pid) &&
			(first.time == second.time) &&
			(first.ip_addr == second.ip_addr) );
}

/******************************************************************************/
/*                          Static Function                                   */
/******************************************************************************/


static unsigned int GetIP()
{
	struct ifaddrs *ifap = NULL, *ifa = NULL;
	struct sockaddr_in *sa = NULL;
	unsigned int ip_addrs = 0;
		
	if (-1 == getifaddrs(&ifap))
	{
		return -1;
	}
	
	for (ifa = ifap ; NULL != ifa ; ifa = ifa->ifa_next)
	{
		if ((NULL != ifa->ifa_addr) && (0 == strcmp("wlp0s20f3", ifa->ifa_name))
									   && (ifa->ifa_addr->sa_family == AF_INET))
		{
			sa = (struct sockaddr_in*)ifa->ifa_addr;
			ip_addrs = ntohl(sa->sin_addr.s_addr); /*Network byte order is Big-Endian, Host (my computer is Little)*/
			                                       /*(Network TO Host Long) converts the big-endian (network byte order) representation into the correct host byte order*/
			break;
		}
	
	}
	freeifaddrs(ifap);
	
	return ip_addrs;
}
/******************************************************************************/

