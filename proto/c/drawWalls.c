#include "config.h"

#include "dda.c"

extern unsigned int offTexture;
extern unsigned char *     ptrTexture;             // Address of the texture 
#ifdef USE_C_DRAWWALLS


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
// IN, 
//   idxCurrentSlice,
//   wallId
// OUT
// 
    columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1); // modulo 32
    offTexture          = (multi32_high[columnTextureCoord] << 8) | multi32_low[columnTextureCoord];

    ptrTexture          = (unsigned char *)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]);

    ptrReadTexture      = &(ptrTexture[offTexture]);
    
    columnHeight        = TableVerticalPos[idxCurrentSlice]; 

    ddaNbStep           = columnHeight<<1;

    // ddaInit();
    ddaCurrentValue         = 0;

    idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;

    if (TEXTURE_SIZE > ddaNbStep) {
        ddaCurrentError     = TEXTURE_SIZE;
        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_1;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine])); 
        do {
            DDA_STEP_1;
            renCurrentColor = ptrReadTexture[ddaCurrentValue];
            COLOR_LEFT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

    } else if   (TEXTURE_SIZE < ddaNbStep) {
        ddaCurrentError     = ddaNbStep;

        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_2;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine])); 
        do {
            DDA_STEP_2;
            renCurrentColor = ptrReadTexture[ddaCurrentValue];
            COLOR_LEFT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

    } else {
        ddaCurrentError     = TEXTURE_SIZE;
        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_0;
            idxScreenLine           += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine])); 
        do {
            DDA_STEP_0;
            renCurrentColor         = ptrReadTexture[ddaCurrentValue];
            COLOR_LEFT_TEXEL;
            idxScreenLine           += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

    }
}

// =====================================
// ============ RIGHT TEXEL
// =====================================

void drawRightColumn(){


    ptrTexture          = (unsigned char *)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]);

    columnHeight        = TableVerticalPos[idxCurrentSlice];

    columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);  // modulo 32
    offTexture          = (multi32_high[columnTextureCoord] << 8) | multi32_low[columnTextureCoord];
    
    ptrTexture          = (unsigned char*)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]); // wallTexture[wallId];

    ptrReadTexture      = &(ptrTexture[offTexture]);
    
    idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;

    ddaNbStep           = columnHeight<<1;



    // ddaInit();

    ddaCurrentValue         = 0; // ddaStartValue;

    if  (TEXTURE_SIZE > ddaNbStep) {
        ddaCurrentError     = TEXTURE_SIZE;

        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_1;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));

        do {
            DDA_STEP_1;

            renCurrentColor = ptrReadTexture [ddaCurrentValue];

            COLOR_RIGHT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

    } else if   (TEXTURE_SIZE < ddaNbStep) {
        ddaCurrentError     = ddaNbStep;
        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_2;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));

        do {
            DDA_STEP_2;
            renCurrentColor = ptrReadTexture [ddaCurrentValue];
            COLOR_RIGHT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


    } else {
        ddaCurrentError     = TEXTURE_SIZE;

        while (idxScreenLine < VIEWPORT_START_LINE){
            DDA_STEP_0;
            idxScreenLine   += 1;
        } 
        theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));
        do {
            DDA_STEP_0;
            renCurrentColor = ptrReadTexture [ddaCurrentValue];
            COLOR_RIGHT_TEXEL;
            idxScreenLine   += 1;
        } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

    }

}

void drawWalls(){


    // ddaNbVal            = TEXTURE_SIZE;
    idxScreenCol        = VIEWPORT_START_COLUMN-1;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
    // ddaStartValue       = 0;
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