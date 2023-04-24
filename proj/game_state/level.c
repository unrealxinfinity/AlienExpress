#include "level.h"



void draw_level(uint16_t mode){
    memset(frame_buffer, 0xDDDDDD, frame_size);
    draw(player, player.x, player.y, mode);
    draw(animated_img.images[(counter_timer/30)%7], animated_img.img.x, animated_img.img.y, mode);
}
