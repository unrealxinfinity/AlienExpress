#ifndef MENU_H
#define MENU_H

#include "../macros/includes.h"
#include "../load/view.h"
action_t mouse_ih_menu();
action_t keyboard_ih_menu(uint32_t scancode);


void draw_menu();
void draw_menu_words();

bool mouse_position(unsigned int xi, unsigned int yi, unsigned int xf, unsigned int yf);
#endif
