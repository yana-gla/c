#define MAX2(a, b) (((a) < (b)) > (b) : (a))
#define MAX3(a, b, c) (max(a,MAX2(a, b)))

#define SIZEOF_VAR(var) (char *)((&var)+1) - (char *)(&var)
#define SIZEOF_TYPE(type) (char*)((type *)0 + 1) - (char*)((type *)0)
