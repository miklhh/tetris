#include "input.h"
#include "game.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#define FIRST_REPEAT_WAIT_TIME  400
#define REPEAT_WAIT_TIME        50

/* Handle application events. */
void handle_event(SDL_Event* evnt)
{
    switch (evnt->type)
    {
    case SDL_KEYDOWN:
        break;

    case SDL_KEYUP:
        break;

    default:
        break;

    }
}

/* The function keyboard_key_timer test if a keypress shall be processed, ie if a key is being held down, it
 * shouldn't be processed each iteration of the game. Instead it should wait a couple of milliseconds. */
static bool keyboard_key_timer(SDL_Scancode scancode, keyboard_state_t* keyboard_state)
{
    using namespace std::chrono;

    static SDL_Scancode last_scancode;
    static bool         first_time_key_repeat   = false;
    static bool         last_scancode_released  = false;
    static auto		    last_call_timestamp     = high_resolution_clock::now();
    auto                this_call_timestamp     = high_resolution_clock::now();
    milliseconds        time_since_last_call    = duration_cast<milliseconds>(this_call_timestamp - last_call_timestamp);


    /* Test if 'this' key (scancode) is pressed, otherwise always return false. */
    if (keyboard_state[scancode])
    {
        /* Test if another key has been pressed since last time. */
        if (last_scancode != scancode)
        {
            last_scancode           = scancode;
            first_time_key_repeat   = true;
            last_scancode_released  = false;
            last_call_timestamp     = this_call_timestamp;
            return true;
        }

        /* Else, the key is pressed, and the key is the same as the last key pressed. */
        else
        {
            /* Two cases. If this is the first time the keycode is repeated we wait 
             * FIRST_REPEAT_WAIT_TIME milliseconds before giving key allowance. */
            if (first_time_key_repeat)
            {
                /* If the key has been released since last call, return true. */
                if (last_scancode_released)
                {
                    last_scancode_released  = false;
                    last_call_timestamp     = this_call_timestamp;
                    return true;
                }


                if (time_since_last_call.count() < FIRST_REPEAT_WAIT_TIME)
                    return false;
                else
                {
                    first_time_key_repeat   = false;
                    last_call_timestamp     = this_call_timestamp;
                    return true;
                }
            }

            /* Else if this isn't the first time the keycode is repeated we wait
             * REPEAT_WAIT_TIME milliseconds before giving key allowance. */
            else
            {
                if (time_since_last_call.count() < REPEAT_WAIT_TIME)
                    return false;
                else
                {
                    last_call_timestamp = this_call_timestamp;
                    return true;
                }
            }
        }
    }

    /* Else, if the key is not pressed. */
    else
    {
        if (last_scancode == scancode)
        {
            last_scancode_released  = true;
            first_time_key_repeat   = true;
        }
        return false;
    }   
}

/* Function for handling continues keyboard input. */
void handle_keyboard_input(keyboard_state_t* keyboard_state)
{
    if (keyboard_key_timer(SDL_SCANCODE_LEFT, keyboard_state))
        current_block_move(DIRECTION_LEFT);

    if (keyboard_key_timer(SDL_SCANCODE_RIGHT, keyboard_state))
        current_block_move(DIRECTION_RIGHT);

}
