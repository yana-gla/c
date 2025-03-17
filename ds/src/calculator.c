#include <math.h> /*pow*/
#include <errno.h> /*errno*/

#include "stack.h"
#include "calculator.h"

#define ASCI_SIZE 256
#define NUM_STATES 2
#define OPRND_SIZE 54 /* '^' = 94 - '()' = 40 */
#define STACK_SIZE 100

/*typedef enum*/
/*{*/
/*    CALC_SUCCESS,*/
/*    CALC_DIV_BY_ZERO,*/
/*    CALC_SYNTAX_ERROR,*/
/*    CALC_OUT_OF_BOUNDS,*/
/*	CALC_STACK_OVERFLOW,*/
/*	CALC_MEM_ALLOC_ERROR*/
/*}calc_status_t;*/


/*} calc_status_t; /* status of operation evaluation */*/

/*states*/
typedef enum
{
	W4N, /*wait for number*/        /*0*/
	W4O, /*wait for opertor*/      /*1*/
/*	ACCEPT, /*end of string*/*/   
	ERROR, /*invalid state*/       /*2*/
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
static int prec_lut[ASCI_SIZE] = {0};
static calc_fp operation_lut[NUM_OPT] = {0};

/*LUT initialization function*/
static void Init_transition_lut();
static void Init_prec_lut();
static void Init_operation_lut();

/*Calculation functions*/
/*typedef double (*calc_fp)(double num1, double num2);*/
static double Add(double num1, double num2);
static double Subtract(double num1, double num2);
static double Multiply(double num1, double num2);
static double Divide(double num1, double num2);
static double Power(double num1, double num2);


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























