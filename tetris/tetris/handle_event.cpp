#include "handle_event.h"
#include "game.h"

#include <SDL.h>
#include <iostream>

void handle_event(SDL_Event* evnt)
{
    switch (evnt->type)
    {
    case SDL_KEYDOWN:
        switch (evnt->key.keysym.sym)
        {
        case SDLK_LEFT:
            current_block_move(DIRECTION_LEFT);
            break;

        case SDLK_RIGHT:
            current_block_move(DIRECTION_RIGHT);
            break;

        case SDLK_UP:
            std::cout << "Up key pressed!" << std::endl;
            break;

        case SDLK_DOWN:
            std::cout << "Down key pressed!" << std::endl;
            break;

        case SDLK_z:
            current_block_rotate(true);
            break;

        case SDLK_x:
            current_block_rotate(false);
            break;

        default:
            break;
        }
        break;

    case SDL_KEYUP:
        break;

    default:
        break;

    }
}
