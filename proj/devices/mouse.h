#ifndef MOUSE_H
#define MOUSE_H

#include "../macros/includes.h"

uint8_t mouse_subscribe();
int mouse_unsubscribe();
int mouse_write(uint8_t command);

int mouse_read_output(int port);
int mouse_write_output(int port, unsigned long command);

int mouse_control();
void fill_mouse_packet(uint32_t scancode);

#endif
