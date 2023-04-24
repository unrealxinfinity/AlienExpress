

#include <lcom/lcf.h>
#include<lcom/timer.h>
#include "mouse.h"

int hook_id_mouse=12;
 
int (mouse_subscribe_int)(uint32_t *bit_nr){

if( bit_nr==NULL) return 1;
*bit_nr|=BIT(hook_id_mouse);

return sys_irqsetpolicy(KBD_AUX_IRQ,IRQ_ENABLE|IRQ_EXCLUSIVE,&hook_id_mouse);

}

int (mouse_unsubscribe_int)(){
  return sys_irqrmpolicy(&hook_id_mouse);
}
int (mouse_write)(uint8_t command){
  uint8_t error_byte;
  int attempts=10;
 do{
    if(write_KBC_command(KEYBOARD_CMD_PREP,MOUSE_WRITE_BYTE)) return 1;
    if(write_KBC_command(KEYBOARD_CMD_IN,command)) return 1;
    tickdelay(micros_to_ticks(Delay_interval));
    if(read_KBC_output(KEYBOARD_OUT,&error_byte,1))return 1;
    error_byte &= 0xff;
    attempts--;
 }while(error_byte != 0xFA && attempts);
  return 0;
}
int (mouse_disable_data_reporting)(){
  return mouse_write(MOUSE_DISABLE_REPORT);
}
void (fill_struct)(){
  uint8_t control = m_bytes[0];
  uint8_t x = m_bytes[1];
  uint8_t y = m_bytes[2];

  for(int i=0;i<3;i++){
    p.bytes[i]=m_bytes[i];
  }
  p.lb=control & MOUSECTRL_LMB;
  p.mb=control & MOUSECTRL_MMB;
  p.rb=control & MOUSECTRL_RMB;
  if(control & MOUSECTRL_MSB_X_SIGN) p.delta_x = x | 0xFF00;
  else p.delta_x = x;

  if(control & MOUSECTRL_MSB_Y_SIGN) p.delta_y = y | 0xFF00;
  else p.delta_y = y;

  p.x_ov=control & MOUSECTRL_X_OVFL;
  p.y_ov=control & MOUSECTRL_y_OVFL;
}

void (mouse_sync_bytes)(){
  
  if (byte_index == 0 && (current_byte & BIT(3))) {
    // é o byte CONTROL, o bit 3 está ativo
    m_bytes[byte_index]= current_byte;
    byte_index++;
  }
  else if (byte_index > 0) {
    // recebe os deslocamentos em X e Y
    m_bytes[byte_index] = current_byte;
    byte_index++;
  }

  if (byte_index == 3) {
    // completou o pacote
    fill_struct();
    mouse_print_packet(&p);
    byte_index = 0;
  }
}
void(mouse_ih)(void){
  read_KBC_output(KEYBOARD_OUT,&current_byte,1);
}

