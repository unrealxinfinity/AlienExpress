#ifndef MENU_H
#define MENU_H

#include "../macros/includes.h"
#include "../load/view.h"

action_t keyboard_ih_menu(uint32_t scancode);
void draw_menu(uint16_t mode);
void draw_menu_words(uint16_t mode);
#endif
