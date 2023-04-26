#ifndef LEVEL_H
#define LEVEL_H
#include "../macros/includes.h"
#include "../load/view.h"

action_t keyboard_ih_level(uint32_t scancode);
void draw_level();
void draw_player();
void draw_enemies();
void change_dir(int index);
#endif
