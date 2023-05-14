#include "rtc.h"

int hook_id_rtc = 2;

uint8_t (rtc_subscribe)(){
    uint8_t bit_no = BIT(hook_id_rtc);
    sys_irqsetpolicy(8, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_rtc);
    update(true);
    return bit_no;
}
int (rtc_unsubscribe)(){
    if(sys_irqrmpolicy(&hook_id_rtc))return 1;
    update(false);
    return 0;
}

int (update)(bool flag) {
  uint32_t status;

  sys_outb(RTC_ADRESS, RTC_COMMAND);
  sys_inb(RTC_OUTPUT, &status);

  if (flag)status |= BIT(4);
  else status &= ~BIT(4);

  sys_outb(RTC_ADRESS, RTC_COMMAND);
  sys_outb(RTC_OUTPUT, status);

  return 0;
}
int (wait)() {
  uint32_t status = 0;

  do {

    sys_irqdisable(&hook_id_rtc);
    sys_outb(RTC_ADRESS, RTC_COMMAND3);
    sys_inb(RTC_OUTPUT, &status);
    sys_irqenable(&hook_id_rtc);

  } while (BIT(7) & status);

  return 0;
}
void (rtc_ih)() {
  uint32_t status;

  sys_outb(RTC_ADRESS, RTC_COMMAND2);
  sys_inb(RTC_OUTPUT, &status);

  if (BIT(4) & status) {
    rtc_read(RTC_SECONDS, 0);
    rtc_read(RTC_MINUTES, 1);
    rtc_read(RTC_HOURS, 2);
    rtc_read(RTC_DAYS, 3);
    rtc_read(RTC_MONTHS, 4);
    rtc_read(RTC_YEARS, 5);
  }
}

void (rtc_read)(uint8_t command, uint8_t index){
    wait();
    uint32_t data;
    sys_outb(RTC_ADRESS, command);
    sys_inb(RTC_OUTPUT, &data);

    rtc_time[index] = (data-6*(data >> 4));

}


