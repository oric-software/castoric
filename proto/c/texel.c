// Texel Rendering Routines for Oric  
// Author : Jean-Baptiste PERIN
// Date : 2021


unsigned char           renCurrentColor;

#ifdef USE_C_COLORRIGHTTEXEL
// [ref texel_codec]
void colorRightTexel(){

#ifndef __GNUC__
    *theAdr |= tabRightRed[renCurrentColor];
#endif // __GNUC__
    theAdr += NEXT_SCANLINE_INCREMENT;

#ifndef __GNUC__
    *theAdr |= tabRightGreen[renCurrentColor];
#endif // __GNUC__
    theAdr += NEXT_SCANLINE_INCREMENT;

#ifndef __GNUC__
    *theAdr |= tabRightBlue[renCurrentColor];
#endif // __GNUC__
    theAdr += NEXT_SCANLINE_INCREMENT;
}
#endif // USE_C_COLORRIGHTTEXEL

#ifdef USE_C_COLORLEFTTEXEL
void colorLeftTexel(){

#ifndef __GNUC__
    *theAdr = tabLeftRed[renCurrentColor];
#endif // __GNUC__
    theAdr += NEXT_SCANLINE_INCREMENT;

#ifndef __GNUC__
    *theAdr = tabLeftGreen[renCurrentColor];
#endif // __GNUC__
    theAdr += NEXT_SCANLINE_INCREMENT;

#ifndef __GNUC__
    *theAdr = tabLeftBlue[renCurrentColor];
#endif
    theAdr += NEXT_SCANLINE_INCREMENT;

}
#endif // USE_C_COLORLEFTTEXEL


#ifdef USE_SLOW_TEXEL
unsigned int multi40[] = {
        0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600
        , 640, 680, 720, 760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160, 1200, 1240
        , 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560, 1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880
        , 1920, 1960, 2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360, 2400, 2440, 2480, 2520
        , 2560, 2600, 2640, 2680, 2720, 2760, 2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160
        , 3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560, 3600, 3640, 3680, 3720, 3760, 3800
        , 3840, 3880, 3920, 3960, 4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360, 4400, 4440
        , 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760, 4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080
        , 5120, 5160, 5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560, 5600, 5640, 5680, 5720
        , 5760, 5800, 5840, 5880, 5920, 5960, 6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360
        , 6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760, 6800, 6840, 6880, 6920, 6960, 7000
        , 7040, 7080, 7120, 7160, 7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560, 7600, 7640
        , 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960
        };


// [ref texel_codec]
void drawTexelOnScreen (signed char line, signed char column, unsigned char theColor){

    unsigned char *adr;

    if ((line >= 0) && (line < 64) && (column >= 2) && (column < 80)){

        adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(line<<1) + line] + (column>>1));

        if ((column&0x01) == 0){
            *adr = tabLeftRed[theColor];
            adr += NEXT_SCANLINE_INCREMENT;
            *adr = tabLeftGreen[theColor];
            adr += NEXT_SCANLINE_INCREMENT;
            *adr = tabLeftBlue[theColor];
        } else {
            *adr |= tabLeftRed[theColor];
            adr += NEXT_SCANLINE_INCREMENT;
            *adr |= tabLeftGreen[theColor];
            adr += NEXT_SCANLINE_INCREMENT;
            *adr |= tabLeftBlue[theColor];
        }

    }
}

void drawTexelOnViewport (signed char line, signed char column, unsigned char theColor){
    if ((line >= 0) && (line < VIEWPORT_HEIGHT) && (column >= 0) && (column < VIEWPORT_WIDTH)) {
        // TODO
    }
}


#endif // USE_SLOW_TEXEL
