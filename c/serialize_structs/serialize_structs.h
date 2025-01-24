#ifndef __SEREALIZE_STRUCTS_H__
#define __SEREALIZE_STRUCTS_H__

#include <limits.h> /*for SCHAR_MAX*/
#include <stdio.h> /*for FILE* */

typedef struct{
        int math;
        int physics;
        int chimics;
} real_grades_t;

typedef struct {
        int sociology;
        int psychology;
        int literature;
} humanistic_grades_t;

typedef struct {
        real_grades_t real_gr;
        humanistic_grades_t human_gr;
        float sport_gr;
} grades_t;

typedef struct {
	char name[SCHAR_MAX];
	char last_name[SCHAR_MAX];
        grades_t grades_all;
} student_t;

void SaveStudent(FILE *file_write, student_t *student);
void LoadStudent(FILE *file_read, student_t *student);

#endif
