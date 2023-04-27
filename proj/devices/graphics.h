#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../macros/includes.h"


int set_graphics_mode(uint16_t mode);
int init_graphics(uint16_t mode);
int set_frame_buffer(uint16_t mode);

void Allocate();
void pass_to_vm_buffer();
void pass_map();

int draw_pixel(uint16_t x,uint16_t y,uint32_t color);
int draw_pixel_map(uint16_t x, uint16_t y, uint32_t colors_32);


#endif
