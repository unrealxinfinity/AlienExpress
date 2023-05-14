#include "view.h"

int is_occupied(img_t img, int distance){
    uint32_t colors_32 = 0;
    switch(img.direction){
        case UP:
            for(int j = 0; j < distance; j++){
                for(int i = img.hitbox_x-3; i <= img.hitbox_x+3; i++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(img.y-(j+1))+ i) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY && img.type != WORKER && img.type != WOLF){
                        if(img.type == BULLET){
                            hit_monster(i, img.y-j-1);
                        }
                        return 1;
                    }
                    else if(colors_32 == PLAYER && (img.type == ENEMY || img.type == WOLF)){
                        player_lives--;
                    }
                    else if(colors_32 == WORKER && img.type == WORKER){
                        return 1;
                    }
                }
            }
            break;
        case LEFT:
            for(int i = 0; i < distance; i++){
                for(int j = img.hitbox_y-3; j <= img.hitbox_y+3; j++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(j)+img.x-(i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY && img.type != WORKER && img.type != WOLF){
                        if(img.type == BULLET){
                            hit_monster(img.x-i-1, j);
                        }
                        return 1;
                    }
                    else if(colors_32 == PLAYER && (img.type == ENEMY || img.type == WOLF)){
                        player_lives--;
                    }
                    else if(colors_32 == WORKER && img.type == WORKER){
                        return 1;
                    }
                }
            }
            break;
        case RIGHT:
            for(int i = 0; i < distance; i++){
                for(int j = img.hitbox_y-3; j <= img.hitbox_y+3; j++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(j)+(img.x+img.width+i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY && img.type != WORKER && img.type != WOLF){
                        if(img.type == BULLET){
                            hit_monster(img.x+img.width+i+1, j);
                        }
                        return 1;
                    }
                    else if(colors_32 == PLAYER && (img.type == ENEMY || img.type == WOLF)){
                        player_lives--;;
                    }
                    else if(colors_32 == WORKER && img.type == WORKER){
                        return 1;
                    }
                }
            }
            break;
        case DOWN:
            for(int j = 0; j < distance; j++){
                for(int i = img.hitbox_x-3; i <= img.hitbox_x+3; i++){
                    memcpy(&colors_32, &frame_buffer[(x_res*(img.y+img.height+j+1)+i) * bytes_per_pixel], bytes_per_pixel);
                    if(colors_32 == ENEMY && img.type != WORKER && img.type != WOLF){
                        if(img.type == BULLET){
                            hit_monster(i, img.y+img.height+j+1);
                        }
                        return 1;
                    }
                    else if(colors_32 == PLAYER && (img.type == ENEMY || img.type == WOLF)){
                        player_lives--;
                    }
                    else if(colors_32 == WORKER && img.type == WORKER){
                        return 1;
                    }
                }
            }
            break;
        default:
            break;
    }
    return 0;
}
int manage_collision(img_t *img, int distance){
    if(img->direction == STILL)return 0;
    uint32_t colors_32 = 0;
    switch(img->direction) {
        case UP:
            if((img->y-distance) < 0){
                if(img->type == BULLET){
                    img->is_dead = true;
                }
                img->y = 0;
                img->hitbox_y = img->y + (img->height/2);
                break;
            }
            for(int j = 0; j < distance; j++){
                for(int i = img->hitbox_x-3; i <= img->hitbox_x+3; i++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(img->y-(j+1))+ i) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) ||  (colors_32 == ENEMY && img->type != WORKER && img->type != GRENADE && img->type != WOLF) || (colors_32 == WORKER && img->type == WORKER)){
                        if(img->type == BULLET){
                            if(colors_32 == ENEMY)hit_monster(i, img->y-j-1);
                            img->is_dead = true;
                        }
                        img->y -= j;
                        img->hitbox_y -= j;
                        return 0;
                    }
                    if(colors_32 == PISTOL_BULLET && img->type == ENEMY && img->type == WOLF){
                        img->is_dead = true;
                        break;
                    }
                }
            }
            img->y -= distance;
            img->hitbox_y -= distance;

            break;
        case LEFT:
            if((img->x-distance) < 0){
                if(img->type == BULLET){
                    img->is_dead = true;
                }
                img->x = 0;
                img->hitbox_x = (img->width/2);
                break;
            }
            for(int i = 0; i < distance; i++){
                for(int j = img->hitbox_y-3; j <= img->hitbox_y+3; j++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(j)+img->x-(i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY && img->type != WORKER && img->type != GRENADE && img->type != WOLF) || (colors_32 == WORKER && img->type == WORKER)){
                        if(img->type == BULLET){
                            if(colors_32 == ENEMY)hit_monster(img->x-i-1, j);
                            img->is_dead = true;
                        }
                        img->x -= i;
                        img->hitbox_x -= i;
                        return 0;
                    }
                    if(colors_32 == PISTOL_BULLET && img->type == ENEMY && img->type == WOLF){
                        img->is_dead = true;
                        break;
                    }
                }
            }
            img->x -= distance;
            img->hitbox_x -= distance;
            break;
        case RIGHT:
            if((img->x+img->width+distance) > x_res){
                if(img->type == BULLET){
                    img->is_dead = true;
                }
                img->x = x_res-img->width;
                img->hitbox_x = img->x+(img->width/2);
                break;
            }
            for(int i = 0; i < distance; i++){
                for(int j = img->hitbox_y-3; j <= img->hitbox_y+3; j++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(j)+(img->x+img->width+i+1)) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY && img->type != WORKER && img->type != GRENADE && img->type != WOLF) || (colors_32 == WORKER && img->type == WORKER)){
                        if(img->type == BULLET){
                            if(colors_32 == ENEMY)hit_monster(img->x+img->width+i+1, j);
                            img->is_dead = true;
                        }
                        img->x += i;
                        img->hitbox_x += i;
                        return 0;
                    }
                    if(colors_32 == PISTOL_BULLET && img->type == ENEMY && img->type == WOLF){
                        img->is_dead = true;
                        break;
                    }
                }
            }
            img->x += distance;
            img->hitbox_x += distance;
            break;
        case DOWN:
            if((img->y + img->height+distance) > y_res){
                if(img->type == BULLET){
                    img->is_dead = true;
                }
                img->y = y_res-img->height;
                img->hitbox_y = img->y + (img->height/2);
                break;
            }
            for(int j = 0; j < distance; j++){
                for(int i = img->hitbox_x-3; i <= img->hitbox_x+3; i++){
                    memcpy(&colors_32, &prev_buffer[(x_res*(img->y+img->height+j+1)+i) * bytes_per_pixel], bytes_per_pixel);
                    if((colors_32 == UNBREAKABLE_WALL) || (colors_32 == ENEMY && img->type != WORKER && img->type != GRENADE && img->type != WOLF) || (colors_32 == WORKER && img->type == WORKER)){
                        if(img->type == BULLET){
                            if(colors_32 == ENEMY)hit_monster(i, img->y+img->height+j+1);
                            img->is_dead = true;
                        }
                        img->y += j;
                        img->hitbox_y += j;
                        return 0;
                    }
                    if(colors_32 == PISTOL_BULLET && img->type == ENEMY && img->type == WOLF){
                        img->is_dead = true;
                        break;
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
void hit_monster(int x, int y){
        for(int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++){
            if(!enemies_lv1[i].is_dead){
                if(((y<=(enemies_lv1[i].y+enemies_lv1[i].height)) && y >= enemies_lv1[i].y) && (x >= enemies_lv1[i].x && x <= (enemies_lv1[i].x+enemies_lv1[i].width))){
                    enemies_lv1[i].is_dead = true;
                    break;
                }
            }
        }
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
        draw_number(number, x, 20, 0);
        x -= 15;
        count++;
    }
    x = 560;
    count = 1;
    while(count < 3){
        number = sec % 10;
        sec = sec / 10;
        draw_number(number, x, 20, 0);
        x-= 15;
        count++;
    }
    return 0;
}
int draw_rtc(){
    int x = 400;
    int seconds = rtc_time[0];
    int size = 2;
    while(size>0){
        int number = seconds % 10;
        seconds = seconds /10;
        draw_number(number, x, 20, 0);
        x-=15;
        size--;
    }
    draw_small_xpm((xpm_map_t)two_dots_xpm, x, 20);
    x-=15;
    int minutes = rtc_time[1];
    size = 2;
    while(size > 0){
        int number = minutes%10;
        minutes = minutes / 10;
        draw_number(number, x, 20, 0);
        x-=15;
        size--;
    }
    draw_small_xpm((xpm_map_t)two_dots_xpm, x, 20);
    x-=15;
    int hour = rtc_time[2] + 1;
    size = 2;
    while(size > 0){
        int number = hour % 10;
        hour = hour/10;
        draw_number(number, x, 20, 0);
        x-=15;
        size--;
    }
    return 0;
}
int draw_number(int number, int x, int y, int type){
    switch(number){
        case 0:
            if(type == 0)draw_small_xpm((xpm_map_t)zero_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)zero_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_zero_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)zero_red_xpm, x, y);
            break;
        case 1:
            if(type == 0)draw_small_xpm((xpm_map_t)one_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)one_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_one_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)one_red_xpm, x, y);
            break;
        case 2:
            if(type == 0)draw_small_xpm((xpm_map_t)two_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)two_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_two_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)two_red_xpm, x, y);
            break;
        case 3:
            if(type == 0)draw_small_xpm((xpm_map_t)three_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)three_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_three_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)three_red_xpm, x, y);
            break;
        case 4:
            if(type == 0)draw_small_xpm((xpm_map_t)four_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)four_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_four_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)four_red_xpm, x, y);
            break;
        case 5:
            if(type == 0)draw_small_xpm((xpm_map_t)five_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)five_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_five_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)five_red_xpm, x, y);
            break;
        case 6:
            if(type == 0)draw_small_xpm((xpm_map_t)six_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)six_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_six_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)six_red_xpm, x, y);
            break;
        case 7:
            if(type == 0)draw_small_xpm((xpm_map_t)seven_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)seven_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_seven_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)seven_red_xpm, x, y);
            break;
        case 8:
            if(type == 0)draw_small_xpm((xpm_map_t)eight_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)eight_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_eight_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)eight_red_xpm, x, y);
            break;
        case 9:
            if(type == 0)draw_small_xpm((xpm_map_t)nine_xpm, x, y);
            if(type == 1)draw_small_xpm((xpm_map_t)nine_selected_xpm, x, y);
            if(type == 2)draw_small_xpm((xpm_map_t)small_nine_xpm, x, y);
            if(type == 4)draw_small_xpm((xpm_map_t)nine_red_xpm, x, y);
            break;
    }
    return 0;
}
int draw_health(){
    if(player_lives < -20)player_lives = -20;
    for(int i = 1; i <= max_health; i++){
        if(i > player_lives){
            draw_line(player.x + i-6, player.y -8, 4, EMPTY_HEALTH);
        }
        else{
            draw_line(player.x + i - 6, player.y -8, 4, HEALTH);
        }
    }
    return 0;
}
int draw_img_number(img_t img, int x, int y){
    int count = img.idle_time;
    if(count == 0){
        draw_number(0, x, y, 2);
    }
    else{
        while(count > 0){
            int number = count % 10;
            count = count/10;
            draw_number(number, x, y, 2);
            x -= 9;
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
int get_item(int index, int rate){
    if(rate < 2 && watch.is_dead && !watch.is_in_inventory){
        get_watch(index);
        return 1;
    }
    else if(rate < 4 && boots.is_dead && !boots.is_in_inventory){
        get_boots(index);
        return 1;
    }
    else if(rate < 6 && backpack.is_dead && !backpack.is_in_inventory){
        get_backpack(index);
        return 1;
    }
    else if(rate < 8 && bone.is_dead && !bone.is_in_inventory){
        get_bone(index);
        return 1;
    }
    else if(rate < 25 && grenade_size){
        get_grenade(index);
        grenade_size--;
        return 1;
    }
    else if(rate < 50 && pistol_size){
        get_pistol(index);
        pistol_size--;
        return 1;
    }
    else if(rate < 40 && food_size){
        get_pizza(index);
        food_size--;
        return 1;
    }
    else if(rate < 70 && ammo_size){
        get_ammo(index);
        ammo_size--;
        return 1;
    }
    if(ammo_size){
        get_ammo(index);
        ammo_size--;
        return 1;
    }
    if(food_size){
        get_pizza(index);
        food_size--;
        return 1;
    }
    if(pistol_size){
        get_pistol(index);
        pistol_size--;
        return 1;
    }
    if(grenade_size){
        get_grenade(index);
        grenade_size--;
        return 1;
    }
    if(bone.is_dead && !bone.is_in_inventory){
        get_bone(index);
        return 1;
    }
    if(backpack.is_dead && !backpack.is_in_inventory){
        get_backpack(index);
        return 1;
    }
    if(boots.is_dead && !boots.is_in_inventory){
        get_boots(index);
        return 1;
    }
    if(watch.is_dead && !watch.is_in_inventory){
        get_watch(index);
        return 1;
    }
    return 0;
}
void get_pistol(int index){
    for(int z = 0; z < (int) (sizeof(pistols) / sizeof(pistols[0])); z++){
        if(!pistols[z].is_in_inventory && pistols[z].is_dead){
            pistols[z].is_in_inventory = true;
            pistols[z].is_dead = false;
            pistols[z].idle_time = 0;
            pistols[z].type = PISTOL;
            inventory[index].colors_32 = pistols[z].colors_32;
            inventory[index].width = pistols[z].width;
            inventory[index].height = pistols[z].height;
            inventory[index].type = PISTOL;
            inventory[index].idle_time = 0;
            break;
        }
    }
}
void get_ammo(int index){
    for(int z = 0; z < (int) (sizeof(ammo) / sizeof(ammo[0])); z++){
        if(!ammo[z].is_in_inventory && ammo[z].is_dead){
            ammo[z].is_in_inventory = true;
            ammo[z].is_dead = false;
            ammo[z].idle_time = 8;
            ammo[z].type = AMMO;
            inventory[index].colors_32 = ammo[z].colors_32;
            inventory[index].width = ammo[z].width;
            inventory[index].height = ammo[z].height;
            inventory[index].type = AMMO;
            inventory[index].idle_time = 8;
            break;
        }
    }
}
void get_pizza(int index){
    for(int z = 0; z < (int) (sizeof(pizza) / sizeof(pizza[0])); z++){
        if(!pizza[z].is_in_inventory && pizza[z].is_dead){
            pizza[z].is_in_inventory = true;
            pizza[z].is_dead = false;
            pizza[z].idle_time = 20;
            pizza[z].type = PIZZA;
            inventory[index].colors_32 = pizza[z].colors_32;
            inventory[index].width = pizza[z].width;
            inventory[index].height = pizza[z].height;
            inventory[index].type = PIZZA;
            inventory[index].idle_time = 20;
            break;
        }
    }
}
void get_watch(int index){
    watch.is_dead = false;
    watch.is_in_inventory = true;
    inventory[index].colors_32 = watch.colors_32;
    inventory[index].width = watch.width;
    inventory[index].height = watch.height;
    inventory[index].type = WATCH;
    watch.type = WATCH;
}
void get_boots(int index){
    boots.is_dead = false;
    boots.is_in_inventory = true;
    inventory[index].colors_32 = boots.colors_32;
    inventory[index].width = boots.width;
    inventory[index].height = boots.height;
    inventory[index].type = BOOTS;
    boots.type = BOOTS;
}
void get_backpack(int index){
    backpack.is_dead = false;
    backpack.is_in_inventory = true;
    inventory[index].colors_32 = backpack.colors_32;
    inventory[index].width = backpack.width;
    inventory[index].height = backpack.height;
    inventory[index].type = BACKPACK;
    backpack.type = BACKPACK;
}
void get_bone(int index){
    bone.is_dead = false;
    bone.is_in_inventory = true;
    bone.type = BONE;
    inventory[index].colors_32 = bone.colors_32;
    inventory[index].width = bone.width;
    inventory[index].height = bone.height;
    inventory[index].type = BONE;
}
void get_grenade(int index){
    for(int z = 0; z < (int) (sizeof(grenades) / sizeof(grenades[0])); z++){
        if(!grenades[z].is_in_inventory && grenades[z].is_dead){
            grenades[z].is_in_inventory = true;
            grenades[z].is_dead = false;
            grenades[z].idle_time = 3;
            grenades[z].direction = STILL;
            inventory[index].colors_32 = grenades[z].colors_32;
            inventory[index].width = grenades[z].width;
            inventory[index].height = grenades[z].height;
            inventory[index].type = GRENADE;
            inventory[index].idle_time = 0;
            break;
        }
    }
}
void init_monsters(){
    for (int i =0; i<150; i++) {
        enemies_lv1[i] = make_img((xpm_map_t) enemy3_xpm,0+i, 0+i);
        enemies_lv1[i].direction = RIGHT;
        enemies_lv1[i].type = ENEMY;
    }
    xpm_map_t down1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t left1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t right1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    xpm_map_t up1[8] = {(xpm_map_t)enemy1_xpm, (xpm_map_t)enemy2_xpm,(xpm_map_t)enemy3_xpm,(xpm_map_t)enemy4_xpm,(xpm_map_t)enemy5_xpm,(xpm_map_t)enemy6_xpm,(xpm_map_t)enemy7_xpm, (xpm_map_t)enemy8_xpm};
    animated_img_enemy1 = make_animated_img(8, 2, up1, left1, right1, down1);
    for(int i = 0; i<5; i++){
        workers[i] = make_img((xpm_map_t)idle2_xpm, 0+i, 0+i);
        workers[i].direction = RIGHT;
        workers[i].type = WORKER;
    }
    xpm_map_t down[8] = {(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm,(xpm_map_t)right2_xpm,(xpm_map_t)right3_xpm,(xpm_map_t)right4_xpm,(xpm_map_t)right5_xpm,(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm};
    xpm_map_t left[8] = {(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm,(xpm_map_t)right2_xpm,(xpm_map_t)right3_xpm,(xpm_map_t)right4_xpm,(xpm_map_t)right5_xpm,(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm};
    xpm_map_t right[8] = {(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm,(xpm_map_t)right2_xpm,(xpm_map_t)right3_xpm,(xpm_map_t)right4_xpm,(xpm_map_t)right5_xpm,(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm};
    xpm_map_t up[8] = {(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm,(xpm_map_t)right2_xpm,(xpm_map_t)right3_xpm,(xpm_map_t)right4_xpm,(xpm_map_t)right5_xpm,(xpm_map_t)idle2_xpm, (xpm_map_t)right1_xpm};
    animated_img_workers = make_animated_img(8, 5, up, left, right, down);
    
    wolf = make_img((xpm_map_t)healing32_xpm, 0, 0);
    wolf.direction = RIGHT;
    wolf.type = WOLF;
}
void init_packages(){
    for (int i =0; i<6; i++) {
        packages[i] = make_img((xpm_map_t)small_box_xpm, 0, 0);
        packages[i].type = PACKAGE;
    }
}
void init_teleports(){
    for (int i =0; i<3; i++) {
        teleports[i] = make_img((xpm_map_t)teleport_xpm, 0, 0);
    }
}
void init_inventory(){
     for(int j = 0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            inventory[j*3+i] = make_img((xpm_map_t)small_box_xpm, 10+(i*36), 10+(j*36));
            inventory[j*3+i].type = PACKAGE;
        }
    }
    for(int i = 0; i < 3; i++){
        equipment[i] = make_img((xpm_map_t)small_box_xpm, 166, 5+(i*36));
        equipment[i].type = PACKAGE;
    }


    selected = make_img((xpm_map_t)selected_xpm, 0, 0);
}
void init_guns(){
    for(int i = 0; i < 3; i++){
        pistols[i] = make_img((xpm_map_t)pistol32_xpm, 0, 0);
        pistols[i].type = PISTOL;
        ammo[i] = make_img((xpm_map_t)bullet32_xpm, 0, 0);
        ammo[i].type = AMMO;
        ammo[i].idle_time = 8;
        pizza[i] = make_img((xpm_map_t)pizza32_xpm, 0, 0);
        pizza[i].type = PIZZA;
        pizza[i].idle_time = 20;
        grenades[i] = make_img((xpm_map_t)healing32_xpm, 0, 0);
        grenades[i].type = GRENADE;
        grenades[i].idle_time = 0;
        grenades[i].direction = STILL;
    }
}
void init_bullets(){
    for(int i = 0; i < 50; i++){
        bullets[i] = make_img((xpm_map_t)shoot2_xpm, 0, 0);
        bullets[i].type = BULLET;
    }
}
void initialize_game(){
    inventory_size = 1;
    init_monsters();
    init_packages();
    init_teleports();
    init_inventory();
    init_inventory();
    init_guns();
    init_bullets();
    watch = make_img((xpm_map_t)clock32_xpm, 0, 0);
    boots = make_img((xpm_map_t)speedBoots_xpm, 0, 0);
    backpack = make_img((xpm_map_t)healing32_xpm, 0, 0);
    bone = make_img((xpm_map_t)dmgBoost_xpm, 0, 0);
}
void init_img(){
    seconds = 0;
    minutes = 0;
    score = 0;
    counter_timer = 0;
    inventory_size = 1;
    ammo_size = 3;
    pistol_size = 1;
    food_size = 3;
    max_health = 40;
    grenade_size = 3;
    //player
    player = make_img((xpm_map_t) mc1_xpm,214,100);
    player.prev_direction = RIGHT;
    player_lives = max_health;
    player.idle_time = 1;
    count = 0;

}
void eliminate_entities(){
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++){
        if(!enemies_lv1[i].is_dead){
            enemies_lv1[i].is_dead = true;
        }
    }
    for(int i = 0; i < (int) (sizeof(workers) / sizeof(workers[0])); i++){
        if(!workers[i].is_dead){
            workers[i].is_dead = true;
        }
    }

    wolf.is_dead = true;
    wolf.is_in_inventory = false;

    for(int i = 0; i < (int) (sizeof(teleports) / sizeof(teleports[0])); i++){
        teleports[i].is_dead = true;
        teleports[i].is_in_inventory = false;
    }
    for(int i = 0; i < (int) (sizeof(packages) / sizeof(packages[0])); i++){
        packages[i].is_dead = true;
        packages[i].is_in_inventory = false;
    }
    for(int i = 0; i < 9; i++){
        inventory[i].is_in_inventory = false;
        inventory[i].is_dead = true;
    }
    for(int i = 0; i < (int) (sizeof(pistols) / sizeof(pistols[0])); i++){
        pistols[i].is_dead = true;
        pistols[i].is_in_inventory = false;
        ammo[i].is_dead = true;
        ammo[i].is_in_inventory = false;
        pizza[i].is_dead = true;
        pizza[i].is_in_inventory = false;
        grenades[i].is_dead = true;
        grenades[i].is_in_inventory = false;
    }
    for(int i = 0; i < (int) (sizeof(bullets) / sizeof(bullets[0])); i++){
        bullets[i].is_dead = true;
        bullets[i].is_in_inventory = false;
    }
    for(int i = 0; i < (int) (sizeof(equipment) / sizeof(equipment[0])); i++){
        equipment[i].is_dead = true;
        equipment[i].is_in_inventory = false;
    }
    watch.is_dead = true;
    watch.is_in_inventory = false;
    boots.is_dead = true;
    boots.is_in_inventory = false;
    backpack.is_dead = true;
    backpack.is_in_inventory = false;
    bone.is_dead = true;
    bone.is_in_inventory = false;
}
void init_mouse(){
    mouse_hover = false;
    mouse_click = false;
    mouse_x = -20;
    mouse_y = -20;
    mouse = make_img((xpm_map_t)mouse_normal_xpm, mouse_x, mouse_y);  
    xpm_map_t mouse_movement[2] = {(xpm_map_t)mouse_normal_xpm, (xpm_map_t)mouse_selected_xpm};
    mouse_animation = make_simple_animation(2, mouse_movement);  
}
void init_anim_img(){
    //player
    xpm_map_t up_pistol[8] = {(xpm_map_t)mcUp1_xpm, (xpm_map_t)mcUp2_xpm,(xpm_map_t)mcUp3_xpm,(xpm_map_t)mcUp4_xpm,(xpm_map_t)mcUp5_xpm,(xpm_map_t)mcUp6_xpm,(xpm_map_t)mcUp7_xpm, (xpm_map_t)mcUp8_xpm};
    xpm_map_t left_pistol[8] = {(xpm_map_t)mcLeft1_xpm, (xpm_map_t)mcLeft2_xpm,(xpm_map_t)mcLeft3_xpm,(xpm_map_t)mcLeft4_xpm,(xpm_map_t)mcLeft5_xpm,(xpm_map_t)mcLeft6_xpm,(xpm_map_t)mcLeft7_xpm, (xpm_map_t)mcLeft8_xpm};
    xpm_map_t right_pistol[8] = {(xpm_map_t)mcRight1_xpm, (xpm_map_t)mcRight2_xpm,(xpm_map_t)mcRight3_xpm,(xpm_map_t)mcRight4_xpm,(xpm_map_t)mcRight5_xpm,(xpm_map_t)mcRight6_xpm,(xpm_map_t)mcRight7_xpm, (xpm_map_t)mcRight8_xpm};
    xpm_map_t down_pistol[8] = {(xpm_map_t)mcDown1_xpm, (xpm_map_t)mcDown2_xpm,(xpm_map_t)mcDown3_xpm,(xpm_map_t)mcDown4_xpm,(xpm_map_t)mcDown5_xpm,(xpm_map_t)mcDown6_xpm,(xpm_map_t)mcDown7_xpm, (xpm_map_t)mcDown8_xpm};

    xpm_map_t up[8] = {(xpm_map_t)mcUpPistol1_xpm, (xpm_map_t)mcUpPistol2_xpm,(xpm_map_t)mcUpPistol3_xpm,(xpm_map_t)mcUpPistol4_xpm,(xpm_map_t)mcUpPistol5_xpm,(xpm_map_t)mcUpPistol6_xpm,(xpm_map_t)mcUpPistol7_xpm, (xpm_map_t)mcUpPistol8_xpm};
    xpm_map_t right[8] = {(xpm_map_t)mcRightPistol1_xpm, (xpm_map_t)mcRightPistol2_xpm,(xpm_map_t)mcRightPistol3_xpm,(xpm_map_t)mcRightPistol4_xpm,(xpm_map_t)mcRightPistol5_xpm,(xpm_map_t)mcRightPistol6_xpm,(xpm_map_t)mcRightPistol7_xpm, (xpm_map_t)mcRightPistol8_xpm};
    xpm_map_t left[8] = {(xpm_map_t)mcLeftPistol1_xpm, (xpm_map_t)mcLeftPistol2_xpm,(xpm_map_t)mcLeftPistol3_xpm,(xpm_map_t)mcLeftPistol4_xpm,(xpm_map_t)mcLeftPistol5_xpm,(xpm_map_t)mcLeftPistol6_xpm,(xpm_map_t)mcLeftPistol7_xpm, (xpm_map_t)mcLeftPistol8_xpm};
    xpm_map_t down[8] = {(xpm_map_t)mcDownPistol1_xpm, (xpm_map_t)mcDownPistol2_xpm,(xpm_map_t)mcDownPistol3_xpm,(xpm_map_t)mcDownPistol4_xpm,(xpm_map_t)mcDownPistol5_xpm,(xpm_map_t)mcDownPistol6_xpm,(xpm_map_t)mcDownPistol7_xpm, (xpm_map_t)mcDownPistol8_xpm};
    animated_img_player_pistol= make_animated_img(8, 4, up_pistol, left_pistol, right_pistol, down_pistol);
    animated_img_player_bear_hands= make_animated_img(8, 4, up, left, right, down);
    animated_img_player = animated_img_player_bear_hands;
    
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
        img.idle_time = 0;

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

