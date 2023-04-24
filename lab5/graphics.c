#include "graphics.h"

int set_VBE_Mode(u16_t mode ){

  memset(&reg, 0, sizeof(reg));
  reg.intno=int_nr;
  reg.ah=video_set_func;
  reg.al=func_set_VBE_mode;
  reg.bx= mode | BIT(14);

  if(sys_int86(&reg)){
    printf("Failed to operate on the register!");
    return 1;
  };

  if(reg.al != func_supported){
    printf("Function not supported!");
    return 1;
  }
  else{
    if(reg.ah==func_call_failed){
      printf("Function call failed");
      return 1;
    }
    if(reg.ah==func_not_supported_curent_HW){
      printf("Function is not supported in the current HW configuration!");
      return 1;
    }
    if(reg.ah==invalid_func_in_current_vid_mode){
      printf("Function is invalid in the current video mode");
      return 1;
    }
  }
  return 0;
}

int map_Vmem(u16_t mode){
  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode,&mode_info)){
    printf("Failed to get mode info!");
    return 1 ;
  }
  vram_base = mode_info.PhysBasePtr;
  bytes_per_pixel =  (mode_info.BitsPerPixel+7)/8;
  xRes = mode_info.XResolution;
  yRes=mode_info.YResolution;
  vram_offset = bytes_per_pixel * xRes*yRes;

  

  mr.mr_base =   (phys_bytes)vram_base;
  mr.mr_limit = mr.mr_base + vram_offset;
  
  if(sys_privctl(SELF,SYS_PRIV_ADD_MEM,&mr)){
      printf("Failed to set permission to map the physical address!");
      return 1;
  }

  if((vid_mem = vm_map_phys(SELF,(void *)mr.mr_base,vram_offset))==NULL){
    printf("Failed to map the physical address!");
    return 1;
  }
  return 0;
}


int draw_pixel(uint16_t x,uint16_t y,uint32_t color){
   if(x>xRes || y>yRes){
      printf("Invalid x and y to draw!");
      vg_exit();
      return 1;
    }
    if(color>0xff && mode_info.MemoryModel != direct_mode){
      
    }
    int starting_paint_point = xRes*y+x;
    unsigned int index=starting_paint_point*bytes_per_pixel;
  if(memcpy(&vid_mem[index], &color, bytes_per_pixel) == NULL) return 1;
  return 0;
}
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){

  for (unsigned i=0; i<len;i++){
    if(draw_pixel(x+i,y,color)) return 1;
  }
  
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(unsigned i=0 ; i<height;i++){
    if(vg_draw_hline(x,y+i,width,color)) vg_exit();
  }
  return 0;
}

uint8_t Red(uint32_t color){

  return ((1<<mode_info.RedMaskSize)-1) & (color >> mode_info.RedFieldPosition) ;

}

uint8_t Green(uint32_t color){
  return (color >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize)-1);
}

uint8_t Blue(uint32_t color){
  return (color >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize)-1);
}

uint32_t R(unsigned x, unsigned y,uint32_t step,uint32_t first){
  return (Red(first) + x*step) % (1 << mode_info.RedMaskSize);
}

uint32_t G(unsigned x, unsigned y,uint32_t step,uint32_t first){
  return (Green(first) + y*step) % (1 << mode_info.GreenMaskSize);
}

uint32_t B(unsigned x, unsigned y,uint32_t step,uint32_t first){
  return (Blue(first) + (x+y)*step) % (1 << mode_info.BlueMaskSize);
}

uint32_t indexed_mode(uint16_t col ,uint16_t row ,uint8_t step,uint32_t first,uint8_t no_rectangles){
  return (first + (row * no_rectangles + col) * step) % (1 << mode_info.BitsPerPixel);
}

int load_xmp_to_Vmem(xpm_map_t xpm,unsigned x,unsigned y){

  xpm_image_t x_image;
  
  //array de cores de cada pixel
  uint8_t *colors = xpm_load(xpm, XPM_INDEXED, &x_image);
  /*if(memcpy(vid_mem,to_vram,x_image.size)==NULL) {
    printf("Failed to load xpm to video mem!");
    return 1;
    }*/
   for (unsigned int h = 0 ; h < x_image.height ; h++) {
    for (unsigned int w = 0 ; w < x_image.width ; w++) {
     
      if (draw_pixel(x + w, y + h, *colors) != 0) return 1;
      colors++; // avança para a próxima cor
    }
  }
  return 0;
}
