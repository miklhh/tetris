#include <SDL.h>
#include <stdlib.h>
#include <iostream>

void exit_game(SDL_Window* window, SDL_Renderer* renderer)
{
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    std::cout << "SDL-resources returned to system." << std::endl;
    
    #ifdef _WIN32
    system("pause");
    #endif
    
    exit(0);
}