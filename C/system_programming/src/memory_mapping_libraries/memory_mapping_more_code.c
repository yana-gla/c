#include <stdlib.h>
#include <stdio.h>
#include "memory_mapping.h"

int more_code_global = something + 1;
static int something_else = something + 1;

static void StaticFunction()
{
    int* p_more_code_global = &more_code_global;
    int* p_something_else = &something_else;

    /* Cancel "unsused variable" warnings: */
    (void)p_more_code_global;
    (void)p_something_else;
}

void ExternFunction()
{
    int a = something_else;

    /* Cancel "unsused variable" warnings: */
    (void)a;
}

int MemoryMappingCode2(int functions_arg_1,float functions_arg_2,double functions_arg_3)
{  
    static int recursion_level = 0;

    int i = 5;
    int* p_i = &i;
    char a = 'h';
    char* p_a = &a;
    char b = 'w';
    char* p_b = &b;
    int j = 1;
    int* p_j = &j;

    int* p_arg1 = &functions_arg_1;
    
    float* p_arg2 = &functions_arg_2;
    
    double* p_arg3 = &functions_arg_3;
    
    void(*p_static_function)() = StaticFunction;
    void(*p_extern_function)() = ExternFunction;
    int* p_heap_var = (int*)malloc(sizeof(int));
    char* p_heap_var2 = (char*)malloc(sizeof(char)); /* Check allignment */
    short* p_heap_var3 = (short*)malloc(sizeof(short)); /* Check allignment */    
    const int const_local = 5;
    const int* p_const_local = &const_local;
    const int non_const_local = 5;
    const int* p_non_const_local = &non_const_local;
    int* p_global_var1 = &global_var1;
    int* p_global_var2 = &global_var2;
    int* p_global_var3 = &global_var3;
    static int static_local_var1 = 111;
    static int static_local_var2 = 222;
    static int static_local_var3 = 333;
    int* p_static_local_var1 = &static_local_var1;
    int* p_static_local_var2 = &static_local_var2;
    int* p_static_local_var3 = &static_local_var3;
    int* p_static_global_var1 = &static_global_var1;
    int* p_static_global_var2 = &static_global_var2;
    int* p_static_global_var3 = &static_global_var3;
    char* string_literal = "abc";
    int* p_global_weak_symbol = &g_weak_symbol;

    ++recursion_level;

    /* While debugging, when you want to stop the recursion and see stack unwinding - 
       set this variable to 0 (using the debugger itslef: */
    if (global_var1 == 0)
    {
        return recursion_level;
    }
	printf("yana2\n");
    MemoryMappingCode1(functions_arg_1+1,functions_arg_2+1,functions_arg_1+1);

    /* Cancel "unsused variable" warnings: */
    (void)i;
    (void)p_i;
    (void)a;
    (void)p_a;
    (void)b;
    (void)p_b;
    (void)p_j;
    (void)p_arg1;
    (void)p_arg2;
    (void)p_arg3;
    (void)p_static_function;
    (void)p_extern_function;
    (void)p_heap_var;
    (void)p_heap_var2;
    (void)p_heap_var3;
    (void)const_local;
    (void)p_const_local;
    (void)non_const_local;
    (void)p_non_const_local;
    (void)p_global_var1;
    (void)p_global_var2;
    (void)p_global_var3;
    (void)global_var3;
    (void)static_local_var1;
    (void)static_local_var2;
    (void)static_local_var3;
    (void)p_static_local_var1;
    (void)p_static_local_var2;
    (void)p_static_local_var3;
    (void)p_static_global_var1;
    (void)p_static_global_var2;
    (void)p_static_global_var3;
    (void)string_literal;
    (void)p_global_weak_symbol;

    /* Unreachable code: */
    
    /* free is here for bravity, code is unreachable, we never free - 
       in order to examine heap allocations growth. */
    free(p_heap_var);
    free(p_heap_var2);
    free(p_heap_var3);

    return recursion_level;
}

