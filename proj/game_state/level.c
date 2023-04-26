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
        player.y -= animated_img_player.speed;
        player.hitbox_y -= animated_img_player.speed;
        player.no_img += 1;
        player.direction = UP;
        is_idle = false;
    }
    if(move[1] == RIGHT){
        player.x += animated_img_player.speed;
        player.hitbox_x += animated_img_player.speed;
        player.no_img += 1;
        player.direction = RIGHT;
        is_idle = false;
    }
    if(move[2] == LEFT){
        player.x -= animated_img_player.speed;
        player.hitbox_x -= animated_img_player.speed;
        player.no_img += 1;
        player.direction = LEFT;
        is_idle = false;
    }
    if(move[3] == DOWN){
        player.y += animated_img_player.speed;
        player.hitbox_y += animated_img_player.speed;
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
    drawTiles();
    drawBorder();

        drawPackage(100,100);

    draw_player();
    draw_enemies();
}

void draw_player(){
    switch(player.direction){
        case UP:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = UP;
            manage_collision(animated_img_player.up[player.no_img%8], &player);
            draw(animated_img_player.up[player.no_img%8], player);
            break;
        case LEFT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = LEFT;
            manage_collision(animated_img_player.left[player.no_img%8], &player);
            draw(animated_img_player.left[player.no_img%8], player);
            break;
        case RIGHT:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = RIGHT;
            manage_collision(animated_img_player.right[player.no_img%8], &player);
            draw(animated_img_player.right[player.no_img%8], player);
            break;
        case DOWN:
            if(player.prev_direction == STILL) player.direction = STILL;
            else player.idle_time = 1;
            player.prev_direction = DOWN;
            manage_collision(animated_img_player.down[player.no_img%8], &player);
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

void draw_enemies(){
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++) {
        switch (enemies_lv1[i].direction) {
            case UP:
                enemies_lv1[i].y -= animated_img_enemy1.speed;
                enemies_lv1[i].hitbox_y -= animated_img_player.speed;
                enemies_lv1[i].no_img += 1;
                if (enemies_lv1[i].y - 32 > inner_border_right) {
                    manage_collision(animated_img_enemy1.up[enemies_lv1[i].no_img % 8], &enemies_lv1[i]);
                    draw(animated_img_enemy1.up[enemies_lv1[i].no_img % 8], enemies_lv1[i]);
                }
                else change_dir(i);
                break;
            case DOWN:
                enemies_lv1[i].y += animated_img_enemy1.speed;
                enemies_lv1[i].hitbox_y += animated_img_player.speed;
                enemies_lv1[i].no_img += 1;
                if (enemies_lv1[i].y + 32 < inner_border_down) {
                    manage_collision(animated_img_enemy1.down[enemies_lv1[i].no_img % 8], &enemies_lv1[i]);
                    draw(animated_img_enemy1.down[enemies_lv1[i].no_img % 8], enemies_lv1[i]);
                }else change_dir(i);
                break;
            case LEFT:
                enemies_lv1[i].x -= animated_img_enemy1.speed;
                enemies_lv1[i].hitbox_x -= animated_img_player.speed;
                enemies_lv1[i].no_img += 1;
                if (enemies_lv1[i].x -32 > inner_border_left) {
                    manage_collision(animated_img_enemy1.left[enemies_lv1[i].no_img % 8], &enemies_lv1[i]);
                    draw(animated_img_enemy1.left[enemies_lv1[i].no_img % 8], enemies_lv1[i]);
                }else change_dir(i);
                break;
            default:
                enemies_lv1[i].x += animated_img_enemy1.speed;
                enemies_lv1[i].hitbox_x = animated_img_player.speed;
                enemies_lv1[i].no_img += 1;
                if (enemies_lv1[i].x + 32 < inner_border_right) {
                    manage_collision(animated_img_enemy1.right[enemies_lv1[i].no_img % 8], &enemies_lv1[i]);
                    draw(animated_img_enemy1.right[enemies_lv1[i].no_img % 8], enemies_lv1[i]);
                }else change_dir(i);
                break;
        }
    }
}

void change_dir(int i) {
    /*int r = rand() % 4;
    movement_t dir[4] = {UP, DOWN, RIGHT, LEFT};
    enemies_lv1[i].direction = dir[r];*/
    if(enemies_lv1[i].y < player.y)
        enemies_lv1[i].direction = UP;
    if(enemies_lv1[i].y > player.y)
        enemies_lv1[i].direction = DOWN;
    if(enemies_lv1[i].x < player.x)
        enemies_lv1[i].direction = RIGHT;
    if(enemies_lv1[i].x > player.x)
        enemies_lv1[i].direction = LEFT;
}
