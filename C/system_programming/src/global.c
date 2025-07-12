#include <stdio.h>
#include <dlfcn.h>
#include "ins_glb.h"

typedef void (*fnct_ptr)(void);

int main()
{
	void *lib = dlopen("../system_programming/fooglb.so", RTLD_LAZY);
	void *lib2 = dlopen("../system_programming/fooglb2.so", RTLD_LAZY);
	fnct_ptr Foo = NULL;
	fnct_ptr Foo2 = NULL;
	
	if (NULL == lib || NULL == lib2)
	{
		return -1;
	}
	
	/*check later*/
	Foo = dlsym(lib, "Foo");
	Foo2 = dlsym(lib2, "Foo2");
	
	if (NULL == Foo || NULL == Foo2)
	{
		return -1;
	}
	
	PrintGlobalVariableAddress();
	Foo();
	Foo2();
	
	dlclose(lib);
	dlclose(lib2);
	
	return 0;
}
