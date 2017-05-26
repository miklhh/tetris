#include "exit_game.h"
#include "draw.h"
#include "get_window_size.h"
#include "game.h"
#include "blocks.h"
#include "input.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>


/* Windows, renderer and window variables. */
SDL_DisplayMode display_mode;
SDL_Event       events;
SDL_Window*     window          = NULL;
SDL_Renderer*   renderer        = NULL;
int             window_width    = 0;
int             window_height   = 0;
int             block_width     = 0;
int             block_height    = 0;

/* GAME FIELD FOR DEBUGING. */
extern box_t field[GRID_HEIGHT][GRID_WIDTH];

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
	#define MONITOR_0   0
	SDL_GetCurrentDisplayMode(MONITOR_0, &display_mode);
	window_height   = get_window_height(display_mode);
	window_width    = get_window_width(display_mode);

	block_width     = window_width / 20;
	block_height    = window_height / 20;

	/* Print screen and window information. */
	std::cout << "Screen-width: "   << display_mode.w   << ", Screen-height: "  << display_mode.h   << std::endl;
	std::cout << "Window-width: "   << window_width     << ", Window-height: "  << window_height    << std::endl;
	std::cout << "Block-width: "    << block_width      << ", Block-height: "   << block_height     << std::endl;

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

	bool is_running = true;
	while (is_running)
	{
		/* Clear the screen. */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		/* Iterate the game and draw the field. */
        static uint64_t i = 0;
        if (i % 300 == 0)
        {
            iterate_game();
        }
        i++;
        game_draw_field();
        game_draw_current_block();
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&events))
		{
            if (events.type == SDL_QUIT)
                is_running = false;
            else
                handle_event(&events);
		}

        static keyboard_state_t* keyboard_state = SDL_GetKeyboardState(NULL);
        handle_keyboard_input(keyboard_state);

		SDL_Delay(2);
	}
	

	exit_game(window);
    return 0;
}