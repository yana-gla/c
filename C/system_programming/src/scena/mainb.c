#include <stdio.h>
#include <dlfcn.h>
#include "b.h"

int main()
{
	void *lib = NULL; 
	
	g_x = 10;
	
	printf("address of g_x is %p\n", (void*)&g_x);
	
	lib = dlopen("libdb.so", RTLD_LAZY);
	
/*	g_x = (int)dlsym(lib, "g_x");*/
	
	printf("address of g_x is %p\n", dlsym(lib, "g_x"));
	
	dlclose(lib);
	
	return 0;
}

