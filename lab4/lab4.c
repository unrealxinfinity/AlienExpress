// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include "mouse.h"
#include"i8042.h"
#include "i8254.h"
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */
    uint32_t irq_set;
    message msg;
    int ipc_status;
    int r;
    cnt = cnt *3;
    byte_index=0;
    
    if(mouse_enable_data_reporting()) return 1;
    if(mouse_subscribe_int(&irq_set)) return 1;

    while(cnt){
      if((r=driver_receive(ANY,&msg,&ipc_status))!=0){
        printf("Error %d",r);
        continue;
      }
      if(is_ipc_notify(ipc_status)){
        switch (_ENDPOINT_P(msg.m_source))
        {
        case HARDWARE:
          if(msg.m_notify.interrupts & (irq_set & IRQ_SET_MOUSE)){
            mouse_ih();
            mouse_sync_bytes();
            cnt--;
          }
          break;
        default:
          break;
        }
      }
      
    }
    if(mouse_unsubscribe_int()) return 1;
    if(mouse_disable_data_reporting()) return 1;
    
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    uint32_t irq_set;
    uint8_t irq_set_timer=0x00;
    message msg;
    int ipc_status;
    int r;
    
    byte_index=0;
    timerCount=0;

    if(mouse_enable_data_reporting()){
      printf("1");
      return 1;
    } 
    if(mouse_subscribe_int(&irq_set)){
      printf("2");
      return 1;
    } 
    if(timer_subscribe_int(&irq_set_timer)){
      printf("3");
      return 1;
    };

    while(timerCount/60 < idle_time){

      if((r=driver_receive(ANY,&msg,&ipc_status))!=0){
        continue;
      }
      if(is_ipc_notify(ipc_status)){
        switch (_ENDPOINT_P(msg.m_source))
        {
        case HARDWARE:
          if(msg.m_notify.interrupts & (irq_set & IRQ_SET_MOUSE)){
            mouse_ih();
            mouse_sync_bytes();
            timerCount=0;
            
          }
          if(msg.m_notify.interrupts & irq_set_timer){
            timer_int_handler();
          }

          break;
          default: 
          break;
        }
      }
    }
    if(mouse_unsubscribe_int()) return 1;
    if(timer_unsubscribe_int()) return 1;
    if(mouse_disable_data_reporting()) return 1;
    
    return 0;
}

int (mouse_test_gesture)(uint8_t x_len,uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
