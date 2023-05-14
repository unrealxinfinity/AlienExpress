#include "level.h"
#include <math.h>


movement_t move[4]={STILL,STILL,STILL,STILL};
int res = 0;
int current_index = -1;
int reached = 0;
bool is_holding_i = false;
int throwing_index = -5;

void reset_movement(){
    for(int i = 0; i<4; i++){
        move[i] = STILL;
    }
}

action_t keyboard_ih_level(uint32_t scancode){
    if(scancode == MAKE_ESC){
        return EXIT;
    }
    if(scancode == MAKE_W)move[0] = UP;
    if(scancode == MAKE_D)move[1] = RIGHT;
    if(scancode == MAKE_A)move[2] = LEFT;
    if(scancode == MAKE_S)move[3] = DOWN;
    if(scancode == MAKE_L){
        if(current_index != -1){
            if(inventory[current_index].type == PISTOL && inventory[current_index].is_in_inventory && inventory[current_index].idle_time > 0){
                spawn_bullet(current_index);
            }
        }
        kill_workers();
    }
    if(scancode == MAKE_I && current_index != -1){
        open_package(current_index);
        is_holding_i = true;

    }
    if(scancode == B(MAKE_I)){
        is_holding_i = false;
    }
    if(scancode == MAKE_P){
        remove_package(player);
        remove_guns(player);
    }
    if(scancode == MAKE_O){
        if(current_index != -1)remove_from_inventory(current_index);
    }
    if(scancode == MAKE_1){
        selected.is_dead = false;
        selected.x = inventory[0].x-4;
        selected.y = inventory[0].y -4;
        selected.hitbox_x = inventory[0].hitbox_x-4;
        selected.hitbox_y = inventory[0].hitbox_y-4;
        current_index = 0;
    }
    if(scancode == MAKE_2){
        selected.is_dead = false;
        selected.x = inventory[1].x-4;
        selected.y = inventory[1].y-4;
        selected.hitbox_x = inventory[1].hitbox_x-4;
        selected.hitbox_y = inventory[1].hitbox_y-4;
        current_index = 1;
    }
    if(scancode == MAKE_3){
        selected.is_dead = false;
        selected.x = inventory[2].x-4;
        selected.y = inventory[2].y-4;
        selected.hitbox_x = inventory[2].hitbox_x-4;
        selected.hitbox_y = inventory[2].hitbox_y-4;
        current_index = 2;
    }
    if(current_index != -1){
        int speed = animated_img_player.speed;
        if(inventory[current_index].type == PISTOL && inventory[current_index].is_in_inventory){
            animated_img_player = animated_img_player_pistol;
        }
        else{
            animated_img_player = animated_img_player_bear_hands;
        }
        animated_img_player.speed = speed;
    }
    if(scancode == B(MAKE_W))move[0] = STILL;
    if(scancode == B(MAKE_D))move[1] = STILL;
    if(scancode == B(MAKE_A))move[2] = STILL;
    if(scancode == B(MAKE_S))move[3] = STILL;
    return AFK;
}
action_t mouse_ih_level(){
    for(int i = 0; i < (inventory_size*3); i++){
            if(mouse_position(inventory[i].x, inventory[i].y, inventory[i].x+inventory[i].width, inventory[i].y+inventory[i].height)){
                if(mouse_packet.lb && !mouse_click){
                    mouse_index = i;
                    mouse_click = true;
                }
                if(!mouse_packet.lb && mouse_click){
                    mouse_click = false;
                    img_t temp = inventory[mouse_index];
                    inventory[mouse_index].colors_32 = inventory[i].colors_32;
                    inventory[mouse_index].is_in_inventory = inventory[i].is_in_inventory;
                    inventory[mouse_index].type = inventory[i].type;
                    inventory[mouse_index].width = inventory[i].width;
                    inventory[mouse_index].height = inventory[i].height;
                    inventory[mouse_index].idle_time = inventory[i].idle_time;

                    inventory[i].colors_32 = temp.colors_32;
                    inventory[i].is_in_inventory = temp.is_in_inventory;
                    inventory[i].type = temp.type;
                    inventory[i].width = temp.width;
                    inventory[i].height = temp.height;
                    inventory[i].idle_time = temp.idle_time;
                    mouse_index = -1;
                }
                if(mouse_packet.rb){
                    mouse_click = false;
                    remove_from_inventory(i);
                    mouse_index = -1;
                }
                if(mouse_packet.mb && inventory[i].is_in_inventory){
                    mouse_click = false;
                    mouse_index = -1;
                    open_package(i);
                }
            }
    }
    for(int i = 0; i < 3; i++){
        if(mouse_position(equipment[i].x, equipment[i].y, equipment[i].x+equipment[i].width, equipment[i].y+equipment[i].height)){
            if(mouse_packet.rb){
                mouse_click = false;
                remove_from_equipment(i);
                mouse_index = -1;
            }
        }
    }
    if(!mouse_packet.lb && mouse_click){
        remove_from_inventory(mouse_index);
        mouse_index = -1;
        mouse_click = false;
    }
    return AFK;
}
void open_package(int index){
    if(inventory[index].type == PACKAGE && inventory[index].is_in_inventory){
        int rate = rand()%70;
        if(get_item(index, rate)){
            animated_img_player.speed += 1;
            for(int i = 0; i < (int) (sizeof(packages) / sizeof(packages[0])); i++){
                if(packages[i].is_in_inventory){
                    packages[i].is_in_inventory = false;
                    packages[i].is_dead = true;
                    packages[i].idle_time = inventory[index].idle_time;
                    break;
            }
        }
        }
    }
    else if(inventory[index].type == PISTOL && inventory[index].is_in_inventory){
        if(inventory[index].idle_time < 40){
            for(int i = 0; i < inventory_size*3; i++){
                if(inventory[i].type == AMMO && inventory[i].is_in_inventory){
                    int ammo_count = inventory[index].idle_time;
                    ammo_count += inventory[i].idle_time;
                    if(ammo_count > 40){
                        inventory[i].idle_time = ammo_count-40;
                        inventory[index].idle_time = 40;
                    }
                    else{
                        inventory[index].idle_time += inventory[i].idle_time;
                        inventory[i].is_dead = true;
                        inventory[i].is_in_inventory = false;
                        for(int z = 0; z < (int) (sizeof(ammo) / sizeof(ammo[0])); z++){
                            if(ammo[z].is_in_inventory && !ammo[z].is_dead){
                                ammo[z].is_dead = true;
                                ammo[z].is_in_inventory = false;
                                ammo_size++;
                                break;
                            }
                        }
                    }
                    if(inventory[index].idle_time == 40)break;
                }
            }
        }
    }
    else if(inventory[index].type == PIZZA && player_lives <40 && inventory[index].is_in_inventory){
        if(player_lives+inventory[index].idle_time > max_health){
            player_lives = max_health;
        }
        else{
            player_lives += inventory[index].idle_time;
        }
        inventory[index].is_dead = true;
        inventory[index].is_in_inventory = false;
        for(int i = 0; i < (int) (sizeof(pizza) / sizeof(pizza[0])); i++){
            if(pizza[i].is_in_inventory){
                pizza[i].is_in_inventory = false;
                pizza[i].is_dead = true;
                food_size++;
                break;
            }
        }
    }
    else if(inventory[index].type == BOOTS && inventory[index].is_in_inventory){
        if(!equipment[2].is_in_inventory){
            inventory[index].is_in_inventory = false;
            equipment[2].colors_32 = boots.colors_32;
            equipment[2].width = boots.width;
            equipment[2].height = boots.height;
            equipment[2].is_in_inventory = true;
            equipment[2].type = BOOTS;
            equipment[2].idle_time = boots.idle_time;
            animated_img_player.speed += 1;
        }
    }
    else if(inventory[index].type == BACKPACK && inventory[index].is_in_inventory){
        if(!equipment[1].is_in_inventory){
            inventory[index].is_in_inventory = false;
            equipment[1].colors_32 = backpack.colors_32;
            equipment[1].width = backpack.width;
            equipment[1].height = backpack.height;
            equipment[1].is_in_inventory = true;
            equipment[1].type = BACKPACK;
            equipment[1].idle_time = backpack.idle_time;
            inventory_size = 3;
        }
    }
    else if(inventory[index].type == GRENADE && inventory[index].is_in_inventory){
        inventory[index].is_dead = true;
        inventory[index].is_in_inventory = false;
        for(int i = 0; i < (int) (sizeof(grenades) / sizeof(grenades[0])); i++){
            if(grenades[i].is_in_inventory && !grenades[i].is_dead){
                grenades[i].is_in_inventory = true;
                grenades[i].is_dead = true;
                grenades[i].direction = STILL;
                grenades[i].x = player.x;
                grenades[i].y = player.y;
                grenades[i].hitbox_x = grenades[i].x+(grenades[i].width/2);
                grenades[i].hitbox_y = grenades[i].y+(grenades[i].height/2);
                throwing_index = current_index;
                grenade_size++;
                break;
            }
        }
    }
    else if(inventory[index].type == BONE && inventory[index].is_in_inventory){
        inventory[index].is_dead = true;
        inventory[index].is_in_inventory = false;
        if(bone.is_in_inventory && !bone.is_dead){
            bone.is_in_inventory = true;
            bone.is_dead = true;
            bone.direction = STILL;
            bone.x = player.x;
            bone.y = player.y;
            bone.hitbox_x = bone.x+(bone.width/2);
            bone.hitbox_y = bone.y+(bone.height/2);
            throwing_index = current_index;
        }
    }
}
int score_animation(img_t *character, int type){
    int width = 890 - character->x;
    int height = 20 - character->y;

    int distance;
    int final_x;
    int final_y;
    if(abs(width) <= 20 && abs(height) <= 20) {
        if(type == 0){
            score += character->idle_time;
            reached = 20;
        }
        if(type == 1){
            score -= 30;
            reached = -20;
        }
        if(score < 0)score = 0;
        character->is_in_inventory = false;
        return 0;
    }
    else {
        distance = sqrt(width*width + height*height);
        final_x = (width*4)/distance;
        final_y = (height*4)/distance;
    }
    if(final_x > 0){
        character->x += 20;
    }
    else if(final_x < 0)character->x -= 20;

    if(final_y > 0){
        character->y += 20;
    }
    else if(final_y < 0)character->y -= 20;
    if(type == 1){
        character->idle_time = 30;
    }
    draw_img_number(*character, character->x, character->y);
    if(type == 1){
        character->idle_time = 0;
    }
    return 0; 
}
void remove_from_equipment(int index){
    if(equipment[index].type == BOOTS && equipment[index].is_in_inventory){
        equipment[index].is_in_inventory = false;
        boots.is_dead = false;
        boots.is_in_inventory = false;
        boots.x = player.x;
        boots.y = player.y;
        boots.idle_time = equipment[index].idle_time;
        animated_img_player.speed -= 1;
    }
    if(equipment[index].type == BACKPACK && equipment[index].is_in_inventory){
        equipment[index].is_in_inventory = false;
        backpack.is_dead = false;
        backpack.is_in_inventory = false;
        backpack.x = player.x;
        backpack.y = player.y;
        backpack.idle_time = equipment[index].idle_time;
        int count = count_packages();
        while(count > 0){
            animated_img_player.speed += 1;
            count--;
        }
        inventory_size = 1;
    }
}
int count_packages(){
    int count = 0;
    for(int i = 3; i < 9; i++){
        if(inventory[i].type == PACKAGE && inventory[i].is_in_inventory){
            count++;
        }
    }
    return count;
}
void remove_from_inventory(int index){
    if(inventory[index].type == PACKAGE && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        for(int z = 0; z < (int) (sizeof(packages) / sizeof(packages[0])); z++){
            if(packages[z].is_in_inventory){
                packages[z].is_dead = false;
                packages[z].is_in_inventory = false;
                packages[z].y = player.y;
                packages[z].x = player.x;
                packages[z].hitbox_x = packages[z].x+(packages[z].width/2);
                packages[z].hitbox_y = packages[z].y+(packages[z].height/2);
                packages[z].idle_time = inventory[index].idle_time;
                animated_img_player.speed +=1;
                int teleport_index = is_on_teleport(player);
                if(teleport_index != -1){
                    packages[z].is_dead = true;
                    teleports[teleport_index].is_dead = true;
                    teleports[teleport_index].is_in_inventory = true;
                    teleports[teleport_index].idle_time = teleports[teleport_index].idle_time *5;
                    //score += 100;
                }
                break;
            }
        }
    }
    if(inventory[index].type == PISTOL && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        for(int z = 0; z < (int) (sizeof(pistols) / sizeof(pistols[0])); z++){
            if(pistols[z].is_in_inventory){
                pistols[z].is_dead = false;
                pistols[z].is_in_inventory = false;
                pistols[z].y = player.y;
                pistols[z].x = player.x;
                pistols[z].hitbox_x = pistols[z].x+(pistols[z].width/2);
                pistols[z].hitbox_y = pistols[z].y+(pistols[z].height/2);
                pistols[z].idle_time = inventory[index].idle_time;
                break;
            }
        }
    }
    if(inventory[index].type == AMMO && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        for(int z = 0; z < (int) (sizeof(ammo) / sizeof(ammo[0])); z++){
            if(ammo[z].is_in_inventory){
                ammo[z].is_dead = false;
                ammo[z].is_in_inventory = false;
                ammo[z].y = player.y;
                ammo[z].x = player.x;
                ammo[z].hitbox_x = ammo[z].x+(ammo[z].width/2);
                ammo[z].hitbox_y = ammo[z].y+(ammo[z].height/2);
                ammo[z].idle_time = inventory[index].idle_time;
                break;
            }
        }
    }  
    if(inventory[index].type == PIZZA && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        for(int z = 0; z < (int) (sizeof(pizza) / sizeof(pizza[0])); z++){
            if(pizza[z].is_in_inventory){
                pizza[z].is_dead = false;
                pizza[z].is_in_inventory = false;
                pizza[z].y = player.y;
                pizza[z].x = player.x;
                pizza[z].hitbox_x = pizza[z].x+(pizza[z].width/2);
                pizza[z].hitbox_y = pizza[z].y+(pizza[z].height/2);
                pizza[z].idle_time = inventory[index].idle_time;
                break;
            }
        }
    }
    if(inventory[index].type == WATCH && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        watch.is_in_inventory = false;
        watch.is_dead = false;
        watch.x = player.x;
        watch.y = player.y;
        watch.hitbox_x = watch.x+(watch.width/2);
        watch.hitbox_y = watch.y+(watch.height/2);
    }
    if(inventory[index].type == BOOTS && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        boots.is_in_inventory = false;
        boots.is_dead = false;
        boots.x = player.x;
        boots.y = player.y;
        boots.hitbox_x = boots.x+(boots.width/2);
        boots.hitbox_y = watch.y+(watch.height/2);
    }
    if(inventory[index].type == BACKPACK && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        backpack.is_in_inventory = false;
        backpack.is_dead = false;
        backpack.x = player.x;
        backpack.y = player.y;
        backpack.hitbox_x = backpack.x+(backpack.width/2);
        backpack.hitbox_y = backpack.y+(backpack.height/2);
        int count = count_packages();
        while(count > 0){
            animated_img_player.speed += 1;
            count--;
        }
    }
    if(inventory[index].type == GRENADE && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        for(int z = 0; z < (int) (sizeof(grenades) / sizeof(grenades[0])); z++){
            if(grenades[z].is_in_inventory){
                grenades[z].is_dead = false;
                grenades[z].is_in_inventory = false;
                grenades[z].y = player.y;
                grenades[z].x = player.x;
                grenades[z].hitbox_x = grenades[z].x+(grenades[z].width/2);
                grenades[z].hitbox_y = grenades[z].y+(grenades[z].height/2);
                grenades[z].idle_time = inventory[index].idle_time;
                break;
            }
        }
    }
    if(inventory[index].type == BONE && inventory[index].is_in_inventory){
        inventory[index].is_in_inventory = false;
        if(bone.is_in_inventory){
            bone.is_dead = false;
            bone.is_in_inventory = false;
            bone.x = player.x;
            bone.y = player.y;
            bone.hitbox_x = bone.x+(bone.width/2);
            bone.hitbox_y = bone.y+(bone.height/2);
            bone.idle_time = inventory[index].idle_time;
        }
    }
}
int is_on_teleport(img_t character){
    for(int i = 0; i < (int) (sizeof(teleports) / sizeof(teleports[0])); i++){
        if(!teleports[i].is_dead){
            if(manage_hitbox(teleports[i], character)){
                return i;
            }
        }
    }
    return -1;
}
void remove_package(img_t character){
    for(int i = 0; i < (int) (sizeof(packages) / sizeof(packages[0])); i++){
        if(!packages[i].is_dead && !packages[i].is_in_inventory){
            if(manage_hitbox(packages[i], character)){
                int index = is_inventory_full();
                if(index != -1){
                    packages[i].is_in_inventory = true;
                    inventory[index].colors_32 = packages[i].colors_32;
                    inventory[index].width = packages[i].width;
                    inventory[index].height = packages[i].height;
                    inventory[index].is_in_inventory = packages[i].is_in_inventory;
                    inventory[index].type = PACKAGE;
                    if(animated_img_player.speed != 0)animated_img_player.speed -=1;
                    inventory[index].idle_time = packages[i].idle_time;
                }
                
            }
        }
    }
}
void remove_guns(img_t character){
    for(int i = 0; i < (int) (sizeof(pistols) / sizeof(pistols[0])); i++){
        if(!pistols[i].is_dead && !pistols[i].is_in_inventory){
            if(manage_hitbox(pistols[i], character)){
                int index = is_inventory_full();
                if(index != -1){
                    pistols[i].is_in_inventory = true;
                    inventory[index].colors_32 = pistols[i].colors_32;
                    inventory[index].width = pistols[i].width;
                    inventory[index].height = pistols[i].height;
                    inventory[index].is_in_inventory = pistols[i].is_in_inventory;
                    inventory[index].type = PISTOL;
                    inventory[index].idle_time = pistols[i].idle_time;
                }
            }
        }
        if(!ammo[i].is_dead && !ammo[i].is_in_inventory){
            if(manage_hitbox(ammo[i], character)){
                int index = is_inventory_full();
                if(index != -1){
                    ammo[i].is_in_inventory = true;
                    inventory[index].colors_32 = ammo[i].colors_32;
                    inventory[index].width = ammo[i].width;
                    inventory[index].height = ammo[i].height;
                    inventory[index].is_in_inventory = ammo[i].is_in_inventory;
                    inventory[index].type = AMMO;
                    inventory[index].idle_time = ammo[i].idle_time;
                }
            }
        }
        if(!pizza[i].is_dead && !pizza[i].is_in_inventory){
            if(manage_hitbox(pizza[i], character)){
                int index = is_inventory_full();
                if(index != -1){
                    pizza[i].is_in_inventory = true;
                    inventory[index].colors_32 = pizza[i].colors_32;
                    inventory[index].width = pizza[i].width;
                    inventory[index].height = pizza[i].height;
                    inventory[index].is_in_inventory = pizza[i].is_in_inventory;
                    inventory[index].type = PIZZA;
                    inventory[index].idle_time = pizza[i].idle_time;
                }
            }
        }
        if(!grenades[i].is_dead && !grenades[i].is_in_inventory){
            if(manage_hitbox(grenades[i], character)){
                int index = is_inventory_full();
                if(index != -1){
                    grenades[i].is_in_inventory = true;
                    inventory[index].colors_32 = grenades[i].colors_32;
                    inventory[index].width = grenades[i].width;
                    inventory[index].height = grenades[i].height;
                    inventory[index].is_in_inventory = grenades[i].is_in_inventory;
                    inventory[index].type = GRENADE;
                    inventory[index].idle_time = grenades[i].idle_time;
                }
            }
        }
    }
    if(!watch.is_dead && !watch.is_in_inventory){
        if(manage_hitbox(watch, character)){
            int index = is_inventory_full();
            if(index != -1){
                watch.is_in_inventory = true;
                inventory[index].colors_32 = watch.colors_32;
                inventory[index].width = watch.width;
                inventory[index].height = watch.height;
                inventory[index].is_in_inventory = watch.is_in_inventory;
                inventory[index].type = WATCH;
            }
        }
    }
    if(!boots.is_dead && !boots.is_in_inventory){
        if(manage_hitbox(boots, character)){
            int index = is_inventory_full();
            if(index != -1){
                boots.is_in_inventory = true;
                inventory[index].colors_32 = boots.colors_32;
                inventory[index].width = boots.width;
                inventory[index].height = boots.height;
                inventory[index].is_in_inventory = boots.is_in_inventory;
                inventory[index].type = BOOTS;
            }
        }
    }
    if(!backpack.is_dead && !backpack.is_in_inventory){
        if(manage_hitbox(backpack, character)){
            int index = is_inventory_full();
            if(index != -1){
                backpack.is_in_inventory = true;
                inventory[index].colors_32 = backpack.colors_32;
                inventory[index].width = backpack.width;
                inventory[index].height = backpack.height;
                inventory[index].is_in_inventory = backpack.is_in_inventory;
                inventory[index].type = BACKPACK;
                int count = count_packages();
                while(count > 0){
                    if(animated_img_player.speed != 0)animated_img_player.speed -= 1;
                    count--;
                }
            }
        }
    }
    if(!bone.is_dead && !bone.is_in_inventory){
        if(manage_hitbox(bone, character)){
            int index = is_inventory_full();
            if(index != -1){
                bone.is_in_inventory = true;
                inventory[index].colors_32 = bone.colors_32;
                inventory[index].width = bone.width;
                inventory[index].height = bone.height;
                inventory[index].is_in_inventory = bone.is_in_inventory;
                inventory[index].type = BONE;
            }
        }
    }
}

