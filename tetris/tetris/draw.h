#ifndef DRAW_BLOCK_H
#define DRAW_BLOCK_H

#include "game.h"

#include <SDL.h>

/* Colors. */
#define COLOR_BLUE				0
#define COLOR_RED				1
#define COLOR_GREEN				2
#define COLOR_BACKGROUND_BACK	3
#define COLOR_BACKGROUND_FORTH	4
#define COLOR_BACKGROUND_BLOCK	5

void draw_box(
	int x,
	int y,
	int w,
	int h,
	int inner_color,
	int outer_color,
	SDL_Renderer* renderer,
	int margin = 2
);

void draw_block(block block, int tile_x, int tile_y);



#endif