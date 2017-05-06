#ifndef GAME_H
#define GAME_H

#include "data_structures.h"



/* Functions. */
int             random_int(int n);
void            setup_game();
void            block_move(block_t* block, direction_t direction);
void            block_rotate(block_t* block, bool counter_clockwise);
collision_t     test_rotatable(block_t* block, bool counter_clockwise);
collision_t     test_movable(block_t* block, direction_t left);
block_t*        block_spawn(block_type_t block_type = BLOCK_RANDOM, int start_x = 4, int start_y = 0, color_t color = COLOR_RANDOM);
void            draw_current_block();
void            draw_field();
bool            iterate_game();

#endif
