#include <math.h> /*pow*/
#include <errno.h> /*errno*/
#include <stdlib.h> /*strtod*/
#include <ctype.h> /*isspace*/

#include "stack.h"
#include "calculator.h"

#define ASCI_SIZE 256
#define NUM_STATES 2
#define OPRND_SIZE 54 /* '^' = 94 - '()' = 40 */
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

typedef enum{
	ADD,  /*0*/
	SUB,  /*1*/
	MUL,  /*2*/
	DIV,  /*3*/
	POW,  /*4*/
	NUM_OPT  /*5*/
}oprt_t;

/* Function Pointers **********************************************************/
typedef calc_status_t (*handler_f)(char **str, stack_t *num_stack, stack_t *opr_stack);
typedef double (*calc_fp)(double num1, double num2);
typedef calc_status_t (*prec)(stack_t *num_stack, stack_t *opr_stack);


typedef struct 
{
	handler_f handler;
	state_t next_state;
}tran_t; /*transition*/

/*LUT*/
static tran_t transition_lut[NUM_STATES][ASCI_SIZE] = {0};
static int prcdnt_lut[OPRND_SIZE][OPRND_SIZE] = {0};
static calc_fp operation_lut[NUM_OPT] = {0};

/*LUT initialization function*/
static void Init_transition_lut();
static void Init_prec_lut();
static void Init_operation_lut();

/*Calculation functions*/
static double Add(double num1, double num2);
static double Subtract(double num1, double num2);
static double Multiply(double num1, double num2);
static double Divide(double num1, double num2);
static double Power(double base, double power);

/*typedef calc_status_t (*handler_f)(char **str, stack_t *num_stack, stack_t *opr_stack);*/

/*Handlers*/


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

static HndlrTrap(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	(void)equation;
	(void)num_stack;
	(void)opr_stack;
	return SYNTAX_ERROR;
}

/*open parentheses*/
static HndlrOpenParen(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	Push(opr_stack, *equation); /*pushing '(' */     /*Q*/
	++(*equation);

	(void)num_stack;
		
	return SUCCESS;
}


/*static HndlrOprnd(char **equation, stack_t *num_stack, stack_t *opr_stack)*/
/*{*/
/*	char curr_oprnd = **equation;*/
/*	char prev_oprnd = *(char*)(Peek(opr_stack));*/
/*	*/
/*	prcdnt_lut[curr_oprnd][prev_oprnd]( params );*/
/*	*/
/*	++(*equation);*/
/*	*/
/*}*/

/*static HndlrCalc(char **equation, stack_t *num_stack, stack_t *opr_stack)*/
/*{*/
/*	double num1 = 0, num2 = 0, result = 0;*/
/*	char oprt = *(char*)Peek(opr_stack);*/
/*	Pop(opr_stack);*/
/*	*/
/*	num2 = *(double*)Peek(num_stack);*/
/*	Pop(num_stack);*/
/*	*/
/*	num1 = *(double*)Peek(num_stack);*/
/*	Pop(num_stack);*/
/*	*/
/*	result = operation_lut[oprt](num1)(num2);*/
/*	*/
/*	Push(num_stack, &result);*/
/*	*/
/*}*/


/*static HndlrPushOprnd(char **equation, stack_t *num_stack, stack_t *opr_stack)*/
/*{*/
/*	char oprt = **equation;*/
/*	Push(opr_stack, *equation);*/
/*	*/
/*	(void)num_stack;*/
/*}*/


static HndlrFrwrd(char **equation, stack_t *num_stack, stack_t *opr_stack)

/*W4O space*/
static HndlrFrwrd(char **equation, stack_t *num_stack, stack_t *opr_stack)
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

static HndlrCloseParen(char **equation, stack_t *num_stack, stack_t *opr_stack)
{
	
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
		return CALC_MEM_ALLOC_ERROR;
	}
	opr_stack = Create(STACK_SIZE ,sizeof(double));
	if (NULL == opr_stack)
	{
		Destroy(num_stack);
		return CALC_MEM_ALLOC_ERROR;
	}
	

	
	
	
	calc_state_t curr_state = W4N; /*at the begin wait for num*/  /*curr = current*/
	calc_status_t curr_status = SUCCESS;
	
	
	
	Destroy(num_stack);
	Destroy(opr_stack);
	
}



/*************************  Calculation functions  ****************************/
static double Add(double num1, double num2)
{
	return (num1 + num2);
}
static double Subtract(double num1, double num2)
{
	return (num1 - num2);
}
static double Multiply(double num1, double num2)
{
	return (num1 * num2);
}
static double Divide(double num1, double num2)
{
	if (0 == num2)
	{
		
	}
	return (num1 / num2);
}
static double Power(double num1, double num2)
{
	return (pow(num1, num2));
}


/************************   LUT Initialization functions   ********************/
static void Init_transition_lut();
static void Init_prec_lut();

static void Init_operation_lut()
{
	prec_lut[ADD] = 1;
	prec_lut[SUB] = 1;
	prec_lut[MUL] = 2;
	prec_lut[DIV] = 2;
	prec_lut[POW] = 3;
}























