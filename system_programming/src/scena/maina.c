#include <stdio.h>
#include <dlfcn.h>
#include "a.h"

int g_x = 5;

int main()
{
	void *lib = NULL; 
	
	printf("address of g_x is %p\n", (void*)&g_x);
	
	lib = dlopen("libda.so", RTLD_LAZY);
	
/*	g_x = (int)dlsym(lib, "g_x");*/
	
	printf("address of g_x is %p\n", dlsym(lib, "g_x"));
	
	dlclose(lib);
	
	return 0;
}





