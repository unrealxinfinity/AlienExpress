#include "level.h"


movement_t move[4]={STILL,STILL,STILL,STILL};

action_t keyboard_ih_level(uint32_t scancode){
    bool is_idle = true;
    if(scancode == MAKE_ESC){
        return EXIT;
    }
    if(scancode == MAKE_W)move[0] = UP;
    if(scancode == MAKE_D)move[1] = RIGHT;
    if(scancode == MAKE_A)move[2] = LEFT;
    if(scancode == MAKE_S)move[3] = DOWN;
    if(scancode == B(MAKE_W))move[0] = STILL;
    if(scancode == B(MAKE_D))move[1] = STILL;
    if(scancode == B(MAKE_A))move[2] = STILL;
    if(scancode == B(MAKE_S))move[3] = STILL;
    if(move[0] == UP){
        player.y -= 10;
        player.no_img += 1;
        player.direction = UP;
        is_idle = false;
    }
    if(move[1] == RIGHT){
        player.x += 10;
        player.no_img += 1;
        player.direction = RIGHT;
        is_idle = false;
    }
    if(move[2] == LEFT){
        player.x -= 10;
        player.no_img += 1;
        player.direction = LEFT;
        is_idle = false;
    }
    if(move[3] == DOWN){
        player.y += 10;
        player.no_img += 1;
        player.direction = DOWN;
        is_idle = false;
    }
    if(is_idle){
        player.direction = STILL;
    }
    return AFK;
}
void draw_level(){
    //memset(frame_buffer, 0xDDDDDD, frame_size);
    drawTiles();
    draw_player();
}
void draw_player(){
    switch(player.direction){
        case UP:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = UP;
            draw(animated_img_player.up[player.no_img%8], player.x, player.y);
            break;
        case LEFT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = LEFT;
            draw(animated_img_player.left[player.no_img%8], player.x, player.y);
            break;
        case RIGHT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = RIGHT;
            draw(animated_img_player.right[player.no_img%8], player.x, player.y);
            break;
        case DOWN:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = DOWN;
            draw(animated_img_player.down[player.no_img%8], player.x, player.y);
            break;
        case STILL:
            if((player.idle_time % 15) == 0){
                player.direction = player.prev_direction;
                player.prev_direction = player.direction;
                player.no_img = 0;
                draw_player();
            }
            else{
                player.idle_time += 1;
                player.direction = player.prev_direction;
                player.prev_direction = STILL;
                draw_player();
            }
        default:
            break;
    }
}
