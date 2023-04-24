#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  //("%s is not yet implemented!\n", __func__);
  if(lsb==NULL) return 1;
  uint16_t mask= 0x00ff;
  *lsb = (uint8_t) (mask & val);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  if(msb==NULL) return 1;
  *msb = val>>8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  if(port<0x40 || port>0x43) return 1;
  uint32_t temp;
  if(sys_inb(port,&temp)) return 1;
  *value= temp & 0xff;
  return 0;
}
