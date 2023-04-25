#ifndef VIEW_H
#define VIEW_H

#include "../macros/includes.h"
#include "../devices/graphics.h"
#include "../devices/timer_proj.h"


void init_img(unsigned int x, unsigned int y);
img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y);

void init_anim_img(unsigned int x, unsigned int y);
AnimatedImg_t make_animated_img(int no_images, unsigned int x, unsigned int y, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down);

int draw(img_t img, int x, int y);
int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);
int drawTiles();
#endif
