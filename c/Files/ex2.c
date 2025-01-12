#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char *cmmnd;
	int (*cmp_fnc)(const char *cmmnd, const char *input);
	int (*op_func)(const char *filename, const char *input);
}StrOpr;
	
	enum file_op{REMOVE, COUNT, APPEND, EXIT, DEFAULT, SIZE};
	

int CmpFnct(const char *filename, const char *input)

/*Remove Function*/
int RmvFnct(const char *filename, const char *input)
{
}

/*Count Function*/
int CntFnct(const char *filename, const char *input);

/*Append Function*/
int ApndFnct(const char *filename, const char *input);

/*Exit Function*/
int ExtFnct(const char *filename, const char *input);

/*Default Function*/
int DfltFnct(const char *filename, const char *input);


void AppndToFl(char *file_name, char *str_input)
{
	FILE *file =  fopen(file_name, "a");
	
	if (NULL == file)
	{ 
		printf("Error opening file");
		return;
	}
	
	if (fputs(str_input, file)==EOF)
	{	
		printf("Error writng to file");
		return;
	}
	fputs("\n", file);
	
	if(EOF == fclose(file))
	{
		printf("Error closing");
		return;
	}
}

int main(int argc, char** argv)
{
	char *file_name = argv[1];
	char *str_input = '\0';

	str_input = (char*)malloc(100*sizeof(char));
	 
	if (NULL == str_input)
	{
		return 1;
	}
	

	StrOpr arr_op[SIZE] = 
		{ {"-remove", CmpFnct, RmvFnct},
		{"-count",CmpFnct,CntFnct}, 
		{"compare",CmpFnct,AppndToFl}, 
		{"exit",CmpFnct,ExtFnct},
		{"", CmpFnct, DfltFnct}};
	
	printf("Please enter strings\n");
	
	while(1)
	{
		scanf("%s\n", str_input);
	
		AppndToFl(file_name, str_input);
		
	}
	
	free(str_input);

	return 0;
		
}
	
	
