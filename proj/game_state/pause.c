#include "pause.h"

action_t pause_selection = AFK;


void set_selection_pause(action_t action){
    pause_selection = action;
}

action_t keyboard_ih_pause(uint32_t scancode){
    if(scancode == MAKE_ENTER){
        return pause_selection;
    }
    else if(scancode == MAKE_ESC){
        return START;
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
    if(mouse_position(493, 300, 583, 315)){
        pause_selection = START;
    }
    else if(mouse_position(506, 360, 566, 375)){
        pause_selection = EXIT;
    }
    else{
        if(mouse_hover){
            mouse_hover = false;
            pause_selection = AFK;
        }
    }
    if(mouse_packet.lb && mouse_hover) {
        mouse_hover = false;
        return pause_selection;
    }
    return AFK;
}

void draw_pause(){
    draw_packages();
    draw_guns();
    count = -1;
    draw_afk_player();
    draw_teleports();
    for (int i = 0; i < (int) (sizeof(workers) / sizeof(workers[0])); i++) {
        if(!workers[i].is_dead)draw_workers(workers[i]);
    }
    
    for (int i = 0; i < (int) (sizeof(enemies_lv1) / sizeof(enemies_lv1[0])); i++) {
        if(!enemies_lv1[i].is_dead)draw_enemies(enemies_lv1[i]);
    }

    draw_pause_words();

    draw_level_words();
    draw_timer(seconds, minutes);

    if(mouse_hover)draw(mouse_animation.animation[1], mouse);
    else draw(mouse_animation.animation[0], mouse);

    draw_health();
    draw_inventory();
    if(!selected.is_dead)draw(selected, selected);
}

void draw_pause_words(){
     switch(pause_selection){
        case START:
            draw_small_xpm((xpm_map_t)selected_r_xpm, 493, 300);
            draw_small_xpm((xpm_map_t)selected_e_xpm, 508, 300);
            draw_small_xpm((xpm_map_t)selected_s_xpm, 523, 300);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 538, 300);
            draw_small_xpm((xpm_map_t)selected_m_xpm, 553, 300);
            draw_small_xpm((xpm_map_t)selected_e_xpm, 568, 300);

            draw_small_xpm((xpm_map_t)m_xpm, 506, 360);
            draw_small_xpm((xpm_map_t)e_xpm, 521, 360);
            draw_small_xpm((xpm_map_t)n_xpm, 536, 360);
            draw_small_xpm((xpm_map_t)u_xpm, 551, 360);
            break;
        case EXIT:
            draw_small_xpm((xpm_map_t)r_xpm, 493, 300);
            draw_small_xpm((xpm_map_t)e_xpm, 508, 300);
            draw_small_xpm((xpm_map_t)s_xpm, 523, 300);
            draw_small_xpm((xpm_map_t)u_xpm, 538, 300);
            draw_small_xpm((xpm_map_t)m_xpm, 553, 300);
            draw_small_xpm((xpm_map_t)e_xpm, 568, 300);

            draw_small_xpm((xpm_map_t)selected_m_xpm, 506, 360);
            draw_small_xpm((xpm_map_t)selected_e_xpm, 521, 360);
            draw_small_xpm((xpm_map_t)selected_n_xpm, 536, 360);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 551, 360);
            break;
        case AFK:
            draw_small_xpm((xpm_map_t)r_xpm, 493, 300);
            draw_small_xpm((xpm_map_t)e_xpm, 508, 300);
            draw_small_xpm((xpm_map_t)s_xpm, 523, 300);
            draw_small_xpm((xpm_map_t)u_xpm, 538, 300);
            draw_small_xpm((xpm_map_t)m_xpm, 553, 300);
            draw_small_xpm((xpm_map_t)e_xpm, 568, 300);

            draw_small_xpm((xpm_map_t)m_xpm, 506, 360);
            draw_small_xpm((xpm_map_t)e_xpm, 521, 360);
            draw_small_xpm((xpm_map_t)n_xpm, 536, 360);
            draw_small_xpm((xpm_map_t)u_xpm, 551, 360);
        default:
            break;
    }
}

