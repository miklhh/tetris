#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef const Uint8 keyboard_state_t;

void handle_event(SDL_Event* evnt);
void handle_keyboard_input(keyboard_state_t* keyboard_state);

#endif