/*******************************************************************************
* File: knight_tour.h
*
* Purpose:
*   Implement Knight’s tour problem
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

typedef unsigned char position_t; /*x: 11110000 y: 00001111*/
typedef unsigned char uchar_t;

typedef enum
{
    SUCCESS,
    DEADEND, /* no solution found */
    TIMEOUT  /* timed-out before finding solution */
} status_t;


status_t KnightTour(position_t initial_position, 
            	    position_t path[BOARD_SIZE],  
             	   unsigned int max_runtime,        
               		 int use_heuristics);         

position_t BuildPosition(unsigned char x, unsigned char y);
void ExtractPosition(position_t pos, unsigned char* x, unsigned char* y);


#endif
