#include <stdio.h>
#include "ins_glb.h"


int g_x = 27;

void PrintGlobalVariableAddress()
{
	printf("Adress of g_x is: %p.\n", (void*)&g_x);
}
 