int is_inventory_full(){
    for(int i = 0; i < (inventory_size*3); i++){
        if(inventory[i].is_in_inventory == false){
            return i;
        }
    }
    return -1;
}

void player_hit(){
}

void throw_animation(img_t *item, bool was_throwed){
    if(was_throwed){
        if(item->idle_time <= -3 && item->type == GRENADE){
            item->is_in_inventory = false;
            item->is_dead = true;
            item->direction = STILL;
            int x = item->x-120;
            if(x < 0)x = 0;
            int max_x = item->x + item->width +120;
            if(x > x_res)x=x_res;
            int y = item->y - 120;
            if(y < 0)y = 0;
            int max_y = item->y+item->height+120;
            if(y > y_res)y = y_res;
            kill_monster_radius(x, y, max_x, max_y);
            if((player.hitbox_x <= max_x && player.hitbox_x >= x) && (player.hitbox_y <= max_y && player.hitbox_y >= y)){
                player_lives -= 20;
                if(player_lives <= 0)player_lives = 0;
            }
        }
        else if(item->idle_time > 0){
            manage_collision(item, 10);
            item->idle_time -= 4;
            if(item->idle_time < 0){
                item->idle_time = 0;
            }
        }
        else if(item->type == GRENADE){
            if((counter_timer%30)== 0)item->idle_time -= 1;
        }
        else if(item->type == BONE){
            item->is_in_inventory = false;
            item->is_dead = false;
            if(!wolf.is_dead){
                int width = bone.hitbox_x - wolf.hitbox_x;
                int height = bone.hitbox_y - wolf.hitbox_y;
                int distance = 0;
                if(!(width == 0 && height == 0)){
                    distance = sqrt(width * width + height * height);
                }
                if(distance >= 150){
                    if(catched != 15)catched = 15;
                }
            }
        }
    }
    else{
        if(is_holding_i && throwing_index == current_index){
            if(item->idle_time < 70) item->idle_time += 4;
        }
        else{
            throwing_index = -5;
            item->is_in_inventory = true;
            item->is_dead = true;
            int offset = 3;
            if(player.direction == STILL)item->direction = player.prev_direction;
            else item->direction = player.direction;
            switch(item->direction){
                case UP:
                    item->x = player.x;
                    item->y = player.y-offset*animated_img_player.speed;
                    break;
                case LEFT:
                    item->x = player.x-offset*animated_img_player.speed;
                    item->y = player.y;
                    break;
                case RIGHT:
                    item->x = player.x+player.width+offset*animated_img_player.speed;
                    item->y = player.y;
                    break;
                case DOWN:
                    item->x = player.x;
                    item->y = player.y+player.height+offset*animated_img_player.speed;
                    break;
                default:
                    break;
            }
            item->hitbox_x = item->x +(item->width/2);
            item->hitbox_y = item->y +(item->height/2);
        }
    }
}

