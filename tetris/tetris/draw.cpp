#include "draw.h"
#include "blocks.h"
#include <iostream>	// FOR DEBUGING, REMOVE ON RELEASE!

/* Local help function for seting color. */
static void SetColor(int color, SDL_Renderer* renderer)
{
	switch (color)
	{
	case COLOR_BLUE:
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
		break;

	case COLOR_RED:
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		break;

	case COLOR_GREEN:
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		break;

	case COLOR_WHITE:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		break;

	case COLOR_BLACK:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		break;

	case COLOR_GREY:
		SDL_SetRenderDrawColor(renderer, 110, 110, 80, 0);
		break;

	case COLOR_DARK_GREY:
		SDL_SetRenderDrawColor(renderer, 25, 25, 20, 0);
		break;

	case COLOR_TRANS_WHITE:
		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 210);
		break;

	default:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		break;
	}
}

/* Function for drawing a 'block' to a renderer. */
void draw_box(
	int				x_px,
	int				y_px,
	int				w_px,
	int				h_px,
	color_t			color_forth,
	color_t			color_back,
	SDL_Renderer*	renderer,
	int				margin
)
{
	/* Create rectangles. */
	SDL_Rect rectangle_outer;
	SDL_Rect rectangle_inner;

	/* Set parameters. */
	rectangle_outer.h = h_px;
	rectangle_outer.w = w_px;
	rectangle_outer.x = x_px;
	rectangle_outer.y = y_px;

	rectangle_inner.h = h_px - 2 * margin;
	rectangle_inner.w = w_px - 2 * margin;
	rectangle_inner.x = x_px + margin;
	rectangle_inner.y = y_px + margin;

	/* Draw outer rectangle. */
	SetColor(color_back, renderer);
	SDL_RenderFillRect(renderer, &rectangle_outer);
	SDL_RenderDrawRect(renderer, &rectangle_outer);


	/* Draw inner rectangle. */
	SetColor(color_forth, renderer);
	SDL_RenderFillRect(renderer, &rectangle_inner);
	SDL_RenderDrawRect(renderer, &rectangle_inner);

	return;
}

void draw_block(block_t block, int tile_x, int tile_y)
{
	extern int block_width;
	extern int block_height;
	extern SDL_Renderer* renderer;

	for (int y = 0; y < MAX_BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_BLOCK_WIDTH; x++)
		{
			if (block.structure.tile[y][x] == FILLED)
			{
				draw_box(
					(tile_x + x) * block_width,
					(tile_y + y) * block_width,
					block_width,
					block_height,
					block.color,
					COLOR_BLOCK_BACKGROUND,
					renderer
				);
			}
		}
	}
}

/* Draw field draws the entire field to the screen. Make sure to render the tetrigon
 * after the field has be drawn, to not cover up the tetrigon. */
void draw_field(box_t field[GRID_HEIGHT][GRID_WIDTH])
{
	extern SDL_Renderer* renderer;
	extern int block_width;
	extern int block_height;
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			draw_box(
				x * block_width, y * block_height,	// Position.
				block_width, block_height,			// Size.
				field[x][y].color_f,					// Foreground color.
				field[x][y].color_b,					// Background color.
				renderer,							// Renderer to draw to.
				GLOBAL_MARGIN						// Margin level (px).
			);
		}
	}
}