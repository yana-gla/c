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
#include <time.h> 		  /*clock*/
#include "knight_tour.h" /*own header*/

#define RIGHT_MASK (0x0F) /*0000 1111*/
#define NUM_MOVES (8)

typedef struct
{
	char x;
	char y;
}move_t;

static move_t moves[NUM_MOVES] = {{1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2, 1}, {-1,2}};


static position_t NextPosition(position_t position, move_t move);
static size_t BitOnBoard(position_t postion);
static int IsSafe(position_t position, move_t move, size_t board);
status_t KnightTourHelper(position_t path[BOARD_SIZE], int pi, 
						unsigned int max_runtime, int use_heuristics, 
						clock_t start_clock, size_t board); /*path index*/ 
static void CopyMovesArr(move_t sorted_moves[]);
static void Warnsdorff(position_t position, move_t sorted_moves[], size_t board);
static void InsertionSort(int num_safe_moves[], move_t sorted_moves[]);
static int CountSafeMoves(position_t pos, move_t moves[], size_t board);

/******************************************************************************/
/* returns success / failure indicator */
status_t KnightTour(
                position_t initial_position, 
                position_t path[BOARD_SIZE],    /* path arr to store results */
                unsigned int max_runtime,       /* allowed runtime duration before TIMEOUT */
                int use_heuristics)            /* flag to apply Warnsdorff´s heuristics: 1 = use it*/
{
	clock_t start_clock = clock();
	size_t board = 0;
	
	path[0] = initial_position;
	board |= BitOnBoard(initial_position);
	return (KnightTourHelper(path, 0, max_runtime, use_heuristics, 
							start_clock, board));  
}

/******************************************************************************/
position_t BuildPosition(uchar_t x, uchar_t y)
{
	return ((x << 4) | y) ;	
}

/******************************************************************************/
void ExtractPosition(position_t pos, uchar_t *x, uchar_t *y)
{
	*y = RIGHT_MASK & pos;
	*x = pos >> 4;
}

/**********************     Static function ***********************************/
status_t KnightTourHelper(
                position_t path[BOARD_SIZE], 
                int pi,
                unsigned int max_runtime,        
                int use_heuristics, 
				clock_t start_clock,
				size_t board/*size_t num_checker*/
				) /*path index*/            
{
	int i = 0;
	position_t next_position = 0;
	move_t sorted_moves[NUM_MOVES] = {0};
	
	/*if time passed*/
	clock_t pass_time = (clock() - start_clock) / CLOCKS_PER_SEC;
	if (pass_time > max_runtime)
	{
		return TIMEOUT;
	} 
	
	/*if covered all the board*/
	if (pi == BOARD_SIZE -1 )
	{
		return SUCCESS;
	}
	
	CopyMovesArr(sorted_moves);
	if (use_heuristics) /*Always move the knight to the 
						square with the fewest onward moves*/
	{
		Warnsdorff(path[pi], sorted_moves, board);
	}
	
	for (i = 0; i < NUM_MOVES; ++i)
	{
		if (IsSafe(path[pi], sorted_moves[i], board))
		{
			
			
			status_t status = SUCCESS;
		
			next_position = NextPosition(path[pi],sorted_moves[i]);
			board |= BitOnBoard(next_position); /*Mark board*/
			path[++pi] = next_position;
			
			status = KnightTourHelper(path, pi, max_runtime, use_heuristics,
									 start_clock, board);
			if (SUCCESS == status)
			{
				return SUCCESS;
			}
			else if (TIMEOUT == status)
			{
				return TIMEOUT;
			}
			
			board ^= BitOnBoard(next_position); /*UnMark board*/
		}
	}
	return DEADEND;
}

/******************************************************************************/
static position_t NextPosition(position_t position, move_t move)
{
	uchar_t next_x = 0, next_y = 0;
	
	ExtractPosition(position, &next_x, &next_y);
	next_x += move.x;
	next_y += move.y;
	
	return BuildPosition(next_x, next_y);
}

/******************************************************************************/
static size_t BitOnBoard(position_t position)
{
	uchar_t x = 0, y = 0;
	size_t bit_board = 1;
	position_t position_on_board = 0;
	
	ExtractPosition(position, &x, &y);
	
	position_on_board = x * BOARD_DIMENSIONS + y;
	/*create mask*/
	bit_board <<= position_on_board; /*0000 1000*/
	return bit_board;
}

/******************************************************************************/
/*current position, next move*/
static int IsSafe(position_t position, move_t move, size_t board)
{
	size_t bit_board = BitOnBoard(NextPosition(position,move)) & board;
	char next_x = 0, next_y = 0;
	
	ExtractPosition(position, (uchar_t*)&next_x, (uchar_t*)&next_y);
	next_x += move.x, next_y+= move.y;
		
	return ((next_x >= 0) && (next_x <= 7) && (next_y >= 0) && (next_y <= 7) 
			&& (bit_board == 0));
}

/******************************************************************************/
static void CopyMovesArr(move_t sorted_moves[])
{
	int i = 0;
	
	for (i = 0 ; i < NUM_MOVES ; ++i)
	{
		sorted_moves[i] = moves[i];
	}
}

/******************************************************************************/
static void Warnsdorff(position_t position, move_t sorted_moves[], size_t board)
{
	int i = 0;
	int num_safe_moves[NUM_MOVES] = {0};
	
	for (i = 0; i < NUM_MOVES ; ++i)
	{
		/*if next move is safe*/
		if (IsSafe(position, sorted_moves[i], board))
		{
			position_t next_pos = NextPosition(position, sorted_moves[i]);
			num_safe_moves[i] = CountSafeMoves(next_pos, sorted_moves, board);
		}
	}
	InsertionSort(num_safe_moves, sorted_moves);	
}

/******************************************************************************/
static void InsertionSort(int num_safe_moves[], move_t sorted_moves[])
{
	size_t i = 0, j = 0;
	int key_num = 0;
	move_t key_move = {0};
	
	for (i = 1; i < NUM_MOVES ; ++i)
	{
		key_num = num_safe_moves[i];
		key_move = sorted_moves[i];
		 /*start comparing from adjacent element to key, key is 3- 2,1,0*/
		/*move elemnts greater than key one position right*/
		for (j = i ; (j > 0) && (key_num < num_safe_moves[j - 1]); --j)
		{
			num_safe_moves[j] = num_safe_moves[j-1];
			sorted_moves[j] = sorted_moves[j-1];
		}
		num_safe_moves[j] = key_num;
		sorted_moves[j] = key_move;
	}
}

/******************************************************************************/
static int CountSafeMoves(position_t pos, move_t moves[], size_t board)
{
	int i = 0;
	int num_safe_moves = 0;
	
	for (i = 0; i < NUM_MOVES ; ++i)
	{
		if (IsSafe(pos, moves[i], board))
		{
			++num_safe_moves;
		}
	}
	return num_safe_moves;
}

/******************************************************************************/
