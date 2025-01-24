#include <limits.h> /*for UCHAR*/
#include <stdio.h> /*for files*/
#include "serialize_structs.h"
#include <assert.h> /*for assert*/
#include <string.h> /*for strcmp*/

static void TestSerializeStructs(student_t *ps1, student_t *ps2);

int main()
{
    student_t yana = {"Yana", "Glazer", { {99, 98, 97}, {85, 86, 87}, 100 } };
    student_t test_student = {0};
    
    FILE *file = fopen("Yana.bin", "wb");
    
    if (NULL == file)
    {
        printf("Error opening file for saving!\n");
        return 1;
    }
  
    SaveStudent(file, &yana);
    
    file = fopen("Yana.bin", "rb+");
    
    if (NULL == file)
    {
        printf("Error opening file for loading!\n");
        return 1;
    }
    
    LoadStudent(file, &test_student);
    
    TestSerializeStructs(&yana, &test_student);
    
    return 0;
}


static void TestSerializeStructs(student_t *ps1, student_t *ps2)
{
    printf("Begin compare each field..\n");
    
    assert (0 == strcmp(ps1 -> name, ps2 -> name)); 
    assert (0 == strcmp(ps1 -> last_name, ps2 -> last_name)); 
    
    assert (ps1 -> grades_all.sport_gr == ps2 -> grades_all.sport_gr);
    
    assert (ps1 -> grades_all.real_gr.math == ps2 -> grades_all.real_gr.math) ;
    assert (ps1 -> grades_all.real_gr.physics == ps2 -> grades_all.real_gr.physics);
    assert (ps1 -> grades_all.real_gr.chimics ==  ps2 -> grades_all.real_gr.chimics);
    
    assert (ps1 -> grades_all.human_gr.sociology == ps2 -> grades_all.human_gr.sociology) ;
    assert (ps1 -> grades_all.human_gr.psychology == ps2 -> grades_all.human_gr.psychology);
    assert (ps1 -> grades_all.human_gr.literature ==  ps2 -> grades_all.human_gr.literature);

    printf("Finish compare fields.\n");

}




