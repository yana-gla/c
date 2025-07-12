#include <stdio.h> /*FILES*/
#include <limits.h> /*for UCHAR*/
#include "serialize_structs.h"

void SaveStudent(FILE *file_write, student_t *student)
{
    if (NULL == file_write)
    {
        printf("Error opening file!\n");
    }
    
    if (0 == fwrite(student, sizeof(student_t), 1, file_write))
    {
        printf("Error writing to file!\n");
    }
    
    if (EOF == fclose(file_write))
    {
        printf("Error closing file!\n");
    }
}

void LoadStudent(FILE *file_read, student_t *student)

{
    if (NULL == file_read)
    {
        printf("Error opening file!\n");
    }
    
    if (0 == fread(student, sizeof(student_t), 1, file_read))
    {
        printf("Error reading from file!\n");
    }
    
   if (EOF == fclose(file_read))
   {
        printf("Error closing file!\n");
   }
   

}






