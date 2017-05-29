#ifndef GAME_H
#define GAME_H

#include "data_structures.h"

#define CURRENT_LEVEL_TIME_MS   0

/* Setup/set fucntions. */
int   random_int(int n);
void  setup_game();
void  set_temp_iteration_timer(int time_ms);
void  set_iteration_timer(int time_ms = CURRENT_LEVEL_TIME_MS);
bool  iteration_timer();

/* Game functions. */
bool      iterate_game();
block_t*  block_spawn(block_type_t block_type = BLOCK_RANDOM, int start_x = 4, int start_y = 0, color_t color = COLOR_RANDOM);
void      remove_row(int row);
void      move_field_down(int row, int n);
bool      test_row_full(int row);


/* Drawing funcitons. */
void  game_draw_current_block();
void  game_draw_field();

/* Block functions*/
void         block_move(block_t* block, direction_t direction);
void         block_rotate(block_t* block, rotation_t counter_clockwise);
collision_t  test_rotatable(block_t* block, rotation_t counter_clockwise);
collision_t  test_movable(block_t* block, direction_t left);
void         current_block_move(direction_t direction);
void         current_block_rotate(rotation_t counter_clockwise);





#endif
