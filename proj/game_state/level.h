#ifndef LEVEL_H
#define LEVEL_H
#include "../macros/includes.h"
#include "../load/view.h"
#include "../load/spawner.h"
#include "../devices/mouse.h"


action_t keyboard_ih_level(uint32_t scancode);
action_t mouse_ih_level();
void open_package(int index);
void remove_package(img_t character);
void remove_guns(img_t character);
void remove_from_inventory(int index);
void remove_from_equipment(int index);
int is_inventory_full();
int is_on_teleport(img_t character);
void player_hit();
void reset_movement();
int score_animation(img_t *character, int type);
void throw_animation(img_t *item, bool was_throwed);
int count_packages();
void kill_monster_radius(int x, int y, int max_x, int max_y);

void draw_level();
void draw_player();
void draw_afk_player();
void draw_enemies(img_t enemy);
void draw_workers(img_t worker);
void draw_wolf(img_t wolf);
void move_monsters();
void kill_workers();
void move_workers();
void move_wolf();
void move_bullets();
void draw_level_words();
void draw_level_numbers();
void draw_packages();
void draw_inventory();
void draw_teleports();
void draw_score(int type);
void draw_guns();
void draw_bullets(img_t bullet);
#endif
