#include "graphics.h"

char *double_buffer;

uint8_t *vm_buffer;


int set_graphics_mode(uint16_t mode){
    reg86_t res;
    memset(&res, 0, sizeof(res));

    res.intno = INTNO;
    res.al = AL;
    res.ah = AH;
    res.bx = BX | mode;

    if(sys_int86(&res) != OK){
        printf("sys_int86 has failed\n");
        return 1;
    }
    return 0;
}
int set_frame_buffer(uint16_t mode){
    memset(&mode_info, 0, sizeof(mode_info));
    if(vbe_get_mode_info(mode, &mode_info)) return 1;
    bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    x_res = mode_info.XResolution;
    y_res = mode_info.YResolution;
    int r;
    frame_size = x_res * y_res * bytes_per_pixel;

    struct minix_mem_range mr;
    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + frame_size;

    if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK){
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
        return 1;
    }

    vm_buffer = vm_map_phys(SELF, (void *) mr.mr_base, frame_size);
    if(vm_buffer == MAP_FAILED){
        panic("couldnt map video memory");
        return 1;
    }
    
    return 0;

}
int init_graphics(uint16_t mode){
    if(set_frame_buffer(mode))return 1;
    if(set_graphics_mode(mode))return 1;
    return 0;
}

void allocate(){
    frame_buffer = (uint8_t *)malloc(frame_size); 
    view_buffer = (uint8_t *)malloc(frame_size);
    memset(view_buffer,0xFFFFFF,frame_size);
}
void free_buffers(){
    free(frame_buffer);
    free(view_buffer);
}
void copyBufferToVideo(){
    memcpy(vm_buffer, frame_buffer, frame_size);
    memset(frame_buffer, 0, frame_size); 
}

int draw_pixel(uint16_t x, uint16_t y, uint32_t colors_32){
    if(colors_32 == 0xfffffe) return 0;
    if(x >= x_res || y >= y_res) return 0;
    memcpy(&frame_buffer[(x_res*y + x) * bytes_per_pixel], &colors_32, bytes_per_pixel);
    return 0;
}
