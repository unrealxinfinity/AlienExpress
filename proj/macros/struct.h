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
    int xSpeed, ySpeed;
    uint32_t *colors_32; 
    uint16_t *colors_16;
    uint8_t *colors_8;
}img_t;

typedef struct {
    img_t img; //standard sprite
    int no_img;
    img_t images[16];
}AnimatedImg_t;

#endif

