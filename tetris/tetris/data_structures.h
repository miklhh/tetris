#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define MAX_BLOCK_WIDTH		4
#define MAX_BLOCK_HEIGHT	4

typedef int color_t;
typedef int block_type_t;
typedef int tile_t;

/* Data structures. */
struct position_t;
struct block_struct_t;
struct block_t;
struct box_t;


/* And their definitions. */
struct position_t
{
	int x;
	int y;
};

/* Structure for a block-structure. */

struct block_struct_t
{
				  /*  Y			      X  */
	tile_t tile[MAX_BLOCK_HEIGHT][MAX_BLOCK_WIDTH];
};

/* Structure for a block. */
struct block_t
{
	color_t			color;
	block_type_t	block_type;
	position_t		position;
	block_struct_t	structure;
};

struct box_t
{
	color_t		color_f;
	color_t		color_b;
	tile_t		tile;
};
#endif
