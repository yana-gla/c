#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /*is_digit*/
#include <assert.h>

#define STR_LENGTH 17 /*define in manual*/

void SwapChar(char *x, char *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void Reverse(char* str)
{
	int len = strlen(str);
	char *l = str , *r = str + len - 1;
	
	while (l < r)
	{
		SwapChar(l++, r--);
	}
}


/*itoa*/
char* IntToStringAnyBase(int num, char* buffer, int base) 
{
	int is_negative = 0;
	int rem = 0; /*reminder*/
	char *buffer_start = buffer;
	
	/*Handle 0*/
	if (num == 0)
	{
	 	*buffer++ = '0';
	 	*buffer = '\0';
	 	return buffer_start;
	}
	
	/*if num is negative*/
	if (num < 0 ) 
	{
		is_negative = 1;
		num = -num;
	}
	
	/*building the string, will be reversed 200->002*/
	/*if num != 0*/
	while (num > 0)
	{
		rem = num % base;
		*buffer++ = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num /= base;
	}
	
	if (is_negative == 1)
	{
		*buffer++ = '-';
	}
	
	*buffer = '\0';
	
	Reverse(buffer_start);
	
	return buffer_start;
}        

/*itoa*/
char* IntToStringBase10(int num, char* buffer)
{
	int is_negative = 0;
	char *buffer_start = buffer;
	
	/*Handle 0*/
	if (num == 0)
	{
	 	*buffer++ = '0';
	 	*buffer = '\0';
	 	return buffer_start;
	}
	
	/*if num is negative*/
	if (num < 0 ) 
	{
		is_negative = 1;
		num = -num;
	}
	
	/*Building the string, will be reversed 200->002*/	
	/*if num != 0*/
	while (num > 0)
	{
		*buffer++ = num % 10 + '0';
		num /= 10;
	}
	
	if (is_negative == 1)
	{
		*buffer++ = '-';
	}
	
	*buffer = '\0';
	
	Reverse(buffer_start);
	
	return buffer_start;
}

/*atoi*/
int StringToIntAnyBase(const char *str, int base)
{
	int is_negative = 0;
	int ones_digit = 0;
	int result = 0;
	
	while (0 != isspace(*str)) /*isspace returns non-zero, not necessarily 1*/
	{
		++str;
	}
	if ('-' == *str) 
	{
		is_negative = 1;
		++str;
	}
	
	/*if (  !isdigit(*str) ) return 0;*/
		
	/*Build int*/	
	while ('\0' != *str)
	{
		ones_digit = (isdigit(*str) != 0)  ? *str - '0' : toupper(*str) - 55;
		result = result * base + ones_digit;
		++str;
	}
		
	if (1 == is_negative) 
	{
		result *= -1;
	}
	
	return result ;
}


/*atoi*/
int StringToIntBase10(const char *str)
{
	int is_negative = 0;
	int ones_digit = 0;
	int result = 0;
	
	if ( !isspace(*str)  &&  !isdigit(*str)  &&  ('-' != *str) ) return 0;
		
	while (0 != isspace(*str)) /*isspace returns non-zero, not necessarily 1 */
	{
		++str;
	}
	
	if ('-' == *str) 
	{
		is_negative = 1;
		++str;
	}
		
	while (isdigit(*str) != 0 && '\0' != *str )
	{
		ones_digit = *str - '0';
		result = result * 10 + ones_digit;
		++str;
	}
	
	if (1 == is_negative) 
	{
		result *= -1;
	}
	
	return result ;
}

static void TestAtoi(char *str)
{
    /*printf ("atoi ->  %d ", atoi(str));
    printf (" %d <- StringToIntBase10 \n", StringToIntBase10(str)); */
    printf("Test %s \n", str);
    assert(atoi(str) == StringToIntBase10(str));
}

static void TestAtoiEdgeCases()
{
    /*Test StringToIntBase10*/
    char str1[] = "   12345ad";
    char str2[] = "\n456566";
    char str3[] = "	1223.79798";
    char str4[] = "00002";
    char str5[] = "2";
    char str6[] = "abc3456";
    char str7[] = "~365.8686";
    char str8[] = "2.yug";
    char str9[] = "-777";
    char str10[] = "2147483647"; /*max int*/
    char str11[] = "-2147483648"; /*min int*/
    char str12[] = "4294967295"; /*unsigned int*/
    char str13[] = "0";
    
    printf("Test atoi begin..\n");
    TestAtoi(str1);
    TestAtoi(str2);
    TestAtoi(str3);
    TestAtoi(str4);
    TestAtoi(str5);
    TestAtoi(str6);
    TestAtoi(str7);
    TestAtoi(str8);
    TestAtoi(str9);
    TestAtoi(str10);
    TestAtoi(str11);
    TestAtoi(str12);
    TestAtoi(str13);
    
    printf("\n");
    printf("Test atoi end\n");
}

	
int main (void)
{
	/*
	char str1[STR_LENGTH] = "";
	char str2[STR_LENGTH] = "";
	char str3[STR_LENGTH] = "";
	char str4[STR_LENGTH] = "";
	char str5[STR_LENGTH] = "";
	char str6[STR_LENGTH] = "";
	char str7[STR_LENGTH] = "";
	char str8[STR_LENGTH] = "";
	char str9[STR_LENGTH] = "";
	char str10[STR_LENGTH] = "";
	
	int num1 = -345;
	int num2 = 987;
	
	int num3 = -56;
	int num4 = 1278;
	
	int num5 = 8;
	int num6 = -16;
	
	int num7 = 15;
	int num8 = 0;
	
	int num9 = 567;
	int num10 = 123456789;
	*/
	
	/*
	IntToStringBase10(num1 , str1);
	IntToStringBase10(num2 , str2);
	IntToStringBase10(num3 , str3);
	IntToStringBase10(num4 , str4);
	IntToStringBase10(num5 , str5);
	IntToStringBase10(num6 , str6);
	IntToStringBase10(num7 , str7);
	
	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", str3);
	printf("%s\n", str4);
	printf("%s\n", str5);
	printf("%s\n", str6);
	printf("%s\n", str7);
	
	/******************************/

	
	TestAtoiEdgeCases();
	
	/*
	printf("atoi- StringToIntBase10-\n");
	printf("|       |\n");
	printf ("%d ", atoi(str8));
	printf ("%d\n", StringToIntBase10(str8));
	
	printf ("%d ", atoi(str9));
	printf ("%d\n", StringToIntBase10(str9));
	
	printf ("%d ", atoi(str10));
	printf ("%d\n", StringToIntBase10(str10));
	
	printf ("%d ", atoi(str11));
	printf ("%d\n", StringToIntBase10(str11));
	
	printf ("%d ", atoi(str12));
	printf ("%d\n", StringToIntBase10(str12));
	
	printf ("%d ", atoi(str13));
	printf ("%d\n", StringToIntBase10(str13));
	
	printf ("%d ", atoi(str14));
	printf ("%d\n", StringToIntBase10(str14));
	
	printf ("%d ", atoi(str15));
	printf ("%d\n", StringToIntBase10(str15));
	
	printf ("%d ", atoi(str16));
	printf ("%d\n", StringToIntBase10(str16));
	
	printf ("%d ", atoi(str17));
	printf ("%d\n", StringToIntBase10(str17));
	
	printf ("%d ", atoi(str18));
	printf ("%d\n", StringToIntBase10(str18));
	
	printf ("%d ", atoi(str19));
	printf ("%d\n", StringToIntBase10(str19));
	
	printf ("%d ", atoi(str20));
	printf ("%d\n", StringToIntBase10(str20));
	*/
	
	/******************************/
	
	/*Test IntToStringAnyBase
	
	IntToStringAnyBase(num1, str1, 2);
	IntToStringAnyBase(num2, str2, 2);
	IntToStringAnyBase(num3, str3, 4);
	IntToStringAnyBase(num4, str4, 4);
	IntToStringAnyBase(num5, str5, 8);
	IntToStringAnyBase(num6, str6, 8);
	IntToStringAnyBase(num7, str7, 16);
	IntToStringAnyBase(num8, str8, 16);
	IntToStringAnyBase(num9, str9, 32);
	IntToStringAnyBase(num10, str10, 10);
	
	printf("%s\n", str1);
	printf("%s\n\n", str2);
	printf("%s\n", str3);
	printf("%s\n\n", str4);
	printf("%s\n", str5);
	printf("%s\n\n", str6);
	printf("%s\n", str7);
	printf("%s\n\n", str8);
	printf("%s\n", str9);
	printf("%s\n", str10);
	*/
	
	
	/******************************/
	
        /*
	/*Test StringToIntAnyBase
	char str8[] = "  1245";
	char str9[] = "\n456566";
	char str10[] = "	1223.79798";
	char str11[] = "00002";
	char str12[] = "2";
	char str13[] = "abc3456";
	char str14[] = "~365.8686";
	char str15[] = "2.yug";
	char str16[] = "-777";
	char str17[] = "2147483647"; /*max int
	char str18[] = "-2147483648"; /*min int
	char str19[] = "4294967295"; /*unsigned int
	char str20[] = "0";
	
	
	printf ("%d\n", StringToIntAnyBase(str8, 2));
	printf ("%d\n", StringToIntAnyBase(str9, 4));
	printf ("%d\n", StringToIntAnyBase(str10, 6));
	printf ("%d\n", StringToIntAnyBase(str11, 8));
	printf ("%d\n", StringToIntAnyBase(str12, 10));
	printf ("%d\n", StringToIntAnyBase(str13, 12));
	printf ("%d\n", StringToIntAnyBase(str14, 14));
	printf ("%d\n", StringToIntAnyBase(str15, 16));
	printf ("%d\n", StringToIntAnyBase(str16, 18));
	printf ("%d\n", StringToIntAnyBase(str17, 20));
	printf ("%d\n", StringToIntAnyBase(str18, 22));
	printf ("%d\n", StringToIntAnyBase(str19, 24));
	printf ("%d\n", StringToIntAnyBase(str20, 26));
      
	StringToIntAnyBase(const char *str, int base);
	*/
	return;
}
