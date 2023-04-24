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

//int draw_animated_img(AnimatedImg_t *anim, int x, int y,uint16_t mode,int indexToDraw){
    /*for(int j = 0; j < anim->height; j++){
        for(int i = 0; i < anim->width; i++){
            switch (mode)
            {
            case INDEXED_MODE:
                    if(draw_pixel(x+i, y+j, anim->pics_8[indexToDraw][i+j*anim->width])) return 1;

            case DIRECT_COLOR_1_5_5_5:
                    if(draw_pixel(x+i, y+j, anim->pics_16[indexToDraw][i+j*anim->width])) return 1;
                break;
            case DIRECT_COLOR_8_8_8:
                    if(draw_pixel(x+i, y+j, anim->pics_32[indexToDraw][i+j*anim->width])) return 1;
                break;
            case DIRECT_COLOR_5_6_5:
                    if(draw_pixel(x+i, y+j, anim->pics_16[indexToDraw][i+j*anim->width])) return 1;
                break;
            
            case DIRECT_COLOR_8_8_8_8:
                    if(draw_pixel(x+i, y+j, anim->pics_32[indexToDraw][i+j*anim->width])) return 1;
                break;
            default:
                break;
            }

        }
    }*/
        //if(draw(&anim->images[indexToDraw],x,y,mode)) return 1;

    //return 0;
//}
int draw_small_xpm(xpm_map_t xpm, uint16_t x, uint16_t y, uint16_t mode){
    img_t img = make_img(xpm, x, y, mode);
    if(draw(img, img.x, img.y, mode)) return 1;
    return 0;
}
void init_img(unsigned int x, unsigned int y,unsigned int xSpd,unsigned int ySpd,uint16_t mode){
    //player = make_img((xpm_map_t) mc1_xpm,x,y,mode);
}
void init_anim_img(unsigned int x, unsigned int y, unsigned int speed,uint16_t mode){
    xpm_map_t temp[8] = {(xpm_map_t)mcUp1_xpm, (xpm_map_t)mcUp2_xpm,(xpm_map_t)mcUp3_xpm,(xpm_map_t)mcUp4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)mcUp6_xpm,(xpm_map_t)mcUp7_xpm};
    animated_img= make_animated_img(8,x,y,mode,(xpm_map_t) mcUp1_xpm, temp);
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

    return img;
}

AnimatedImg_t make_animated_img(int no_images,unsigned int x, unsigned int y,uint16_t mode, xpm_map_t curr_xpm, xpm_map_t *images){
    AnimatedImg_t anime_img;
    for(int i=0;i<no_images;i++){
        /*switch(mode){
            case INDEXED_MODE:
            anime_img.pics_8[i] = (uint8_t *) xpm_load(temp, XPM_INDEXED, &xpm_img);
            
            break;
            case DIRECT_COLOR_1_5_5_5:
            anime_img.pics_16[i] = (uint16_t *) xpm_load(temp, XPM_1_5_5_5, &xpm_img);
            
            break;
            case DIRECT_COLOR_5_6_5:
            anime_img->pics_16[i] = (uint16_t *) xpm_load(temp, XPM_5_6_5, &xpm_img);
            
            break;
            case DIRECT_COLOR_8_8_8:
            anime_img->pics_32[i] = (uint32_t *) xpm_load(temp, XPM_5_6_5, &xpm_img);
            
            break;
            case DIRECT_COLOR_8_8_8_8:
            anime_img->pics_32[i] = (uint32_t *) xpm_load(temp, XPM_8_8_8_8, &xpm_img);
            break;

        }*/
        anime_img.images[i] = make_img(images[i],x,y,mode);

    }
    anime_img.img = make_img(curr_xpm, x, y, mode);
    anime_img.no_img = no_images;
    return anime_img;
}

