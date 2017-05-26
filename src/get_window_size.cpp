#include "get_window_size.h"

#include <SDL2/SDL.h>


#define SCALE_FACTOR    5

int get_window_height(SDL_DisplayMode display_mode)
{
	bool height_limiting = false;
	if (display_mode.w > display_mode.h)
		height_limiting = true;

	if (height_limiting)
	{
		/* Must be a multiple of 50. */
		return (display_mode.h / 20 - SCALE_FACTOR) * 20;
	}
	else
	{
		/* Must be a multiple of 50. */
		return (display_mode.w / 20 - SCALE_FACTOR) * 20;
	}
}


int get_window_width(SDL_DisplayMode display_mode)
{
	bool height_limiting = false;
	if (display_mode.w > display_mode.h)
		height_limiting = true;

	if (height_limiting)
	{
		return (display_mode.h / 20 - SCALE_FACTOR) * 20;
	}
	else
	{
		return (display_mode.w / 20 - SCALE_FACTOR) * 20;
	}
}
