#include "menu.h"

action_t menu_selection = AFK;


void set_selection_menu(action_t action){
    menu_selection = action;
}

action_t mouse_ih_menu(){
    if(mouse_position(500, 300, 575, 315)){
        menu_selection = START;
    }
    else if(mouse_position(506, 330, 566, 345)){
        menu_selection = EXIT;
    }
    else{
        if(mouse_hover){
            mouse_hover = false;
            menu_selection = AFK;
        }
    }
    if(mouse_packet.lb && mouse_hover) return menu_selection;
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
    draw_menu_title();
    draw_menu_words();
    if(mouse_hover)draw(mouse_animation.animation[1], mouse);
    else draw(mouse_animation.animation[0], mouse);
}
void draw_menu_words(){
    switch(menu_selection){
        case START:
            draw_small_xpm((xpm_map_t)selected_s_xpm, 500, 300);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 515, 300);
            draw_small_xpm((xpm_map_t)selected_a_xpm, 530, 300);
            draw_small_xpm((xpm_map_t)selected_r_xpm, 545, 300);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 560, 300);

            draw_small_xpm((xpm_map_t)q_xpm, 506, 330);
            draw_small_xpm((xpm_map_t)u_xpm, 521, 330);
            draw_small_xpm((xpm_map_t)i_xpm, 536, 330);
            draw_small_xpm((xpm_map_t)t_xpm, 551, 330);
            break;
        case EXIT:
            draw_small_xpm((xpm_map_t)s_xpm, 500, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 515, 300);
            draw_small_xpm((xpm_map_t)a_xpm, 530, 300);
            draw_small_xpm((xpm_map_t)r_xpm, 545, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 560, 300);

            draw_small_xpm((xpm_map_t)selected_q_xpm, 506, 330);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 521, 330);
            draw_small_xpm((xpm_map_t)selected_i_xpm, 536, 330);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 551, 330);
            break;
        case AFK:
            draw_small_xpm((xpm_map_t)s_xpm, 500, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 515, 300);
            draw_small_xpm((xpm_map_t)a_xpm, 530, 300);
            draw_small_xpm((xpm_map_t)r_xpm, 545, 300);
            draw_small_xpm((xpm_map_t)t_xpm, 560, 300);

            draw_small_xpm((xpm_map_t)q_xpm, 506, 330);
            draw_small_xpm((xpm_map_t)u_xpm, 521, 330);
            draw_small_xpm((xpm_map_t)i_xpm, 536, 330);
            draw_small_xpm((xpm_map_t)t_xpm, 551, 330);
        default:
            break;
    }
}
void draw_menu_title(){
    draw_small_xpm((xpm_map_t)selected_a_xpm, 445, 100);
    draw_small_xpm((xpm_map_t)selected_l_xpm, 460, 100);
    draw_small_xpm((xpm_map_t)selected_i_xpm, 475, 100);
    draw_small_xpm((xpm_map_t)selected_e_xpm, 490, 100);
    draw_small_xpm((xpm_map_t)selected_n_xpm, 505, 100);

    draw_small_xpm((xpm_map_t)selected_e_xpm, 535, 100);
    draw_small_xpm((xpm_map_t)selected_x_xpm, 550, 100);
    draw_small_xpm((xpm_map_t)selected_p_xpm, 565, 100);
    draw_small_xpm((xpm_map_t)selected_r_xpm, 580, 100);
    draw_small_xpm((xpm_map_t)selected_e_xpm, 595, 100);
    draw_small_xpm((xpm_map_t)selected_s_xpm, 610, 100);
    draw_small_xpm((xpm_map_t)selected_s_xpm, 625, 100);
}

