#ifndef DEFINE_H
#define DEFINE_H


#include <lcom/lcf.h>

#define ERROR           0xFFFF
#define BLACK           0

//timer
#define TIMER_IRQ_LINE              0
#define TIMER_STATUS                0x43
#define TIMER_0                     0x40
#define CONST_FREQ                  1193182
#define SELECT_TIMER(n)                (n << 6)
#define SELECT_RB_TIMER(n)             BIT((n) + 1)
#define TIMER_RB_CMD                (BIT(7) | BIT(6))
#define TIMER_COUNT_MODE            BIT(5)
#define TIMER_LSB_MSB               (BIT(4) | BIT(5))




//keyboard
#define KBD_HOOK_ID                 1
#define KBD_IRQ_LINE                1
#define KBC_STATUS                  0x64
#define OUT_BUFFER_BIT              BIT(0)
#define IN_BUFFER_BIT               BIT(1)
#define PARITY_ERROR                BIT(7)
#define TIME_OUT_ERROR              BIT(6)
#define OUT_BUFFER                  0x60
#define IN_BUFFER                   0x20
#define STREAMING_MODE              0xF4
#define ACK                         0xFA
#define RESEND                      0xFE
#define DELAY                       20000

#define MAKE_ESC                    0x01
#define MAKE_ENTER                  0x1C
#define MAKE_W                      0x11
#define MAKE_A                      0x1E
#define MAKE_D                      0x20
#define MAKE_S                      0x1F
#define B(n)                        (n | BIT(7))


//mouse
#define STREAM_MODE                 0xEA
#define DATA_REPORT                 0xF4
#define MOUSE_HOOK_ID               3
#define MOUSE_IRQ_LINE              12
#define WRITE_MOUSE_CMD             0xD4
#define ACK                         0xFA
#define MOUSE_CONTROL_BIT           BIT(3)
#define CLICK_LEFT                  BIT(0)
#define CLICK_RIGHT                 BIT(1)
#define CLICK_MIDDLE                BIT(2)
#define DELTA_X                     BIT(4)
#define DELTA_Y                     BIT(5)
#define X_OVERFLOW                  BIT(6)
#define Y_OVERFLOW                  BIT(7)
#define SET_NEGATIVE                0xFF00

//graphics
#define INTNO                       0x10
#define AL                          0x02
#define AH                          0x4F
#define BX                          BIT(14)
#define INDEXED_MODE                0x105
#define DIRECT_COLOR_1_5_5_5        0x110
#define DIRECT_COLOR_8_8_8          0x115
#define DIRECT_COLOR_5_6_5          0x11A
#define DIRECT_COLOR_8_8_8_8        0x14C

//entities
#define UNBREAKABLE_WALL            0x4E4E4E
#define PLAYER                      0x161516
#define ENEMY                       0x161319
#define PACKAGE                     0x000001
#define HEALTH                      0xFF0000
#define EMPTY_HEALTH                0x000002
#define EMPTY_INVENTORY             0x696969

#endif
