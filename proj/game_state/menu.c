#include "menu.h"
action_t menu_selection = AFK;

bool mouse_position(unsigned int xi, unsigned int yi, unsigned int xf, unsigned int yf){
    if(mouse_x >= xi && mouse_x <= xf && mouse_y <= yf && mouse_y >= yi){
        mouse_hover = true;
        return true;
    }
    return false;
}
action_t mouse_ih_menu(){
    if(mouse_position(400, 300, 460, 315)){
        menu_selection = START;
    }
    else if(mouse_position(406, 330, 451, 345)){
        menu_selection = EXIT;
    }
    else{
        if(mouse_hover){
            mouse_hover = false;
            menu_selection = AFK;
        }
    }
    if(mouse_packet.lb) return menu_selection;
    return AFK;

}

action_t keyboard_ih_menu(uint32_t scancode){
    if(scancode == MAKE_ENTER){
        return menu_selection;
    }
    else if(scancode == MAKE_S){
        if(menu_selection == AFK) menu_selection = START;
        else if(menu_selection == START) menu_selection = EXIT;
    }
    else if(scancode == MAKE_W){
        if(menu_selection == AFK)menu_selection = START;
        else if(menu_selection == EXIT) menu_selection = START;
    }
    return AFK;
}

void draw_menu(){
    draw_menu_words();
    if(mouse_hover)draw(mouse_animation.animation[1], mouse);
    else draw(mouse_animation.animation[0], mouse);
}
void draw_menu_words(){
    switch(menu_selection){
        case START:
            draw_small_xpm((xpm_map_t)selected_s_xpm, 400, 300);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 415, 300);
            draw_small_xpm((xpm_map_t)selected_a_xpm, 430, 300);
            draw_small_xpm((xpm_map_t)selected_r_xpm, 445, 300);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 460, 300);

            draw_small_xpm((xpm_map_t)q_xpm, 406, 330);
            draw_small_xpm((xpm_map_t)u_xpm, 421, 330);
            draw_small_xpm((xpm_map_t)i_xpm, 436, 330);
            draw_small_xpm((xpm_map_t)t_xpm, 451, 330);
            break;
        case EXIT:
            draw_small_xpm((xpm_map_t)s_xpm, 400, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 415, 300);
            draw_small_xpm((xpm_map_t)a_xpm, 430, 300);
            draw_small_xpm((xpm_map_t)r_xpm, 445, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 460, 300);

            draw_small_xpm((xpm_map_t)selected_q_xpm, 406, 330);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 421, 330);
            draw_small_xpm((xpm_map_t)selected_i_xpm, 436, 330);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 451, 330);
            break;
        case AFK:
            draw_small_xpm((xpm_map_t)s_xpm, 400, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 415, 300);
            draw_small_xpm((xpm_map_t)a_xpm, 430, 300);
            draw_small_xpm((xpm_map_t)r_xpm, 445, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 460, 300);

            draw_small_xpm((xpm_map_t)q_xpm, 406, 330);
            draw_small_xpm((xpm_map_t)u_xpm, 421, 330);
            draw_small_xpm((xpm_map_t)i_xpm, 436, 330);
            draw_small_xpm((xpm_map_t)t_xpm, 451, 330);
        default:
            break;
    }
}

