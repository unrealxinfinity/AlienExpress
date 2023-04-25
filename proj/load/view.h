#ifndef VIEW_H
#define VIEW_H

#include "../macros/includes.h"
#include "../devices/graphics.h"
#include "../devices/timer_proj.h"
#include "../macros/xpm_includes.h"


void init_img(unsigned int x, unsigned int y,unsigned int xSpeed, unsigned int ySpeed);
img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y);

void init_anim_img(unsigned int x, unsigned int y,unsigned int speed);
AnimatedImg_t make_animated_img(int no_images, unsigned int x, unsigned int y, xpm_map_t curr_xpm, xpm_map_t *images);

int draw(img_t img, int x, int y);
int drawTiles();
int drawUmbreakableWalls(int x ,int y);
int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);
//int draw_animated_img(AnimatedImg_t *anim, int x, int y,uint16_t mode,int indexToDraw);
#endif
