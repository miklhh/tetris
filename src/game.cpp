#include "draw.h"
#include "game.h"
#include "blocks.h"
#include "data_structures.h"

#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream> // FOR DEBUGING; REMOVE LATER!


/* Variables for the game. */
static box_t     field[GRID_HEIGHT][GRID_WIDTH];
static bool      game_over;
static block_t*  current_block;
static block_t*  next_block;
static int       current_iteration_wait_time_ms;
static int       iteration_wait_time_level_ms;


/* Random number generator. */
int random_int(int n)
{
    n = rand() % n;
    std::cout << "Number: " << n << std::endl;
    return n;
}

void setup_game()
{
    /* Set random seed. */
    srand((unsigned int)time(NULL));

    /* Setup a 'fresh' gamefield. */
	for (int width = 0; width < GRID_WIDTH; width++)
	{
		for (int height = 0; height < GRID_HEIGHT; height++)
		{
			field[height][width].tile      = EMPTY;
			field[height][width].color_f   = COLOR_BACKGROUND_FORTH;
			field[height][width].color_b   = COLOR_BACKGROUND_BACK;
		}
	}

    /* Set variables. */
    game_over     = false;
    current_block = block_spawn();
    next_block    = block_spawn();
    set_iteration_timer(800);
}

/* Move a block. */
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
    /* Create a new block structure and initialize it to EMPTY. */
    block_struct_t rotated_block_structure;
    for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
        {
            rotated_block_structure.tile[y][x] = EMPTY;
        }
    }
	
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

/* Rotate a block. */
void block_rotate(block_t* block, rotation_t counter_clockwise)
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

/* Test if a block is rotatable. */
collision_t test_rotation(block_t* block, rotation_t counter_clockwise)
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

/* Spawn a block. */
block_t* block_spawn(block_type_t block_type, int start_x, int start_y, color_t color)
{
    /* Decide what to spawn. */
    block_type_t block_to_spawn;
    if (block_type == BLOCK_RANDOM)
        block_to_spawn = (block_type_t)random_int(BLOCK_RANDOM);
    else
        block_to_spawn = block_type;


    /* Spawn the block. */
    block_t* block      = new block_t;
    block->block_type   = block_to_spawn;
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

/* Removes an entire row. */
void remove_row(int row)
{
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        field[row][x].tile     = EMPTY;
        field[row][x].color_f  = COLOR_BACKGROUND_FORTH;
        field[row][x].color_b  = COLOR_BACKGROUND_BACK;
    }
}

/* Move the entire field down n levels starting from row.. */
void move_field_down(int row, int n)
{
    for (int y = row - 1; y >= 0; y--)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            field[y + n][x].tile = field[y][x].tile;
            field[y + n][x].color_f = field[y][x].color_f;
            field[y + n][x].color_b = field[y][x].color_b;
        }
    }
}

/* Function for testing if an entire row has been filled up. */
bool test_row_full(int row)
{
    bool res = true;
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        if (field[row][x].tile == EMPTY)
        {
            res = false;
            break;
        }
    }
    return res;
}

/* Function called by main loop. */
void game_draw_current_block()
{
    draw_block(current_block, current_block->position.x, current_block->position.y);
}

/* Draw field draws the entire field to the screen. Make sure to render the tetrigon
 * after the field has be drawn, to not cover up the tetrigon. */
void game_draw_field()
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

/* Function returns true as long as the game is running. */
bool iterate_game()
{
    /* Test if the game already set to game-over. */
    if (game_over)
    {
        delete current_block;
        delete next_block;
        return false;
    }

    /* Test if the game just ended. */
    //TODO: Implement later. Don't forget to remove (delete) all blocks.

    /* If the block hits the ground. */
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

        /* Test and remove posible full rows */
        for (int y1 = 0; y1 < GRID_HEIGHT; y1++)
        {
            /* Test if the row 'y1' is full. If it is, test how many row under 'y1'
            * which also is full. */
            if (test_row_full(y1))
            {
                int   row = y1;
                int   n = 1;
                bool  one_found = false;
                for (int y2 = y1; y2 < GRID_HEIGHT; y2++)
                {
                    bool row_full = test_row_full(y2);
                    if (row_full)
                    {
                        n = y2 - y1 + 1;
                        one_found = true;
                    }
                    if (one_found && !row_full)
                        break;
                }

                /* The appropriate rows to remove and the amount of rows under it
                * has been found. Remove accordingly and move field down. */
                for (int y = y1; y < y1 + n; y++)
                {
                    remove_row(y);
                }

                /* Move down the pieces above it and break out of loop. */
                move_field_down(y1, n);
                break;
            }
        }

        /* Remove the old block and prepare a new one. */
        delete current_block;
        current_block   = next_block;
        next_block      = block_spawn();
        return false;
    }

    /* The block hasn't landed. Move it downward a step and continue the game. */
    block_move(current_block, DIRECTION_DOWN);
    return false;
}

