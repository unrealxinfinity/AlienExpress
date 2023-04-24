#include <lcom/lcf.h>
#include"i8042.h"
#include"keyboard.h"


int kbd_hook_id=1;
uint8_t commandbyte;

int (keyboard_subscribe_interrupts)(uint8_t *bit_nr){
  if(bit_nr==NULL) return 1;
  *bit_nr |= BIT(kbd_hook_id);
  return sys_irqsetpolicy(KEYBOARD_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&kbd_hook_id);
}

int(keyboard_unsubscribe_interrupts)(){
  return sys_irqrmpolicy(&kbd_hook_id);
}

int(keyboard_disable_interrupts)(){
  commandbyte=0x00;
  if(write_KBC_command(KEYBOARD_CMD_PREP,Read_CMDBYTE)) return 1;
  if(read_KBC_output(KEYBOARD_OUT,&commandbyte)) return 1;
  commandbyte = commandbyte ^ ENABLE_KBD_INT;
  if(write_KBC_command(KEYBOARD_CMD_PREP,Write_CMDBYTE)) return 1;
  if(write_KBC_command(KEYBOARD_CMD_IN,commandbyte)) return 1;
  return 0;
}

int (keyboard_restore)(){
  commandbyte=0x00;
  if(write_KBC_command(KEYBOARD_CMD_PREP,Read_CMDBYTE)) return 1;
  if(read_KBC_output(KEYBOARD_OUT,&commandbyte)) return 1;

  commandbyte = commandbyte | ENABLE_KBD_INT;
  if(write_KBC_command(KEYBOARD_CMD_PREP,Write_CMDBYTE)) return 1;
  if(write_KBC_command(KEYBOARD_CMD_IN,commandbyte)) return 1;
  return 0;
  
}

void (kbc_ih)(void){
  read_KBC_output(KEYBOARD_OUT,&scancode);
}
