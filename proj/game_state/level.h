#ifndef LEVEL_H
#define LEVEL_H
#include "../macros/includes.h"
#include "../load/view.h"


action_t keyboard_ih_level(uint32_t scancode);
void remove_package(img_t character);

void draw_level();
void draw_player();
void draw_enemies(img_t enemy);
void move_monsters();
#endif
