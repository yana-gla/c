/*
*	Writer : Ofir Hasson
*	Implementation of the knight tour problem
*
*	Reviewed by: 
*	Reviewed date:
*/

#include <stdio.h> /* For printf */
#include <assert.h> /* For assert */
#include "knight_tour.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define UNFORMAT "\x1b[1;0m"

static void KnightTourTest();
static void PrintStatus(status_t status);
static void PrintPath(position_t path[BOARD_SIZE]);

int main(void)
{
	printf("Beginning knight_tour.c tests...\n\n");

	KnightTourTest();

	return (0);
}

static void KnightTourTest()
{
	size_t i = 0 , j = 0;
	position_t path[BOARD_SIZE] = {0};
	
	for(i = 0 ; i < BOARD_DIMENSIONS ; ++i)
	{
		for(j = 0 ; j < BOARD_DIMENSIONS ; ++j)
		{
			printf("X - %ld , Y - %ld", i,j);
			PrintStatus(KnightTour(BuildPosition(i,j), path,300,1));
		}
	}
	
	printf("\n\nExample Path for (0,0)\n\n");
	KnightTour(BuildPosition(0,0), path,300,1);
	PrintPath(path);
	
}

static void PrintStatus(status_t status)
{
	if(0 == status)
	{
		printf(GREEN"\tSUCCESS!\n"UNFORMAT);
	}
	if(1 == status)
	{
		printf(RED"\tDEADEND!\n"UNFORMAT);
	}
	if(2 == status)
	{
		printf(RED"\tTIMEOUT!\n"UNFORMAT);
	}
}

static void PrintPath(position_t path[BOARD_SIZE])
{
	size_t i = 0;

	for(i = 0 ; i < BOARD_SIZE ; ++i)
	{
		unsigned char x = 0 , y = 0;
		ExtractPosition(path[i], &x , &y);
		printf("X - %d , Y - %d\n", x,y);
	}
}















