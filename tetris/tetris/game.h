#ifndef GAME_H
#define GAME_H

/* Block marcros.*/
#define BLOCK_I 0
#define BLOCK_J 1
#define BLOCK_L 2
#define BLOCK_O 3
#define BLOCK_Z 4
#define BLOCK_T 5
#define BLOCK_S 6

/* Grid size. */
#define GRID_WIDTH	10
#define GRID_HEIGHT 20

#define EMPTY	0
#define FILLED	1

struct pair
{
	int x;
	int y;
};

struct block_struct
{
	/*       Y  X       */
	int tile[4][4];
};

struct block
{
	int				color;
	pair			center;
	block_struct	structure;
};

/* Functions. */
int		random_int(int n);
void	setup_game();


#endif