void kill_monster_radius(int x, int y, int max_x, int max_y){
    for(int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++){
        if(!enemies_lv1[i].is_dead){
            int enemy_x = enemies_lv1[i].hitbox_x;
            int enemy_y = enemies_lv1[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                enemies_lv1[i].is_dead = true;
                enemies_lv1[i].is_in_inventory = false;
            }
        }

    }
    for(int i = 0; i < (int) (sizeof(workers) / sizeof(workers[0])); i++){
        if(!workers[i].is_dead){
            int enemy_x = workers[i].hitbox_x;
            int enemy_y = workers[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                workers[i].is_dead = true;
                workers[i].is_in_inventory = false;
            }
        }

    }
    for(int i = 0; i < (int) (sizeof(packages) / sizeof(packages[0])); i++){
        if(!packages[i].is_dead && !packages[i].is_in_inventory){
            int enemy_x = packages[i].hitbox_x;
            int enemy_y = packages[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                packages[i].is_dead = true;
                max_health -= 5;
                player_lives -= 5;
                if(player_lives < 0)player_lives = 0;
            }
        }
    }
    for(int i = 0; i < (int) (sizeof(teleports) / sizeof(teleports[0])); i++){
        if(!teleports[i].is_dead && !teleports[i].is_in_inventory){
            int enemy_x = teleports[i].hitbox_x;
            int enemy_y = teleports[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                teleports[i].is_dead = true;
            }
        }
    }
    for(int i = 0; i < (int) (sizeof(pistols) / sizeof(pistols[0])); i++){
        if(!pistols[i].is_dead && !pistols[i].is_in_inventory){
            int enemy_x = pistols[i].hitbox_x;
            int enemy_y = pistols[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                pistols[i].is_dead = true;
            }
        }
        if(!pizza[i].is_dead && !pizza[i].is_in_inventory){
            int enemy_x = pizza[i].hitbox_x;
            int enemy_y = pizza[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                pizza[i].is_dead = true;
            }
        }
        if(!ammo[i].is_dead && !ammo[i].is_in_inventory){
            int enemy_x = ammo[i].hitbox_x;
            int enemy_y = ammo[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                ammo[i].is_dead = true;
            }
        }
        if(!grenades[i].is_dead && !grenades[i].is_in_inventory){
            int enemy_x = grenades[i].hitbox_x;
            int enemy_y = grenades[i].hitbox_y;
            if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
                grenades[i].is_dead = true;
            }
        }
    }
    if(!wolf.is_dead){
        int enemy_x = wolf.hitbox_x;
        int enemy_y = wolf.hitbox_y;
        if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
            wolf.is_dead = true;
        }
    }
    if(!backpack.is_dead && !backpack.is_in_inventory){
        int enemy_x = backpack.hitbox_x;
        int enemy_y = backpack.hitbox_y;
        if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
            backpack.is_dead = true;
        }
    }
    if(!boots.is_dead && !boots.is_in_inventory){
        int enemy_x = boots.hitbox_x;
        int enemy_y = boots.hitbox_y;
        if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
            boots.is_dead = true;
        }
    }
    if(!watch.is_dead && !watch.is_in_inventory){
        int enemy_x = watch.hitbox_x;
        int enemy_y = watch.hitbox_y;
        if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
            watch.is_dead = true;
        }
    }
    if(!bone.is_dead && !bone.is_in_inventory){
        int enemy_x = bone.hitbox_x;
        int enemy_y = bone.hitbox_y;
        if((enemy_x <= max_x && enemy_x >= x) && (enemy_y <= max_y && enemy_y >= y)){
            bone.is_dead = true;
        }
    }
}




