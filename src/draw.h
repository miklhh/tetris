#ifndef DRAW_BLOCK_H
#define DRAW_BLOCK_H

#include "game.h"

#include <SDL2/SDL.h>

/* Block margin. */
#define GLOBAL_MARGIN   1

void draw_box(
	int             x_px,
	int             y_px,
	int             w_px,
	int             h_px,
	color_t         inner_color,
	color_t         outer_color,
	SDL_Renderer*   renderer,
	int             margin = 2
);

void draw_block(block_t block, int tile_x, int tile_y);
void draw_block(block_t* block, int tile_x, int tile_y);


#endif