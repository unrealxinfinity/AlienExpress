#include <lcom/lcf.h>
#include <lcom/lab2.h>
#include "i8254.h"
#include <stdbool.h>
#include <stdint.h>
#define bit_notification BIT(1) /*aka bit mask to match hook id*/
uint8_t notification_bit = 1 ;/*aka hook id value*/
int timerCount=0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  uint8_t st=0x00;
  timer_get_conf(timer,&st);
  timer_display_conf(timer,st,field);
  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  if(timer_set_frequency(timer,freq)) return 1;
  return 0;
}

int(timer_test_int)(uint8_t time) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  int time_elapsed=0;
  int communication_status;
  message msg;
  int r;
  timerCount=0;

  timer_subscribe_int(&notification_bit);
  while(time_elapsed < time){
    if((r = driver_receive(ANY,&msg,&communication_status))!= 0){
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if(is_ipc_notify(communication_status)){
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if(msg.m_notify.interrupts & bit_notification){
            timer_int_handler();
            if(timerCount % 60 == 0){
              timer_print_elapsed_time();
              time_elapsed++;
            }
        }
        break;
      default:
        break;
      }
    }
  }
  timer_unsubscribe_int();
  return 1;
}
