/*******************************************************************************
* File: knight_tour.h
*
* Purpose:
*   Implement
*	
*	
*	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   __________
*
*Date: 30/03/2025
*Last Update: --/--/----
*******************************************************************************/
#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__


#define BOARD_DIMENSIONS (8)
#define BOARD_SIZE (BOARD_DIMENSIONS * BOARD_DIMENSIONS)

/* Two Options for position_t */
typedef unsigned char position_t; /*x: 11110000 y: 00001111*/
typedef unsigned char uchar_t;

typedef enum
{
    SUCCESS,
    DEADEND, /* no solution found */
    TIMEOUT  /* timed-out before finding solution */
} status_t;

/* returns success / failure indicator */
status_t KnightTour(
                position_t initial_position, 
                position_t path[BOARD_SIZE],    /* path arr to store results */
                unsigned int max_runtime,       /* allowed runtime duration before TIMEOUT */
                int use_heuristics);            /* flag to apply Warnsdorff´s heuristics: 1 = use it*/


position_t BuildPosition(unsigned char x, unsigned char y);
void ExtractPosition(position_t pos, unsigned char* x, unsigned char* y);


/* Client Side *************************************************************/
/* position 0 will be the initial position we get from the user */
position_t path[64] = {0};


/* Other Notes *************************************************************/
/**
 * inside function SolveKnightTour:
 * (initial positions are in path[0])
 * positions[0].x = initial_x;
 * positions[0].y = initial_y; 
 */
 
 /* reach solution in 5 minutes max, even if it can lead to success. */




#endif
