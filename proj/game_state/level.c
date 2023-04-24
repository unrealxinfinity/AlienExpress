#include "level.h"


void draw_level(uint16_t mode){
    memset(frame_buffer, 0xDDDDDD, frame_size);
    draw_player(mode);
}
void draw_player(uint16_t mode){
    switch(player.direction){
        case UP:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = UP;
            draw(animated_img_player.up[player.no_img%8], player.x, player.y, mode);
            break;
        case LEFT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = LEFT;
            draw(animated_img_player.left[player.no_img%8], player.x, player.y, mode);
            break;
        case RIGHT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = RIGHT;
            draw(animated_img_player.right[player.no_img%8], player.x, player.y, mode);
            break;
        case DOWN:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = DOWN;
            draw(animated_img_player.down[player.no_img%8], player.x, player.y, mode);
            break;
        case STILL:
            if((player.idle_time % 15) == 0){
                player.direction = player.prev_direction;
                player.prev_direction = player.direction;
                player.no_img = 0;
                draw_player(mode);
            }
            else{
                player.idle_time += 1;
                player.direction = player.prev_direction;
                player.prev_direction = STILL;
                draw_player(mode);
            }
        default:
            break;
    }
}
