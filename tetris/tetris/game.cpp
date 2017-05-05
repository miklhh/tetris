#include "draw.h"
#include "game.h"
#include "blocks.h"
#include "data_structures.h"

#include <stdlib.h>
#include <iostream> // FOR DEBUGING; REMOVE LATER!


/* Game field. MAKE STATIC IN RELEASE!*/
//static box_t field[GRID_HEIGHT][GRID_WIDTH];
         box_t field[GRID_HEIGHT][GRID_WIDTH];


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
			field[height][width].tile       = EMPTY;
			field[height][width].color_f	    = COLOR_BACKGROUND_FORTH;
			field[height][width].color_b	    = COLOR_BACKGROUND_BACK;
		}
	}
}

void block_move(block_t* block, direction_t direction)
{
	switch (direction)
	{
	case DIRECTION_LEFT:
		block->position.x += -1;
		break;

	case DIRECTION_RIGHT:
		block->position.x += 1;
		break;

	case DIRECTION_UP:
		block->position.y += -1;
		break;

	case DIRECTION_DOWN:
		block->position.y += 1;
		break;

	default:
		std::cout << "Error, tried to move block in non defined direction. " << std::endl;
		break;
	}
}

/* Help function to do matrix rotation of a block. */
static void rotate_block_matrix(block_t* block, bool counter_clockwise, int matrix_size)
{
	block_struct_t rotated_block_structure;
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

void block_rotate(block_t* block, bool counter_clockwise)
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

collision_t test_rotatable(block_t* block, bool counter_clockwise)
{
	/* Make a copy of the block and rotate the copy. */
	block_t block_copy = *block;
	block_rotate(&block_copy, counter_clockwise);

	/* Test if any part of the copied block interfears with the taken boxes on the field. 
	 * Also test if the copied block interfears with the wall. Return accordingly. */
	collision_t collision = NO_COLLISION;
	
	/* Test for collision with other boxes. */
	for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
		{
			if (block_copy.structure.tile[y][x] == FILLED   &&
				field[y + block_copy.position.y][x + block_copy.position.x].tile == TAKEN)
			{
				collision = COLLISION_BLOCK;
			}
		}
	}

	/* Test for collision with left side wall. */
	for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
		{
			if (block_copy.structure.tile[y][x] == FILLED   &&
				x + block_copy.position.x < 0)
			{
				collision = COLLISION_WALL_R;
			}

		}
	}

	/* Test for collision with the right side wall. */
	for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
		{
			if (block_copy.structure.tile[y][x] == FILLED   &&
				x + block_copy.position.x > GRID_WIDTH - 1)
			{
				collision = COLLISION_WALL_R;
			}

		}
	}

	return collision;
}

collision_t test_movable(block_t* block, direction_t direction)
{
	/* Make a copy of the block and move it. */
	block_t block_copy = *block;
	block_move(&block_copy, direction);

	/* Test if the block interfears with any other placed box, or wall. */
	collision_t collision = NO_COLLISION;

	/* Test collision with other boxes. */
	for (int y = 0; y < MAX_BLOCK_WIDTH; y++)
	{
		for (int x = 0; x < MAX_BLOCK_HEIGHT; x++)
		{
			if (block_copy.structure.tile[y][x] == FILLED   &&
				field[y + block_copy.position.y][x + block_copy.position.x].tile == TAKEN)
			{
				collision = COLLISION_BLOCK;
			}
		}
	}

	/* Test collision with wall. */
	switch (direction)
	{
	case DIRECTION_LEFT:
		/* Test for collision with left side wall. */
		for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
			{
				if (block_copy.structure.tile[y][x] == FILLED   &&
					x + block_copy.position.x < 0)
				{
					collision = COLLISION_WALL_R;
				}

			}
		}
		break;

	case DIRECTION_RIGHT:
		/* Test for collision with the right side wall. */
		for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
			{
				if (block_copy.structure.tile[y][x] == FILLED   &&
					x + block_copy.position.x > GRID_WIDTH - 1)
				{
					collision = COLLISION_WALL_R;
				}

			}
		}
		break;
		
	case DIRECTION_UP:
		/* Test for collision with the upper side wall. */
		for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
			{
				if (block_copy.structure.tile[y][x] == FILLED   &&
					y + block_copy.position.y < 0)
				{
					collision = COLLISION_WALL_U;
				}

			}
		}
		break;

	case DIRECTION_DOWN:
		/* Test for collision the the lower side wall. */
		for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
			{
				if (block_copy.structure.tile[y][x] == FILLED   &&
					y + block_copy.position.y > GRID_HEIGHT - 1)
				{
					collision = COLLISION_WALL_D;
				}

			}
		}
		break;

	default:
		break;
	}
	return collision;
}


