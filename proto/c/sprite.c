
#ifdef USE_SPRITE
#include "iea2d.c"
#ifdef __GNUC__
#include <string.h>
#endif


signed char         spriteViewportColIdx, spriteViewportLinIdx;

unsigned char       spriteTextureLinIdx, spriteTextureColIdx;

unsigned char       spriteSavTextureLinIdx;

// input of Sprite drawing
unsigned char       spriteHeight;
unsigned char       *spriteTexture;
unsigned char       spriteRefColumn;

int                 spriteScreenOffset;
unsigned char       spriteSavNbLoopLine;
unsigned char       spriteNbLoopColumn, spriteNbLoopLine;


unsigned char       spriteWallHeight; // TODO: remove

#ifdef USE_C_SPRITE 
unsigned char           *spritePtrReadTexture;
#else
extern unsigned char    *spritePtrReadTexture;
#endif
unsigned char           spriteTexColumn;




//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char           precalTexPixelOffset[100];
unsigned char           idxTexPixel;    // run through precalTexPixelOffset



unsigned char tabSpriteViewportColIdx[OBJECTS_MAX];
unsigned char tabSpriteTextureColIdx[OBJECTS_MAX];
unsigned char tabSpriteNbLoopColumn[OBJECTS_MAX];
unsigned char tabSpriteViewportLinIdx[OBJECTS_MAX];
unsigned char tabSpriteSavTextureLinIdx[OBJECTS_MAX];
unsigned char tabSpriteSavNbLoopLine[OBJECTS_MAX];
unsigned char *tabPrecalTexPixelOffset[OBJECTS_MAX];

extern unsigned char idxCurrentSlice;

unsigned  char *tabPrecalcSpriteOffset;



void precalcSpriteTexPixelRunthrough(){

    // if (spriteHeight > 64) {
    //     idxTexPixel         = 0;

    //     iea2StartValue      = 0;
    //     iea2NbVal           = TEXTURE_SIZE-1;
    //     iea2NbStep          = spriteHeight;


    //     // iea2Init();
    //     iea2CurrentValue         = iea2StartValue;
    //     iea2EndValue             = iea2StartValue + iea2NbVal;
    //     iea2CurrentError     = iea2NbStep;
    //     // iea2StepFunction     = &iea2Step2;

    //     do {
    //         precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;

    //         // (*iea2StepFunction)();
    //         iea2CurrentError         -= iea2NbVal;
    //         if ((iea2CurrentError<<1) < iea2NbStep) {
    //             iea2CurrentError     += iea2NbStep;
    //             iea2CurrentValue     += 1;
    //         }

    //     } while (iea2CurrentValue < iea2EndValue);
    //     precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
    // } else {
    //     memcpy(precalTexPixelOffset, &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]), spriteHeight);
    // }
    tabPrecalTexPixelOffset[engCurrentObjectIdx] = &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]);
}

extern void colorLeftTexel ();
extern void colorRightTexel ();

// ============================================ //
#ifdef USE_C_SPRITE 
void unrollLeftColumn();
void unrollRightColumn();

void spriteDrawColumn() {
    
    if ((objLogDistance[engCurrentObjectIdx] < raylogdist[spriteViewportColIdx-VIEWPORT_START_COLUMN-1])
     || (raywall[spriteViewportColIdx-VIEWPORT_START_COLUMN-1] == 255)) {

        spriteTextureLinIdx     = spriteSavTextureLinIdx;
        spriteNbLoopLine              = spriteSavNbLoopLine;

        theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 

        // Parcours ligne
        spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
        spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);


        if ((spriteViewportColIdx&0x01) != 0){
            unrollLeftColumn();
        } else {
            unrollRightColumn();
        }
    }
}


void unrollRightColumn() {

    do {
        renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
        if (renCurrentColor != EMPTY_ALPHA) {
            colorRightTexel();
        }else{
            theAdr              += 120; 
        }
        spriteTextureLinIdx       ++;
    } while ((--spriteNbLoopLine) != 0);

}

void unrollLeftColumn() {

    do {

        renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
        if (renCurrentColor != EMPTY_ALPHA) {
            colorLeftTexel();
        }else{
            theAdr              += 120; 
        }
        spriteTextureLinIdx       ++;

    } while ((--spriteNbLoopLine) != 0);

}

void prepareScreenAdr(){

    spriteScreenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + 1 + ((spriteViewportColIdx)>>1));

}
#endif // USE_C_SPRITE 




#define min(x,y)          (((x)<(y))?(x):(y))

