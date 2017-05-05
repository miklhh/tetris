#ifndef GAME_H
#define GAME_H

#include "data_structures.h"

/* Block marcros.*/
#define BLOCK_I				0
#define BLOCK_J				1
#define BLOCK_L				2
#define BLOCK_O				3
#define BLOCK_Z				4
#define BLOCK_T				5
#define BLOCK_S				6

/* Grid size. */
#define GRID_WIDTH			10
#define GRID_HEIGHT			20

/* Box macros. */
#define EMPTY				0
#define FILLED				1
#define TAKEN				1

/* Collision macros and typedef. */
typedef int collision_t;
#define NO_COLLISION			0
#define COLLISION_WALL_L		1
#define COLLISION_WALL_R		2
#define COLLISION_WALL_U		3
#define COLLISION_WALL_D		4
#define COLLISION_BLOCK		5

/* Direction macros and typedef. */
typedef int direction_t;
#define	DIRECTION_LEFT		0
#define DIRECTION_RIGHT		1
#define DIRECTION_UP			2
#define DIRECTION_DOWN		3


/* Functions. */
int				random_int(int n);
void				setup_game();
void				block_move(block_t* block, direction_t direction);
void				block_rotate(block_t* block, bool counter_clockwise);
collision_t		test_rotatable(block_t* block, bool counter_clockwise);
collision_t		test_movable(block_t* block, direction_t left);

#endif
