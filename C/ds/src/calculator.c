#include <math.h> /*pow, isfinite*/
#include <errno.h> /*errno*/
#include <stdlib.h> /*strtod*/
#include <ctype.h> /*isspace*/

#include "stack.h"
#include "calculator.h"

#define ASCI_SIZE 256
#define NUM_STATES 2
#define OPRND_SIZE 53 /* '^' = 94 - '()' = 40 */
#define OFFSET 42 /*asci num of * */
#define STACK_SIZE 100

/*typedef enum*/
/*{*/
/*    SUCCESS,*/
/*    DIV_BY_ZERO,*/
/*    SYNTAX_ERROR,*/
/*    OUT_OF_BOUNDS,*/
/*    MEMORY_FAULT,*/
/*    STACK_OVER_FLOW*/
/*} calc_status_t;*/

/*states*/
typedef enum
{
	W4N, /*wait for number*/        /*0*/
	W4O, /*wait for opertor*/      /*1*/
/*	ACCEPT, /*end of string*/*/   
	FINISH /*invalid state*/       /*2*/
/*	NUM_STATES                    /*3*/*/
}calc_state_t;


/* Function Pointers **********************************************************/
typedef calc_status_t (*handler_f)(char **str, stack_t *num_stack, stack_t *opr_stack);
typedef calc_status_t (*prec_func_t)(char opr, stack_t *num_stack, stack_t *opr_stack);
typedef calc_status_t (*calc_func_t)(double *result, double num1, double num2);

typedef struct 
{
	handler_f handler;
	calc_state_t next_state;
}tran_t; /*transition*/

/*LUT*/
static tran_t g_transition_lut[NUM_STATES][ASCI_SIZE] = {0};
static prec_func_t g_prcdnt_lut[OPRND_SIZE][OPRND_SIZE] = {0};
static calc_func_t g_operation_lut[OPRND_SIZE] = {0};

/*LUT initialization function*/
static void Init_transition_lut();
static void Init_prec_lut();
static void Init_operation_lut();

/*Calculation functions*/
/* calc_func_t */
static calc_status_t Add(double *result, double num1, double num2);
static calc_status_t Subtract(double *result, double num1, double num2);
static calc_status_t Multiply(double *result, double num1, double num2);
static calc_status_t Divide(double *result, double num1, double num2);
static calc_status_t Power(double *result, double num1, double num2)

/*typedef calc_status_t (*handler_f)(char **str, stack_t *num_stack, stack_t *opr_stack);*/

/*Handlers*/

/*W4N Handlers*/
static calc_status_t HndlrGotNum(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	char *remain_eq = NULL;
	calc_status_t status = SUCCESS;
	errno = 0;
	
	double num = strtod(*equation, &remain_eq); /*Q*/
	
	/*error check*/
	if (*equation == remain_eq) /*valid- .5 , invalid- . 5 */
	{
		status = SYNTAX_ERROR;
	}
	
	if (ERANGE == errno)
	{
		status = OUT_OF_BOUND;
	}
	
	Push(num_stack, &num); /*Q*/
	*equation = remain_eq;
	
	(void)opr_stack;
	
	return status;
}

static calc_status_t HndlrTrap(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	(void)equation;
	(void)num_stack;
	(void)opr_stack;
	
	return SYNTAX_ERROR;
}

/*open parentheses*/
static calc_status_t HndlrOpenParen(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	Push(opr_stack, *equation); /*pushing '(' */     /*Q*/
	++(*equation);

	(void)num_stack;
		
	return SUCCESS;
}


/*stack_t *Create(size_t capacity, size_t element_size)*/
status_t Calculate(double *result, const char *str_calc)
{
	double dummy_num = 0;
	char dummy_oprt = '+';
	stack_t *num_stack = NULL, *opr_stack = NULL;
	
	assert (NULL != result);
	assert (NULL != str_calculate);
	
	num_stack = Create(STACK_SIZE, sizeof(double));
	if (NULL == num_stack)
	{
		return MEMORY_FAULT;
	}
	opr_stack = Create(STACK_SIZE ,sizeof(char));
	if (NULL == opr_stack)
	{
		Destroy(num_stack);
		return MEMORY_FAULT;
	}
	
	
	
	
	
	calc_state_t curr_state = W4N; /*at the begin wait for num*/  /*curr = current*/
	calc_status_t curr_status = SUCCESS;
	
	
	
	Destroy(num_stack);
	Destroy(opr_stack);
	
}



