#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define kEYBOARD_IN 0x64 //Input buffer for keyboard
#define KEYBOARD_OUT 0x60 //Output buffer for keyboard
#define KEYBOARD_STATUS 0x64 //Status buffer for keyboard
#define KEYBOARD_CMD_PREP 0x64 // Port to input instruction to the cpu whether to read or write a command word
#define KEYBOARD_CMD_IN 0x60 //Port to insert the command word
#define Delay_interval 20000 //interval in 20 ms
#define Read_CMDBYTE 0x20 // Command to read
#define Write_CMDBYTE 0x60 //Write command 
#define ENABLE_KBD_INT BIT(0)
#define FULL_OUT_BUFFER BIT(0)
#define FULL_IN_BUFFER BIT(1)
#define PARITY_ERROR BIT(7)
#define TIMEOUT_ERROR BIT(6)
#define BREAK_ESC 0x81 //breakcode for ESC
#define TWO_BYTES 0xE0
#define IRQ_SET_KEYBOARD BIT(1) 

uint32_t counter_KBC;
uint8_t scancode;

#endif /* _LCOM_I8042_H_ */
