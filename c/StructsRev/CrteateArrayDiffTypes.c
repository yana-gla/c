#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARR_LEN 3
#define MAX_SIZE_STR 100 /*fix*/

typedef enum {
			INT,       /* =0 */ /*fix*/
			FLT,      /* =1 */
			STR,     /* =2 */
			FUTURE  /* =3 */
} DataType_t;

enum State {SUCCESS, FAIL}; /*fix*/

typedef struct {
	DataType_t type; /*fix*/
	void *ptr_data;                 /* like- int*,  ptr to data */
	void (*p_prnt)(void* element); /*pointer to print function*/
	void (*p_add)(void* element, int a); /*pointer to add function*/ 
	void (*p_cln)(void* element); /*pointer to clen function*/
} strct_element_t;               /*general member*/


void intToStr(int num, char *str) {/*sprintf*/
    int i = 0;
    int j = 0;
    char temp = '\0';
    
    /*if num is negative*/
    int sign = num;

    if (num < 0)
        num = -num;

    while (num > 0) {
      
        str[i++] = num % 10 + '0';
      	num /= 10;
    } 

    if (sign < 0) {
        str[i++] = '-';
    }

    str[i] = '\0';

    /* Reverse- j left, i right*/
   i -= 1;
    while (j < i)
    {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        ++j, --i;
    }
}

	
void EmptyFnct(void* ptr_data)
{
	(void)ptr_data;
}
	
void PrntInt(void *ptr_data)
{
	printf("%d\n", *(int*)&ptr_data);/*fix*/
}

void PrntFlt(void *ptr_data)
{
	printf("%f\n", *(float*)ptr_data);
}

void PrntStr(void *ptr_data)
{
	printf("%s\n", (char*)ptr_data);
}

void AddInt(void* ptr_data, int num)
{
	*(int*)(ptr_data) += num;
}

void AddFlt(void* ptr_data, int num)
{
	*(float*)(ptr_data) += num;
}

void AddStr(void* ptr_data, int num)
{
	char str_num[10] = "";
	intToStr(num, str_num); /*str_num will return num as string*/
	strcat((char*)ptr_data, str_num);
}

void ClnStr(void *data)
{
	free(data);/*fix*/
}

void InitInt(strct_element_t *ptr_strct, int pi)/*fix pi*/
{
	ptr_strct -> type = INT;
	ptr_strct -> ptr_data = pi;
	ptr_strct -> p_prnt = PrntInt;
	ptr_strct -> p_add = AddInt;
	ptr_strct -> p_cln = EmptyFnct;
}

void InitFlt(strct_element_t *ptr_strct, float *pf)
{
	ptr_strct -> type = FLT;
	ptr_strct -> ptr_data = pf;
	ptr_strct -> p_prnt = PrntFlt;
	ptr_strct -> p_add = AddFlt;
	ptr_strct -> p_cln = EmptyFnct;
}

void InitStr(strct_element_t *ptr_strct, char *str)
{
	char *inner_str = (char*)calloc(MAX_SIZE_STR, sizeof(char)); /*The string 
											that will hold the str & the add */
	ptr_strct -> type = STR;
	
	strcpy(inner_str, str);
	
	ptr_strct -> ptr_data = inner_str;
	ptr_strct -> p_prnt = PrntStr;
	ptr_strct -> p_add = AddStr;
	ptr_strct -> p_cln = ClnStr;
}


void InitArr(strct_element_t *ptr_strct, int *pi, float *pf, char *ps) /*pi = pointer int..*/ /*init prnt add to test*/
{	
	InitInt(&ptr_strct[INT], pi);
	InitFlt(&ptr_strct[FLT], pf);
	InitStr(&ptr_strct[STR], ps);
}


void PrntArr(strct_element_t *ptr_strct)
{
	int i = 0;
	for (; i < ARR_LEN ; ++i)
	{
		ptr_strct[i].p_prnt(ptr_strct[i].ptr_data);
	}
}

void AddArr(strct_element_t *ptr_strct, int num)
{
	int i = 0;

	for ( i= 0 ; i < ARR_LEN ; ++i)
	{
		ptr_strct[i].p_add(ptr_strct[i].ptr_data ,num);
	}	
}


void CleanArr(strct_element_t *ptr_strct)
{
	int i = 0;
	
	for ( ; i <  ARR_LEN ; ++i)
	{
		ptr_strct[i].p_cln(ptr_strct[i].ptr_data);
	}
}



int main(void)
{
	int x = 3;
	float f = 2.7;
	char str[] = "Amber The Sweetest Cavalier"; /*Amber is my perfect dog*/
	
	int int_to_add = 0;
	
	strct_element_t strct_arr[ARR_LEN] = {0}; /*initilizing strtct array*/
	
	InitArr(strct_arr, &x, &f, str);
	PrntArr(strct_arr);
	
	printf("\n");
	printf("Enter integer number to add\n");
	scanf("%d", &int_to_add);
	printf("\n");
	
	AddArr(strct_arr, int_to_add);
	PrntArr(strct_arr);
	
	CleanArr(strct_arr);
	
	return (SUCCESS);
}
	
	


