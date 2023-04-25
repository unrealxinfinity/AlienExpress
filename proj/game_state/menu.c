#include "menu.h"
action_t menu_selection = START;

action_t keyboard_ih_menu(uint32_t scancode){
    if(scancode == MAKE_ENTER){
        return menu_selection;
    }
    else if(scancode == MAKE_S){
        menu_selection = EXIT;
    }
    else if(scancode == MAKE_W){
        menu_selection = START;
    }
    return AFK;
}

void draw_menu(){
    memset(frame_buffer, 0xDDDDDD, frame_size);
    draw_menu_words();
}
void draw_menu_words(){
    switch(menu_selection){
        case START:
            draw_small_xpm((xpm_map_t)selected_s_xpm, 400, 200);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 415, 200);
            draw_small_xpm((xpm_map_t)selected_a_xpm, 430, 200);
            draw_small_xpm((xpm_map_t)selected_r_xpm, 445, 200);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 460, 200);

            draw_small_xpm((xpm_map_t)q_xpm, 406, 230);
            draw_small_xpm((xpm_map_t)u_xpm, 421, 230);
            draw_small_xpm((xpm_map_t)i_xpm, 436, 230);
            draw_small_xpm((xpm_map_t)t_xpm, 451, 230);
            break;
        case EXIT:
            draw_small_xpm((xpm_map_t)s_xpm, 400, 200);
            draw_small_xpm((xpm_map_t)t_xpm, 415, 200);
            draw_small_xpm((xpm_map_t)a_xpm, 430, 200);
            draw_small_xpm((xpm_map_t)r_xpm, 445, 200);
            draw_small_xpm((xpm_map_t)t_xpm, 460, 200);

            draw_small_xpm((xpm_map_t)selected_q_xpm, 406, 230);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 421, 230);
            draw_small_xpm((xpm_map_t)selected_i_xpm, 436, 230);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 451, 230);
            break;
        default:
            break;
    }
}

