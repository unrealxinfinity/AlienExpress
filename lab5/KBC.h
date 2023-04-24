#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "KBC.h"


int (read_KBC_status)(uint8_t* status);

int (read_KBC_output)(uint8_t port, uint8_t *output);

int (write_KBC_command)(uint8_t port, uint8_t command);

int (is_makecode)(uint8_t code);

#endif /* _LCOM_KBC_H_ */
