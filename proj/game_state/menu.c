#include "menu.h"


img_t letter;

void draw_menu(){
    memset(frame_buffer, 0xDDDDDD, frame_size);
    //draw(title, title.x, title.y);
    draw_small_xpm((xpm_map_t)s_xpm, 400, 200);
    draw_small_xpm((xpm_map_t)t_xpm, 415, 200);
    draw_small_xpm((xpm_map_t)a_xpm, 430, 200);
    draw_small_xpm((xpm_map_t)r_xpm, 445, 200);
    draw_small_xpm((xpm_map_t)t_xpm, 460, 200);


    draw_small_xpm((xpm_map_t)q_xpm, 406, 230);
    draw_small_xpm((xpm_map_t)u_xpm, 421, 230);
    draw_small_xpm((xpm_map_t)i_xpm, 436, 230);
    draw_small_xpm((xpm_map_t)t_xpm, 451, 230);
}

