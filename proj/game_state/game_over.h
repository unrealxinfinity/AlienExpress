#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "../macros/includes.h"
#include "../devices/mouse.h"
#include "../game_state/level.h"

action_t keyboard_ih_game_over(uint32_t scancode);
action_t mouse_ih_game_over();


void set_selection_game_over(action_t action);

void draw_game_over();
void draw_game_over_words();
void draw_game_over_tag();

#endif
