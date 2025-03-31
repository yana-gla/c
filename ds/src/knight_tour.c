/*******************************************************************************
* File: knight_tour.c
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
#include <time.h> /*clock*/

#define LEFT_MASK (0xF0)   /*1111 0000*/
#define RIGHT_MASK (0x0F) /*0000 1111*/
#define NUM_MOVES (8)
#define BOARD_IS_FULL 255 /*1111 1111*/


typedef struct
{
	char x;
	char y;
}move_t;

static size_t board = 0; /*64 bit array of the board*/
static move_t moves[NUM_MOVES] = {{1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2, 1}, {-1,2}};


static posotion_t NextPosition(position_t postion, moves_t move);
static void BitOnBoard(position_t postion);
static int IsSafe(position_t position, moves_t move, size_t board);

/******************************************************************************/

/* returns success / failure indicator */
status_t KnightTour(
                position_t initial_position, 
                position_t path[BOARD_SIZE],    /* path arr to store results */
                unsigned int max_runtime,       /* allowed runtime duration before TIMEOUT */
                int use_heuristics)            /* flag to apply Warnsdorff´s heuristics: 1 = use it*/
{
	clock_t start_clock = clock();
	size_t num_checker = 1;
	
	
	path[0] = initial_position;
	board |= BitOnBoard(initial_position);
	
}

position_t BuildPosition(unsigned char x, unsigned char y)
{
	return ((x << 4) | y) ;	
}

void ExtractPosition(position_t pos, unsigned char* x, unsigned char* y)
{
	*y = RIGHT_MASK & pos;
	*x = pos >> 4;
}

/*
int CountOnwardMoves(position_t position, )
{
	
}

/* returns success / failure indicator */
status_t KnightTourHelper(
                position_t path[BOARD_SIZE], 
                int pi,
                unsigned int max_runtime,        
                int use_heuristics, 
				clock_t start_clock,
				size_t board/*size_t num_checker,*/
				) /*path index*/            
{
	int i = 0;
	position_t next_position = 0;
	move_t sorted_moves[NUM_MOVES] = {0};
	
	/*if time passed*/
	clock_t pass_time = (clock() - start_clock) / CLOCKS_PER_SEC;
	if (pass_time > max_run_time)
	{
		return TIMEOUT;
	} 
	
	/*if covered all the board*/
	if (board == BOARD_IS_FULL)
	{
		return SUCCESS;
	}
	
	
	CopyMovesArr(sorted_moves);
	if (use_heuristics) /*Always move the knight to the 
						square with the fewest onward moves*/
	{
		sorted_moves
	}
	
	for (i = 0; i < NUM_MOVES; ++i)
	{
		if (IsSafe(path[pi], moves[i], board))
		{
			status_t status = SUCCESS;
			next_position = NextPosition(postion, move[i]);
			board |= BitOnBoard(next_postion); /*Mark board*/
			path[++pi] = next_position;
			
			status = KnightTourHelper(path, max_runtime, use_heuristicks, start_clock, pi);
			if (SUCCESS == status)
			{
				return SUCCESS;
			}
			else if (TIMEOUT == status)
			{
				return TIMEOUT;
			}
			
			board ^= BitOnBoard(next_postion); /*UnMark board*/
		}
	}
	return DEADEND;
}

static posotion_t NextPosition(position_t postion, moves_t move)
{
	char next_x = 0, next_y = 0;
	
	ExtractPosition(position, &next_x, &next_y);
	next_x += move.x;
	next_y += move.y;
	
	return BuildPosition(next_x, next_y);
}



static void BitOnBoard(position_t postion)
{
	char x = 0, y = 0;
	size_t bit_board = 1;
	
	ExtractPosition(position, &x, &y);
	
	position_on_board = y * BOARD_DIMENSIONS + x;
	/*create mask*/
	bit_board <<= position_on_board; /*0000 1000*/
	return bit_board;
}



/*current position, next move*/
static int IsSafe(position_t position, moves_t move, size_t board)
{
	size_t bit_board = BitOnBoard(postion) & board;
	
	char next_x = 0, next_y = 0;
	position_t next_pos = NextPosition(position, move);
	ExtractPosition(next_pos, &next_x, &next_y);
		
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

static void SortMoves(position_t position, move_t sorted_moves[], board_t board)
{
	int i = 0, j = 0;
	int num_safe_moves[NUM_MOVES] = {0};
	
	for (i = 0; i < NUM_MOVES ; ++i)
	{
		/*if next move is safe*/
		if (IsSafe(position, moves[i], board))
		{
			position_t next_pos = NextPosition(position, move[i]);
/*			char next_x = 0, next_y = 0;*/
			int num_safe_moves = 0;
/*			ExtractPosition(next_pos, &next_x, &next_y);*/
			num_safe_moves[i] = CountSafeMoves(next_pos, move_t moves[]);
			
			
		}
	}	
}

static int CountSafeMoves(position_t pos, move_t moves[])
{
	int i = 0 ;
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














