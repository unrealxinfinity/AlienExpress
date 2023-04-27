#ifndef PAUSE_H
#define PAUSE_H

#include "../macros/includes.h"
#include "../game_state/level.h"
#include "../devices/mouse.h"

void draw_pause();
void draw_pause_words();

void set_selection_pause(action_t action);

action_t keyboard_ih_pause(uint32_t scancode);
action_t mouse_ih_pause();

#endif

