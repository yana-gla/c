/*************************************************************************
Author: Yana Glazer

Atoi WorkSheet

Revied by: Sharona Amran

22/01/2025
*************************************************************************/
#ifndef __ATOI_H__
#define __ATOI_H__

char* IntToStringBase10(int num, char* buffer);
int StringToIntBase10(const char *str);

char* IntToStringAnyBase(int num, char* buffer, int base);
int StringToIntAnyBase(const char *str, int base);

void PrintLetters(const char *str1, const char *str2, const char *str3);
int CheckLittleEndian();

#endif
