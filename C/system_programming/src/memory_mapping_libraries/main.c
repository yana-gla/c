#include "memory_mapping.h"

int main(int argc, char *argv[], char *envp[])
{
    char** p_command_line_arguments = argv;
    char** p_environment_variables = envp;

    MemoryMappingCode1(1,1.0f,1.0);

    /* Cancel "unsused variable" warnings: */
    (void)p_environment_variables;
    (void)p_command_line_arguments;
    (void)argc;    

    return 0;
}