/*************************  Calculation functions  ****************************/
static calc_status_t Add(double *result, double num1, double num2)
{
	calc_status_t status = SUCCESS;
	
	*result = num1 + num2;
	
	if (!isfinite(*result))
	{
		status = OUT_OF_BOUNDS;
	}
	
	return status;
}
static calc_status_t Subtract(double *result, double num1, double num2)
{
	calc_status_t status = SUCCESS;
	
	*result = num1 - num2;
	
	if (!isfinite(*result))
	{
		status = OUT_OF_BOUNDS;
	}
	
	return status;
}
static calc_status_t Multiply(double *result, double num1, double num2)
{
	calc_status_t status = SUCCESS;
	
	*result = num1 * num2;
	
	if (!isfinite(*result))
	{
		status = OUT_OF_BOUNDS;
	}
	
	return status;
}
static calc_status_t Divide(double *result, double num1, double num2)
{
	calc_status_t status = SUCCESS;
	
	if (0 == num2)
	{
		return DIV_BY_ZERO;
	}
	
	*result = num1 / num2;
	
	if (!isfinite(*result))
	{
		status = OUT_OF_BOUNDS;
	}
	
	return status;
}

static calc_status_t Power(double *result, double num1, double num2)
{
	calc_status_t status = SUCCESS;
	errno = 0;
	
	*result = pow(num1, num2);
	
	if (EDOM == errno)  /* √(-2) */
	{
		status = SYNTAX_ERROR;
	}
	else if (ERANGE == errno)
	{
		status = OUT_OF_BOUNDS;
	}
	
	return status;
}

/************************   LUT Initialization functions   ********************/
static void Init_operation_lut()
{
	g_operation_lut['+'- OFFSET] = Add;
	g_operation_lut['-' - OFFSET] = Subtract;
	g_operation_lut['*' - OFFSET] = Multiply;
	g_operation_lut['/' - OFFSET] = Divide;
	g_operation_lut['^' - OFFSET] = Power;
}

