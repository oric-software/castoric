#include "config.h"

#include "dda.c"

extern unsigned int offTexture;
extern unsigned char *     ptrTexture;             // Address of the texture 
#ifdef USE_C_DRAWWALLS


#define PREPARE    columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);\
    offTexture          = (multi32_high[columnTextureCoord] << 8) | multi32_low[columnTextureCoord];\
    ptrTexture          = (unsigned char *)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]);\
    ptrReadTexture      = &(ptrTexture[offTexture]);\
    columnHeight        = TableVerticalPos[idxCurrentSlice];\
    ddaNbStep           = columnHeight<<1;\
    idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;\
    ddaCurrentValue     = 0;


// #define COLOR_LEFT_TEXEL colorLeftTexel()
#define COLOR_LEFT_TEXEL  *theAdr = tabLeftRed[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr = tabLeftGreen[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr = tabLeftBlue[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;


// #define COLOR_RIGHT_TEXEL colorRightTexel()
#define COLOR_RIGHT_TEXEL *theAdr |= tabRightRed[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr |= tabRightGreen[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;\
    *theAdr |= tabRightBlue[renCurrentColor];theAdr += NEXT_SCANLINE_INCREMENT;

#define DDA_STEP_0 ddaCurrentValue         += 1;

#define DDA_STEP_1  while ((ddaCurrentError<<1) >= ddaNbStep) {\
                ddaCurrentError         -= ddaNbStep;\
                ddaCurrentValue         += 1;\
            }\
            ddaCurrentError     += TEXTURE_SIZE;


#define DDA_STEP_2  ddaCurrentError         -= TEXTURE_SIZE;\
            if ((ddaCurrentError<<1) < ddaNbStep) {\
                ddaCurrentError     += ddaNbStep;\
                ddaCurrentValue     += 1;\
            }


#define UNDER_SAMPLE(prim)         ddaCurrentError     = TEXTURE_SIZE;\
        while (idxScreenLine < VIEWPORT_START_LINE){\
            DDA_STEP_1;\
            idxScreenLine   += 1;\
        } \
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
        do {\
            DDA_STEP_1;\
            renCurrentColor = ptrReadTexture [ddaCurrentValue];\
            prim;\
            idxScreenLine   += 1;\
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

#define OVER_SAMPLE(prim) ddaCurrentError     = ddaNbStep;\
        while (idxScreenLine < VIEWPORT_START_LINE){\
            DDA_STEP_2;\
            idxScreenLine   += 1;\
        } \
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
        do {\
            DDA_STEP_2;\
            renCurrentColor = ptrReadTexture [ddaCurrentValue];\
            prim;\
            idxScreenLine   += 1;\
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

#define COPY_SAMPLE(prim)         ddaCurrentError     = TEXTURE_SIZE;\
        while (idxScreenLine < VIEWPORT_START_LINE){\
            DDA_STEP_0;\
            idxScreenLine   += 1;\
        } \
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
        do {\
            DDA_STEP_0;\
            renCurrentColor = ptrReadTexture [ddaCurrentValue];\
            prim;\
            idxScreenLine   += 1;\
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


unsigned char *     ptrReadTexture;             // Address of the texture 
unsigned char       idxCurrentSlice;
unsigned char *     baseAdr;
signed char         idxScreenLine, idxScreenCol;
unsigned char       columnHeight, columnTextureCoord;
unsigned char       wallId;


// =====================================
// ============ LEFT TEXEL
// =====================================

void drawLeftColumn(){

    PREPARE;

    if (TEXTURE_SIZE > ddaNbStep) {
        UNDER_SAMPLE(COLOR_LEFT_TEXEL)
    } else if   (TEXTURE_SIZE < ddaNbStep) {
        OVER_SAMPLE(COLOR_LEFT_TEXEL)
    } else {
        COPY_SAMPLE(COLOR_LEFT_TEXEL)
    }
}

// =====================================
// ============ RIGHT TEXEL
// =====================================


void drawRightColumn(){


    PREPARE;

    if  (TEXTURE_SIZE > ddaNbStep) {
        UNDER_SAMPLE(COLOR_RIGHT_TEXEL)
    } else if   (TEXTURE_SIZE < ddaNbStep) {
        OVER_SAMPLE(COLOR_RIGHT_TEXEL)
    } else {
        COPY_SAMPLE(COLOR_RIGHT_TEXEL)
    }

}

void drawWalls(){

    idxScreenCol        = VIEWPORT_START_COLUMN-1;
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