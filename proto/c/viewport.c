#include "config.h"
// [ref config_viewport]
#ifdef USE_C_VIEWPORT
void clearViewport(){
 
    unsigned char *      adrTopLeft;
    unsigned char ii, jj;
    adrTopLeft = (unsigned char *)(HIRES_SCREEN_ADDRESS + VIEWPORT_START_COLUMN/2 + NEXT_SCANLINE_INCREMENT * VIEWPORT_START_LINE*3);
    for (ii = 0; ii< VIEWPORT_HEIGHT*3; ii++){
        for (jj = 0; jj < VIEWPORT_WIDTH/2; jj++) {
            adrTopLeft[jj] = 0x40   ;
        }
        adrTopLeft += NEXT_SCANLINE_INCREMENT;
    }
}
extern signed char          idxScreenCol; // idxScreenLine,
void clearColumn(){
    int ii;
    ;
    for (ii=0; ii< (VIEWPORT_HEIGHT * 3)/2; ii+=3){
#ifndef __GNUC__        
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii) + (idxScreenCol / 2)) = 0x40;
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii + 1) + (idxScreenCol / 2)) = 0x40;
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii + 2) + (idxScreenCol / 2)) = 0x7F;
#endif
    }
    for (ii=(VIEWPORT_HEIGHT * 3)/2; ii< VIEWPORT_HEIGHT * 3; ii+=3){
#ifndef __GNUC__
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii) + (idxScreenCol / 2)) = 0x40;
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii + 1) + (idxScreenCol / 2)) = 0x7F;
        *(unsigned char*)(HIRES_SCREEN_ADDRESS + 1 + NEXT_SCANLINE_INCREMENT * ( VIEWPORT_START_LINE*3 + ii + 2) + (idxScreenCol / 2)) = 0x40;
#endif
    }
}

#endif // USE_C_VIEWPORT