#include <stdio.h>
#include <dlfcn.h>

/*void Foo(int num);*/

int main()
{
	void *lib = dlopen("libdfoo.so", RTLD_LAZY);
	void (*Foo)(int) ;

	if (NULL == lib)
	{
		return 1;
	}
	
	/*load symbols table*/
	Foo = (void(*)(int))dlsym(lib, "Foo");
	
	if (NULL == Foo)
	{
		return 1;
	}
	 
	Foo(5);
	
	dlclose(lib);
	return 0;
}
