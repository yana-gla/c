#include <stdio.h>

void Print(int x)
{
	printf("%d\n", x);
}

typedef struct Print // יש לך גם פונקציה וגם סטרקט עם אותו שם וזה עשוי לבלבל
{
	int x;
	void (*fptr)(int); // ממליץ לעשות לו גם טייפ-דפ

}print_me;

int main(void)
{
	size_t i = 0; //לא יודע אם זה קריטי אבל size_t זה בגודל 8 בתים ואין צורך בכל כך הרבה.
	print_me arr[10]; 
	
	for( ; i < 10; ++i)
	{
		arr[i].x = i;
		arr[i].fptr = &Print;
		arr[i].fptr(arr[i].x); 
	}
	
	return 0;
}

	
	
	
	