void prepareDrawSprite (){

    unsigned char visibility;  
    unsigned char   objHeight;
    
    // compute objAngle, objLogDist
    objX = objPosX[engCurrentObjectIdx];
    objY = objPosY[engCurrentObjectIdx];

    visibility = isVisibleSprite();

    // if (visibility == 0) return ;

    if ((objHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;

    

    spriteHeight            = objHeight*2;

    precalcSpriteTexPixelRunthrough();


    if (visibility == 1){
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        // displaySprite03();

        // Rejoindre la bordure gauche
        if (spriteRefColumn <= spriteHeight/2) {
            tabSpriteViewportColIdx[engCurrentObjectIdx]       = VIEWPORT_START_COLUMN + 1;
            tabSpriteTextureColIdx[engCurrentObjectIdx]         = spriteHeight/2 - spriteRefColumn + 2;
            tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteRefColumn-2);
        } else {
            tabSpriteViewportColIdx[engCurrentObjectIdx]       = spriteRefColumn - spriteHeight/2 + VIEWPORT_START_COLUMN;
            tabSpriteTextureColIdx[engCurrentObjectIdx]        = 0;
            tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH-2-spriteRefColumn+spriteHeight/2,spriteHeight);
        }

        if (spriteHeight > VIEWPORT_HEIGHT){
            tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_START_LINE + 1;
            tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = spriteHeight/2 - VIEWPORT_HEIGHT/ 2 + 1;
            tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = VIEWPORT_HEIGHT  - 1;
        } else {
            tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
            tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = 0;
            tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = spriteHeight ;
        }


    } else if (visibility == 2) {
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
        if (spriteRefColumn > VIEWPORT_START_COLUMN) {

            // displaySpriteRightVisible();
            tabSpriteViewportColIdx[engCurrentObjectIdx]          = spriteRefColumn;
            tabSpriteTextureColIdx[engCurrentObjectIdx]           = spriteHeight-1;
            tabSpriteNbLoopColumn[engCurrentObjectIdx]                = spriteRefColumn-VIEWPORT_START_COLUMN;
            // if (spriteNbLoopColumn == 0) return ;

            if (spriteHeight > VIEWPORT_HEIGHT){
                tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
                tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
                tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
            } else {
                tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
                tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
                tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
            }

            tabSpriteViewportColIdx[engCurrentObjectIdx]          -= tabSpriteNbLoopColumn[engCurrentObjectIdx];
            tabSpriteTextureColIdx[engCurrentObjectIdx]           -= tabSpriteNbLoopColumn[engCurrentObjectIdx];
        }
    } else if (visibility == 3) {
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];

        // displaySpriteLeftVisible();
        tabSpriteViewportColIdx[engCurrentObjectIdx]        = spriteRefColumn;
        tabSpriteTextureColIdx[engCurrentObjectIdx]         = 0;

        tabSpriteNbLoopColumn[engCurrentObjectIdx]                = VIEWPORT_WIDTH-spriteRefColumn;

        if (spriteHeight > VIEWPORT_HEIGHT){
            tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
            tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
            tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
        } else {
            tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
            tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
            tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
        }

    }
}

// -VIEWPORT_START_COLUMN-1
void drawSpriteCol(){

    int ii;
    ii= dichoNbVal;
    while (ii >0) {
        ii -= 1;
        engCurrentObjectIdx = tabDichoIdxs[ii];
        spriteTexture = objTexture[engCurrentObjectIdx];
        
        if (
            ((objLogDistance[engCurrentObjectIdx] < raylogdist[idxCurrentSlice])
        || (raywall[idxCurrentSlice] == 255))
        && (tabSpriteNbLoopColumn[engCurrentObjectIdx] != 0)
        && (idxCurrentSlice >= tabSpriteViewportColIdx[engCurrentObjectIdx])
        ) {

            spriteTextureLinIdx     = tabSpriteSavTextureLinIdx[engCurrentObjectIdx];
            spriteNbLoopLine        = tabSpriteSavNbLoopLine[engCurrentObjectIdx];

            // Parcours ligne
            tabPrecalcSpriteOffset = tabPrecalTexPixelOffset[engCurrentObjectIdx];
            spriteTexColumn               = tabPrecalcSpriteOffset [tabSpriteTextureColIdx[engCurrentObjectIdx]];
            spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

            idxVertCol = (tabSpriteViewportLinIdx[engCurrentObjectIdx]-VIEWPORT_START_LINE)*3 ; //(idxScreenLine-VIEWPORT_START_LINE)*3
            if ((idxCurrentSlice&0x01) == 0){
                // unrollLeftColumn();

                do {

                    renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                    if (renCurrentColor != EMPTY_ALPHA) {
                        // colorLeftTexel();
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0x07)|tabLeftRed[renCurrentColor];idxVertCol++;
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0x07)|tabLeftGreen[renCurrentColor];idxVertCol++;
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0x07)|tabLeftBlue[renCurrentColor];idxVertCol++;
                    }else{
                        idxVertCol += 3; 
                    }
                    spriteTextureLinIdx       ++;

                } while ((--spriteNbLoopLine) != 0);


            } else {
                // unrollRightColumn();
                do {
                    renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                    if (renCurrentColor != EMPTY_ALPHA) {
                        // colorRightTexel();
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0xF8)|tabRightRed[renCurrentColor];idxVertCol++;\
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0xF8)|tabRightGreen[renCurrentColor];idxVertCol++;\
                        bufVertCol[idxVertCol]=(bufVertCol[idxVertCol]&0xF8)|tabRightBlue[renCurrentColor];idxVertCol++;

                    }else{
                        idxVertCol += 3;
                    }
                    spriteTextureLinIdx       ++;
                } while ((--spriteNbLoopLine) != 0);

            }

            if ((tabSpriteNbLoopColumn[engCurrentObjectIdx] != 0)) {
                tabSpriteTextureColIdx[engCurrentObjectIdx] += 1;
                tabSpriteNbLoopColumn[engCurrentObjectIdx]  -= 1;
            }

        }

    }
}





void prepareDrawSprites (){
    int ii;
    ii= dichoNbVal;
    while (ii >0) {
        ii -= 1;
        engCurrentObjectIdx = tabDichoIdxs[ii];
        prepareDrawSprite ();
    }

}

#endif // USE_SPRITE