#include "view.h"

bool is_occupied(img_t img, int distance){
    uint32_t colors_32 = 0;
    switch(img.direction){
        case UP:
            for(int j = 0; j < distance; j++){
                for(int i = img.hitbox_x-3; i <= img.hitbox_x+3; i++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(img.y-(j+1))+ i) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY){
                        return true;
                    }
                    else if(colors_32 == PLAYER){
                        player_lives--;
                    }
                }
            }
            break;
        case LEFT:
            for(int i = 0; i < distance; i++){
                for(int j = img.hitbox_y-3; j <= img.hitbox_y+3; j++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(j)+img.x-(i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY){
                        return true;
                    }
                    else if(colors_32 == PLAYER){
                        player_lives--;
                    }
                }
            }
            break;
        case RIGHT:
            for(int i = 0; i < distance; i++){
                for(int j = img.hitbox_y-3; j <= img.hitbox_y+3; j++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(j)+(img.x+img.width+i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY){
                        return true;
                    }
                    else if(colors_32 == PLAYER){
                        player_lives--;;
                    }
                }
            }
            break;
        case DOWN:
            for(int j = 0; j < distance; j++){
                for(int i = img.hitbox_x-3; i <= img.hitbox_x+3; i++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(img.y+img.height+j+1)+i) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY){
                        return true;
                    }
                    else if(colors_32 == PLAYER){
                        player_lives--;
                    }
                }
            }
            break;
        default:
            break;
    }
    return false;
}
int manage_collision(img_t *img, int distance){
    if(img->direction == STILL)return 0;
    uint32_t colors_32 = 0;
    switch(img->direction) {
        case UP:
            if((img->y-distance) < 0){
                img->y = 0;
                img->hitbox_y = img->y + (img->height/2);
                break;
            }
            for(int j = 0; j < distance; j++){
                for(int i = img->hitbox_x-3; i <= img->hitbox_x+3; i++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(img->y-(j+1))+ i) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) ||  (colors_32 == ENEMY)){
                        img->y -= j;
                        img->hitbox_y -= j;
                        return 0;
                    }
                    if(colors_32 == PACKAGE && img->hitbox_x == player.hitbox_x && img->hitbox_y == player.hitbox_y){
                        img->hitbox_y -= distance;
                        remove_package(*img);
                        img->hitbox_y += distance;
                    }
                }
            }
            img->y -= distance;
            img->hitbox_y -= distance;

            break;
        case LEFT:
            if((img->x-distance) < 0){
                img->x = 0;
                img->hitbox_x = (img->width/2);
                break;
            }
            for(int i = 0; i < distance; i++){
                for(int j = img->hitbox_y-3; j <= img->hitbox_y+3; j++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(j)+img->x-(i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY)){
                        img->x -= i;
                        img->hitbox_x -= i;
                        return 0;
                    }
                    if(colors_32 == PACKAGE && img->hitbox_x == player.hitbox_x && img->hitbox_y == player.hitbox_y){
                        img->hitbox_x -= distance;
                        remove_package(*img);
                        img->hitbox_x += distance;
                    }
                }
            }
            img->x -= distance;
            img->hitbox_x -= distance;
            break;
        case RIGHT:
            if((img->x+img->width+distance) > x_res){
                img->x = x_res-img->width;
                img->hitbox_x = img->x+(img->width/2);
                break;
            }
            for(int i = 0; i < distance; i++){
                for(int j = img->hitbox_y-3; j <= img->hitbox_y+3; j++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(j)+(img->x+img->width+i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY)){
                        img->x += i;
                        img->hitbox_x += i;
                        return 0;
                    }
                    if(colors_32 == PACKAGE && img->hitbox_x == player.hitbox_x && img->hitbox_y == player.hitbox_y){
                        img->hitbox_x += distance;
                        remove_package(*img);
                        img->hitbox_x -= distance;
                    }
                }
            }
            img->x += distance;
            img->hitbox_x += distance;
            break;
        case DOWN:
            if((img->y + img->height+distance) > y_res){
                img->y = y_res-img->height;
                img->hitbox_y = img->y + (img->height/2);
                break;
            }
            for(int j = 0; j < distance; j++){
                for(int i = img->hitbox_x-3; i <= img->hitbox_x+3; i++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(img->y+img->height+j+1)+i) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY)){
                        img->y += j;
                        img->hitbox_y += j;
                        return 0;
                    }
                    if(colors_32 == PACKAGE && img->hitbox_x == player.hitbox_x && img->hitbox_y == player.hitbox_y){
                        img->hitbox_y += distance;
                        remove_package(*img);
                        img->hitbox_y -= distance;
                    }
                }
            }
            img->y += distance;
            img->hitbox_y += distance;
            break;
        default:
            break;
    }
    return 0;
}
bool manage_hitbox(img_t target, img_t character){
    if(character.hitbox_x >= target.x && character.hitbox_x <= (target.x+target.width) && character.hitbox_y <= (target.y+target.height) && character.hitbox_y >= target.y){
        return true;
    }
    return false;
}
int draw(img_t draw_img, img_t img){
    for(int j = 0; j < draw_img.height; j++){
        for(int i = 0; i < draw_img.width; i++){
            int index = j*draw_img.width + i;
            if(draw_pixel(img.x+i, img.y+j, draw_img.colors_32[index])) return 1;
        }
    }
    return 0;
}

