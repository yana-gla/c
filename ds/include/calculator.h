
/*legal operands 0 1 2 3 4 5 6 7 8 9 . e? */
/*legal operation -, +, *, /, ^, ( ) */
/*spaces between num/ operand discarded, spaces within a number cause error*/
/*Time complecity O()*/


typedef enum
{
    CALC_SUCCESS,
    CALC_SYNTAX_ERROR,
    CALC_DIV_BY_ZERO,
    CALC_OUT_OF_BOUNDS
} calc_status_t; /* status of operation evaluation */

status_t Calculate(double *result, const char *str);

