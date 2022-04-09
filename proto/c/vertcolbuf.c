#include "config.h"

unsigned char bufVertColRight[VIEWPORT_HEIGHT+ VIEWPORT_START_LINE];
unsigned char bufVertColLeft[VIEWPORT_HEIGHT+ VIEWPORT_START_LINE];
unsigned char idxBufVertCol;

#define BLUE_SKY 21
#define GREEN_GRASS 42

#ifdef USE_C_VERTCOLBUF

void initBufVertCol (){
    for (idxBufVertCol = 0; idxBufVertCol < VIEWPORT_HEIGHT/2; idxBufVertCol++) {
        bufVertColRight[idxBufVertCol] = BLUE_SKY;
        bufVertColLeft[idxBufVertCol] = BLUE_SKY;
    }
    for (;idxBufVertCol < VIEWPORT_HEIGHT; idxBufVertCol++) {
        bufVertColRight[idxBufVertCol] = GREEN_GRASS;
        bufVertColLeft[idxBufVertCol] = GREEN_GRASS;
    }
}

extern unsigned char *     baseAdr;
extern unsigned char           *theAdr;
extern signed char         idxScreenLine, idxScreenCol;

void drawBufVertCol () {
    // TODO : remove this useless baseAdr computation because it is done in main loop
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
    theAdr  = (unsigned char *)(baseAdr + (int)((multi120_high[VIEWPORT_START_LINE]<<8) | multi120_low[VIEWPORT_START_LINE])); 


    for (idxBufVertCol = 0; idxBufVertCol < VIEWPORT_HEIGHT; ) {
#ifndef __GNUC__
        *theAdr  = tabLeftRed[bufVertColLeft[idxBufVertCol]] | tabRightRed[bufVertColRight[idxBufVertCol]];
#endif
        theAdr += NEXT_SCANLINE_INCREMENT;
#ifndef __GNUC__
        *theAdr  = tabLeftGreen[bufVertColLeft[idxBufVertCol]] | tabRightGreen[bufVertColRight[idxBufVertCol]];
#endif
        theAdr += NEXT_SCANLINE_INCREMENT;
#ifndef __GNUC__
        *theAdr  = tabLeftBlue[bufVertColLeft[idxBufVertCol]] | tabRightBlue[bufVertColRight[idxBufVertCol]];
#endif
        theAdr += NEXT_SCANLINE_INCREMENT;

        idxBufVertCol++;
    }
}

#endif // USE_C_VERTCOLBUF
