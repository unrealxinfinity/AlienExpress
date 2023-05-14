#ifndef STRUCT_H
#define STRUCT_H



typedef struct {
	game_state_t state;
    action_t action;
} game_info_t;


typedef struct{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint32_t *colors_32; 
    int hitbox_x;
    int hitbox_y;
    int no_img;
    int idle_time;
    bool is_dead;
    bool is_in_inventory;
    uint32_t type;
    movement_t direction;
    movement_t prev_direction;
}img_t;

typedef struct {
    img_t up[8];
    img_t left[8];
    img_t right[8];
    img_t down[8];
    int speed;
}AnimatedImg_t;

typedef struct{
    img_t animation[8];
}simple_animation_t;

typedef struct{
    int tilesPerXAxis;
    int tilesPerYAxis;
}tilesPerAxis;

#endif

