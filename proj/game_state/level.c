#include "level.h"
#include <math.h>


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
    int distance = animated_img_player.speed;
    if(move[0] == UP){
        player.no_img += 1;
        player.direction = UP;
        manage_collision(&player, distance);
        is_idle = false;
    }
    if(move[1] == RIGHT){
        player.no_img += 1;
        player.direction = RIGHT;
        manage_collision(&player, distance);
        is_idle = false;
    }
    if(move[2] == LEFT){
        player.no_img += 1;
        player.direction = LEFT;
        manage_collision(&player, distance);
        is_idle = false;
    }
    if(move[3] == DOWN){
        player.no_img += 1;
        player.direction = DOWN;
        manage_collision(&player, distance);
        is_idle = false;
    }
    if(is_idle){
        player.direction = STILL;
    }
    return AFK;
}

void remove_package(img_t character){
    if(alive[0]){
        if(character.hitbox_x >= 100 && character.hitbox_x <= 132 && character.hitbox_y <= 128 && character.hitbox_y >= 100){
            alive[0] = 0;
        }
    }
}


void draw_level(){

    if(alive[0])drawPackage(100,100);
    
    draw_player();
    move_monsters();
}

void draw_player(){
    switch(player.direction){
        case UP:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = UP;
            draw(animated_img_player.up[player.no_img%8], player);
            break;
        case LEFT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = LEFT;
            draw(animated_img_player.left[player.no_img%8], player);
            break;
        case RIGHT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = RIGHT;
            draw(animated_img_player.right[player.no_img%8], player);
            break;
        case DOWN:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = DOWN;
            draw(animated_img_player.down[player.no_img%8], player);
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

void draw_enemies(img_t enemy){
        switch (enemy.direction) {
            case UP:
                draw(animated_img_enemy1.up[enemy.no_img % 8], enemy);
                break;
            case DOWN:
                draw(animated_img_enemy1.down[enemy.no_img % 8], enemy);
                break;
            case LEFT:
                draw(animated_img_enemy1.left[enemy.no_img % 8], enemy);
                break;
            case RIGHT:
                draw(animated_img_enemy1.right[enemy.no_img % 8], enemy);
                break;
            default:
                break;
        }
}

void move_monsters(){
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++){

        int width = player.hitbox_x - enemies_lv1[i].hitbox_x;
        int height = player.hitbox_y - enemies_lv1[i].hitbox_y;
        if(width == 0 && height == 0){
            if(counter_timer % 5 == 0)enemies_lv1[i].no_img += 1;
            draw_enemies(enemies_lv1[i]);
            continue;
        }
        int distance = sqrt(width*width + height*height);
        int final_x = (width*animated_img_enemy1.speed)/distance;
        int final_y = (height*animated_img_enemy1.speed)/distance;

        if(final_x > 0) enemies_lv1[i].direction = RIGHT;
        else if(final_x < 0) {
            enemies_lv1[i].direction = LEFT;
            final_x = abs(final_x);
        }
        if(counter_timer % 5 == 0)enemies_lv1[i].no_img += 1;
        if(!is_occupied(enemies_lv1[i], final_x)){
            manage_collision(&enemies_lv1[i], final_x);
        }


        if(final_y>0)enemies_lv1[i].direction = DOWN;
        else if(final_y <0) {
            enemies_lv1[i].direction = UP;
            final_y = abs(final_y);
        }
        if(!is_occupied(enemies_lv1[i], final_y)){
            manage_collision(&enemies_lv1[i], final_y);
        }
        draw_enemies(enemies_lv1[i]);

    }
}
