#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "keyboard.h"
#include "i8254.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  /* To be completed by the students */
  int ipc_status;
  uint8_t irq_set=0x00;
  message msg;
  scancode=0x00;
  counter_KBC=0;  
  int r;
  int s=1;
  if (keyboard_subscribe_interrupts(&irq_set) != 0)
    return 1;

  while(scancode != BREAK_ESC) {
    if ((r=driver_receive(ANY, &msg, &ipc_status) )!= 0) {
      printf("Error: %d",r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            if(scancode==TWO_BYTES){
              s=2;
            }
              kbd_print_scancode(is_makecode(scancode), s, &scancode);
          }
            break;
        default:
            break;
        }
      }
    }
  
  if (keyboard_unsubscribe_interrupts())
    return 1;
  if (kbd_print_no_sysinb(counter_KBC))
    return 1;

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  //printf("%s is not yet implemented!\n", __func__);
  int s=1;
  scancode=0x00;
  while(scancode != BREAK_ESC){
    if(read_KBC_output(KEYBOARD_OUT,&scancode)) return 1;
    if(scancode==TWO_BYTES){
      s=2;
    }
      if(kbd_print_scancode(is_makecode(scancode), s, &scancode)) return 1;
  }
  
  if(keyboard_restore()) return 1;
  if (kbd_print_no_sysinb(counter_KBC)) return 1;
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  

  int ipc_status;
  uint8_t irq_set=0x00;
  message msg;
  int s=1;

  if(timer_subscribe_int(&irq_set)) return 1;

  if (keyboard_subscribe_interrupts(&irq_set) != 0)
    return 1;
 

  while(scancode != BREAK_ESC && (timerCount/60 < n)) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & (irq_set & IRQ_SET_KEYBOARD)) {
             kbc_ih();
            if(scancode==TWO_BYTES){
              s=2;
            }
              kbd_print_scancode(is_makecode(scancode), s, &scancode);
          }
          if(msg.m_notify.interrupts & (irq_set & IRQ_SET_TIMER)){
           timer_int_handler(); 
          }
        }
      }
    }
  if(timer_unsubscribe_int()) return 1 ;
  if (keyboard_unsubscribe_interrupts() != 0)
    return 1;
  if (kbd_print_no_sysinb(counter_KBC) != 0)
    return 1;

  return 0;
}

