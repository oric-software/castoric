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
unsigned  char *tabPrecalcSpriteOffset;
#else
extern unsigned char    *spritePtrReadTexture;
extern unsigned  char *tabPrecalcSpriteOffset;
#endif
unsigned char           spriteTexColumn;




//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char           precalTexPixelOffset[256];
unsigned char           idxTexPixel;    // run through precalTexPixelOffset



unsigned char tabSpriteViewportColIdx[OBJECTS_MAX];
unsigned char tabSpriteTextureColIdx[OBJECTS_MAX];
unsigned char tabSpriteNbLoopColumn[OBJECTS_MAX];
unsigned char tabSpriteViewportLinIdx[OBJECTS_MAX];
unsigned char tabSpriteSavTextureLinIdx[OBJECTS_MAX];
unsigned char tabSpriteSavNbLoopLine[OBJECTS_MAX];
unsigned char *tabPrecalTexPixelOffset[OBJECTS_MAX];

extern unsigned char idxCurrentSlice;



unsigned char   theVisibility;  
unsigned char   theObjHeight;
unsigned char unCompteur;


// void precalcSpriteTexPixelRunthrough(){

//     if (spriteHeight >= 64) {
//         // idxTexPixel         = 0;

//         // iea2StartValue      = 0;
//         // iea2NbVal           = TEXTURE_SIZE-1;
//         // iea2NbStep          = spriteHeight;

//         // iea2CurrentValue         = iea2StartValue;
//         // iea2EndValue             = iea2StartValue + iea2NbVal;
//         // iea2CurrentError     = iea2NbStep;


//         {asm(
//             "lda #0:"
//             "sta _idxTexPixel: sta _iea2StartValue: "
//             "lda #TEXTURE_SIZE-1: sta _iea2NbVal:"
//             "lda _spriteHeight: sta _iea2NbStep:"
//             "lda _iea2StartValue: sta _iea2CurrentValue:"
//             "clc: adc _iea2NbVal: sta _iea2EndValue:"
//             "lda _iea2NbStep: sta _iea2CurrentError:"
//         );}


//         do {
//             // precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
//             // iea2CurrentError         -= iea2NbVal;
//             // if ((iea2CurrentError<<1) < iea2NbStep) {
//             //     iea2CurrentError     += iea2NbStep;
//             //     iea2CurrentValue     += 1;
//             // }
//             {asm(
//                 "ldy _idxTexPixel: lda _iea2CurrentValue: sta _precalTexPixelOffset,y :iny: sty _idxTexPixel:"
//                 "lda _iea2CurrentError: sec: sbc _iea2NbVal: sta _iea2CurrentError:"
//                 ":.(:bmi updateError:"
//                 "asl:"
//                 "cmp _iea2NbStep:"
//                 "bcc updateError: jmp endUpdateError:"
//                 "updateError:"
//                 "lda _iea2CurrentError: clc: adc _iea2NbStep: sta _iea2CurrentError:"
//                 "inc _iea2CurrentValue:"
//                 "endUpdateError:.):"
//             );}



//         } while (iea2CurrentValue < iea2EndValue);

//         // precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
//         {asm(
//             "ldy _idxTexPixel: lda _iea2CurrentValue: sta _precalTexPixelOffset,y: iny: sty _idxTexPixel:"
//         );}
//         // tabPrecalTexPixelOffset[engCurrentObjectIdx] = precalTexPixelOffset; // &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]);
//         {asm(
//             "lda _engCurrentObjectIdx: asl: tay:"
//             "lda #<(_precalTexPixelOffset): sta _tabPrecalTexPixelOffset,y:"
//             "iny:"
//             "lda #>(_precalTexPixelOffset):"
//             "sta _tabPrecalTexPixelOffset,y:"
//         );}

//     } else {
//         // memcpy(precalTexPixelOffset, &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]), spriteHeight);
//         tabPrecalTexPixelOffset[engCurrentObjectIdx] = &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)>>1]);
//     }
// }


extern void colorLeftTexel ();
extern void colorRightTexel ();


#define min(x,y)          (((x)<(y))?(x):(y))



