#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "videoConstants.h"



int set_VBE_Mode(u16_t mode);

int get_VBE_Mode_info(struct reg86 reg, u16_t mode, u16_t returnInfoAddr );

int map_Vmem(u16_t mode);

int draw_pixel(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint8_t Red(uint32_t color);

uint8_t Green(uint32_t color);

uint8_t Blue(uint32_t color);

uint32_t R(unsigned x, unsigned y,uint32_t step,uint32_t first);
uint32_t G(unsigned x,unsigned y,uint32_t step,uint32_t first);
uint32_t B(unsigned x, unsigned y,uint32_t step,uint32_t first);

uint32_t indexed_mode(uint16_t col ,uint16_t row ,uint8_t step,uint32_t first,uint8_t no_rectangles);

int load_xmp_to_Vmem(xpm_map_t xpm,unsigned x,unsigned y);


