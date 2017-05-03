#include "exit_game.h"
#include "draw.h"
#include "get_window_size.h"
#include "game.h"
#include "blocks.h"

#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>


/* Windows, renderer and window variables. */
SDL_DisplayMode	display_mode;
SDL_Event		events;
SDL_Window*		window = NULL;
SDL_Renderer*	renderer = NULL;
int				window_width = 0;
int				window_height = 0;
int				block_width = 0;
int				block_height = 0;


int main(int argc, char* argv[])
{
	setup_game();



	/* Intialize SDL. */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL... Exiting." << std::endl;
		exit_game(NULL);
	}

	/* Initialize random seed. */
	srand((unsigned int)time(NULL));

	/* Aquire the monitor size and set the initial window size. */
	#define MONITOR_0 0
	SDL_GetCurrentDisplayMode(MONITOR_0, &display_mode);
	window_height	= get_window_height(display_mode);
	window_width	= get_window_width(display_mode);

	block_width		= window_width / 20;
	block_height	= window_height / 20;

	/* Print screen and window information. */
	std::cout << "Screen-width: " << display_mode.w << ", Screen-height: " << display_mode.h << std::endl;
	std::cout << "Window-width: " << window_width << ", Window-height: " << window_height << std::endl;
	std::cout << "Block-width: " << block_width << ", Block-height: " << block_height << std::endl;

	/* Initialize the window. */
	window = SDL_CreateWindow(
		"Tetris", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		window_width, 
		window_height,
		NULL
	);
	if (window == NULL)
	{
		std::cout << "Failed to create a window... Exiting." << std::endl;
		exit_game(window);
	}

	/* Intialize the renderer. */
	#define FIRST_RENDERING_DEVICE -1
	renderer = SDL_CreateRenderer(
		window,
		FIRST_RENDERING_DEVICE,
		SDL_RENDERER_ACCELERATED
	);
	if (renderer == NULL)
	{
		std::cout << "Failed to create a renderer... Exiting." << std::endl;
		exit_game(window);
	}

	SDL_Rect* rectangle = new SDL_Rect;

	

	block test_block_t = block_ref_t;
	block test_block_j = block_ref_j;
	block test_block_s = block_ref_s;
	block test_block_z = block_ref_z;
	block test_block_l = block_ref_l;
	block test_block_o = block_ref_o;
	block test_block_i = block_ref_i;

	bool is_running = true;
	while (is_running)
	{
		/* Draw background. */
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				draw_box(
					window_width/20*x, 
					window_height/20*y, 
					block_width, 
					block_height, 
					COLOR_RED, 
					COLOR_BLUE, 
					renderer, 
					1);
			}
		}




		
		test_block_t.color = COLOR_GREEN;
		test_block_j.color = COLOR_BLUE;
		test_block_s.color = COLOR_RED;
		test_block_i.color = COLOR_RED;
		test_block_o.color = COLOR_GREEN;


		rotate_block(&test_block_t, false);
		rotate_block(&test_block_j, false);
		rotate_block(&test_block_s, false);
		rotate_block(&test_block_z, false);
		rotate_block(&test_block_l, false);
		rotate_block(&test_block_o, false);
		rotate_block(&test_block_i, false);

		draw_block(test_block_t, 2, 1);
		draw_block(test_block_j, 6, 1);
		draw_block(test_block_s, 2, 5);
		draw_block(test_block_z, 6, 5);
		draw_block(test_block_l, 2, 10);
		draw_block(test_block_o, 6, 10);
		draw_block(test_block_i, 5, 15);





		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&events))
		{
			switch (events.type)
			{
			case SDL_QUIT:
				is_running = false;
				break;

			default:
				break;
			}
		}
		SDL_Delay(1000);
	}
	

	exit_game(window);
    return 0;
}