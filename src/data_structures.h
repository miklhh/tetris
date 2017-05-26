#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* Max block sizes. */
#define MAX_BLOCK_WIDTH	            4
#define MAX_BLOCK_HEIGHT            4

/* Block marcros.*/
typedef int block_type_t; 
#define BLOCK_I                     0
#define BLOCK_J                     1
#define BLOCK_L                     2
#define BLOCK_O                     3
#define BLOCK_Z                     4
#define BLOCK_T                     5
#define BLOCK_S                     6
#define BLOCK_RANDOM                7

/* Grid size. */
#define GRID_WIDTH                  10
#define GRID_HEIGHT                 20

/* Box macros. */
#define EMPTY                       0
#define FILLED                      1
#define TAKEN                       1

/* Collision macros and typedef. */
typedef int collision_t;
#define NO_COLLISION                0
#define COLLISION_WALL_L            1
#define COLLISION_WALL_R            2
#define COLLISION_WALL_U            3
#define COLLISION_WALL_D            4
#define COLLISION_BLOCK             5

/* Direction macros and typedef. */
typedef int direction_t;
#define	DIRECTION_LEFT              0
#define DIRECTION_RIGHT             1
#define DIRECTION_UP                2
#define DIRECTION_DOWN              3

/* Color macros and typedef. */
typedef int color_t;
#define COLOR_BLUE                  0
#define COLOR_RED                   1
#define COLOR_GREEN                 2
#define COLOR_WHITE                 3
#define COLOR_BLACK                 4
#define COLOR_GREY                  5
#define COLOR_DARK_GREY             6
#define COLOR_TRANS_WHITE           7
#define COLOR_RANDOM                8
#define COLOR_BACKGROUND_BACK       COLOR_GREY
#define COLOR_BACKGROUND_FORTH      COLOR_DARK_GREY
#define COLOR_BLOCK_BACKGROUND      COLOR_TRANS_WHITE
typedef int color_t;
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
               /*       Y                X      */
    tile_t tile[MAX_BLOCK_HEIGHT][MAX_BLOCK_WIDTH];
};

/* Structure for a block. */
struct block_t
{
	color_t         color;
	block_type_t    block_type;
	position_t      position;
	block_struct_t  structure;
};

/* Structure for a single block. */
struct box_t
{
	color_t     color_f;
	color_t     color_b;
	tile_t      tile;
};
#endif
