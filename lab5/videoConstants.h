#ifndef _VIDEOCONSTANTS_
#define _VIDEOCONSTANTS_

#include <lcom/lcf.h>

#define video_set_func 0x4f
#define func_supported 0x4f
#define func_call_failed 0x01
#define func_not_supported_curent_HW 0x02
#define invalid_func_in_current_vid_mode 0x03
#define func_set_VBE_mode 0x02
#define func_get_VBE_info 0x01
#define int_nr 0x10
#define indexed_color_mode 0x105
#define direct_mode 0x06

static uint8_t *vid_mem;
unsigned int vram_base;
unsigned int vram_offset;
struct minix_mem_range mr;
struct reg86 reg;
static unsigned int xRes;
static unsigned int yRes;
static unsigned int bytes_per_pixel;
vbe_mode_info_t mode_info;

struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
 } rbg_8_8_8_t;

#endif

