#ifndef PAUSE_H
#define PAUSE_H

#include "../macros/includes.h"
#include "../game_state/level.h"
#include "../devices/mouse.h"

void draw_pause();
void draw_pause_words();

action_t keyboard_ih_pause(uint32_t scancode);
action_t mouse_ih_pause();

#endif

