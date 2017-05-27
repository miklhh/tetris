#ifndef GAME_H
#define GAME_H

#include "data_structures.h"


/* Setup/set fucntions. */
#define CURRENT_LEVEL_TIME_MS   0
int     random_int(int n);
void    setup_game();
void    set_temp_iteration_timer(int time_ms);
void    set_iteration_timer(int time_ms = CURRENT_LEVEL_TIME_MS);

/* Game/drawing functions. */
void        game_draw_current_block();
void        game_draw_field();
bool        iterate_game();
bool        iteration_timer();
block_t*    block_spawn(block_type_t block_type = BLOCK_RANDOM, int start_x = 4, int start_y = 0, color_t color = COLOR_RANDOM);

/* Block functions*/
void            block_move(block_t* block, direction_t direction);
void            block_rotate(block_t* block, bool counter_clockwise);
collision_t     test_rotatable(block_t* block, bool counter_clockwise);
collision_t     test_movable(block_t* block, direction_t left);
void            current_block_move(direction_t direction);
void            current_block_rotate(bool counter_clockwise);





#endif
