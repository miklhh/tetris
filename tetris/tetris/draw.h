#ifndef DRAW_BLOCK_H
#define DRAW_BLOCK_H

#include "game.h"

#include <SDL.h>

/* Block margin. */
#define GLOBAL_MARGIN               1

/* Colors. */
#define COLOR_BLUE                  0
#define COLOR_RED                   1
#define COLOR_GREEN                 2
#define COLOR_WHITE                 3
#define COLOR_BLACK                 4
#define COLOR_GREY                  5
#define COLOR_DARK_GREY             6
#define COLOR_TRANS_WHITE           7
#define COLOR_BACKGROUND_BACK       COLOR_GREY
#define COLOR_BACKGROUND_FORTH      COLOR_DARK_GREY
#define COLOR_BLOCK_BACKGROUND      COLOR_TRANS_WHITE

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
void draw_field(box_t field[GRID_HEIGHT][GRID_WIDTH]);


#endif