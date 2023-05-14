#ifndef RTC_H
#define RTC_H

#include "../macros/includes.h"
#include <lcom/lcf.h>

uint8_t (rtc_subscribe)();
int (rtc_unsubscribe)();

int (update)(bool flag);
int (wait)();

void (rtc_read)(uint8_t command, uint8_t index);

void (rtc_ih)();

#endif