int draw_map(img_t draw_img, img_t img){
    for(int j = 0; j < draw_img.height; j++){
        for(int i = 0; i < draw_img.width; i++){
            int index = j*draw_img.width + i;
            if(draw_pixel_map(img.x+i, img.y+j, draw_img.colors_32[index])) return 1;
        }
    }
    return 0;
}

int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y){
    img_t img = make_img(xpm, x, y);
    if(draw(img, img)) return 1;
    return 0;
}
/*int drawTile(int x ,int y,img_t *img){
    xpm_map_t image=(xpm_map_t) ground_xpm;
    *img = make_img(image,x,y);
    if(draw(*img,x,y))return 1;
    return 0;
}*/
int drawTiles(){
    tilesPerAxis tilesXY;
    xpm_map_t image=(xpm_map_t) ground_xpm;
    img_t img = make_img(image,0,0);

    tilesXY.tilesPerXAxis=inner_border_right/img.width+1;
    tilesXY.tilesPerYAxis=y_res/img.height+1;
   for(int i=0 ; i<tilesXY.tilesPerYAxis;i++){
        for(int j=0; j<tilesXY.tilesPerXAxis;j++){
            img.x = j*img.width;
            img.y = i*img.height;
            if(draw_map(img,img))return 1;
        }
    }
    return 0;
}
int drawBorder(){
    tilesPerAxis tilesXY;
    xpm_map_t image=(xpm_map_t)unbreakableWalls_xpm;
    img_t img = make_img(image,0,0);
    tilesXY.tilesPerXAxis=x_res/img.width+1;
    tilesXY.tilesPerYAxis=y_res/img.height+1;
    for(int i=0 ; i<tilesXY.tilesPerYAxis;i++){
        img.y = i*img.height;
        if(draw_map(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerXAxis;i++){
        img.x = i*img.width;
        img.y = 0;
        if(draw_map(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerYAxis;i++){
        img.x = (x_res-img.width-200);
        img.y = i*img.height;
        if(draw_map(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerXAxis;i++){
        img.x = img.width*i;
        img.y = y_res - img.height;
        if(draw_map(img,img)) return 1;
    }

    inner_border_up=img.height;
    inner_border_down=y_res-img.height;
    inner_border_left=img.width;
    inner_border_right=tilesXY.tilesPerXAxis*img.width;
    outter_border_right=inner_border_right+img.width;
    return 0;

}
int drawPackage(int x, int y){
    xpm_map_t image=(xpm_map_t)small_box_xpm;
    img_t img = make_img(image,x,y);
    if(draw(img,img))return 1;
    return 0;

}
int drawInventory(){
    return 0;

}
int draw_timer(int sec, int min){
    int x = 515;
    int number;
    int count = 1;
    while(count < 3){
        number = min % 10;
        min = min/10;
        draw_number(number, x, 20);
        x -= 15;
        count++;
    }
    x = 560;
    count = 1;
    while(count < 3){
        number = sec % 10;
        sec = sec / 10;
        draw_number(number, x, 20);
        x-= 15;
        count++;
    }
    return 0;
}
int draw_number(int number, int x, int y){
    switch(number){
        case 0:
            draw_small_xpm((xpm_map_t)zero_xpm, x, y);
            break;
        case 1:
            draw_small_xpm((xpm_map_t)one_xpm, x, y);
            break;
        case 2:
            draw_small_xpm((xpm_map_t)two_xpm, x, y);
            break;
        case 3:
            draw_small_xpm((xpm_map_t)three_xpm, x, y);
            break;
        case 4:
            draw_small_xpm((xpm_map_t)four_xpm, x, y);
            break;
        case 5:
            draw_small_xpm((xpm_map_t)five_xpm, x, y);
            break;
        case 6:
            draw_small_xpm((xpm_map_t)six_xpm, x, y);
            break;
        case 7:
            draw_small_xpm((xpm_map_t)seven_xpm, x, y);
            break;
        case 8:
            draw_small_xpm((xpm_map_t)eight_xpm, x, y);
            break;
        case 9:
            draw_small_xpm((xpm_map_t)nine_xpm, x, y);
            break;
    }
    return 0;
}
int draw_health(){
    int health = 40;
    if(player_lives < -20)player_lives = -20;
    for(int i = 1; i <= health; i++){
        if(i > player_lives){
            draw_line(player.x + i-5, player.y+player.height + 8, 4, EMPTY_HEALTH);
        }
        else{
            draw_line(player.x + i - 5, player.y+player.height + 8, 4, HEALTH);
        }
    }
    return 0;
}
int draw_line(int x, int y, int len, uint32_t colors){
    for(int i = 0; i < len; i++){
        if(draw_pixel(i+x, y+i, colors)) return 1;
    }
    return 0;
}
void init_img(){
    seconds = 0;
    minutes = 0;
    score = 0;
    //player
    player = make_img((xpm_map_t) mc1_xpm,214,100);
    player.prev_direction = RIGHT;
    player_lives = 40;
    //enemies
    for (int i =0; i<5; i++) {
        enemies_lv1[i] = make_img((xpm_map_t) enemy1_xpm,100*(i),100*(i));
        enemies_lv1[i].direction = RIGHT;

        packages[i] = make_img((xpm_map_t)small_box_xpm, 0, 0);
    }
    packages[3].x = 100;
    packages[3].y = 100;
    packages[3].is_dead = false;
    //mouse


}
void init_mouse(){
    mouse_hover = false;
    mouse_x = -20;
    mouse_y = -20;
    mouse = make_img((xpm_map_t)mouse_normal_xpm, mouse_x, mouse_y);  
    xpm_map_t mouse_movement[2] = {(xpm_map_t)mouse_normal_xpm, (xpm_map_t)mouse_selected_xpm};
    mouse_animation = make_simple_animation(2, mouse_movement);  
}
void init_anim_img(){
    //player
    xpm_map_t up[8] = {(xpm_map_t)mcUp1_xpm, (xpm_map_t)mcUp2_xpm,(xpm_map_t)mcUp3_xpm,(xpm_map_t)mcUp4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)mcUp6_xpm,(xpm_map_t)mcUp7_xpm, (xpm_map_t)mcUp8_xpm};
    xpm_map_t left[8] = {(xpm_map_t)mcLeft1_xpm, (xpm_map_t)mcLeft2_xpm,(xpm_map_t)mcLeft3_xpm,(xpm_map_t)mcLeft4_xpm,(xpm_map_t)mcLeft5_xpm,(xpm_map_t)mcLeft6_xpm,(xpm_map_t)mcLeft7_xpm, (xpm_map_t)mcLeft8_xpm};
    xpm_map_t right[8] = {(xpm_map_t)mcRight1_xpm, (xpm_map_t)mcRight2_xpm,(xpm_map_t)mcRight3_xpm,(xpm_map_t)mcRight4_xpm,(xpm_map_t)mcRight5_xpm,(xpm_map_t)mcRight6_xpm,(xpm_map_t)mcRight7_xpm, (xpm_map_t)mcRight8_xpm};
    xpm_map_t down[8] = {(xpm_map_t)mcDown1_xpm, (xpm_map_t)mcDown2_xpm,(xpm_map_t)mcDown3_xpm,(xpm_map_t)mcDown4_xpm,(xpm_map_t)mcDown5_xpm,(xpm_map_t)mcDown6_xpm,(xpm_map_t)mcDown7_xpm, (xpm_map_t)mcDown8_xpm};
    animated_img_player= make_animated_img(8, 20, up, left, right, down);
    //enemy1
    xpm_map_t down1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t left1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t right1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t up1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    animated_img_enemy1 = make_animated_img(8, 2, up1, left1, right1, down1);
}
void init_simple_animation(){
}


img_t make_img(xpm_map_t xpm, unsigned int x, unsigned int y){
    xpm_image_t xpm_img;
    img_t img;
    
        img.colors_32 = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &xpm_img);
        img.width = xpm_img.width;
        img.height = xpm_img.height;
        img.x = x;
        img.y = y;
        img.no_img = 0;
        img.direction = STILL;
        img.hitbox_x = x + (img.width/2);
        img.hitbox_y = y + (img.height/2);
        img.is_dead = true;
        img.is_in_inventory = false;

    return img;
}

AnimatedImg_t make_animated_img(int no_images, int speed, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down){
    AnimatedImg_t anime_img;
    for(int i=0;i<no_images;i++){
        anime_img.up[i] = make_img(up[i],0,0);
        anime_img.left[i] = make_img(left[i],0,0);
        anime_img.right[i] = make_img(right[i],0,0);
        anime_img.down[i] = make_img(down[i],0,0);

    }
    anime_img.speed = speed;
    return anime_img;
}
simple_animation_t make_simple_animation(int no_images, xpm_map_t *animation){
    simple_animation_t simple_animation;
    for(int i = 0; i < no_images; i++){
        simple_animation.animation[i] = make_img(animation[i], 0, 0);
    }
    return simple_animation;
}

