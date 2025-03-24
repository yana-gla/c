/*******************************************************************************
* File: calculator.h
*
* Purpose:
*   Implement Calculator that supports: +, -, *, /, ^, ( ).
	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   __________
*
*Date: 22/03/2025
*Last Update: --/--/----
*******************************************************************************/
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum
{
    SUCCESS,
    DIV_BY_ZERO,
    SYNTAX_ERROR,
    OUT_OF_BOUNDS,
    MEMORY_FAULT,
    STACK_OVER_FLOW
} calc_status_t; /* status of operation evaluation */



/*******************************************************************************
* Calculate
* x
* 
* Params:
* 	x
*   x
*
* Returns:
* 	x
*
* Time Complexity: O(n)
* Space Complexity: O(1)
*
*Note:
*	x
*******************************************************************************/
status_t Calculate(double *result, const char *str);


#endif
