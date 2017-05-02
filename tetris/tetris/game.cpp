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