// void prepareDrawSprite(){

    
//     // compute objAngle, objLogDist
//     // objX = objPosX[engCurrentObjectIdx];
//     // objY = objPosY[engCurrentObjectIdx];
//     {asm(
//         "ldy _engCurrentObjectIdx:"
//         "lda _objPosX,y:"
//         "sta _objX:"
//         "lda _objPosY,y:"
//         "sta _objY:"
//     );}

//     theVisibility = isVisibleSprite();

//     if ((theObjHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;
   

//     // spriteHeight            = theObjHeight*2;
//     {asm(
//         "lda _theObjHeight:"
//         "asl:"
//         "sta _spriteHeight:"
//     );}


//     precalcSpriteTexPixelRunthrough();


//     if (theVisibility == 1){
//         // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
//         {asm(
//             "ldy _engCurrentObjectIdx: lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngle,y: tay: lda _tabAngle2Col,y:"
//             "sta _spriteRefColumn:"
//         );}


//         // Rejoindre la bordure gauche
//         if (spriteRefColumn <= spriteHeight/2) {
//             // tabSpriteViewportColIdx[engCurrentObjectIdx]       = 0 ; // VIEWPORT_START_COLUMN + 1;
//             {asm(
//                 "lda #0: ldy _engCurrentObjectIdx: sta _tabSpriteViewportColIdx,y:"
//                 ""
//             );}
//             // tabSpriteTextureColIdx[engCurrentObjectIdx]         = spriteHeight/2 - spriteRefColumn + 2;
//             {asm(
//                 "lda _spriteHeight: lsr: clc: adc #2: sec: sbc _spriteRefColumn:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteTextureColIdx,y:" // TODO: Remove loading of engCurrentObjectIdx cause it is already loaded
//             );}

//             // tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteRefColumn-2);
//             {asm(
//                 "lda _spriteHeight: lsr: clc: adc _spriteRefColumn : sec: sbc #2:"
//                 ".(:cmp #VIEWPORT_WIDTH - 3:bcc skip:lda #VIEWPORT_WIDTH - 3"
//                 ":skip:.):ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y:"
//             );}

//         } else {
//             // tabSpriteViewportColIdx[engCurrentObjectIdx]       = spriteRefColumn - spriteHeight/2; // + VIEWPORT_START_COLUMN;
//             {asm(
//                 "lda _spriteHeight: lsr: eor #$FF: sec: adc #1: clc: adc _spriteRefColumn:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportColIdx,y:"
//             );}
//             // tabSpriteTextureColIdx[engCurrentObjectIdx]        = 0;
//             {asm(
//                 "lda #0: ldy _engCurrentObjectIdx: sta _tabSpriteTextureColIdx,y:"
//             );}
//             // tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH-2-spriteRefColumn+spriteHeight/2,spriteHeight);
//             {asm(
//                 "lda _spriteHeight: lsr: clc: adc #VIEWPORT_WIDTH-2: sec: sbc _spriteRefColumn:"
//                 ".(:cmp _spriteHeight: bcc skip: lda _spriteHeight :skip:.):"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y:"
//             );}
//         }

//         if (spriteHeight > VIEWPORT_HEIGHT){
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_START_LINE + 1;
//             {asm(
//                 "lda #VIEWPORT_START_LINE+1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = spriteHeight/2 - VIEWPORT_HEIGHT/ 2 + 1;
//             {asm(
//                 "lda _spriteHeight:lsr: sec:"
//                 "sbc #VIEWPORT_HEIGHT/2:"
//                 "clc: adc #1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = VIEWPORT_HEIGHT  - 1;
//             {asm(
//                 "lda #VIEWPORT_HEIGHT-1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         } else {
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
//             {asm(
//                 "lda _spriteHeight: lsr: eor #$FF: clc: adc #1: clc: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = 0;
//             {asm(
//                 "lda #0:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = spriteHeight ;
//             {asm(
//                 "lda _spriteHeight:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         }


//     } else if (theVisibility == 2) {
//         // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
//         {asm(
//             "lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngleRight:tay:lda _tabAngle2Col,y:"
//             "sta _spriteRefColumn:"
//         );}
       

