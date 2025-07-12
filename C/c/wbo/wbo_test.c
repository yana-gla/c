#include <stdio.h> /*printf*/
#include <stddef.h> /*for size_t*/
#include <string.h> /*for- strlen, original memmove (comparing)*/
#include <assert.h>





 void *MeMset(void *s, int c, size_t n)
 {
 	char *ptr_char = (char*)s;
 	size_t *ptr_szt = NULL;
 	size_t middle = 0;
 	size_t byte_end = 0;   /*7 is binary 111*/ /*remainder of 8 is final 3 bits*/
 	size_t c_word = 0;
 	size_t i = 0;
 	
 	size_t byte_begin = sizeof(size_t) - ((size_t)s & 0x7);
 	
 	assert(s != NULL);
 	printf("byte begin is %ld\n", byte_begin);
 	if (byte_begin == 8 )
 	{
 	  byte_begin = 0;
 	}
 	printf("byte begin is %ld\n", byte_begin);

 	
 	
 	 printf("byte begin is %ld\n", byte_begin);
 	 	
 	/*Begining Bytes*/
 	for (i = 0; i < byte_begin ; ++i)
 	{
 		*ptr_char++ = c;
 		--n;
 	}
      
 	/*create byteword*/
 	for (i = 0 ; i < sizeof(size_t); ++i )
 	{
 		c_word = (c_word << 8) | c ;
 	}
 	
 	ptr_szt = (size_t*)ptr_char;
 	middle = n / sizeof(size_t);
 	printf("n is %ld i is %ld middle is %ld\n", n, i, middle);
 	/*Copying Word size*/
 	for (i = 0; i < middle; ++i)
 	{
 		*ptr_szt++ = c_word;
 		 n -= sizeof(size_t);
 	}
 	
 	byte_end = n ;

	ptr_char = (char*)ptr_szt;
	
	/*End Bytes*/
	for (i = 0; i < byte_end; ++i)
 	{
 		*ptr_char++ = c;
 	}
 	
 	return s;
 	
}

 void *MemCpy(void *to, const void *from, size_t n_bytes)
 {
 	
 	size_t *p_szt_to = (size_t*)to; 
 	const size_t *p_szt_from = (size_t*)from;
	char *p_chr_to = NULL, *p_chr_from = NULL;
	
	assert(NULL != to && NULL != from); 
 	
 	for (n_bytes = n_bytes ; n_bytes >= sizeof(size_t) ; n_bytes -= sizeof(size_t))
 	{
 		*p_szt_to++ = *p_szt_from++;

	}
	
	p_chr_to = (char*)p_szt_to, p_chr_from = (char*)p_szt_from;
	
	for(n_bytes = n_bytes ; n_bytes > 0; --n_bytes)
	{
		 *p_chr_to++ = *p_chr_from++;
	}
	
	return to;

 }
 
 void *MemMove(void *to, const void *from, size_t n_bytes)
 {
 	char *p_to = (char*)to;
 	const char *p_from = (char*)from;
 	size_t i = 0;
 	
 	assert(NULL != to && NULL != from);
 	
 	if (p_to == p_from)
 	{
 		return to;
 	}
 	else if (p_from > p_to) /*MemCopy*/
 	{

 		for ( i = 0; i < n_bytes ; ++i)
 		{
 			*p_to++ = *p_from++;

 			
 		}	
 	}
 	else
 	{
 		p_to += n_bytes -1 , p_from += n_bytes -1;
 		
 		for (i = n_bytes ; i > 0 ; --i)
 		{
 		        
 			*p_to-- = *p_from--;

 		}
 	}
 	
 	return to;
 
 }

void CheckMeMset();
void CheckMemCpy();
void CheckMemMove();



