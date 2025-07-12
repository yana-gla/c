#include <stdio.h>
#include <stdlib.h>


void Read(void)
{
	char str[5] ="";
	printf("str is %s\n", str);
	printf ("input string\n");
	
/*	gets(str);*/
	printf("%s\n", str);
	return;
}

void demo()
{
	int a = 10;
	int *p = &a;
	
	(*p)++;
	printf ("a is %d\n", a);
	
	++(*p);
	printf ("a is %d\n", a);
}


/*int *fun()*/
/*{*/
/*	int x=10;*/
/*	printf("&x is %lu\n", &x);*/
/*	printf("&x is %p\n", (void*)&x);*/
/*	return &x;*/
/*}*/


int *intarr()
{
	const int num = 3;
	return (int*)&num;
}

char *string()
{
	char *str = "yana";
	return str;
}


int main ()
{
	int i = 0;
	int *p = (int*)malloc(4*sizeof(int));
	int *pstart = p;
/*	int *r = fun();*/
	int x[10] = { 0 }, *f;
	int *num = intarr();
	char *str = string();
	printf("%s\n", str);
	++p;
	
	printf("%d\n", *num);
	
/*	++x;*/

/*	*/
/*	*r = 20;*/
/*	*/
/*	*/
/*	if (NULL == p)*/
/*	{*/
/*		return -1;*/
/*	}*/
/*	*/
/*	for (i = 0; i < 4 ; ++i)*/
/*	{*/
/*		p[i] = 100;*/
/*	}*/
/*	*/
/*	for (i = 0; i < 4 ; ++i)*/
/*	{*/
/*		printf ("%d ",p[i]);*/
/*	}*/
/*	printf("\n");*/
/*	*/
	free(pstart);
/*	Read();*/
/*	*/
/*	demo();*/
/*	*/

/*	f = &x[0];*/

/*	while (i < 10)*/
/*	{*/
/*		*f = 10;*/

/*		f = f + 4;*/
/*		i++;*/
/*	}*/
/*	*/
/*		i = 0;*/
/*		f =x;*/
/*		while (i < 10)*/
/*	{*/
/*		*/
/*		printf("%d\n", *f);*/
/*		f = f + 4;*/
/*		i++;*/
/*	}*/
/*	*/
/*	printf("size of long id %lu\n", sizeof(long));*/

/*	printf("size of size_t id %lu\n", sizeof(size_t));*/

	return 0;
}
