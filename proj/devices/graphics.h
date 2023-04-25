#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../macros/includes.h"


int set_graphics_mode(uint16_t mode);
int init_graphics(uint16_t mode);
int set_frame_buffer(uint16_t mode);


void copyBufferToVideo();
void allocate();
void free_buffers();
int draw_pixel(uint16_t x,uint16_t y,uint32_t color);


#endif
