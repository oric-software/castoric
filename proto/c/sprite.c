

#include "iea2d.c"
#include "dist.c"


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

#ifdef __GNUC__
unsigned char           *spritePtrReadTexture;
#else
extern unsigned char    *spritePtrReadTexture;
#endif
unsigned char           spriteTexColumn;




//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char           precalTexPixelOffset[100];
unsigned char           idxTexPixel;    // run through precalTexPixelOffset

void precalcTexPixelRunthrough(){

    if (spriteHeight > 64) {
        idxTexPixel         = 0;

        iea2StartValue      = 0;
        iea2NbVal           = TEXTURE_SIZE-1;
        iea2NbStep          = spriteHeight;
        iea2Init();
        do {
            precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
            (*iea2StepFunction)();
        } while (iea2CurrentValue < iea2EndValue);
        precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
    } else {
        memcpy(precalTexPixelOffset, &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]), spriteHeight);
    }

}


extern void colorLeftTexel ();
extern void colorRightTexel ();



// ============================================ //

void unrollLeftColumn();
void unrollRightColumn();

void unrollColumn() {

    spriteWallHeight = TableVerticalPos[spriteViewportColIdx];
    if (spriteHeight > spriteWallHeight) {

        spriteTextureLinIdx     = spriteSavTextureLinIdx;
        spriteNbLoopLine              = spriteSavNbLoopLine;

        theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 

        // Parcours ligne
        spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
        spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

        if ((spriteViewportColIdx&0x01) != 0){
            unrollLeftColumnASM();
        } else {
            unrollRightColumnASM();
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

#define min(x,y)          (((x)<(y))?(x):(y))
void displaySprite03(){

    // Rejoindre la bordure gauche
    if (spriteRefColumn <= spriteHeight/2) {
        spriteViewportColIdx       = VIEWPORT_START_COLUMN + 1;
        spriteTextureColIdx         = spriteHeight/2 - spriteRefColumn + 2;
        spriteNbLoopColumn = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteRefColumn-2);
    } else {
        spriteViewportColIdx       = spriteRefColumn - spriteHeight/2 + VIEWPORT_START_COLUMN;
        spriteTextureColIdx        = 0;
        spriteNbLoopColumn = min(VIEWPORT_WIDTH-2-spriteRefColumn+spriteHeight/2,spriteHeight);
    }
    


    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx    = VIEWPORT_START_LINE + 1;
        spriteSavTextureLinIdx  = spriteHeight/2 - VIEWPORT_HEIGHT/ 2 + 1;
        spriteSavNbLoopLine           = VIEWPORT_HEIGHT  - 1;
    } else {
        spriteViewportLinIdx    = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        spriteSavTextureLinIdx  = 0;
        spriteSavNbLoopLine           = spriteHeight ;
    }

    spriteScreenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        // spriteWallHeight = TableVerticalPos[spriteViewportColIdx];
        // if (spriteHeight > spriteWallHeight) {

        //     spriteTextureLinIdx     = spriteSavTextureLinIdx;
        //     spriteNbLoopLine              = spriteSavNbLoopLine;

        //     theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 

        //     // Parcours ligne
        //     spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
        //     spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

        //     if ((spriteViewportColIdx&0x01) != 0){
        //         unrollLeftColumn();
        //     } else {
        //         unrollRightColumn();
        //     }
        // }

        unrollColumn();

        spriteTextureColIdx         += 1;
        spriteViewportColIdx        += 1;

        if ((spriteViewportColIdx&0x01) != 0){
            baseAdr             += 1;
        }
    } while ((--spriteNbLoopColumn) != 0);
 
}


void displaySpriteRightVisible(){

    spriteViewportColIdx          = spriteRefColumn;
    spriteTextureColIdx           = spriteHeight-1;
    spriteNbLoopColumn                = spriteRefColumn-VIEWPORT_START_COLUMN;
    // if (spriteNbLoopColumn == 0) return ;

    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx        = VIEWPORT_START_LINE + 1;
        spriteSavTextureLinIdx      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
        spriteSavNbLoopLine               = VIEWPORT_HEIGHT  - 1;
    } else {
        spriteSavTextureLinIdx      = 0;
        spriteViewportLinIdx        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        spriteSavNbLoopLine               = spriteHeight ;
    }
    spriteScreenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        // spriteWallHeight = TableVerticalPos[spriteViewportColIdx];
        // if (spriteHeight > spriteWallHeight) {

        //     spriteTextureLinIdx     = spriteSavTextureLinIdx;
        //     spriteNbLoopLine              = spriteSavNbLoopLine;

        //     theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 

        //     // Parcours ligne
        //     spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
        //     spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

        //     if ((spriteViewportColIdx&0x01) != 0){
        //         unrollLeftColumn();
        //     } else {
        //         unrollRightColumn();
        //     }
        // }

        unrollColumn();

        spriteTextureColIdx         -= 1;
        spriteViewportColIdx        -= 1;

        if ((spriteViewportColIdx&0x01) == 0){
            baseAdr                 -= 1;
        }

    } while ((--spriteNbLoopColumn) != 0);    
}

void displaySpriteLeftVisible(){

    spriteViewportColIdx        = spriteRefColumn;
    spriteTextureColIdx         = 0;

    spriteNbLoopColumn                = VIEWPORT_WIDTH-spriteRefColumn;

    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx        = VIEWPORT_START_LINE + 1;
        spriteSavTextureLinIdx      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
        spriteSavNbLoopLine               = VIEWPORT_HEIGHT  - 1;
    } else {
        spriteViewportLinIdx        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        spriteSavTextureLinIdx      = 0;
        spriteSavNbLoopLine               = spriteHeight ;
    }

    spriteScreenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        // spriteWallHeight = TableVerticalPos[spriteViewportColIdx];
        // if (spriteHeight > spriteWallHeight) {

        //     spriteTextureLinIdx     = spriteSavTextureLinIdx;
        //     spriteNbLoopLine              = spriteSavNbLoopLine;

        //     theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 

        //     // Parcours ligne
        //     spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
        //     spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);

        //     if ((spriteViewportColIdx&0x01) != 0){
        //         unrollLeftColumn();
        //     } else {
        //         unrollRightColumn();
        //     }
        // }

        unrollColumn();

        spriteTextureColIdx       ++;

        spriteViewportColIdx++;
        if ((spriteViewportColIdx&0x01) != 0){
            baseAdr             += 1;
        }

    } while ((--spriteNbLoopColumn) != 0);

}

void drawSprite (){

    unsigned char visibility;  
    unsigned char   objHeight;
    
    // compute objAngle, objLogDist
    objX = objPosX[engCurrentObjectIdx];
    objY = objPosY[engCurrentObjectIdx];

    visibility = isVisibleSprite();

    if (visibility == 0) return ;

    if ((objHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;

    spriteTexture = objTexture[engCurrentObjectIdx];

    spriteHeight            = objHeight*2;

    precalcTexPixelRunthrough();



    if (visibility == 1){
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        displaySprite03();
    } else if (visibility == 2) {
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
        if (spriteRefColumn > VIEWPORT_START_COLUMN) {
            displaySpriteRightVisible();
        }
    } else if (visibility == 3) {
        spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];
        displaySpriteLeftVisible();
    }
}


void drawSprites (){
    int ii;
    ii= dichoNbVal;
    while (ii >0) {
        ii -= 1;
        engCurrentObjectIdx = tabDichoIdxs[ii];
        drawSprite ();
    }

}