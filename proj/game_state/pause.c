#include "pause.h"

action_t pause_selection = AFK;
action_t keyboard_ih_pause(uint32_t scancode){
    if(scancode == MAKE_ENTER){
        return pause_selection;
    }
    else if(scancode == MAKE_ESC){
        pause_selection = EXIT;
        return pause_selection;
    }
    else if(scancode == MAKE_S){
        if(pause_selection == AFK) pause_selection = START;
        else if(pause_selection == START) pause_selection = EXIT;
    }
    else if(scancode == MAKE_W){
        if(pause_selection == AFK)pause_selection = START;
        else if(pause_selection == EXIT) pause_selection = START;
    }
    return AFK;
}
action_t mouse_ih_pause(){
    if(mouse_position(500, 300, 575, 315)){
        pause_selection = START;
    }
    else if(mouse_position(506, 330, 566, 345)){
        pause_selection = EXIT;
    }
    else{
        if(mouse_hover){
            mouse_hover = false;
            pause_selection = AFK;
        }
    }
    if(mouse_packet.lb) return pause_selection;
    return AFK;
}

void draw_pause(){
    if(alive[0])drawPackage(100,100);
    
    draw_player();
    
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++) draw_enemies(enemies_lv1[i]);
}

void draw_pause_words(){
    
}

