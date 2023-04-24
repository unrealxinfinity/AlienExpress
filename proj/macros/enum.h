#ifndef ENUM_H
#define ENUM_H


typedef enum{
    MENU,
    LEVEL1,
    GAME_OVER
}game_state_t;
typedef enum{
    START,
    EXIT,
    AFK
}action_t;

typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STILL
}movement_t;
#endif
