#include "view.h"


int draw(img_t img, int x, int y){
    for(int j = 0; j < img.height; j++){
        for(int i = 0; i < img.width; i++){
            int index = j*img.width + i;
                    if(draw_pixel(x+i, y+j, img.colors_32[index])) return 1;
        }
    }
    return 0;
}

int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y){
    img_t img = make_img(xpm, x, y);
    if(draw(img, img.x, img.y)) return 1;
    return 0;
}
int drawTiles(){
    tilesPerAxis tilesXY;
    xpm_map_t image=(xpm_map_t) ground_xpm;
    img_t img = make_img(image,0,0);
    tilesXY.tilesPerXAxis=x_res/img.width;
    tilesXY.tilesPerYAxis=y_res/img.height;
   for(int i=0 ; i<tilesXY.tilesPerYAxis;i++){
        for(int j=0; j<tilesXY.tilesPerXAxis;j++){
            if(draw(img,j*img.width,i*img.height))return 1;
        }
    }
    return 0;
}


void init_img(unsigned int x, unsigned int y){
    player = make_img((xpm_map_t) mc1_xpm,x,y);
    player.prev_direction = RIGHT;

    mouse_normal = make_img((xpm_map_t)mouse_normal_xpm, mouse_x, mouse_y, mode);
}
void init_anim_img(unsigned int x, unsigned int y){
    xpm_map_t up[8] = {(xpm_map_t)mcUp1_xpm, (xpm_map_t)mcUp2_xpm,(xpm_map_t)mcUp3_xpm,(xpm_map_t)mcUp4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)mcUp6_xpm,(xpm_map_t)mcUp7_xpm, (xpm_map_t)mcUp8_xpm};
    xpm_map_t left[8] = {(xpm_map_t)mcLeft1_xpm, (xpm_map_t)mcLeft2_xpm,(xpm_map_t)mcLeft3_xpm,(xpm_map_t)mcLeft4_xpm,(xpm_map_t)mcLeft5_xpm,(xpm_map_t)mcLeft6_xpm,(xpm_map_t)mcLeft7_xpm, (xpm_map_t)mcLeft8_xpm};
    xpm_map_t right[8] = {(xpm_map_t)mcRight1_xpm, (xpm_map_t)mcRight2_xpm,(xpm_map_t)mcRight3_xpm,(xpm_map_t)mcRight4_xpm,(xpm_map_t)mcRight5_xpm,(xpm_map_t)mcRight6_xpm,(xpm_map_t)mcRight7_xpm, (xpm_map_t)mcRight8_xpm};
    xpm_map_t down[8] = {(xpm_map_t)mcDown1_xpm, (xpm_map_t)mcDown2_xpm,(xpm_map_t)mcDown3_xpm,(xpm_map_t)mcDown4_xpm,(xpm_map_t)mcDown5_xpm,(xpm_map_t)mcDown6_xpm,(xpm_map_t)mcDown7_xpm, (xpm_map_t)mcDown8_xpm};
    animated_img_player= make_animated_img(8,x,y, up, left, right, down);
}



img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y){
    xpm_image_t xpm_img;
    img_t img;
    
        img.colors_32 = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &xpm_img);
        img.width = xpm_img.width;
        img.height = xpm_img.height;
        img.x = x;
        img.y = y;
        img.no_img = 0;
        img.direction = STILL;

    return img;
}

AnimatedImg_t make_animated_img(int no_images,unsigned int x, unsigned int y, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down){
    AnimatedImg_t anime_img;
    for(int i=0;i<no_images;i++){
        anime_img.up[i] = make_img(up[i],x,y);
        anime_img.left[i] = make_img(left[i],x,y);
        anime_img.right[i] = make_img(right[i],x,y);
        anime_img.down[i] = make_img(down[i],x,y);

    }
    return anime_img;
}

