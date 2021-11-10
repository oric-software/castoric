

#include "iea2d.c"
#include "dist.c"


signed char         spriteViewportColIdx, spriteViewportLinIdx;

unsigned char       spriteTextureLinIdx, spriteTextureColIdx;
unsigned char       spriteNbColumn, spriteNbLine;

signed char         savSpriteViewportLinIdx;
unsigned char       savSpriteTextureLinIdx;

// input of Sprite drawing
unsigned char       spriteHeight;
unsigned char       *spriteTexture;
unsigned char       spriteCenterColumn;

int screenOffset;
unsigned char savNbLoopLine;
unsigned char nbLoopColumn, nbLoopLine;


unsigned char       wallheight; // TODO: remove
void(*spriteColorFunction)(void);// TODO: optim 
unsigned char *spritePtrReadTexture;

unsigned char           texcolumn, texline;


//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char           precalTexPixelOffset[100];
unsigned char           idxTexPixel;    // run through precalTexPixelOffset

void precalcTexPixelRunthrough(unsigned char height){

    idxTexPixel         = 0;

    iea2StartValue      = 0;
    iea2NbVal           = TEXTURE_SIZE-1;
    iea2NbStep          = height;
    iea2Init();
    do {
        precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
        (*iea2StepFunction)();
    } while (iea2CurrentValue < iea2EndValue);
    precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
}




// ============================================ //


void unrollColumn() {

        wallheight = TableVerticalPos[spriteViewportColIdx];
        if (spriteHeight > wallheight) {

            spriteTextureLinIdx     = savSpriteTextureLinIdx;
            nbLoopLine              = savNbLoopLine;

            theAdr                  = (unsigned char *)((int)baseAdr + screenOffset ); // multi120[spriteViewportLinIdx]); // 

            // Parcours ligne
            texcolumn               = precalTexPixelOffset [spriteTextureColIdx];
            spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[texcolumn] << 8) | multi32_low[texcolumn]);

            do {

                renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
                if (renCurrentColor != EMPTY_ALPHA) {
                    spriteColorFunction();
                }else{
                   theAdr              += 120; 
                }
                spriteTextureLinIdx       ++;

            } while ((--nbLoopLine) != 0);
        }
}

#define min(x,y)          (((x)<(y))?(x):(y))
void displaySprite03(){

    // Rejoindre la bordure gauche
    if (spriteCenterColumn <= spriteHeight/2) {
        spriteViewportColIdx       = VIEWPORT_START_COLUMN + 1;
        spriteTextureColIdx         = spriteHeight/2 - spriteCenterColumn + 2;
        nbLoopColumn = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteCenterColumn-2);
    } else {
        spriteViewportColIdx       = spriteCenterColumn - spriteHeight/2 + VIEWPORT_START_COLUMN;
        spriteTextureColIdx        = 0;
        nbLoopColumn = min(VIEWPORT_WIDTH-2-spriteCenterColumn+spriteHeight/2,spriteHeight);
    }
    


    if ((spriteViewportColIdx&0x01) != 0){
        spriteColorFunction = &colorLeftTexel;
    } else {
        spriteColorFunction = &colorRightTexel;
    }

    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx    = VIEWPORT_START_LINE + 1;
        savSpriteTextureLinIdx  = spriteHeight/2 - VIEWPORT_HEIGHT/ 2 + 1;
        savNbLoopLine           = VIEWPORT_HEIGHT  - 1;
    } else {
        spriteViewportLinIdx    = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        savSpriteTextureLinIdx  = 0;
        savNbLoopLine           = spriteHeight ;
    }

    screenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        unrollColumn();

        spriteTextureColIdx         += 1;
        spriteViewportColIdx        += 1;

        if ((spriteViewportColIdx&0x01) != 0){
            baseAdr             += 1;
            spriteColorFunction = &colorLeftTexel;
        } else {
            spriteColorFunction = &colorRightTexel;
        }
    } while ((--nbLoopColumn) != 0);
 
}


void displaySpriteRightVisible(){

    spriteViewportColIdx          = spriteCenterColumn;
    spriteTextureColIdx           = spriteHeight-1;
    nbLoopColumn                = spriteCenterColumn-VIEWPORT_START_COLUMN;
    if ((spriteViewportColIdx&0x01) != 0){
        spriteColorFunction = &colorLeftTexel;
    } else {
        spriteColorFunction = &colorRightTexel;
    }
    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx        = VIEWPORT_START_LINE + 1;
        savSpriteTextureLinIdx      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
        savNbLoopLine               = VIEWPORT_HEIGHT  - 1;
    } else {
        savSpriteTextureLinIdx      = 0;
        spriteViewportLinIdx        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        savNbLoopLine               = spriteHeight ;
    }
    screenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        unrollColumn();
        
        spriteTextureColIdx         -= 1;
        spriteViewportColIdx        -= 1;

        if ((spriteViewportColIdx&0x01) != 0){
            spriteColorFunction     = &colorLeftTexel;
        } else {
            baseAdr                 -= 1;
            spriteColorFunction     = &colorRightTexel;
        }

    } while ((--nbLoopColumn) != 0);    
}

void displaySpriteLeftVisible(){

    spriteViewportColIdx        = spriteCenterColumn;
    spriteTextureColIdx         = 0;

    nbLoopColumn                = VIEWPORT_WIDTH-spriteCenterColumn;

    if ((spriteViewportColIdx&0x01) != 0){
        spriteColorFunction         = &colorLeftTexel;
    } else {
        spriteColorFunction         = &colorRightTexel;
    }

    if (spriteHeight > VIEWPORT_HEIGHT){
        spriteViewportLinIdx        = VIEWPORT_START_LINE + 1;
        savSpriteTextureLinIdx      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
        savNbLoopLine               = VIEWPORT_HEIGHT  - 1;
    } else {
        spriteViewportLinIdx        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
        savSpriteTextureLinIdx      = 0;
        savNbLoopLine               = spriteHeight ;
    }

    screenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        unrollColumn();

        spriteTextureColIdx       ++;

        spriteViewportColIdx++;
        if ((spriteViewportColIdx&0x01) != 0){
            baseAdr             += 1;
            spriteColorFunction = &colorLeftTexel;
        } else {
            spriteColorFunction = &colorRightTexel;
        }

    } while ((--nbLoopColumn) != 0);

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

    precalcTexPixelRunthrough(objHeight*2);

    spriteHeight            = objHeight*2;


    if (visibility == 1){
        spriteCenterColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        displaySprite03();
    } else if (visibility == 2) {
        spriteCenterColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
        displaySpriteRightVisible();

    } else if (visibility == 3) {
        spriteCenterColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];
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