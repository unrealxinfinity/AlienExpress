#include "view.h"

int manage_collision(img_t draw_img,img_t *img){
    if(img->direction == STILL)return 0;
    uint32_t colors_32 = 0;
    switch(img->direction) {
        case UP:
            for(int i = 0; i < draw_img.width; i++){
                for(int j = draw_img.height; j > 0; j--){
                    int index = j*draw_img.width + i;
                    if(draw_img.colors_32[index] == 0xfffffe)continue;
                    memcpy(&colors_32, &frame_buffer[(x_res*(img->y+j)+img->x+i) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == 0x000000){
                        img->y += j+1;
                        return 0;
                    }
                }
            }
            break;
        case LEFT:
            while(colors_32 == 0xB2B2B2){
                img->hitbox_x += 1;
                img->x += 1;
                memcpy(&colors_32, &frame_buffer[(x_res*img->hitbox_y+img->hitbox_x) * bytes_per_pixel], bytes_per_pixel);
            }
            break;
        case RIGHT:
            while(colors_32 == 0xB2B2B2){
                img->hitbox_x -= 1;
                img->x -= 1;
                memcpy(&colors_32, &frame_buffer[(x_res*img->hitbox_y+img->hitbox_x) * bytes_per_pixel], bytes_per_pixel);
            }
            break;
        case DOWN:
            while(colors_32 == 0xB2B2B2){
                img->hitbox_y -= 1;
                img->y -= 1;
                memcpy(&colors_32, &frame_buffer[(x_res*img->hitbox_y+img->hitbox_x) * bytes_per_pixel], bytes_per_pixel);
            }
            break;
        default:
            break;
    }
    return 0;
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
            if(draw(img,img))return 1;
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
        if(draw(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerXAxis;i++){
        img.x = i*img.width;
        img.y = 0;
        if(draw(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerYAxis;i++){
        img.x = (x_res-img.width);
        img.y = i*img.height;
        if(draw(img,img)) return 1;
    }
    for(int i=0 ; i<tilesXY.tilesPerXAxis;i++){
        img.x = img.width*i;
        img.y = y_res - img.height;
        if(draw(img,img)) return 1;
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

void init_img(){
    //player
    player = make_img((xpm_map_t) mc1_xpm,214,100);
    player.prev_direction = RIGHT;
    //enemies
    for (int i =0; i<5; i++) {
        enemies_lv1[i] = make_img((xpm_map_t) enemy1_xpm,100*(i+1),100*(i+1));
    }
    //mouse
    mouse_x = 5;
    mouse_y = 5;
    mouse_hover = false;
    mouse = make_img((xpm_map_t)mouse_normal_xpm, mouse_x, mouse_y);

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
    xpm_map_t up1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    animated_img_enemy1 = make_animated_img(8, 10, up1, left1, right1, down1);
}
void init_simple_animation(){
    xpm_map_t mouse_movement[2] = {(xpm_map_t)mouse_normal_xpm, (xpm_map_t)mouse_selected_xpm};
    mouse_animation = make_simple_animation(2, mouse_movement);
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

