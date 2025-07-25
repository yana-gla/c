#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 100

typedef struct{
	char *cmmnd;
	int (*cmp_fnc)(const char *cmmnd, const char *input);
	int (*op_func)(const char *filename, const char *input);
}str_op_t;
	
enum file_op {DEFAULT, REMOVE, COUNT, EXIT, BEGIN, SIZE};
	

/*Compare Function For AddBegining*/
int CmpBgn(const char *input, const char *cmm_str)
{
    return (*input == *cmm_str) ? (0) : (1);
}

/*Compare Append- accept every string*/
int CmpApnd(const char *input, const char *cmm_str)
{
    (void) input;
    (void) cmm_str;
    return (0);
}

/*Remove Function*/
int RmvFile(const char *filename, const char *input)
{
	(void) input;
	if (0 != remove(filename))
	{
		printf("Error when deleting a file");
	}
	return (REMOVE);
}

/*Exit Function*/
int Exit(const char *filename, const char *input)
{
	(void) filename;
	(void) input;
	return (EXIT);
}

/*Count Function*/
int CntLines(const char *filename, const char *input)
{
	size_t num_lns = 0;
	FILE* fp = fopen(filename, "r");
	char *tmp = (char*)calloc(MAX_LIMIT, sizeof(char));
	if (NULL == tmp) return -1;
	
	(void) input;
	
	while (NULL != fgets(tmp, MAX_LIMIT, fp))
	{
	    ++num_lns;
	}
	
	fclose(fp);
	free(tmp);
	printf("Number of lines in file is %ld\n", num_lns);
	
	return (COUNT);
}


/*Add To Beginig Function*/
int AddBegin(const char *filename, const char *input)
{
    char buffer[MAX_LIMIT]= "";
    FILE *fpt = NULL; /*the original file*/
    FILE *fpt_tmp = NULL; /*new tmp file*/
     
    fpt = fopen(filename, "r");
        if (NULL == fpt) return -1;
    fpt_tmp = fopen("tmp.txt", "w+");
        if (NULL == fpt_tmp) return -1;
        
    if (EOF == fputs(input+1, fpt_tmp)) return -1; /*skips the first because it <*/
    if (EOF == fputs("\n", fpt_tmp)) return -1; /*new line*/
    
    while (NULL != fgets(buffer, MAX_LIMIT, fpt)) /*reading from origin*/
    { 
      if (EOF == fputs(buffer, fpt_tmp)) return -1; /*and copy to temp*/
    }
    
    fclose(fpt);
    fclose(fpt_tmp);
    
    if (0 != remove(filename)) return -1;
    
    if (0 != rename("tmp.txt", filename)) return -1;
    
    return (BEGIN);
}

/*Append Function*/
int ApndFnct(const char *file_name,const  char *str_input)
{
	FILE *file =  fopen(file_name, "a");
	
	if (NULL == file)
	{ 
		printf("Error opening file");
	}
	
	if (EOF == fputs(str_input, file))
	{	
		printf("Error writng to file");
	}
	fputs("\n", file);
	
	if(EOF == fclose(file))
	{
		printf("Error closing");
	}
	
	return(DEFAULT);
}

int main(int argc, char** argv)
{
	int i = 0;
	char *file_name = argv[1];
	int num_opr = DEFAULT;
	char str_input[MAX_LIMIT] = "";
	str_op_t arr_op[SIZE] = 
		{ {"-remove", strcmp, RmvFile},
		  {"-count",strcmp,CntLines}, 
	   	  {"-exit",strcmp,Exit},
		  {"<", CmpBgn, AddBegin},
		  {"",CmpApnd, ApndFnct} };
		
	(void) argc;
	
	printf("Please enter strings\n");
	
	while(num_opr != EXIT)
	{
		scanf("%99[^\n]", str_input);  /*Reads max 99 chars*/
		getchar(); /* Consume the newline */                              

		for(i = 0 ; i < SIZE ; ++i)
		{
			if (0 == arr_op[i].cmp_fnc(arr_op[i].cmmnd, str_input))
			{
				num_opr = arr_op[i].op_func(file_name, str_input);	
				break;	
			}
		}
	}
	
	return 0;	
}
