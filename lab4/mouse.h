#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "KBC.h"
#include "i8042.h"


int (mouse_subscribe_int)(uint32_t *bit_nr);
int (mouse_unsubscribe_int)();
void (mouse_sync_bytes)();
int (mouse_disable_data_reporting)();
void (mouse_ih)(void);
void fill_struct();
void checkState(uint8_t input);
#endif /* _LCOM_MOUSE_H_ */
