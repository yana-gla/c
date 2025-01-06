#include <stdio.h>

size_t StrLen(char *str)
{
int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
return i;
}

int StrCmp(char *str_1, char *str_2)
{
	int i = 0;
	
	while(*str_1 != '\0' && *str_2 != '\0' && *str_1 == *str_2)
	{
		str_1++;
		str_2++;
	}
	return *str_1 - *str_2;
}

int IsPldrm(char *str)
{
	
	int left = 0;
	int right = StrLen(str)-1;
	//printf("the len is %d", i);
	
	while (left < right)
	{
		if (str[left] != str[right])
		{
			return 0;
		}
		
		left++;
		right--;
	}
	return 1;
}
	
	


int main (void)
{
	char str1[] = "YANA", str2[]= "DANA";
	
	//printf("len of yana is %ld", StrLen(str1));
	//printf("compare is %d", StrCmp(str1, str2));
	
	printf("%d", IsPldrm(str1));
	
}




