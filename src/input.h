#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

/* Control keys. */
#define KEY_MOVE_LEFT                   SDL_SCANCODE_LEFT       // Must be scancode.
#define KEY_MOVE_RIGHT_KEY              SDL_SCANCODE_RIGHT      // Must be scancode.
#define KEY_ROTATE_COUNTER_CLOCKWISE    SDLK_z
#define KEY_ROTATE_CLOCKWISE            SDLK_x
#define KEY_SOFT_DROP                   SDLK_DOWN


typedef const Uint8 keyboard_state_t;
void handle_event(SDL_Event* evnt);
void handle_keyboard_input(keyboard_state_t* keyboard_state);

#endif