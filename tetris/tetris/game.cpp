#include "draw.h"
#include "game.h"
#include "blocks.h"
#include "data_structures.h"

#include <stdlib.h>
#include <time.h>
#include <iostream> // FOR DEBUGING; REMOVE LATER!


/* Game field. MAKE STATIC IN RELEASE!*/
//static box_t field[GRID_HEIGHT][GRID_WIDTH];
box_t           field[GRID_HEIGHT][GRID_WIDTH];
static bool     game_over;
static block_t* current_block;
static block_t* next_block; 


int random_int(int n)
{
    n = rand() % n;
    std::cout << "Number: " << n << std::endl;
    return n;
}

void setup_game()
{
    srand((unsigned int)time(NULL));
	for (int width = 0; width < GRID_WIDTH; width++)
	{
		for (int height = 0; height < GRID_HEIGHT; height++)
		{
			field[height][width].tile           = EMPTY;
			field[height][width].color_f	    = COLOR_BACKGROUND_FORTH;
			field[height][width].color_b	    = COLOR_BACKGROUND_BACK;
		}
	}
    game_over       = false;
    current_block   = block_spawn();
    next_block      = block_spawn();
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

block_t * block_spawn(block_type_t block_type, int start_x, int start_y, color_t color)
{
    /* Decide what to spawn. */
    block_type_t block_to_spawn;
    if (block_type == BLOCK_RANDOM)
    {
        block_to_spawn = (block_type_t)random_int(BLOCK_RANDOM);
    }
    else
    {
        block_to_spawn = block_type;
    }

    /* Spawn the block. */
    block_t* block      = new block_t;
    block->block_type   = block_type;
    switch (block_to_spawn)
    {
    case BLOCK_I:
        block->structure = block_ref_i.structure;
        break;

    case BLOCK_J:
        block->structure = block_ref_j.structure;
        break;

    case BLOCK_L:
        block->structure = block_ref_l.structure;
        break;

    case BLOCK_O:
        block->structure = block_ref_o.structure;
        break;

    case BLOCK_Z:
        block->structure = block_ref_z.structure;
        break;

    case BLOCK_T:
        block->structure = block_ref_t.structure;
        break;

    case BLOCK_S:
        block->structure = block_ref_s.structure;
        break;
    }

    /* Set the block position, color and return the block-pointer. */
    if (color == COLOR_RANDOM)
    {
        block->color = random_int(COLOR_RANDOM);
    }
    else
    {
        block->color = color;
    }
    block->position.x = start_x;
    block->position.y = start_y;
   
    return block;
}

void draw_current_block()
{
    draw_block(current_block, current_block->position.x, current_block->position.y);
}

/* Draw field draws the entire field to the screen. Make sure to render the tetrigon
* after the field has be drawn, to not cover up the tetrigon. */
void draw_field()
{
    extern SDL_Renderer* renderer;
    extern int block_width;
    extern int block_height;
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            draw_box(
                x * block_width, y * block_height,  // Position.
                block_width, block_height,          // Size.
                field[y][x].color_f,                // Foreground color.
                field[y][x].color_b,                // Background color.
                renderer,                           // Renderer to draw to.
                GLOBAL_MARGIN                       // Margin level (px).
            );
        }
    }
}

/* The function returns a pointer to the newly spawned block. */

/* Function returns true as long as the game is running. */
bool iterate_game()
{
    /* Test if the game already set to game-over. */
    if (game_over)
    {
        return false;
    }

    /* Test if the game just ended. */
    //TODO: Implement later. Don't forget to remove (delete) all blocks.

    /* If the block no longer can move downward, add it to the game field, create a new block
     * and return. */
    if (test_movable(current_block, DIRECTION_DOWN) != NO_COLLISION)
    {
        std::cout << "CRACH" << std::endl;
        for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
        {
            for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
            {
                if (current_block->structure.tile[y][x] == FILLED)
                {
                    field[y + current_block->position.y][x + current_block->position.x].tile = FILLED;
                    field[y + current_block->position.y][x + current_block->position.x].color_b = COLOR_BLOCK_BACKGROUND;
                    field[y + current_block->position.y][x + current_block->position.x].color_f = current_block->color;
                }
            }
        }

        /* Draw the block one last time, then remove it and setup for a new block and return. */
        //draw_block(current_block, current_block->position.x, current_block->position.y);
        delete current_block;
        current_block   = next_block;
        next_block      = block_spawn();
        return false;
    }

    /* The block hasn't landed. Move it downward a step and continue the game. */
    block_move(current_block, DIRECTION_DOWN);
    //draw_block(current_block, current_block->position.x, current_block->position.y);
    return false;
}


