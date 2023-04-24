#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

#include "i8254.h"
int hook_id=0;
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  if(timer<0 | timer> 2) return 1;
  if(freq> 0xffffffff) return 1;
  uint8_t config=0x00;
  uint8_t BCD= 0x00;
  uint8_t useful4bits = 0x00;
  uint32_t timer_val= 0x0000;
  uint32_t control=0x0000;
  uint8_t MSB_LSB = 0x00;
     
  timer_get_conf(timer,&config);

  uint8_t counter_init= (BIT(5) | BIT(4)) ;
  
  BCD = BIT(1) & config;
  
  useful4bits = 0x0f & config; 
  
  control =  (timer << 6 ) | counter_init | useful4bits ;
  
  sys_outb(TIMER_CTRL,control);
  timer_val = (TIMER_FREQ)/freq;
  if(timer_val > 0x0000ffff) return 1;
  util_get_LSB((uint16_t)timer_val,&MSB_LSB);
  sys_outb(TIMER_0+timer,MSB_LSB);
  util_get_MSB((uint16_t)timer_val,&MSB_LSB);
  sys_outb(TIMER_0+timer,MSB_LSB);
  return 0;
}


int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
 
  hook_id = *bit_no;
  int r = sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id);
  
  if(r==EINVAL|| r==EPERM || r==ENOSPC ) return -1 ;
  return hook_id;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  int r = sys_irqrmpolicy(&hook_id);
  if(r==EINVAL|| r==EPERM || r==ENOSPC ) return 1;
  return 0;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  timerCount++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  uint32_t controlword = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL, controlword);
  util_sys_inb(TIMER_0+timer,st);
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  
  union timer_status_field_val res_union;
  if(field == tsf_all){
    res_union.byte = st;
  }
  else if(field == tsf_initial){
    uint8_t temp = (st & TIMER_LSB_MSB)>>4;
    res_union.in_mode=temp;
  }
  else if(field== tsf_mode){
    if( st & BIT(2) ) {
       res_union.count_mode= (st & (TIMER_SQR_WAVE)) >>1;
    }
    else{
       res_union.count_mode= (st & (BIT(3)|TIMER_SQR_WAVE)) >>1;
    }
  }
  else if(field == tsf_base){
    res_union.bcd= st & BIT(0);
  }
   timer_print_config(timer,field,res_union);
  return 0;
}