int main()
{
	char str1[50] = "11111111111111111111";
	char str2[50] = "11111111111111111111";
	
	char str3[50] = "";
	char str4[50] = "";
	
	printf("\n begin tests: \n");
	

	MeMset(str1 + 1, '.', 17 * sizeof(char));
	memset(str2 + 1, '.', 17 * sizeof(char));
	
	printf("MY memset       %s\n", str1);
	printf("Original memset %s\n", str2);
	
	
	
	MeMset(str3, '.', 6 * sizeof(char));
	memset(str4, '.', 6 * sizeof(char));
	
	printf("MY memset       %s\n", str1);
	printf("Original memset %s\n", str2);
	
	
	
	CheckMeMset();
	
    CheckMemCpy();
    CheckMemMove();
    
    
    printf("\n all tests finished successfully \n");
    
    return (0);
}

void CheckMeMset()
{
	char str1[50] = "11111111111111111111";
	char str2[50] = "11111111111111111111";
	char str3[50] = "";
	char str4[50] = "";
	char str5[50] = "12345";
	char str6[50] = "12345";
	
	MeMset(str1 + 1, '.', 17 * sizeof(char));
	memset(str2 + 1, '.', 17 * sizeof(char));
	
	MeMset(str3, '.', 6 * sizeof(char));
	memset(str4, '.', 6 * sizeof(char));
	
	MeMset(str5, '.', 0 * sizeof(char));
	memset(str6, '.', 0 * sizeof(char));
	
	assert(strcmp(str1,str2) == 0);
	assert(strcmp(str3,str4) == 0);
	assert(strcmp(str5,str6) == 0);
}

void CheckMemCpy()
{
	char str1[50] = "22222222222222222222222222222";
	char str2[50] = "22222222222222222222222222222";
	char str3[50] = "11111111111111111111";
	char str4[50] = "";
	char str5[50] = "12345";
	char str6[50] = "12345";
	char str7[50] = "123456789";
	
	MemCpy(str1, str3, strlen(str3));
	memcpy(str2, str3, strlen(str3));
	
	assert(strcmp(str1,str2) == 0);
	
	MemCpy(str1, str4, strlen(str4));
	memcpy(str2, str4, strlen(str4));
	
	assert(strcmp(str1,str2) == 0);

	MemCpy(str5, str7, strlen(str7));
	memcpy(str6, str7, strlen(str7));
	
	assert(strcmp(str5,str6) == 0);
}

void CheckMemMove()
{
	char str1[50] = "06789";
	char str2[50] = "11111";
	char str3[50] = "12345";
	char str4[50] = "";
	char str5[50] = "12345";
	char str6[50] = "12345";
	char str7[50] = "123456789";
	
	MemMove(str1, str3, strlen(str3));
	memmove(str2, str3, strlen(str3));
	
	assert(strcmp(str1,str2) == 0);
	
	MemMove(str1, str4, strlen(str4));
	memmove(str2, str4, strlen(str4));
	
	assert(strcmp(str1,str2) == 0);

	MemMove(str5, str7, strlen(str7));
	memmove(str6, str7, strlen(str7));
	
	assert(strcmp(str5,str6) == 0);
	
	MemMove(str5 + 1, str5, strlen(str5)-1);
	memmove(str6 + 1, str6, strlen(str6)-1);
	
	assert(strcmp(str5,str6) == 0);
}



/*

int main(void)
{
	    char str[] = "MushlamMushlamMushlam";
	    char str2[] = "yanabanana";
		char str3[] = "ooo";
	    int n = 7;
	    char *first, *second; 
	    
	    char str4[100] = "LearningIsFun"; 

    	first = str4; 
    	second = str4; 
    
		MeMset(str+1, 'f', n);
		printf("MeMset result is %s\n", str);
		
		
		
		MemCpy(str2, str3, strlen(str3));
		printf("%s\n\n", str2);
		
		printf("%s\n", str4);
		
		MemMove(str4, str4, 10); 
    	printf("memmove overlap : %s\n", str4);
    	
		MemMove(to, to + 8, 10); 
    	printf("memmove overlap : %s\n", str4); 
    
    	MemMove(to + 8, to, 10); 
    	printf("memmove overlap : %s\n", str4); 
		
	    return 0;
	
}

*/
