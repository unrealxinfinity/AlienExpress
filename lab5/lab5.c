// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "videoConstants.h"
#include "keyboard.h"
#include "i8042.h"
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int wait_keyboard(){
  int ipc_status;
  uint8_t irq_set=0x00;
  message msg;
  scancode=0x00;
  int r;
  if (keyboard_subscribe_interrupts(&irq_set) != 0)
    return 1;
  while(scancode != BREAK_ESC) {
    if ((r=driver_receive(ANY, &msg, &ipc_status) )!= 0) {
      printf("Error: %d",r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
          }
            break;
        default:
            break;
        }
      }
    }
    if (keyboard_unsubscribe_interrupts())
    return 1;
    return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  /* To be completed */
  
  if(set_VBE_Mode(mode))return 1;
   

  sleep(delay);
  vg_exit();

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  
   if(map_Vmem(mode)){
    return 1;
  }
                          
  if(set_VBE_Mode(mode)){
    return 1;
  };

 
  if(vg_draw_rectangle(x,y,width,height,color)) return 1;


  if(wait_keyboard()) return 1;
  if(vg_exit()) return 1;

  return 0;                          

}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if(map_Vmem(mode)){
    printf("here");
    return 1;
  }
                          
  if(set_VBE_Mode(mode)){
    return 1;
  };
  /*unsigned int rectangle_w = xRes / no_rectangles;
  unsigned int rectangle_h = yRes / no_rectangles;
  uint32_t color;
  for(unsigned i = 0 ; i<no_rectangles ; i++){
    for(unsigned j = 0 ; j<no_rectangles ; j++){
      
      if(mode==indexed_color_mode){
       color = indexed_mode(j,i,step,first,no_rectangles);
      
      }
      else{
        uint32_t red = R(j,i,step,first);
        uint32_t green= G(j,i,step,first);
        uint32_t blue= B(j,i,step,first);

        color = (red << mode_info.RedFieldPosition) | (green << mode_info.GreenFieldPosition) | (blue << mode_info.BlueFieldPosition) ;
      }
     if(vg_draw_rectangle(j*rectangle_w,i*rectangle_h,rectangle_w,rectangle_h,color))return 1;
     }
    }  */
  if(vg_draw_rectangle(0,0,10,10,first))return 1;
  if(wait_keyboard()) return 1;
  if(vg_exit()) return 1;
  return 0;
}


int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if(map_Vmem(indexed_color_mode)){
    return 1;
  }
                          
  if(set_VBE_Mode(indexed_color_mode)){
    return 1;
  };
  if(load_xmp_to_Vmem(xpm,x,y)) return 1;

  if(wait_keyboard()) return 1;
  if(vg_exit()) return 1;
  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

