#include <stdio.h>
#define MAX_LIMIT 100

int main(void)
{
	char str_input[MAX_LIMIT] = "a";
	printf ("%d %d %d\n", str_input[0], str_input[1], str_input[101]);
	fgets(str_input, MAX_LIMIT, stdin); /*scanf("%s",str_input); %[^\n]s*/
	printf("%s", str_input);
	printf ("%d %d %d\n", str_input[4], str_input[5], str_input[6]);
	
	
	return 0;
}

	
	
