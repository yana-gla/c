#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc*/
#include <string.h>
#include <ctype.h> /*is_digit*/
#include <assert.h>
#include <limits.h> /*UCHAR*/
#include <stddef.h> /*NULL*/
#include "atoi.h"

#define STR_LENGTH 17 /*define in manual*/

static void TestIntToStringBase10(int num, char *buffer)
{
    IntToStringBase10(num, buffer);
    printf ("int %d is, str is %s.\n", num, buffer);
}

static void TestIntToStringBase10EdgeCases()
{
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
	 
        printf("Test IntToStringBase10 begin..\n"); 
        TestIntToStringBase10(-345, str1);
        TestIntToStringBase10(987, str2);
        TestIntToStringBase10(-56, str3);
        TestIntToStringBase10(1278, str4);
        TestIntToStringBase10(8, str5);
        TestIntToStringBase10(-16, str6);
        TestIntToStringBase10(15, str7);
        TestIntToStringBase10(0, str8);
        TestIntToStringBase10(567, str9);
        TestIntToStringBase10(123456789, str10); 
        printf("Test ended.\n\n"); 
}

static void TestAtoi(char *str)
{
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
    printf("Test atoi end\n\n");
}

static void TestIntToStringAnyBase(int num, char* buffer, int base)
{
    printf("%d in base %d is %s.\n", num, base, IntToStringAnyBase(num, buffer,base));
}

static void TestIntToStringAnyBaseEdgeCases()
{
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
    
    printf("Test IntToStringAnyBase begin..\n");
    TestIntToStringAnyBase(-345, str1, 2);
    TestIntToStringAnyBase(987, str2, 2);
    TestIntToStringAnyBase(-56, str3, 4);
    TestIntToStringAnyBase(1278, str4, 4);
    TestIntToStringAnyBase(8, str5, 8);
    TestIntToStringAnyBase(-16, str6, 8);
    TestIntToStringAnyBase(15, str7, 16);
    TestIntToStringAnyBase(0, str8, 16);
    TestIntToStringAnyBase(567, str9, 32);
    TestIntToStringAnyBase(123456789, str10, 10);
    printf("Test ended.\n\n");
}

static void TestStringToIntAnyBase(const char *str, int base)
{
    printf("String %s in base %d is %d.\n", str, base, StringToIntAnyBase(str, base));
}

static void TestStringToIntAnyBaseEdgeCases()
{
    /*Test StringToIntBase10*/
    char str1[] = "   -101011001ad";
    char str2[] = "\n1111011011";
    
    char str3[] = "	-320.79798";
    char str4[] = "0000103332";
    
    char str5[] = "10";
    char str6[] = "-20";
    
    char str7[] = "~f";
    char str8[] = "F.yug";
    char str9[] = "f";
    char str10[] = "0"; /*max int*/
    
    char str11[] = "HN"; /*min int*/
    char str12[] = "123456789"; /*unsigned int*/

    
    printf("Test String To Int Any Base begin..\n");
    TestStringToIntAnyBase(str1, 2);
    TestStringToIntAnyBase(str2, 2);
    TestStringToIntAnyBase(str3, 4);
    TestStringToIntAnyBase(str4, 4);
    TestStringToIntAnyBase(str5, 8);
    TestStringToIntAnyBase(str6, 8);
    TestStringToIntAnyBase(str7, 16);
    TestStringToIntAnyBase(str8, 16);
    TestStringToIntAnyBase(str9, 16);
    TestStringToIntAnyBase(str10, 16);
    TestStringToIntAnyBase(str11, 32);
    TestStringToIntAnyBase(str12, 10);
    
    printf("Test ended.\n\n");
}

static void TestPrintLetters()
{
        printf("Expected : c d - returned : ");
	PrintLetters("abcd","bcd","b");
	
	printf("Expected : g - returned : ");
	PrintLetters("oooggg","gggggg","bd");
	
	printf("Expected :  - returned : ");
	PrintLetters("ooooooo","gggggg","og");
	
	printf("Expected : b - returned : ");
	PrintLetters("aabb","ab","a");
	
	printf("Expected :  - returned : ");
	PrintLetters("aabb","abewr","ab");
	printf("\n");
}

static void TestLittleEndian()
{
    printf("Result of little endian is-\n");
    CheckLittleEndian();
}

	
int main (void)
{

    TestIntToStringBase10EdgeCases();
    TestAtoiEdgeCases();
    
    TestIntToStringAnyBaseEdgeCases();
    TestStringToIntAnyBaseEdgeCases();
    
    TestPrintLetters();
    TestLittleEndian();
    
    return 0;
}