//         // displaySpriteRightVisible();
//         // tabSpriteViewportColIdx[engCurrentObjectIdx]          = 0; 
//         // tabSpriteTextureColIdx[engCurrentObjectIdx]           = spriteHeight-spriteRefColumn-1;
//         // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = spriteRefColumn; // spriteRefColumn-VIEWPORT_START_COLUMN;
//         {asm(
//             "ldy _engCurrentObjectIdx:"
//             "lda #0:"
//             "sta _tabSpriteViewportColIdx,y:"
//             "lda _spriteHeight: sec: sbc _spriteRefColumn: sec : sbc #1 :"
//             "sta _tabSpriteTextureColIdx,y:"
//             "lda _spriteRefColumn:"
//             "sta _tabSpriteNbLoopColumn,y:"
//         );}


//         if (spriteHeight > VIEWPORT_HEIGHT){
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
//             {asm(
//                 "lda #VIEWPORT_START_LINE + 1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
//             {asm(
//                 "lda _spriteHeight: lsr: sec: sbc #VIEWPORT_HEIGHT/2:clc: adc #1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
//             {asm(
//                 "lda #VIEWPORT_HEIGHT-1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         } else {
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
//             {asm(
//                 "lda #0:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
//             {asm(
//                 "lda _spriteHeight: lsr: eor #$FF: clc: adc #1: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
//             {asm(
//                 "lda _spriteHeight:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         }


//     } else if (theVisibility == 3) {
//         // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];
//         {asm(
//             "lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngleLeft: tay: lda _tabAngle2Col,y:"
//             "sta _spriteRefColumn:"
//         );}

//         // tabSpriteViewportColIdx[engCurrentObjectIdx]        = spriteRefColumn;
//         // tabSpriteTextureColIdx[engCurrentObjectIdx]         = 0;
//         // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = VIEWPORT_WIDTH-spriteRefColumn;
//         {asm(
//             "ldy _engCurrentObjectIdx:"
//             "lda _spriteRefColumn:"
//             "sta _tabSpriteViewportColIdx,y:"
//             "lda #0:"
//             "sta _tabSpriteTextureColIdx,y:"
//             "lda #VIEWPORT_WIDTH: sec: sbc _spriteRefColumn:"
//             "sta _tabSpriteNbLoopColumn,y:"
//         );}



//         if (spriteHeight > VIEWPORT_HEIGHT){
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
//             {asm(
//                 "lda #VIEWPORT_START_LINE+1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
//             {asm(
//                 "lda _spriteHeight: lsr: sec: sbc #VIEWPORT_HEIGHT/2+1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
//             {asm(
//                 "lda #VIEWPORT_HEIGHT-1:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         } else {
//             // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
//             {asm(
//                 "lda _spriteHeight: lsr: eor #$FF: clc: adc #1: clc: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y:"
//             );}
//             // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
//             {asm(
//                 "lda #0:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y:"
//             );}
//             // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
//             {asm(
//                 "lda _spriteHeight:"
//                 "ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y:"
//             );}
//         }

//     } else {
//         // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = 0;
//         {asm(
//             "lda #0:"
//             "ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y:"
//         );}
        
//     }
// }

#ifdef USE_C_SPRITE


void precalcSpriteTexPixelRunthrough(){

    if (spriteHeight >= 64) {
        idxTexPixel         = 0;

        iea2StartValue      = 0;
        iea2NbVal           = TEXTURE_SIZE-1;
        iea2NbStep          = spriteHeight;


        // iea2Init();
        iea2CurrentValue         = iea2StartValue;
        iea2EndValue             = iea2StartValue + iea2NbVal;
        iea2CurrentError     = iea2NbStep;
        // iea2StepFunction     = &iea2Step2;

        do {
            precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;

            // (*iea2StepFunction)();
            iea2CurrentError         -= iea2NbVal;
            if ((iea2CurrentError<<1) < iea2NbStep) {
                iea2CurrentError     += iea2NbStep;
                iea2CurrentValue     += 1;
            }

        } while (iea2CurrentValue < iea2EndValue);
        precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
        tabPrecalTexPixelOffset[engCurrentObjectIdx] = precalTexPixelOffset; // &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]);

    } else {
        // memcpy(precalTexPixelOffset, &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]), spriteHeight);
        tabPrecalTexPixelOffset[engCurrentObjectIdx] = &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]);
    }
}

