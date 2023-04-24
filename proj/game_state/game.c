#include "game.h"


uint8_t timer_bit_no;
uint8_t kbd_bit_no;
game_info_t game_info = {MENU, START};
movement_t move[4]={STILL,STILL,STILL,STILL};

//setters
void set_state(game_state_t state){
    game_info.state = state;
    game_info.action = AFK;
}


//handlers
int keyboard_ih(uint32_t scancode){
    if(game_info.state == MENU){
        if(scancode == MAKE_ESC){
            game_info.action = EXIT;
            return 1;
        }
        else if(scancode == MAKE_W)game_info.action = START;
    }
    else if(game_info.state == LEVEL1){
        if(scancode == MAKE_ESC){
            game_info.action = EXIT;
            return 0;
        }
        if(scancode == MAKE_W)move[0] = UP;
        if(scancode == MAKE_D)move[1] = RIGHT;
        if(scancode == MAKE_A)move[2] = LEFT;
        if(scancode == MAKE_S)move[3] = DOWN;
        if(scancode == B(MAKE_W))move[0] = STILL;
        if(scancode == B(MAKE_D))move[1] = STILL;
        if(scancode == B(MAKE_A))move[2] = STILL;
        if(scancode == B(MAKE_S))move[3] = STILL;
        if(move[0] == UP){
            animated_img.img.y -= 10;
            animated_img.no_img += 1;
        }
        if(move[1] == RIGHT){
            animated_img.img.x += 10;
            animated_img.no_img += 1;
        }
        if(move[2] == LEFT){
            animated_img.img.x -= 10;
            animated_img.no_img += 1;
        }
        if(move[3] == DOWN){
            animated_img.img.y += 10;
            animated_img.no_img += 1;
        }
    }
    return 0;
}
int control_state(uint32_t scancode){
    keyboard_ih(scancode);
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

int draw_state(uint16_t mode){
    switch(game_info.state){
        case MENU:
            draw_menu(mode);
            break;
        case LEVEL1:
            draw_level(mode);
            break;
        default:
            return 1;
    }
    return 0;
}

//game_loop
int initialize(uint16_t mode){
    memset(&game_info, 0, sizeof(game_info));
    if(init_graphics(mode)) return 1;
    init_img( 214, 100,1,1,mode);
    init_anim_img(214,100,1,mode);
    allocate();
    set_state(MENU);
    if(timer_set_frequency_proj(0, 30)) return 1;


    timer_bit_no = timer_subscribe();
    if(timer_bit_no == 0xFF) return 1;
    kbd_bit_no = keyboard_subscribe();
    if(kbd_bit_no == 0xFF) return 1;
    return 0;
}

int game_loop(uint16_t mode){
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
                    draw_state(mode);
                   //draw_menu_animated(mode,1);
                    copyBufferToVideo();
                }
				if(msg.m_notify.interrupts & kbd_bit_no) {
                    uint32_t command;
					uint32_t scancode = kbc_read_output(OUT_BUFFER, &command);
                    
                    int res = control_state(scancode);
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
    if(keyboard_unsubscribe()) return 1;
    if(timer_unsubscribe()) return 1;
    keyboard_restore();  
    if(vg_exit()) return 1;
    free_buffers();
    return 0;
}

