#include <lcom/lcf.h>
#include <stdlib.h>
#include "game_state/game.h"
#include "macros/includes.h"
#include "devices/graphics.h"
#include "devices/keyboard.h"
#include <stdbool.h>
#include <stdint.h>

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
int(proj_main_loop)(int argc, char *argv[]){
    
    
    uint16_t mode = (int)strtol(argv[0], NULL, 16);
    if(argc != 1){
      printf("Wrong number of arguments!, valid: %d",argc);
      return EXIT_FAILURE;
    }
    if(!(mode == DIRECT_COLOR_1_5_5_5 || mode == DIRECT_COLOR_5_6_5 || mode==DIRECT_COLOR_8_8_8 || mode==DIRECT_COLOR_8_8_8_8 || mode == INDEXED_MODE)){
      printf("Wrong mode! %d",mode);
      return EXIT_FAILURE;
    }
   
    if(initialize(mode)){
      printf("initialization error\n");
      return EXIT_FAILURE;
    }
    game_loop(mode);
    if(terminate()){
      printf("terminate error\n");
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
