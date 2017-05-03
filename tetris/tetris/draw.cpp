#include "draw.h"
#include "blocks.h"

/* Local help function for seting color. */
static void SetColor(int color, SDL_Renderer* renderer)
{
	switch (color)
	{
	case COLOR_BLUE:
		/* BLUE COLOR. */
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
		break;

	case COLOR_RED:
		/* RED COLOR. */
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		break;

	case COLOR_GREEN:
		/* GREEN COLOR. */
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		break;

	default:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		break;
	}
}

/* Function for drawing a 'block' to a renderer. */
void draw_box(
	int x,
	int y,
	int w,
	int h,
	int inner_color,
	int outer_color,
	SDL_Renderer* renderer,
	int margin
)
{
	/* Create rectangles. */
	SDL_Rect rectangle_outer;
	SDL_Rect rectangle_inner;

	/* Set parameters. */
	rectangle_outer.h = h;
	rectangle_outer.w = w;
	rectangle_outer.x = x;
	rectangle_outer.y = y;

	rectangle_inner.h = h - 2 * margin;
	rectangle_inner.w = w - 2 * margin;
	rectangle_inner.x = x + margin;
	rectangle_inner.y = y + margin;

	/* Draw outer rectangle. */
	SetColor(outer_color, renderer);
	SDL_RenderFillRect(renderer, &rectangle_outer);
	SDL_RenderDrawRect(renderer, &rectangle_outer);


	/* Draw inner rectangle. */
	SetColor(inner_color, renderer);
	SDL_RenderFillRect(renderer, &rectangle_inner);
	SDL_RenderDrawRect(renderer, &rectangle_inner);

	return;
}

void draw_block(block block, int tile_x, int tile_y)
{
	extern int block_width;
	extern int block_height;
	extern SDL_Renderer* renderer;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (block.structure.tile[y][x] == FILLED)
			{
				draw_box(
					(tile_x + x) * block_width,
					(tile_y + y) * block_width,
					block_width,
					block_height,
					COLOR_BACKGROUND_BACK,
					block.color,
					renderer
				);
			}
		}
	}
}