void prepareDrawSprite (){

    
    // compute objAngle, objLogDist
    objX = objPosX[engCurrentObjectIdx];
    objY = objPosY[engCurrentObjectIdx];

    theVisibility = isVisibleSprite();

    if ((theObjHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;
   

    spriteHeight            = theObjHeight*2;

    precalcSpriteTexPixelRunthrough();


    if (theVisibility == 1){
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        // displaySprite03();

        // Rejoindre la bordure gauche
        if (spriteRefColumn <= spriteHeight/2) {
            tabSpriteViewportColIdx[engCurrentObjectIdx]       = 0 ; // VIEWPORT_START_COLUMN + 1;
            tabSpriteTextureColIdx[engCurrentObjectIdx]         = spriteHeight/2 - spriteRefColumn + 2;
            tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteRefColumn-2);
        } else {
            tabSpriteViewportColIdx[engCurrentObjectIdx]       = spriteRefColumn - spriteHeight/2; // + VIEWPORT_START_COLUMN;
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


    } else if (theVisibility == 2) {
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];

        // displaySpriteRightVisible();
        tabSpriteViewportColIdx[engCurrentObjectIdx]          = 0; 
        tabSpriteTextureColIdx[engCurrentObjectIdx]           = spriteHeight-spriteRefColumn-1;
        tabSpriteNbLoopColumn[engCurrentObjectIdx]                = spriteRefColumn; // spriteRefColumn-VIEWPORT_START_COLUMN;
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


    } else if (theVisibility == 3) {
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

    } else {
        tabSpriteNbLoopColumn[engCurrentObjectIdx]                = 0;
    }
}


void prepareDrawSprites (){

    unCompteur= dichoNbVal;
    while (unCompteur >0) {
        unCompteur -= 1;
        engCurrentObjectIdx = tabDichoIdxs[unCompteur];
        prepareDrawSprite ();
        
    }
}


void drawSpriteCol(){

    unCompteur= dichoNbVal;
    while (unCompteur >0) {
        unCompteur -= 1;
        engCurrentObjectIdx = tabDichoIdxs[unCompteur];
        spriteTexture = objTexture[engCurrentObjectIdx];

        if ((tabSpriteNbLoopColumn[engCurrentObjectIdx] != 0)
            && (idxCurrentSlice >= tabSpriteViewportColIdx[engCurrentObjectIdx]) ) {

            if (
                (objLogDistance[engCurrentObjectIdx] < raylogdist[idxCurrentSlice])
            || (raywall[idxCurrentSlice] == 255)) {

                spriteTextureLinIdx     = tabSpriteSavTextureLinIdx[engCurrentObjectIdx];
                spriteNbLoopLine        = tabSpriteSavNbLoopLine[engCurrentObjectIdx];
                idxBufVertCol = tabSpriteViewportLinIdx[engCurrentObjectIdx]-VIEWPORT_START_LINE;

                // Parcours ligne
                tabPrecalcSpriteOffset = tabPrecalTexPixelOffset[engCurrentObjectIdx];

                spriteTexColumn               = tabPrecalcSpriteOffset [tabSpriteTextureColIdx[engCurrentObjectIdx]];

                spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

                if ((idxCurrentSlice&0x01) == 0){
                    // unrollLeftColumn();
                    do {

                        renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                        if (renCurrentColor != EMPTY_ALPHA) {
                            bufVertColLeft[idxBufVertCol] = renCurrentColor;
                        }
                        idxBufVertCol += 1;
                        spriteTextureLinIdx       ++;
                    } while ((--spriteNbLoopLine) != 0);
                } else {
                    // unrollRightColumn();
                    do {
                        renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                        if (renCurrentColor != EMPTY_ALPHA) {
                            bufVertColRight[idxBufVertCol] = renCurrentColor;
                        }
                        idxBufVertCol               += 1;
                        spriteTextureLinIdx       ++;
                    } while ((--spriteNbLoopLine) != 0);
                }
            }
            tabSpriteTextureColIdx[engCurrentObjectIdx] += 1;
            tabSpriteNbLoopColumn[engCurrentObjectIdx]  -= 1;
        }
    }
}

#endif // USE_C_SPRITE

