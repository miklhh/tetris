#include "draw.h"
#include "game.h"
#include "blocks.h"

#include <cstdlib>
#include <iostream> // FOR DEBUGING; REMOVE LATER!


/* Game field. */
static int field[GRID_WIDTH][GRID_HEIGHT];


int random_int(int n)
{
	return rand() % n;
}

void setup_game()
{
	for (int width = 0; width < GRID_WIDTH; width++)
	{
		for (int height = 0; height < GRID_HEIGHT; height++)
		{
			field[height][width] = EMPTY;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << block_ref_s.structure.tile[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
}

/* Help function to do matrix rotation of a block. */
static void rotate_block_matrix(block* block, bool counter_clockwise, int matrix_size)
{
	block_struct rotated_block_structure;
	if (counter_clockwise) 
	{
		/* Counter closewise rotation. */
		for (int y = 0; y < (matrix_size); y++)
		{
			for (int x = 0; x < (matrix_size); x++)
			{
				rotated_block_structure.tile[(matrix_size-1) - x][y] = block->structure.tile[y][x];
			}
		}
	}
	else
	{
		/* Clockwise rotation. */
		for (int y = 0; y < (matrix_size); y++)
		{
			for (int x = 0; x < (matrix_size); x++)
			{
				rotated_block_structure.tile[x][(matrix_size-1) - y] = block->structure.tile[y][x];
			}
		}
	}

	/* Give the rotated structure to the block. */
	block->structure = rotated_block_structure;
}

void rotate_block(block* block, bool counter_clockwise)
{
	/* Switch statement for all the blocks. */
	switch (block->block_type)
	{
	case BLOCK_I:
		/* Rotate normaly within all the four tiles.*/
		rotate_block_matrix(block, counter_clockwise, 4);
		break;

	case BLOCK_J:
		/* Rotate normaly within the upper left three tiles. */
		rotate_block_matrix(block, counter_clockwise, 3);
		break;

	case BLOCK_L:
		/* Rotate normaly within the upper left three tiles. */
		rotate_block_matrix(block, counter_clockwise, 3);
		break;

	case BLOCK_O:
		/* Do not rotate this block at all. */
		break;

	case BLOCK_S:
		/* Rotate normaly within the upper left three tiles. */
		rotate_block_matrix(block, counter_clockwise, 3);
		break;

	case BLOCK_T:
		/* Rotate normaly within the upper left three tiles. */
		rotate_block_matrix(block, counter_clockwise, 3);
		break;

	case BLOCK_Z:
		/* Rotate normaly within the upper left three tiles. */
		rotate_block_matrix(block, counter_clockwise, 3);
		break;

	default:
		break;
	}
}