void draw_level(){
    draw_teleports();
    //draw_small_xpm((xpm_map_t) unbreakableWalls_xpm, 200, 400);
    draw_packages();
    draw_guns();
    move_workers();
    for(int i = 0; i < 4; i++){
        if(move[i] != STILL){
            res++;
        }
    }
    for(int i = 0; i < 4; i++){
        if(move[i] != STILL){
            player.direction = move[i];
            draw_player();
            count++;
        }
    }
    if(count == 0){
        player.direction = STILL;
        draw_player();
    }
    count = 0;
    res = 0;
    move_wolf();
    move_monsters();
    move_bullets();

    draw_level_words();
    draw_level_numbers();

    draw_health();
    draw_inventory();
    if(!selected.is_dead)draw(selected, selected);
    if(current_index != -1){
        if(inventory[current_index].type == WATCH && inventory[current_index].is_in_inventory){
            draw_rtc();
        }
    }

}




void draw_guns(){
    for(int i = 0; i < (int) (sizeof(pistols) / sizeof(pistols[0])); i++){
        if(!pistols[i].is_dead && !pistols[i].is_in_inventory){
            draw(pistols[i], pistols[i]);
            draw_img_number(pistols[i], pistols[i].x+pistols[i].width-12,pistols[i].y+(pistols[i].height/2));
        }
        if(!ammo[i].is_dead && !ammo[i].is_in_inventory){
            draw(ammo[i], ammo[i]);
            draw_img_number(ammo[i], ammo[i].x+ammo[i].width-12,ammo[i].y+(ammo[i].height/2));
        }
        if(!pizza[i].is_dead && !pizza[i].is_in_inventory){
            draw(pizza[i], pizza[i]);
        }
        if(!grenades[i].is_dead && !grenades[i].is_in_inventory){
            draw(grenades[i], grenades[i]);
        }
        if(grenades[i].is_dead && grenades[i].is_in_inventory && grenades[i].direction == STILL){
            throw_animation(&grenades[i], false);
        }
        if(grenades[i].is_dead && grenades[i].is_in_inventory && grenades[i].direction != STILL){
            draw(grenades[i], grenades[i]);
            throw_animation(&grenades[i], true);
        }
    }
    if(!watch.is_dead && !watch.is_in_inventory){
        draw(watch, watch);
    }
    if(!boots.is_dead && !boots.is_in_inventory){
        draw(boots, boots);
    }
    if(!backpack.is_dead && !backpack.is_in_inventory){
        draw(backpack, backpack);
    }
    if(!bone.is_dead && !bone.is_in_inventory){
        draw(bone, bone);
    }
    if(bone.is_dead && bone.is_in_inventory && bone.direction == STILL){
        throw_animation(&bone, false);
    }
    if(bone.is_dead && bone.is_in_inventory && bone.direction != STILL){
        draw(bone, bone);
        throw_animation(&bone, true);
    } 
}
void draw_teleports(){
    for(int i = 0; i < (int) (sizeof(teleports) / sizeof(teleports[0])); i++){
        if(!teleports[i].is_dead){
            draw(teleports[i], teleports[i]);
            draw_img_number(teleports[i], teleports[i].x+15, teleports[i].y-10);
            if((counter_timer % 30) == 0)teleports[i].idle_time -= 1;
            if(teleports[i].idle_time <= 0){
                teleports[i].is_dead = true;
                teleports[i].is_in_inventory = true;
            }
        }
        if(teleports[i].is_in_inventory && teleports[i].idle_time > 0){
            score_animation(&teleports[i], 0);
        }
        if(teleports[i].is_in_inventory && teleports[i].idle_time <= 0){
            score_animation(&teleports[i], 1);
        }
    }
}
void draw_inventory(){
    int x = 6;
    int y = 6;
    for(int j = 0; j < inventory_size; j++){
        for(int i = 0; i < 3; i++){
            draw_small_xpm((xpm_map_t)inventory_xpm, x+i*36, y+j*36);
            if(inventory[j*3+i].is_in_inventory){
                draw(inventory[j*3+i], inventory[j*3+i]);
                if(inventory[j*3+i].type == AMMO || inventory[j*3+i].type == PISTOL){
                    draw_img_number(inventory[j*3+i], inventory[j*3+i].x+inventory[j*3+i].width-12,inventory[j*3+i].y+(inventory[j*3+i].height/2));
                }
            }
        }
    }
    for(int j = 0; j < 3; j++){
        draw_small_xpm((xpm_map_t)inventory_xpm, 166, 5+(j*36));
        if(equipment[j].is_in_inventory){
            draw(equipment[j], equipment[j]);
        }
    }
}
void draw_packages(){
    for(int i = 0; i < (int) (sizeof(packages) / sizeof(packages[0])); i++){
        if(!packages[i].is_dead && !packages[i].is_in_inventory){
            draw(packages[i], packages[i]);
        }
    }
}
void draw_level_numbers(){
    if(player_lives > 0){
        if((counter_timer % 30) == 0) seconds++;
        if(seconds == 60){
            minutes++;
            seconds = 0;
        }
    }
    draw_timer(seconds, minutes);
}
void draw_level_words(){
    draw_small_xpm((xpm_map_t)s_xpm, 800, 20);
    draw_small_xpm((xpm_map_t)c_xpm, 815, 20);
    draw_small_xpm((xpm_map_t)o_xpm, 830, 20);
    draw_small_xpm((xpm_map_t)r_xpm, 845, 20);
    draw_small_xpm((xpm_map_t)e_xpm, 860, 20);
    draw_small_xpm((xpm_map_t)two_dots_xpm, 875, 20);

    draw_small_xpm((xpm_map_t)two_dots_xpm, 530, 20);
    if(reached > 0){
        draw_score(1);
        reached--;
    }
    else if(reached <0){
        draw_score(4);
        reached++;
    }
    else draw_score(0);

}
void draw_score(int type){
    int score_store = score;
    int size = 0;
    if(score == 0)size = 1;
    while(score_store > 0){
        size++;
        score_store = score_store / 10;
    }
    score_store = score;
    int x = 875;
    while(size > 0){
        int number = score_store % 10;
        draw_number(number, x+(15*size), 20, type);
        score_store = score_store / 10;
        size--;
    }
}
void draw_player(){
    int distance = animated_img_player.speed;
    switch(player.direction){
        case UP:
            if(move[0] == UP && player_lives>0){
                if(count == 0)player.no_img += 1;
                manage_collision(&player, distance);
            }
            player.prev_direction = UP;
            if(res-1==count)draw(animated_img_player.up[player.no_img%8], player);
            break;
        case LEFT:
            if(move[2] == LEFT && player_lives>0){
                if(count==0)player.no_img += 1;
                manage_collision(&player, distance);
            }
            player.prev_direction = LEFT;
            if(res-1==count)draw(animated_img_player.left[player.no_img%8], player);
            break;
        case RIGHT:
            if(move[1] == RIGHT && player_lives>0){
                if(count == 0)player.no_img += 1;
                manage_collision(&player, distance);
            }
            player.prev_direction = RIGHT;
            if(res-1==count)draw(animated_img_player.right[player.no_img%8], player);
            break;
        case DOWN:
            if(move[3] == DOWN && player_lives>0){
                if(count == 0)player.no_img += 1;
                manage_collision(&player, distance);
            }
            player.prev_direction = DOWN;
            if(res-1==count)draw(animated_img_player.down[player.no_img%8], player);
            break;
        case STILL:
            if((player.idle_time % 30) == 0){
                player.no_img = 0;
                player.idle_time = 1;
            }
            else{
                player.idle_time += 1;
            }
            draw_afk_player();
        default:
            break;
    }
}
void draw_afk_player(){
    switch(player.prev_direction){
                case UP:
                    draw(animated_img_player.up[player.no_img%8], player);
                    break;
                case RIGHT:
                    draw(animated_img_player.right[player.no_img%8], player);
                    break;
                case LEFT:
                    draw(animated_img_player.left[player.no_img%8], player);
                    break;
                case DOWN:
                    draw(animated_img_player.down[player.no_img%8], player);
                    break;
                case STILL:
                    draw(animated_img_player.down[player.no_img%8], player);
                    break;
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
void draw_workers(img_t worker){
        switch (worker.direction) {
            case UP:
                draw(animated_img_workers.up[worker.no_img % 8], worker);
                break;
            case DOWN:
                draw(animated_img_workers.down[worker.no_img % 8], worker);
                break;
            case LEFT:
                draw(animated_img_workers.left[worker.no_img % 8], worker);
                break;
            case RIGHT:
                draw(animated_img_workers.right[worker.no_img % 8], worker);
                break;
            default:
                break;
        }
}
void draw_wolf(img_t wolf){
    switch (wolf.direction) {
        case UP:
            draw(wolf, wolf);
            break;
        case DOWN:
            draw(wolf, wolf);
            break;
        case LEFT:
            draw(wolf, wolf);
            break;
        case RIGHT:
            draw(wolf, wolf);
            break;
        default:
            break;
    }
}

void move_monsters(){
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++){
        if(enemies_lv1[i].is_dead)continue;
        int width = player.hitbox_x - enemies_lv1[i].hitbox_x;
        int height = player.hitbox_y - enemies_lv1[i].hitbox_y;

        int distance;
        int final_x;
        int final_y;
        if(width == 0 && height == 0) {
            distance = 0;
            final_x = 0;
            final_y = 0;
            player_lives -=2;
        }
        else {
            distance = sqrt(width*width + height*height);
            final_x = (width*animated_img_enemy1.speed)/distance;
            final_y = (height*animated_img_enemy1.speed)/distance;
        }

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
void kill_workers(){
    for (int i = 0; i < (int) (sizeof(workers) / sizeof(workers[0])); i++){
        if(!workers[i].is_dead){
            if(manage_hitbox(workers[i], player)){
                workers[i].is_dead = true;
            }
        }
    }
}
void move_workers(){
    for (int i = 0; i < (int) (sizeof(workers) / sizeof(workers[0])); i++){
        if(workers[i].is_dead)continue;
        int x = x_res*5;
        int y = y_res*5;
        int min = x;
        bool found = false;
        for (int z = 0; z < (int) (sizeof(teleports) / sizeof(teleports[0])); z++){
            if(!teleports[z].is_dead){
                int width = teleports[z].hitbox_x - workers[i].hitbox_x;
                int height = teleports[z].hitbox_y - workers[i].hitbox_y;
                int distance;
                if(abs(width) <= animated_img_workers.speed && abs(height) <= animated_img_workers.speed) {
                    workers[i].x = teleports[z].x;
                    workers[i].y = teleports[z].y;
                    workers[i].hitbox_x = workers[i].x+(workers[i].width/2);
                    workers[i].hitbox_y = workers[i].y+(workers[i].height/2);
                    if((counter_timer % 45) == 0)teleports[z].idle_time -= 1;
                    found = true;
                    break;
                }
                else {
                    distance = sqrt(width*width + height*height);
                    if(distance < min){
                        min = distance;
                        x = width;
                        y = height;
                    }
                }
            }
        }
        for (int z = 0; z < (int) (sizeof(packages) / sizeof(packages[0])); z++){
            if(!packages[z].is_dead && !packages[z].is_in_inventory){
                int width = packages[z].x - workers[i].x;
                int height = packages[z].y - workers[i].y;
                int distance;
                if(abs(width) <= animated_img_workers.speed && abs(height) <= animated_img_workers.speed) {
                    workers[i].x = packages[z].x;
                    workers[i].y = packages[z].y;
                    if(wolf.x == packages[z].x){
                        workers[i].is_dead = true;
                        workers[i].is_in_inventory = false;
                    }
                    workers[i].hitbox_x = workers[i].x+(workers[i].width/2);
                    workers[i].hitbox_y = workers[i].y+(workers[i].height/2);
                    if(packages[z].x <=(x_res/2)){
                        if(packages[z].y <=(y_res/2)){
                            if(packages[z].x <= packages[z].y){
                                packages[z].x -= animated_img_workers.speed /2;
                                packages[z].hitbox_x -= animated_img_workers.speed/2;
                            }
                            else{
                                packages[z].y -= animated_img_workers.speed /2;
                                packages[z].hitbox_y -= animated_img_workers.speed/2;
                            }
                        }
                        else{
                            if(packages[z].x <= (y_res-packages[z].y)){
                                packages[z].x -= animated_img_workers.speed /2;
                                packages[z].hitbox_x -= animated_img_workers.speed/2;
                            }
                            else{
                                packages[z].y += animated_img_workers.speed /2;
                                packages[z].hitbox_y += animated_img_workers.speed/2;
                            }
                        }
                    }
                    else{
                        if(packages[z].y <=(y_res/2)){
                            if((x_res-packages[z].x) <= packages[z].y){
                                packages[z].x += animated_img_workers.speed /2;
                                packages[z].hitbox_x += animated_img_workers.speed/2;
                            }
                            else{
                                packages[z].y -= animated_img_workers.speed /2;
                                packages[z].hitbox_y -= animated_img_workers.speed/2;
                            }
                        }
                        else{
                            if((x_res - packages[z].x) <= (y_res-packages[z].y)){
                                packages[z].x += animated_img_workers.speed /2;
                                packages[z].hitbox_x += animated_img_workers.speed/2;
                            }
                            else{
                                packages[z].y += animated_img_workers.speed /2;
                                packages[z].hitbox_y += animated_img_workers.speed/2;
                            }
                        }
                    }
                    if((packages[z].x <= 1) || ((packages[z].x+packages[z].width) >= (x_res +10)) || (packages[z].y <= 1) || ((packages[z].y+packages[z].height) >= (y_res +10))){
                        packages[z].is_dead = true;
                    }
                    found = true;
                    break;
                }
                else {
                    distance = sqrt(width*width + height*height);
                    if(distance < min){
                        min = distance;
                        x = width;
                        y = height;
                    }
                }
            }
        }
        if(found)continue;
        
        int count = 0;
        for(int z= 0; z < 4; z++){
            if(move[z] != STILL){
                count++;
            }
        }
        if(count == 0){
            int speed = 4;
            if(count == 2)speed = 2;
            int width = player.hitbox_x - workers[i].hitbox_x;
            int height = player.hitbox_y - workers[i].hitbox_y;

            int distance;
            int final_x = 0;
            int final_y = 0;
            if(abs(width) <= 10 && abs(height) <= 10) {
                workers[i].x = player.hitbox_x-10;
                workers[i].y = player.hitbox_y-10;
                workers[i].hitbox_x = workers[i].x+(workers[i].width/2);
                workers[i].hitbox_y = workers[i].y+(workers[i].height/2);
                continue;
            }
            else{
                distance = sqrt(width*width + height*height);
                final_x = (width*speed)/distance;
                final_y = (height*speed)/distance;
            }
            if(distance < min){
                if(final_x > 0) workers[i].direction = RIGHT;
                else if(final_x < 0) {
                    workers[i].direction = LEFT;
                    final_x = abs(final_x);
                }
                if(counter_timer % 5 == 0)workers[i].no_img += 1;
                if(!is_occupied(workers[i], final_x))manage_collision(&workers[i], final_x);


                if(final_y>0)workers[i].direction = DOWN;
                else if(final_y <0) {
                    workers[i].direction = UP;
                    final_y = abs(final_y);
                }
                if(!is_occupied(workers[i], final_y)) manage_collision(&workers[i], final_y);

                draw_workers(workers[i]);
                continue;
            }
        }
        if(min != (x_res*5)){
            int final_x = (x*animated_img_workers.speed)/min;
            int final_y = (y*animated_img_workers.speed)/min;
            if(final_x > 0) workers[i].direction = RIGHT;
            else if(final_x < 0) {
                workers[i].direction = LEFT;
                final_x = abs(final_x);
            }
            if(counter_timer % 5 == 0)workers[i].no_img += 1;
            if(!is_occupied(workers[i], final_x))manage_collision(&workers[i], final_x);


            if(final_y>0)workers[i].direction = DOWN;
            else if(final_y <0) {
                workers[i].direction = UP;
                final_y = abs(final_y);
            }
            if(!is_occupied(workers[i], final_y)) manage_collision(&workers[i], final_y);

        }
        else if(min == (x_res*5)){
                if(counter_timer % 5 == 0)workers[i].no_img += 1;
                int speed = animated_img_workers.speed/2;
                int width = workers[i].hitbox_x - player.hitbox_x;
                int height = workers[i].hitbox_y - player.hitbox_y;

                int distance;
                int final_x = 0;
                int final_y = 0;
                if(abs(width) <= speed && abs(height) <= speed) {
                    workers[i].x = player.x+speed;
                    workers[i].y = player.y+speed;
                    workers[i].hitbox_x = workers[i].x+(workers[i].width/2);
                    workers[i].hitbox_y = workers[i].y+(workers[i].height/2);
                    draw_workers(workers[i]);
                    continue;
                }
                else {
                    distance = sqrt(width*width + height*height);
                    if(distance <= 100)speed = 6;
                    else if(distance <= 200)speed = 4;
                    else if(distance <= 300)speed = 2;
                    else speed = 0;
                    final_x = (width*speed)/distance;
                    final_y = (height*speed)/distance;
                } 
                if(final_x > 0){
                    workers[i].direction = RIGHT;
                }
                else if(final_x < 0)workers[i].direction = LEFT;
                if(!is_occupied(workers[i], final_x)) manage_collision(&workers[i], final_x);
                
                if(final_y > 0)workers[i].direction = DOWN;
                else if(final_y<0)workers[i].direction = UP;
                if(!is_occupied(workers[i], final_y)) manage_collision(&workers[i], final_y);
        }
        draw_workers(workers[i]);
    }
}
void move_wolf(){
    if(!wolf.is_dead && !wolf.is_in_inventory){
        int width = player.hitbox_x - wolf.hitbox_x;
        int height = player.hitbox_y - wolf.hitbox_y;

    

        if(!bone.is_dead && !bone.is_in_inventory){
            width = bone.hitbox_x - wolf.hitbox_x;
            height = bone.hitbox_y - wolf.hitbox_y;
        }

        int distance = 0;
        int final_x = 0;
        int final_y = 0;
        
        if((abs(width) <= 3 && abs(height) <= 3)) {
            distance = 0;
            final_x = 0;
            final_y = 0;
            if(!(!bone.is_dead && !bone.is_in_inventory))player_lives -=2;
            else{
                if(catched){
                    if((counter_timer % 30) == 0){
                        if(catched == 15)wolf.idle_time -= 1;
                        catched -= 1;
                        if(catched == 0){
                            wolf.is_dead = true;
                        }
                    }
                    
                }
                if(wolf.idle_time == 0){
                    wolf.is_in_inventory = true;
                    
                }
            }
        }
        else if(!bone.is_dead && bone.is_in_inventory && current_index != -1 && (abs(width) <= 200 && abs(height) <= 200)){
            if(inventory[current_index].type == BONE && inventory[current_index].is_in_inventory){
                distance = 0;
                final_x = 0;
                final_y = 0;
            }
            else {
                distance = sqrt(width*width + height*height);
                final_x = (width*3)/distance;
                final_y = (height*3)/distance;
            }
        }
        else {
            distance = sqrt(width*width + height*height);
            final_x = (width*3)/distance;
            final_y = (height*3)/distance;
        }

        if(final_x > 0) wolf.direction = RIGHT;
        else if(final_x < 0) {
            wolf.direction = LEFT;
            final_x = abs(final_x);
        }
        if(!is_occupied(wolf, final_x)){
            manage_collision(&wolf, final_x);
        }


        if(final_y>0)wolf.direction = DOWN;
        else if(final_y <0) {
            wolf.direction = UP;
            final_y = abs(final_y);
        }
        if(!is_occupied(wolf, final_y)){
            manage_collision(&wolf, final_y);
        }
        draw_wolf(wolf);
    }
    if(!wolf.is_dead && wolf.is_in_inventory){
        bool found = false;
        bool found_teleporter = false;
        int min = x_res;
        int x = 0;
        int y = 0;
        int package = -1;
        for (int z = 0; z < (int) (sizeof(packages) / sizeof(packages[0])); z++){
            if(!packages[z].is_dead && !packages[z].is_in_inventory){
                int width = packages[z].x - wolf.x;
                int height = packages[z].y - wolf.y;
                int distance;
                if(abs(width) <= 3 && abs(height) <= 3) {
                    wolf.x = packages[z].x;
                    wolf.y = packages[z].y;
                    wolf.hitbox_x = wolf.x+(wolf.width/2);
                    wolf.hitbox_y = wolf.y+(wolf.height/2);
                    package = z;
                    found = true;
                    break;
                }
                else {
                    distance = sqrt(width*width + height*height);
                    if(distance < min){
                        min = distance;
                        x = width;
                        y = height;
                    }
                }
            }
        }
        if(found){
            for (int z = 0; z < (int) (sizeof(teleports) / sizeof(teleports[0])); z++){
                if(!teleports[z].is_dead && !teleports[z].is_in_inventory){
                    int width = teleports[z].x - wolf.x;
                    int height = teleports[z].y - wolf.y;
                    int distance;
                    if(abs(width) <= 3 && abs(height) <= 3) {
                        wolf.x = teleports[z].x;
                        wolf.y = teleports[z].y;
                        wolf.hitbox_x = wolf.x+(wolf.width/2);
                        wolf.hitbox_y = wolf.y+(wolf.height/2);
                        int index = is_on_teleport(wolf);
                        if(index != -1){
                            teleports[index].is_dead = true;
                            teleports[index].is_in_inventory = true;
                            teleports[index].idle_time = teleports[index].idle_time *5;
                            packages[package].is_dead = true;
                            packages[package].is_in_inventory = false;
                        }
                        found_teleporter = true;
                        break;
                    }
                    else {
                        distance = sqrt(width*width + height*height);
                        if(distance < min){
                            min = distance;
                            x = width;
                            y = height;
                        }
                        found_teleporter = true;
                    }
                } 
            }
            if(!found_teleporter){
                x = player.x - wolf.x;
                y = player.y - wolf.y;
                if(!(abs(x)<= 50 && abs(y) <= 50)){
                    min = sqrt(x*x + y*y);
                    found_teleporter = true;
                }
                else {
                    found = false;
                    min = x_res;
                }
            }
        }
        if(found || min != x_res){

            x = (x*3)/min;
            y = (y*3)/min;
            if(x > 0) wolf.direction = RIGHT;
            else if(x < 0) {
                wolf.direction = LEFT;
                x = abs(x);
            }
            if(!is_occupied(wolf, x)){
                manage_collision(&wolf, x);
                if(found_teleporter){
                    packages[package].x = wolf.x;
                    packages[package].y = wolf.y;
                    packages[package].hitbox_x = packages[package].x +(packages[package].width/2);
                    packages[package].hitbox_y = packages[package].y +(packages[package].height /2);
                }
            }


            if(y>0)wolf.direction = DOWN;
            else if(y <0) {
                wolf.direction = UP;
                y = abs(y);
            }
            if(!is_occupied(wolf, y)){
                manage_collision(&wolf, y);
                if(found_teleporter){
                    packages[package].x = wolf.x;
                    packages[package].y = wolf.y;
                    packages[package].hitbox_x = packages[package].x +(packages[package].width/2);
                    packages[package].hitbox_y = packages[package].y +(packages[package].height /2);
                }
            }
        }
        draw_wolf(wolf);
    }
}
void move_bullets(){
    for (int i = 0; i < (int) (sizeof(bullets) / sizeof(bullets[0])); i++){
        if(bullets[i].is_dead)continue;
        is_occupied(bullets[i], 20);
        manage_collision(&bullets[i], 10);
        draw_bullets(bullets[i]);
    }
}
void draw_bullets(img_t bullet){
    draw(bullet, bullet);
}
