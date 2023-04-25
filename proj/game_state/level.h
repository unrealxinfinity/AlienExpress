#ifndef LEVEL_H
#define LEVEL_H
#include "../macros/includes.h"
#include "../load/view.h"

action_t keyboard_ih_level(uint32_t scancode);
void draw_level(uint16_t mode);
void draw_player(uint16_t mode);
#endif
