#ifndef GLOBAL_H
#define GLOBAL_H

#include "struct.h"
//timer 
int counter_timer;

//graphics
vbe_mode_info_t mode_info;
unsigned bytes_per_pixel;
uint16_t x_res;
uint16_t y_res;
unsigned int frame_size;
uint8_t *frame_buffer;
uint16_t mode;

//mouse
uint16_t mouse_x;
uint16_t mouse_y;

//xpm images
img_t letters;
img_t mouse_normal;

img_t player;
AnimatedImg_t animated_img_player;



#endif

