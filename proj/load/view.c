#include "view.h"


int draw(img_t img, int x, int y,uint16_t mode){
    for(int j = 0; j < img.height; j++){
        for(int i = 0; i < img.width; i++){
            int index = j*img.width + i;
            switch (mode)
            {
            case INDEXED_MODE:
                    if(draw_pixel(x+i, y+j, img.colors_8[index])) return 1;

            case DIRECT_COLOR_1_5_5_5:
                    if(draw_pixel(x+i, y+j, img.colors_16[index])) return 1;
                break;
            case DIRECT_COLOR_8_8_8:
                    if(draw_pixel(x+i, y+j, img.colors_32[index])) return 1;
                break;
            case DIRECT_COLOR_5_6_5:
                    if(draw_pixel(x+i, y+j, img.colors_16[index])) return 1;
                break;
            
            case DIRECT_COLOR_8_8_8_8:
                    if(draw_pixel(x+i, y+j, img.colors_32[index])) return 1;
                break;
            default:
                break;
            }
        }
    }
    return 0;
}

int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y, uint16_t mode){
    img_t img = make_img(xpm, x, y, mode);
    if(draw(img, img.x, img.y, mode)) return 1;
    return 0;
}
void init_img(unsigned int x, unsigned int y,unsigned int xSpd,unsigned int ySpd,uint16_t mode){
    player = make_img((xpm_map_t) mc1_xpm,x,y,mode);
    player.prev_direction = RIGHT;
}
void init_anim_img(unsigned int x, unsigned int y, unsigned int speed,uint16_t mode){
    xpm_map_t up[8] = {(xpm_map_t)mcUp1_xpm, (xpm_map_t)mcUp2_xpm,(xpm_map_t)mcUp3_xpm,(xpm_map_t)mcUp4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)mcUp6_xpm,(xpm_map_t)mcUp7_xpm, (xpm_map_t)mcUp8_xpm};
    xpm_map_t left[8] = {(xpm_map_t)mcLeft1_xpm, (xpm_map_t)mcLeft2_xpm,(xpm_map_t)mcLeft3_xpm,(xpm_map_t)mcLeft4_xpm,(xpm_map_t)mcLeft5_xpm,(xpm_map_t)mcLeft6_xpm,(xpm_map_t)mcLeft7_xpm, (xpm_map_t)mcLeft8_xpm};
    xpm_map_t right[8] = {(xpm_map_t)mcRight1_xpm, (xpm_map_t)mcRight2_xpm,(xpm_map_t)mcRight3_xpm,(xpm_map_t)mcRight4_xpm,(xpm_map_t)mcRight5_xpm,(xpm_map_t)mcRight6_xpm,(xpm_map_t)mcRight7_xpm, (xpm_map_t)mcRight8_xpm};
    xpm_map_t down[8] = {(xpm_map_t)mcDown1_xpm, (xpm_map_t)mcDown2_xpm,(xpm_map_t)mcDown3_xpm,(xpm_map_t)mcDown4_xpm,(xpm_map_t)mcDown5_xpm,(xpm_map_t)mcDown6_xpm,(xpm_map_t)mcDown7_xpm, (xpm_map_t)mcDown8_xpm};
    animated_img_player= make_animated_img(8,x,y,mode, up, left, right, down);
}



img_t make_img(xpm_map_t xpm,unsigned int x, unsigned int y,uint16_t mode){
    xpm_image_t xpm_img;
    img_t img;
    switch(mode){
        case INDEXED_MODE:
        img.colors_8 = (uint8_t *) xpm_load(xpm, XPM_INDEXED, &xpm_img);
        break;
        case DIRECT_COLOR_1_5_5_5:
        img.colors_16 = (uint16_t *) xpm_load(xpm, XPM_1_5_5_5, &xpm_img);
        break;
        case DIRECT_COLOR_5_6_5:
        img.colors_16 = (uint16_t *) xpm_load(xpm, XPM_5_6_5, &xpm_img);
        break;
        case DIRECT_COLOR_8_8_8:
        
        img.colors_32= (uint32_t *)xpm_load(xpm, XPM_8_8_8, &xpm_img);;
        break;
        case DIRECT_COLOR_8_8_8_8:
        img.colors_32 = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &xpm_img);
        break;
    }
    
        img.width = xpm_img.width;
        img.height = xpm_img.height;
        img.x = x;
        img.y = y;
        img.no_img = 0;
        img.direction = STILL;

    return img;
}

AnimatedImg_t make_animated_img(int no_images,unsigned int x, unsigned int y,uint16_t mode, xpm_map_t *up, xpm_map_t *left, xpm_map_t *right, xpm_map_t *down){
    AnimatedImg_t anime_img;
    for(int i=0;i<no_images;i++){
        anime_img.up[i] = make_img(up[i],x,y,mode);
        anime_img.left[i] = make_img(left[i],x,y,mode);
        anime_img.right[i] = make_img(right[i],x,y,mode);
        anime_img.down[i] = make_img(down[i],x,y,mode);

    }
    return anime_img;
}

