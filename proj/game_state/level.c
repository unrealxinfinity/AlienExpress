#include "level.h"



void draw_level(){
   // memset(frame_buffer, 0xDDDDDD, frame_size);
   //tilesPerAxis temp;
    drawTiles();
    //draw(player, player.x, player.y);
    
    draw(animated_img.images[animated_img.no_img%7], animated_img.img.x, animated_img.img.y);
}

