#ifndef VIEW_H
#define VIEW_H

#include "../macros/includes.h"
#include "../devices/graphics.h"
#include "../devices/timer_proj.h"
#include "../game_state/level.h"


void init_img();
img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y);

void init_anim_img();
AnimatedImg_t make_animated_img(int no_images, int speed, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down);

void init_simple_animation();
simple_animation_t make_simple_animation(int no_images, xpm_map_t *animation);

int manage_collision(img_t *img, int distance);
bool is_occupied(img_t img, int distance);

int draw(img_t draw_img, img_t img);
int draw_map(img_t draw_img, img_t img);
int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);
int drawTiles();
int drawTile(int x ,int y,img_t img);
int drawBorder();
int drawSidePannel();
int drawSidePannelBG();
int drawInventory();
int drawPackage(int x,int y);

#endif
