#include "input.h"
#include "game.h"

#include <SDL.h>
#include <iostream>
#include <chrono>

#define HOLD_DOWN_WAIT_FIRST_TIME   400
#define HOLD_DOWN_WAIT              50

using namespace std::chrono;
struct keyboard_timer_t
{
    time_point<steady_clock>    time;
    SDL_Scancode                scancode;
    bool                        first_time_scancode;
};



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

static bool keyboard_key_timer(SDL_Scancode scancode, keyboard_state_t* keyboard_state)
{
    /* Variables for keeping track of the last keyboard input time. */
    static SDL_Scancode             last_scancode;
    static bool                     first_time_scancode_repeat;
    static bool                     key_released                    = true;
    static bool                     once_if_key_released            = true;
    static time_point<steady_clock> time_last_call                  = high_resolution_clock::now();
    time_point<steady_clock>        time_now                        = high_resolution_clock::now();
    milliseconds                    time_since_last_call            = duration_cast<milliseconds>(time_now - time_last_call);



    if (keyboard_state[scancode])
    {
        /* Test if the scancode differs since last call. */
        if (last_scancode != scancode)
        {
            first_time_scancode_repeat  = true;
            last_scancode               = scancode;
            time_last_call              = high_resolution_clock::now();
            key_released                = false;
            return true;
        }

        /* If the scancode is the same as for the last time being called, test if this is the first
         * time the scancode is being repeated. */
        else if (first_time_scancode_repeat)
        {
            if (time_since_last_call.count() > HOLD_DOWN_WAIT_FIRST_TIME)
            {
                time_last_call              = high_resolution_clock::now();
                first_time_scancode_repeat  = false;
                return true;
            }
            else
            {
                return false;
            }
        }

        /* Scancode is the same as before and the scancode has repeated more than one time. */
        else
        {
            /* If the key has been released since last time the function was called with this keycode. */
            if (key_released)
            {
                if (once_if_key_released)
                {
                    once_if_key_released = false;
                    return true;
                }
                else if (time_since_last_call.count() > HOLD_DOWN_WAIT_FIRST_TIME)
                {
                    time_last_call  = high_resolution_clock::now();
                    key_released    = false;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            /* If the key NOT has been released since last time the function was called with this keycode. */
            else
            {
                if (time_since_last_call.count() > HOLD_DOWN_WAIT)
                {
                    time_last_call = high_resolution_clock::now();
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    else
    {
        if (last_scancode == scancode)
        {
            time_last_call          = high_resolution_clock::now();
            once_if_key_released    = true;
            key_released            = true;
        }
        return false;
    }
}


void handle_keyboard_input(keyboard_state_t* keyboard_state)
{
    if (keyboard_key_timer(SDL_SCANCODE_LEFT, keyboard_state))
    {
        current_block_move(DIRECTION_LEFT);
    }

    if (keyboard_key_timer(SDL_SCANCODE_RIGHT, keyboard_state))
    {
        current_block_move(DIRECTION_RIGHT);
    }
}
