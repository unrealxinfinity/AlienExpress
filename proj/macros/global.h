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
struct packet mouse_packet;
uint16_t mouse_x;
uint16_t mouse_y;
bool mouse_hover;

//xpm images
img_t letters;


//border positions
int inner_border_up;
int inner_border_left;
int inner_border_right;
int inner_border_down;
int outter_border_right;

//package status
//bool picked=false;

img_t mouse;
simple_animation_t mouse_animation;

img_t player;
AnimatedImg_t animated_img_player;

img_t enemies_lv1[5];
AnimatedImg_t animated_img_enemy1;


#endif

