#include "config.h"
#include "tabidxrdtexture.h"
#include "dda.c"

extern unsigned int         offTexture;
extern unsigned char *      ptrTexture;             // Address of the texture 

#ifdef __GNUC__
unsigned char *             ptrOffsetIndex;
unsigned char *             ptrTexture;             // Address of the texture 
#else 
extern unsigned char *      ptrOffsetIndex;
#endif
unsigned char               nxtOffsetIndex;

#ifdef USE_C_DRAWWALLS

unsigned char *     ptrReadTexture;             // Address of the texture 
unsigned char       idxCurrentSlice;
unsigned char *     baseAdr;
signed char         idxScreenLine, idxScreenCol;
unsigned char       columnHeight, columnTextureCoord;
unsigned char       wallId;
unsigned char       ddaNbIter;

#define min(x,y)          (((x)<(y))?(x):(y))

void PREPARE(){
    columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);
    offTexture          = (multi32_high[columnTextureCoord] << 8) | multi32_low[columnTextureCoord];
#ifndef __GNUC__    
    ptrTexture          = (unsigned char *)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]);
#else
    ptrTexture          = (unsigned char *)(texture_00[wallId]);
#endif
    ptrReadTexture      = &(ptrTexture[offTexture]);
    columnHeight        = min(47,TableVerticalPos[idxCurrentSlice]);
    ddaNbStep           = columnHeight<<1;
    idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;
    ddaCurrentValue     = 0;
}

#ifdef __GNUC__
#define COLOR_LEFT_TEXEL  theAdr += NEXT_SCANLINE_INCREMENT;\
    theAdr += NEXT_SCANLINE_INCREMENT;\
    theAdr += NEXT_SCANLINE_INCREMENT;
#else
// #define COLOR_LEFT_TEXEL colorLeftTexel()
#define COLOR_LEFT_TEXEL  *theAdr = tabLeftRed[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr = tabLeftGreen[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr = tabLeftBlue[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;
#endif

// #define COLOR_RIGHT_TEXEL colorRightTexel()
#ifdef __GNUC__
#define COLOR_RIGHT_TEXEL theAdr += NEXT_SCANLINE_INCREMENT;\
    theAdr += NEXT_SCANLINE_INCREMENT;\
    theAdr += NEXT_SCANLINE_INCREMENT;
#else
#define COLOR_RIGHT_TEXEL *theAdr |= tabRightRed[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr |= tabRightGreen[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr |= tabRightBlue[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;
#endif

#define DDA_STEP ddaCurrentValue = ptrOffsetIndex[nxtOffsetIndex++];\

void DDA_STEP_2(){
            ddaCurrentError         -= TEXTURE_SIZE;
            if ((ddaCurrentError<<1) < ddaNbStep) {
                ddaCurrentError     += ddaNbStep;
                ddaCurrentValue     += 1;
            }    
}

void OVER_SAMPLE_COLOR_LEFT_TEXEL() {
        ddaCurrentError     = ddaNbStep;
        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_2();
            ddaNbIter       -= 1;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));
        do {
            DDA_STEP_2();
            ddaNbIter       -= 1;
#ifdef __GNUC__            
            renCurrentColor = ddaCurrentValue; 
#else
            renCurrentColor = ptrReadTexture [ddaCurrentValue];
#endif
            COLOR_LEFT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaNbIter > 0) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
}

void OVER_SAMPLE_COLOR_RIGHT_TEXEL() {
        ddaCurrentError     = ddaNbStep;
        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_2();
            ddaNbIter       -= 1;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));
        do {
            DDA_STEP_2();
            ddaNbIter       -= 1;
#ifdef __GNUC__            
            renCurrentColor = ddaCurrentValue; 
#else
            renCurrentColor = ptrReadTexture [ddaCurrentValue];
#endif
            COLOR_RIGHT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaNbIter > 0) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
}

// #define OVER_SAMPLE(prim) ddaCurrentError     = ddaNbStep;\
//         while (idxScreenLine < VIEWPORT_START_LINE){\
//             DDA_STEP_2;\
//             ddaNbIter       -= 1;\
//             idxScreenLine   += 1;\
//         } \
//         theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
//         do {\
//             DDA_STEP_2;\
//             ddaNbIter       -= 1;\
//             renCurrentColor = ptrReadTexture [ddaCurrentValue];\
//             prim;\
//             idxScreenLine   += 1;\
//         } while ((ddaNbIter > 0) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


#define UNROLL_SAMPLE(prim)         ddaCurrentError     = TEXTURE_SIZE;\
        while (idxScreenLine < VIEWPORT_START_LINE){\
            DDA_STEP\
            ddaNbIter       -= 1;\
            idxScreenLine   += 1;\
        } \
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
        do {\
            DDA_STEP\
            ddaNbIter       -= 1;\
            renCurrentColor = ptrReadTexture [ddaCurrentValue];\
            prim;\
            idxScreenLine   += 1;\
            DDA_STEP\
            ddaNbIter       -= 1;\
            renCurrentColor = ptrReadTexture [ddaCurrentValue];\
            prim;\
            idxScreenLine   += 1;\
        } while ((ddaNbIter > 0) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


// =====================================
// ============ LEFT TEXEL
// =====================================

void drawLeftColumn(){

    PREPARE();

    if (ddaNbStep >= 64) {
        //OVER_SAMPLE(COLOR_LEFT_TEXEL)
        ddaNbIter           = ddaNbStep;
        OVER_SAMPLE_COLOR_LEFT_TEXEL();
    } else {
        ddaNbIter           = ddaNbStep;
        ptrOffsetIndex = &(tabIdxRdTexture[((ddaNbStep+1)*ddaNbStep)/2]);
        nxtOffsetIndex = 0;
        DDA_STEP
        UNROLL_SAMPLE(COLOR_LEFT_TEXEL)
    }
}

// =====================================
// ============ RIGHT TEXEL
// =====================================


void drawRightColumn(){


    PREPARE();

    if (ddaNbStep >= 64){
        // OVER_SAMPLE(COLOR_RIGHT_TEXEL)
        ddaNbIter           = ddaNbStep;
        OVER_SAMPLE_COLOR_RIGHT_TEXEL();
    } else {
        ddaNbIter           = ddaNbStep;
        ptrOffsetIndex = &(tabIdxRdTexture[((ddaNbStep+1)*ddaNbStep)/2]);
        nxtOffsetIndex = 0;
        DDA_STEP
        UNROLL_SAMPLE(COLOR_RIGHT_TEXEL)

    }
}
#ifdef __GNUC__
void clearColumn(){

}
#endif
void drawWalls(){

    idxScreenCol        = VIEWPORT_START_COLUMN;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));

    idxCurrentSlice     = 0;

    do {
        baseAdr             += 1;
        idxScreenCol        += 1;

        clearColumn();

        wallId              = raywall[idxCurrentSlice];

        if (wallId !=255) {
            drawLeftColumn ();
        }

        idxScreenCol        += 1;
        idxCurrentSlice     += 1;

        wallId              = raywall[idxCurrentSlice];

        if (wallId !=255) {
            drawRightColumn();
        }

        idxCurrentSlice++;

    } while (idxCurrentSlice < NUMBER_OF_SLICE-2);
}
#else
extern unsigned char *baseAdr;
extern void drawWalls();
#endif // USE_C_DRAWWALLS