/* Timer for testing if an iteration shall occur. */
bool iteration_timer()
{
    using namespace std::chrono;
    static time_point<high_resolution_clock>  last_timestamp;
    time_point<high_resolution_clock>         current_timestamp         = high_resolution_clock::now();
    milliseconds                              time_since_last_call      = duration_cast<milliseconds>(current_timestamp - last_timestamp);

    if (current_iteration_wait_time_ms < time_since_last_call.count())
    {
        last_timestamp = current_timestamp;
        return true;
    }
    else return false;

}

/* Function to set the interation timer. */
void set_temp_iteration_timer(int time_ms)
{
    current_iteration_wait_time_ms = time_ms;
}

/* Function for seting the iteration timer back to normal speed. */
void set_iteration_timer(int time_ms)
{
    if (time_ms == 0)
    {
        current_iteration_wait_time_ms = iteration_wait_time_level_ms;
    }
    else
    {
        iteration_wait_time_level_ms = time_ms;
        current_iteration_wait_time_ms = time_ms;
    }
}

/* Move the current block on the field. */
void current_block_move(direction_t direction)
{
    if (test_movable(current_block, direction) == NO_COLLISION)
    {
        block_move(current_block, direction);
    }
}

/* Rotate the currentn block on the field. */
void current_block_rotate(rotation_t counter_clockwise)
{
    /* Test if the current block can rotate. */
    if (test_rotation(current_block, counter_clockwise) == NO_COLLISION)
    {
        block_rotate(current_block, counter_clockwise);
        return;
    }

    /* Test if a left wall kick can be preformed. */
    block_t temp_block = *current_block;
    block_move(&temp_block, DIRECTION_RIGHT);
    if (test_rotation(&temp_block, counter_clockwise) == NO_COLLISION)
    {
        block_move(current_block, DIRECTION_RIGHT);
        block_rotate(current_block, counter_clockwise);
        return;
    }

    /* Test if a right side wall kick can be preformed. */
    temp_block = *current_block;
    block_move(&temp_block, DIRECTION_LEFT);
    if (test_rotation(&temp_block, counter_clockwise) == NO_COLLISION)
    {
        block_move(current_block, DIRECTION_LEFT);
        block_rotate(current_block, counter_clockwise);
        return;
    }

    //   ------------------------------------------------------------
    //   -------------        SPECTIAL BLOCKS       -----------------
    //   ------------------------------------------------------------

    /* 1x4 block, also known as I-block. */
    if (current_block->block_type == BLOCK_I)
    {
        /* Test a left side double wall kick. */
        temp_block = *current_block;
        for (int i = 0; i < 2; i++)
            block_move(&temp_block, DIRECTION_RIGHT);

        if (test_rotation(&temp_block, counter_clockwise)  == NO_COLLISION)
        {
            for (int i = 0; i < 2; i++)
                block_move(current_block, DIRECTION_RIGHT);

            block_rotate(current_block, counter_clockwise);
            return;
        }



        /* Test a right side double wall kick. */
        temp_block = *current_block;
        for (int i = 0; i < 2; i++)
            block_move(&temp_block, DIRECTION_LEFT);

        if (test_rotation(&temp_block, counter_clockwise) == NO_COLLISION)
        {
            for (int i = 0; i < 2; i++)
                block_move(current_block, DIRECTION_LEFT);

            block_rotate(current_block, counter_clockwise);
            return;
        }
    }
}


