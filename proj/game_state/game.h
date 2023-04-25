#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "../macros/includes.h"
#include "../load/view.h"
#include "../devices/graphics.h"
#include "../devices/keyboard.h"
#include "../devices/mouse.h"
#include "../devices/timer_proj.h"
#include "../game_state/menu.h"
#include "../game_state/level.h"

void set_state(game_state_t state);


int keyboard_ih(uint32_t scancode);
int control_state(uint32_t scancode);
int draw_state();


int initialize();
int game_loop();

int terminate();
#endif