static void InitPrecLut()
{
	int i = 0, j = 0;
	
	for (i = 0; i < OPRND_SIZE; ++i)
	{
		for (j = 0; i < OPRND_SIZE; ++j)
		{
			g_prcdnt_lut[OPRND_SIZE][OPRND_SIZE] = NULL;
		}
	}
	
	/*			prev          present */
	g_prcdnt_lut['+' - OFFSET]['+' - OFFSET] = CalcOpr;
	g_prcdnt_lut['+' - OFFSET]['-' - OFFSET] = CalcOpr;
	g_prcdnt_lut['+' - OFFSET]['*' - OFFSET] = PushOpr;
	g_prcdnt_lut['+' - OFFSET]['/' - OFFSET] = PushOpr;
	g_prcdnt_lut['+' - OFFSET]['^' - OFFSET] = PushOpr;
	g_prcdnt_lut['+' - OFFSET][')' - OFFSET] = CalcParen;
	
	g_prcdnt_lut['-' - OFFSET]['+' - OFFSET] = CalcOpr;
	g_prcdnt_lut['-' - OFFSET]['-' - OFFSET] = CalcOpr;
	g_prcdnt_lut['-' - OFFSET]['*' - OFFSET] = PushOpr;
	g_prcdnt_lut['-' - OFFSET]['/' - OFFSET] = PushOpr;
	g_prcdnt_lut['-' - OFFSET]['^' - OFFSET] = PushOpr;
	g_prcdnt_lut['-' - OFFSET][')' - OFFSET] = CalcParen;
	
	g_prcdnt_lut['*' - OFFSET]['+' - OFFSET] = CalcOpr;
	g_prcdnt_lut['*' - OFFSET]['-' - OFFSET] = CalcOpr;
	g_prcdnt_lut['*' - OFFSET]['*' - OFFSET] = CalcOpr;
	g_prcdnt_lut['*' - OFFSET]['/' - OFFSET] = CalcOpr;
	g_prcdnt_lut['*' - OFFSET]['^' - OFFSET] = PushOpr;
	g_prcdnt_lut['*' - OFFSET][')' - OFFSET] = CalcParen;
	
	g_prcdnt_lut['/' - OFFSET]['+' - OFFSET] = CalcOpr;
	g_prcdnt_lut['/' - OFFSET]['-' - OFFSET] = CalcOpr;
	g_prcdnt_lut['/' - OFFSET]['*' - OFFSET] = CalcOpr;
	g_prcdnt_lut['/' - OFFSET]['/' - OFFSET] = CalcOpr;
	g_prcdnt_lut['/' - OFFSET]['^' - OFFSET] = PushOpr;
	g_prcdnt_lut['/' - OFFSET][')' - OFFSET] = CalcParen;
	
	g_prcdnt_lut['^' - OFFSET]['+' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET]['-' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET]['*' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET]['/' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET]['^' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcParen;
	
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcOpr;
	g_prcdnt_lut['^' - OFFSET][')' - OFFSET] = CalcOpr;
	g_prcdnt_lut[')' - OFFSET][')' - OFFSET] = CalcParen;
	 
}

typedef struct 
{
	handler_f handler;
	calc_state_t next_state;
}tran_t; 

static void InitTransitionLut()
{
/*	g_transition_lut[NUM_STATES][ASCI_SIZE]*/
	
	int i = 0;
	
	for (i = 0 ; i < ASCI_SIZE ; ++i)
	{
		g_transition_lut[W4N][i] = {HndlrTrap, FINISH};
		g_transition_lut[W4O][i] = {HndlrTrap, FINISH};
	}
	
	/*init W4N*/
	for (i = '0' ; i <= '9' ; ++i)
	{
		g_transition_lut[W4N][i] = {HndlrGotNum, W4O};
	}
	g_transition_lut[W4N]['+'] = {HndlrGotNum, W4O};
	g_transition_lut[W4N]['-'] = {HndlrGotNum, W4O};
	g_transition_lut[W4N][' '] = {HndlrGotNum, W4O};
	g_transition_lut[W4N]['('] = {HndlrOpenParen, W4N};
	
	/*init W4O*/
	g_transition_lut[W4O]['+'] = {, W4N};
	g_transition_lut[W4O]['-'] = {, W4N};
	g_transition_lut[W4O]['*'] = {, W4N};
	g_transition_lut[W4O]['/'] = {, W4N};
	g_transition_lut[W4O]['^'] = {, W4N};
	
	g_transition_lut[W4O][' '] = {HndlrFrwrd, W4O};
	g_transition_lut[W4O][')'] = {, W4O};
	
	g_transition_lut[W4O]['\0'] = {, FINISH};
	g_transition_lut[W4O]['\n'] = {, FINISH};
}


/*typedef enum*/
/*{*/
/*    SUCCESS,*/
/*    DIV_BY_ZERO,*/
/*    SYNTAX_ERROR,*/
/*    OUT_OF_BOUNDS,*/
/*    MEMORY_FAULT,*/
/*    STACK_OVER_FLOW*/
/*} calc_status_t;*/

calc_status_t HndlrCalcOpr(char opr, stack_t *num_stack, stack_t *opr_stack)
{
	double num1 = 0, num2 = 0, result = 0;
	char opr = 0;
	calc_func_t calc_func = 0;
	calc_status_t status = 0;
	
	opr = *(char*)Peek(opr_stack);
	Pop(opr_stack);
	
	num2 = *(double*)Peek(num_stack);
	Pop(num_stack);
	
	num1 = *(double*)Peek(num_stack);
	Pop(num_stack);
	
	calc_func = g_operation_lut[opr - OFFSET];
	status = calc_func(&result, num1, num2);
	
	Push(num_stack, &result);
	Push(opr_stack, &opr);	
	
	return status;
}

calc_status_t HndlrPushOpr(char opr, stack_t *num_stack, stack_t *opr_stack)
{
	Push(opr_stack, &opr);
	
	(void)num_stack;
	
	return SUCCESS;
}

calc_status_t HndlrCalcParen(char opr, stack_t *num_stack, stack_t *opr_stack)
{
	calc_status_t status = SUCCESS;
	
	opr = *(char*)Peek(opr_stack);
	
	while ( (Size(stack_num) > 1) && 
		  ( *(char*)Peek(opr_stack) != '(' ) &&
			 (SUCCESS == status) )
	{
		Pop(opr_stack);
		status = CalcOpr(opr - OFFSET, num_stack, opr_stack);
	}
	
	if ('(' == opr)
	{
		Pop(opr_stack);
		return status;
	}
	else 
	{
		return SYNTAX_ERROR;
	}
}


/*W4O Handlers*/
/*W4O space*/
static calc_status_t HndlrFrwrd(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	++(*equation);
	
	(void)num_stack;
	(void)opr_stack;
	
	return SUCCESS;
}

/* /0 /n */
static HndlrCalcAll(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	
}
















