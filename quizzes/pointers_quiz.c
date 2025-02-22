#include <stdio.h>

char *string_fun(void)
{
	char *string = "Yana";
	char a = 'y';
	
	return &a;
}

int check_for_endianness()
{
  unsigned int x = 1;
  char *c = (char*) &x;
  return (int)*c;
}


int main()
{
	unsigned int x = 0x76543210;
  	char *cc = (char*) &x;
	
	int *pi = NULL; /*pointer to int var*/
	int a =1, b=2, c=3; /*define 3 int var */
	const char *c_str = "abcd"; /*const string abcd*/
	char *m_str = NULL;
	char *p_str = (char*)c_str; /*pointer that points to abcd*/
/*	char *p_str = (char*)c_str;*/
	char arr_str[] = "abcd"; /*another string abcd but non const*/
	const char ch = '1';
	short *ps = NULL;
/*	int arr[0];*/
	
	char *aa = string_fun();
	printf ("%p\n", aa);
/*	printf ("%c\n", *aa);*/
	
	printf("%s\n", c_str+1); 
	printf("%lu\n", sizeof(c_str));
	
	printf("%s\n", arr_str+1);
	printf("%lu\n", sizeof(arr_str));
	
/*	*p_str = '0';*/
	printf("%s\n", p_str);
	printf("%lu\n", sizeof(p_str));
	

	printf("%lu\n", sizeof(*ps));
	printf("%lu\n", sizeof(*pi));
	
	pi = &a;
	pi = &c;
/*	&b = pi;*/

/*	c_str[2] = '0'; */
	printf("%s\n", c_str);
	*(arr_str + 1) = '0';
	printf("%s\n", arr_str);
/*	++arr_str;*/

	p_str = (char*)&c ;
	*p_str = '1';
	printf("%d\n", c);
	
	printf("ch is %d\n", ch);
	pi = (int*)&ch;
	*pi = 1000000;
	printf("ch is %d\n", ch);
	
	printf ("%d\n",check_for_endianness());

    return 0;
}
