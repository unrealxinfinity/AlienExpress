#ifndef VIEW_H
#define VIEW_H

#include "../macros/includes.h"
#include "../devices/graphics.h"
#include "../devices/timer_proj.h"
#include "../game_state/level.h"

void eliminate_entities();
void initialize_game();
void init_mouse();
void init_img();
void init_monsters();
void init_packages();
void init_teleports();
void init_inventory();
void init_guns();
void init_bullets();
void get_pistol(int index);
void get_ammo(int index);
void get_pizza(int index);
void get_watch(int index);
void get_boots(int index);
void get_backpack(int index);
void get_bone(int index);
void get_grenade(int index);
img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y);

void init_anim_img();
AnimatedImg_t make_animated_img(int no_images, int speed, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down);

void init_simple_animation();
simple_animation_t make_simple_animation(int no_images, xpm_map_t *animation);

int is_occupied(img_t img, int distance);
int manage_collision(img_t *img, int distance);
bool manage_hitbox(img_t target, img_t character);
int get_item(int index, int rate);
void hit_monster(int x, int y);


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
int draw_timer(int sec, int min);
int draw_rtc();
int draw_number(int number, int x, int y, int type);
int draw_health();
int draw_img_number(img_t img, int x, int y);
int draw_line(int x, int y, int len, uint32_t colors);

#endif
