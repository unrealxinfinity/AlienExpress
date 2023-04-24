#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../macros/includes.h"

uint8_t (keyboard_subscribe)();
int (keyboard_unsubscribe)();

int (kbc_read_output)(int port, uint32_t *command);
int (kbc_write_output)(int port, unsigned long command);
int (keyboard_restore)();

#endif
