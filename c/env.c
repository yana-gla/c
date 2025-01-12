#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>     
#include <ctype.h>
  
extern char **environ; 


void CpyStrToLwr(char* dst, char* src)
{
	
	while('\0' != *src)
	{
		*(dst) = tolower(*src);
		++dst, ++src;
	}
	
	*dst = '\0';
}



int main(void)
{
	size_t i = 0;
	size_t str_num = 0;
	size_t str_len = 0;
	char **buffer = NULL;

	/*number of strings*/
	while (environ[i] != NULL)
	{
		++str_num;
		++i;
	}
	
	/*One dimensional array of ponter to strings*/
	buffer= (char**)calloc(str_num, sizeof(char*));
	
	for (i=0; i< str_num; ++i)
	{	
		str_len = strlen(*(environ+i));
		buffer[i] = (char*)calloc(str_len, sizeof(char*));
		CpyStrToLwr(buffer[i], environ[i]);
		printf("%s\n", buffer[i]);
	}
	
	
	printf("-------------------------------------------------------\n");
	 

	for (i=0; i< str_num; ++i)
    {
    	printf("%s\n", environ[i++]);
	}
	
	for(i=0; i< str_num; ++i)
	{
		free(buffer[i]);
	}
	
	free(buffer);
	
	return 0;
}
	
	   	

	   	   



