#ifndef GLOBAL_H
#define GLOBAL_H

#include "struct.h"
//timer 
int counter_timer;
int seconds;
int minutes;


//points
int score;

//graphics
vbe_mode_info_t mode_info;
unsigned bytes_per_pixel;
uint16_t x_res;
uint16_t y_res;
unsigned int frame_size;
uint8_t *frame_buffer;
uint8_t *prev_buffer;
uint8_t *map;
uint16_t mode;

//mouse
struct packet mouse_packet;
uint16_t mouse_x;
uint16_t mouse_y;
bool mouse_hover;
int mouse_index;
bool mouse_click;

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
AnimatedImg_t animated_img_player_bear_hands;
AnimatedImg_t animated_img_player_pistol;
int player_lives;
int max_health;
int count;

img_t enemies_lv1[150];
AnimatedImg_t animated_img_enemy1;

img_t workers[5];
AnimatedImg_t animated_img_workers;

img_t wolf;
int catched;


img_t packages[6];

img_t teleports[3];

img_t pistols[3];
int pistol_size;

img_t ammo[3];
int ammo_size;

img_t grenades[3];
int grenade_size;

img_t pizza[3];
int food_size;

uint16_t rtc_time[6];
img_t watch;

img_t bullets[50];

//inventory
img_t inventory[9];

//equipment
img_t equipment[3];

uint8_t inventory_size;

img_t selected;

img_t boots;

img_t backpack;

img_t bone;
//uint8_t rtc_time[6];


#endif

