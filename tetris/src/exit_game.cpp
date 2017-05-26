#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

void exit_game(SDL_Window* window)
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	std::cout << "Window closed. SDL-resources returned to system." << std::endl;

	#ifdef WIN32
	system("pause");
	#endif

	exit(0);
}