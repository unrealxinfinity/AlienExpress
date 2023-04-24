#include <lcom/lcf.h>
#include"i8042.h"
#include "timer.c"
#include "KBC.h"
uint8_t status;
int (is_makecode)(uint8_t code){
  return !(code & BIT(7));
}


int (read_KBC_status)(uint8_t *status){ 
  return util_sys_inb(KEYBOARD_STATUS,status);
}

int (read_KBC_output)(uint8_t port, uint8_t *out){
  int attempts=10;
  if(!(port == KEYBOARD_OUT )){
    printf("Error: Wrong Port!\n");
    return 1;
  }
  while(attempts){
    if(read_KBC_status(&status)){
      printf("Status read error!\n");
      return 1;
    }
    if(status & PARITY_ERROR){
      printf("Parity Error!\n");
      return 1;
      }
    if(status & TIMEOUT_ERROR){ 
      printf("Timeout Error!\n");
      return 1;
      }
    if(status & FULL_OUT_BUFFER){
      if(util_sys_inb(KEYBOARD_OUT,out)){
        printf("Output read Error!");
        return 1;
        };
      return 0;
    }
    attempts--;
    tickdelay(micros_to_ticks(Delay_interval));
  }
  printf("Exceeded attempts Error!\n");
  return 1;
}

int (write_KBC_command)(uint8_t port,uint8_t command){
  if(!(port == KEYBOARD_CMD_IN || port == KEYBOARD_CMD_PREP )){
    printf("Error: Wrong Port!\n");
    return 1;
  }
  int attempts=10;
  while(attempts){
    if(read_KBC_status(&status)){
        printf("Failed reading status\n");
        return 1;
      }
    if(!(status & FULL_IN_BUFFER)){
      if(sys_outb(port,command)){
        printf("Command byte write Error!\n");
        return 1;
      }
      return 0;
    }
    attempts--;
    tickdelay(micros_to_ticks(Delay_interval));
  }
  printf("Error:Exceeded attemps!\n");
  return 1;
}

