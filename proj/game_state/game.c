#include "game.h"


uint8_t timer_bit_no;
uint8_t kbd_bit_no;
uint8_t mouse_bit_no;
game_info_t game_info = {MENU, START};

//setters
void set_state(game_state_t state){
    game_info.state = state;
    game_info.action = AFK;
    player.direction = STILL;
}


//handlers
int keyboard_ih(uint32_t scancode){
    if(game_info.state == MENU){
        game_info.action = keyboard_ih_menu(scancode);
    }
    else if(game_info.state == LEVEL1){
        game_info.action = keyboard_ih_level(scancode);
    }
    return 0;
}
int mouse_proj_ih(){
    mouse.x = mouse_x;
    mouse.y = mouse_y;
    if(game_info.state == MENU){
        game_info.action = mouse_ih_menu();
    }
    return 0;
}
int control_state(){
    switch(game_info.state){
        case MENU:
            if(game_info.action == START){
                set_state(LEVEL1);
            }
            else if(game_info.action == EXIT){
                set_state(GAME_OVER);
                return 1;
            }
            break;
        case LEVEL1:
            if(game_info.action == EXIT){
                set_state(MENU);
            }
            break;
        default:
            return 0;
    }
    return 0;
}

int draw_state(){
    switch(game_info.state){
        case MENU:
            draw_menu();
            break;
        case LEVEL1:
            draw_level();
            break;
        default:
            return 1;
    }
    return 0;
}

//game_loop
int initialize(){
    memset(&game_info, 0, sizeof(game_info));
    if(init_graphics(DIRECT_COLOR_8_8_8_8)) return 1;
    init_img();
    init_anim_img();
    init_simple_animation();
    frame_buffer = (uint8_t *)malloc(frame_size);
    set_state(MENU);
    if(mouse_write(STREAM_MODE)) return 1;
    if(mouse_write(DATA_REPORT))return 1;
    if(timer_set_frequency_proj(0, 30)) return 1;


    timer_bit_no = timer_subscribe();
    if(timer_bit_no == 0xFF) return 1;
    kbd_bit_no = keyboard_subscribe();
    if(kbd_bit_no == 0xFF) return 1;
    mouse_bit_no = mouse_subscribe();
    if(mouse_bit_no == 0xFF)return 1;
    return 0;
}

int game_loop(){
  int ipc_status;
  message msg;
  while(true) {
		if ((driver_receive(ANY, &msg, &ipc_status)) != 0) { 
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
                if (msg.m_notify.interrupts & timer_bit_no){
                    timer_int_handler_proj();
                    draw_state();
                    pass_to_vm_buffer();
                }
				if(msg.m_notify.interrupts & kbd_bit_no) {
                    uint32_t command;
					uint32_t scancode = kbc_read_output(OUT_BUFFER, &command);
                    keyboard_ih(scancode);
                    
                    int res = control_state();
					if(res == 1){
                        return 0;
                    }
				}
                if(msg.m_notify.interrupts & mouse_bit_no){
                    mouse_control();
                    mouse_proj_ih();
                    int res = control_state();
                    if(res == 1){
                        return 0;
                    }
                }
                
				break;

			default:
				break;
			}
		}
	}
  return 0;
}



int terminate(){
    if(mouse_unsubscribe())return 1;
    if(keyboard_unsubscribe()) return 1;
    if(mouse_write(0xF5))return 1;
    if(timer_unsubscribe()) return 1;
    keyboard_restore();  
    if(vg_exit()) return 1;
    free(frame_buffer);
    return 0;
}

