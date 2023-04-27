#include "game_over.h"

action_t game_over_selection = AFK;

void set_selection_game_over(action_t action){
    game_over_selection = action;
}
action_t mouse_ih_game_over(){
    if(mouse_position(486, 400, 576, 415)){
        game_over_selection = START;
    }
    else if(mouse_position(506, 430, 551, 445)){
        game_over_selection = EXIT;
    }
    else{
        if(mouse_hover){
            mouse_hover = false;
            game_over_selection = AFK;
        }
    }
    if(mouse_packet.lb && mouse_hover) return game_over_selection;
    return AFK;
}

action_t keyboard_ih_game_over(uint32_t scancode){
    if(scancode == MAKE_ENTER){
        return game_over_selection;
    }
    else if(scancode == MAKE_S){
        if(game_over_selection == AFK) game_over_selection = START;
        else if(game_over_selection == START) game_over_selection = EXIT;
    }
    else if(scancode == MAKE_W){
        if(game_over_selection == AFK)game_over_selection = START;
        else if(game_over_selection == EXIT) game_over_selection = START;
    }
    return AFK;
}

void draw_game_over(){
    counter_timer++;
    draw_level();

    draw_game_over_tag();

    draw_game_over_words();

    if(mouse_hover)draw(mouse_animation.animation[1], mouse);
    else draw(mouse_animation.animation[0], mouse);
}
void draw_game_over_words(){
    switch(game_over_selection){
        case START:
            draw_small_xpm((xpm_map_t)selected_r_xpm, 486, 400);
            draw_small_xpm((xpm_map_t)selected_e_xpm, 501, 400);
            draw_small_xpm((xpm_map_t)selected_s_xpm, 516, 400);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 531, 400);
            draw_small_xpm((xpm_map_t)selected_a_xpm, 546, 400);
            draw_small_xpm((xpm_map_t)selected_r_xpm, 561, 400);
            draw_small_xpm((xpm_map_t)selected_t_xpm, 576, 400);

            draw_small_xpm((xpm_map_t)m_xpm, 506, 430);
            draw_small_xpm((xpm_map_t)e_xpm, 521, 430);
            draw_small_xpm((xpm_map_t)n_xpm, 536, 430);
            draw_small_xpm((xpm_map_t)u_xpm, 551, 430);
            break;
        case EXIT:
            draw_small_xpm((xpm_map_t)r_xpm, 486, 400);
            draw_small_xpm((xpm_map_t)e_xpm, 501, 400);
            draw_small_xpm((xpm_map_t)s_xpm, 516, 400);
            draw_small_xpm((xpm_map_t)t_xpm, 531, 400);
            draw_small_xpm((xpm_map_t)a_xpm, 546, 400);
            draw_small_xpm((xpm_map_t)r_xpm, 561, 400);
            draw_small_xpm((xpm_map_t)t_xpm, 576, 400);

            draw_small_xpm((xpm_map_t)selected_m_xpm, 506, 430);
            draw_small_xpm((xpm_map_t)selected_e_xpm, 521, 430);
            draw_small_xpm((xpm_map_t)selected_n_xpm, 536, 430);
            draw_small_xpm((xpm_map_t)selected_u_xpm, 551, 430);
            break;
        case AFK:
            draw_small_xpm((xpm_map_t)r_xpm, 486, 400);
            draw_small_xpm((xpm_map_t)e_xpm, 501, 400);
            draw_small_xpm((xpm_map_t)s_xpm, 516, 400);
            draw_small_xpm((xpm_map_t)t_xpm, 531, 400);
            draw_small_xpm((xpm_map_t)a_xpm, 546, 400);
            draw_small_xpm((xpm_map_t)r_xpm, 561, 400);
            draw_small_xpm((xpm_map_t)t_xpm, 576, 400);

            draw_small_xpm((xpm_map_t)m_xpm, 506, 430);
            draw_small_xpm((xpm_map_t)e_xpm, 521, 430);
            draw_small_xpm((xpm_map_t)n_xpm, 536, 430);
            draw_small_xpm((xpm_map_t)u_xpm, 551, 430);
        default:
            break;
    }
}
void draw_game_over_tag(){
    draw_small_xpm((xpm_map_t)selected_g_xpm, 475, 300);
    draw_small_xpm((xpm_map_t)selected_a_xpm, 490, 300);
    draw_small_xpm((xpm_map_t)selected_m_xpm, 505, 300);
    draw_small_xpm((xpm_map_t)selected_e_xpm, 520, 300);


    draw_small_xpm((xpm_map_t)selected_o_xpm, 550, 300);
    draw_small_xpm((xpm_map_t)selected_v_xpm, 565, 300);
    draw_small_xpm((xpm_map_t)selected_e_xpm, 580, 300);
    draw_small_xpm((xpm_map_t)selected_r_xpm, 595, 300);
}
