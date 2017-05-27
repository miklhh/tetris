#include "exit_game.h"
#include "draw.h"
#include "get_window_size.h"
#include "game.h"
#include "blocks.h"
#include "input.h"

#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

/* For testing timings. */
#include <chrono>

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
    /* Intialize SDL. */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize SDL... Exiting." << std::endl;
        exit_game(NULL);
    }

	/* Aquire the monitor size and set the window size variables. */
	#define MONITOR_0 0
	SDL_GetCurrentDisplayMode(MONITOR_0, &display_mode);
	window_height   = get_window_height(display_mode);
	window_width    = get_window_width(display_mode);
	block_width     = window_width / 20;
	block_height    = window_height / 20;

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



	/* Initialize random seed, and setup the game. */
	srand((unsigned int)time(NULL));
	setup_game();

	/* Print screen and window information. */
	std::cout << "Screen-width: "   << display_mode.w   << ", Screen-height: "  << display_mode.h   << std::endl;
	std::cout << "Window-width: "   << window_width     << ", Window-height: "  << window_height    << std::endl;
	std::cout << "Block-width: "    << block_width      << ", Block-height: "   << block_height     << std::endl;

	/* DEBUGING TIMINGS, REMOVE LATER ON. */
	using namespace std::chrono;
	time_point<high_resolution_clock> t1;
	time_point<high_resolution_clock> t2;
	/* DEBUGING TIMINGS, REMOVE LATER ON. */

	bool is_running = true;
	while (is_running)
	{
		/* DEBUGING TIMINGS, REMOVE LATER ON. */
		t1 = high_resolution_clock::now();
		/* DEBUGING TIMINGS, REMOVE LATER ON. */

		/* Clear the screen. */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		/* Replace with real timer instead. */
		if (iteration_timer())
		{ 
            iterate_game();
		}


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

		/* DEBUGING TIMINGS, REMOVE LATER ON. */
		t2 = high_resolution_clock::now();
		std::cout << "Iteration time: " << duration_cast<microseconds>(t2 - t1).count() << " microseconds." << std::endl;
		/* DEBUGING TIMINGS, REMOVE LATER ON. */

		/* Later we want a total time of 10 milliseconds per iteration. Game updates 100 times a seconds.*/
		SDL_Delay(10);
	}
	

	exit_game(window);
    return 0;
}
