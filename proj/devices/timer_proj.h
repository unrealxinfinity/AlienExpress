#ifndef TIMER_PROJ_H
#define TIMER_PROJ_H

#include "../macros/includes.h"



uint8_t (timer_subscribe)();
int (timer_unsubscribe)();
void (timer_int_handler_proj)();

int (timer_set_frequency_proj)(uint8_t timer, uint32_t freq);
uint32_t timer_get_config(uint8_t timer);

#endif
