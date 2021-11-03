

#include "iea2d.c"
#include "dist.c"


signed char         spriteViewportColIdx, spriteViewportLinIdx;

unsigned char       spriteTextureLinIdx, spriteTextureColIdx;
unsigned char       spriteNbColumn, spriteNbLine;
unsigned char       wallheight; // TODO: remove
void(*spriteColorFunction)(void);


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



// void displaySprite02(unsigned char column, unsigned char height){

//     // ptrTexture = texture_pillar;
//     precalcTexPixelRunthrough(height);
//     // for (idxTexPixel = 0; idxTexPixel <= iea2NbStep; idxTexPixel ++) {
//     //     printf ("%d\n", precalTexPixelOffset [idxTexPixel]);
//     // }

//     spriteViewportColIdx          = column - height/2 + VIEWPORT_START_COLUMN;
//     spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
//     spriteTextureLinIdx           = 0;
//     spriteTextureColIdx           = 0;

//     spriteNbColumn                = height; // number of column on Screen of the Sprite
//     spriteNbLine                  = height; // number of line on Screen of the Sprite

//     // Rejoindre la bordure gauche
//     while ((spriteViewportColIdx <= VIEWPORT_START_COLUMN) && (spriteNbColumn != 0)) {
//         spriteNbColumn            --;
//         spriteViewportColIdx      ++;
//         spriteTextureColIdx       ++;
//     }
//     if (spriteNbColumn == 0) return ;


//     baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

//     // Parcours colonne
//     do {
// #ifdef DEBUG        
//         printf ("--== drawing column %d (spriteNbColumn = %d) ==-- \n", spriteViewportColIdx, spriteNbColumn);
// #endif
//         // Si Profondeur [colonne] < DistanceObject
//         // On determine ici la colonne du sprite est visible en comparant la hauteur à l'ecran du sprite à celle du 
//         // Cela évite d'utiliser la 
//         // si l'objet du sprite est plus grand ou plus petit que le mur affiche sur cette colonne
//         //          if (rayzbuffer[RaySliceIdx] < DistanceObject) {
//         //          if (raylogdist[RaySliceIdx] < 32*log2(DistanceObject) ){
//         wallheight = TableVerticalPos[spriteViewportColIdx-VIEWPORT_START_COLUMN]; // (100-TableVerticalPos[spriteViewportColIdx])/4;
//         if (height > wallheight) {
//             // Rejoindre la bordure haute de l'ecran
//             spriteTextureLinIdx           = 0;
//             spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE; // TODO : remove
//             spriteNbLine                  = height;  // TODO : remove
//             while ((spriteViewportLinIdx++) < VIEWPORT_START_LINE) {
// #ifdef DEBUG                
//                 printf ("skipped lin %d \n", spriteViewportLinIdx, spriteNbColumn);
// #endif
//                 spriteTextureLinIdx ++;
//             }
//             theAdr              = (unsigned char *)((int)baseAdr + ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx])) ); // multi120[spriteViewportLinIdx]); // 
//             // Parcours ligne
//             do {

//                 // baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));                
//                 // theAdr              = (unsigned char *)(baseAdr + multi120[spriteTextureLinIdx]); 
//                 // Si couleur [ligneTGexture][colonneTexture] != EMPTY
//                 texcolumn           = precalTexPixelOffset [spriteTextureColIdx];
//                 offTexture          = (multi32_high[texcolumn] << 8) | multi32_low[texcolumn];
//                 texline             = precalTexPixelOffset [spriteTextureLinIdx];
//                 renCurrentColor     = ptrTexture[offTexture + texline];
//                 if (renCurrentColor != EMPTY_ALPHA) {
//                     // afficher texel [couleur] a ligneViewport, colonneViewpport
// #ifdef DEBUG                    
//                     printf ("display color %d (= texture [%d, %d]) at position(%d, %d)\n", renCurrentColor, texline, texcolumn, spriteViewportLinIdx, spriteViewportColIdx);
// #endif 
//                     // colorSquare(unsigned char line, unsigned char column, unsigned char theColor);
//                     // printf ("%d %d\n", spriteViewportLinIdx, spriteViewportColIdx);get();
//                     // colorSquare(spriteViewportLinIdx, spriteViewportColIdx, renCurrentColor);
//                     if ((spriteViewportColIdx&0x01) != 0){
//                         colorLeftTexel();
//                     } else {
//                         colorRightTexel();
//                     }
//                 }else{
//                    theAdr              += 120; 
//                 }
//                 spriteTextureLinIdx       ++;
                
//                 // theAdr              += 120;
                
//             // Jusqu'à indice ligne > 64 
//             } while (((++spriteViewportLinIdx) < VIEWPORT_START_LINE+VIEWPORT_HEIGHT) && ((--spriteNbLine) != 0));
//         }
//         spriteTextureColIdx       ++;
//         if ((spriteViewportColIdx&0x01) == 0){
//             baseAdr             += 1;
//         }
//         spriteViewportColIdx++;
//     } while ((spriteViewportColIdx < VIEWPORT_START_COLUMN + VIEWPORT_WIDTH - 2) && ((--spriteNbColumn) > 0));
//     // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  spriteNbColumn = 0


// }

// void drawSprite01 (signed char posX, signed char posY, unsigned char texture[]){

//     signed char     deltaX, deltaY;
//     signed char     alpha;
//     unsigned char   log2Delta;
//     unsigned int    log2dist;
//     unsigned char   height;
//     signed char     column;
//     signed char angle;


//     deltaX          = posX-rayCamPosX;
//     deltaY          = posY-rayCamPosY;
//     if ((deltaX == 0) && (deltaY == 0)) return;
//     alpha           = ATAN2(deltaY, deltaX);
//     angle       = alpha-rayCamRotZ;
//     if (abs(angle) < HALF_FOV_FIX_ANGLE) {
//         // if (lWallsCosBeta[RayCurrentWall] == 0){    // Wall is O,y aligned   
//         //     RayWallLog      = log2_tab[(unsigned char)(abs(lPointsX[RayIdXPoint1]-glCamPosX))];
//         //     tab_denom       = tab_1overcos;
//         // } else {                                    // Wall is O,x aligned
//         //     RayWallLog      = log2_tab[(unsigned char)(abs(lPointsY[RayIdXPoint1]-glCamPosY))];
//         //     tab_denom       = tab_1oversin;
//         // }
//         column = tabAngle2Col[HALF_FOV_FIX_ANGLE-angle];
//         if (abs(deltaX) > abs(deltaY)) {
//             log2Delta = log2_tab[(unsigned char)(abs(deltaX))];
//             // unsigned char dist2hh(unsigned int x)
//             // signed char log2sin(unsigned char x)
//             // signed char log2cos(unsigned char x)
//             // distance = RayWallLog + (unsigned int)tab_denom[(unsigned char)RayAlpha];
            
//             log2dist = log2Delta + (unsigned int)tab_1overcos[(unsigned char)alpha];

//             // if (unfish[column] < log2dist)
//             //     log2dist -= unfish[column];

//         } else {
//             log2Delta = log2_tab[(unsigned char)(abs(deltaY))];
//             log2dist = log2Delta + (unsigned int)tab_1oversin[(unsigned char)alpha];
            


//             // if (unfish[column] < log2dist)
//             //     log2dist -= unfish[column];


//         }
//         height = dist2hh(log2dist); // (100-dist2hh(log2dist))/4;


//         //alpha glCamRotZ
//         ptrTexture = texture ;             // Address of the texture 

//         displaySprite02(column, height*2);
//     } else {
//         // displaySprite02(column, height);
//     }
    
// }





// ============================================ //


void displaySprite03(unsigned char column, unsigned char height, unsigned char texture[]){
// assert height <> 0 


    spriteViewportColIdx          = column - height/2 + VIEWPORT_START_COLUMN;
    spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
    spriteTextureLinIdx           = 0;
    spriteTextureColIdx           = 0;

    spriteNbColumn                = height; // number of column on Screen of the Sprite
    spriteNbLine                  = height; // number of line on Screen of the Sprite



    // Rejoindre la bordure gauche
    while ((spriteViewportColIdx <= VIEWPORT_START_COLUMN) && (spriteNbColumn != 0)) {
        spriteNbColumn            --;
        spriteViewportColIdx      ++;
        spriteTextureColIdx       ++;
    }
    if (spriteNbColumn == 0) return ;


    if ((spriteViewportColIdx&0x01) != 0){
        spriteColorFunction = &colorLeftTexel;
    } else {
        spriteColorFunction = &colorRightTexel;
    }


    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {
        wallheight = TableVerticalPos[spriteViewportColIdx-VIEWPORT_START_COLUMN]; // (100-TableVerticalPos[spriteViewportColIdx])/4;
        if (height > wallheight) {


            // Rejoindre la bordure haute de l'ecran
            spriteTextureLinIdx           = 0;
            spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE; // TODO : remove
            spriteNbLine                  = height;  // TODO : remove
            while ((spriteViewportLinIdx++) < VIEWPORT_START_LINE) {
                spriteTextureLinIdx ++;
            }




            
            theAdr              = (unsigned char *)((int)baseAdr + ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx])) ); // multi120[spriteViewportLinIdx]); // 
            // Parcours ligne
            texcolumn           = precalTexPixelOffset [spriteTextureColIdx];
            offTexture          = (multi32_high[texcolumn] << 8) | multi32_low[texcolumn];
            do {

                texline             = precalTexPixelOffset [spriteTextureLinIdx];
                renCurrentColor     = texture[offTexture + texline];
                if (renCurrentColor != EMPTY_ALPHA) {
                    spriteColorFunction();
                }else{
                   theAdr              += 120; 
                }
                spriteTextureLinIdx       ++;

            // Jusqu'à indice ligne > 64 
            } while (((++spriteViewportLinIdx) < VIEWPORT_START_LINE+VIEWPORT_HEIGHT) && ((--spriteNbLine) != 0));
        }
        spriteTextureColIdx       ++;
        if ((spriteViewportColIdx&0x01) == 0){
            baseAdr             += 1;
        }
        spriteViewportColIdx++;
        if ((spriteViewportColIdx&0x01) != 0){
            spriteColorFunction = &colorLeftTexel;
        } else {
            spriteColorFunction = &colorRightTexel;
        }

    } while ((spriteViewportColIdx < VIEWPORT_START_COLUMN + VIEWPORT_WIDTH - 2) && ((--spriteNbColumn) > 0));
    // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  spriteNbColumn = 0

 
}


void displaySpriteRightVisible(unsigned char column, unsigned char height, unsigned char texture[]){


    spriteViewportColIdx          = column;
    spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
    spriteTextureLinIdx           = 0;
    spriteTextureColIdx           = height-1;

    spriteNbColumn                = height; // number of column on Screen of the Sprite
    spriteNbLine                  = height; // number of line on Screen of the Sprite

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        wallheight = TableVerticalPos[spriteViewportColIdx-VIEWPORT_START_COLUMN]; // (100-TableVerticalPos[spriteViewportColIdx])/4;
        if (height > wallheight) {

            // Rejoindre la bordure haute de l'ecran
            spriteTextureLinIdx           = 0;
            spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE; // TODO : remove
            spriteNbLine                  = height;  // TODO : remove
            while ((spriteViewportLinIdx++) < VIEWPORT_START_LINE) {
                spriteTextureLinIdx ++;
            }




            
            theAdr              = (unsigned char *)((int)baseAdr + ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx])) ); // multi120[spriteViewportLinIdx]); // 

            // Parcours ligne
            texcolumn           = precalTexPixelOffset [spriteTextureColIdx];
            offTexture          = (multi32_high[texcolumn] << 8) | multi32_low[texcolumn];
            do {

                texline             = precalTexPixelOffset [spriteTextureLinIdx];
                renCurrentColor     = texture[offTexture + texline];
                if (renCurrentColor != EMPTY_ALPHA) {
                    if ((spriteViewportColIdx&0x01) != 0){
                        colorLeftTexel();
                    } else {
                        colorRightTexel();
                    }
                }else{
                   theAdr              += 120; 
                }
                spriteTextureLinIdx       ++;
            // Jusqu'à indice ligne > 64 
            } while (((++spriteViewportLinIdx) < VIEWPORT_START_LINE+VIEWPORT_HEIGHT) && ((--spriteNbLine) != 0));
        }
        spriteTextureColIdx       --;
        if ((spriteViewportColIdx&0x01) == 1){
            baseAdr             -= 1;
        }
        spriteViewportColIdx--;
    } while (spriteViewportColIdx > VIEWPORT_START_COLUMN+1 );
    // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  spriteNbColumn = 0

}

void displaySpriteLeftVisible(unsigned char column, unsigned char height, unsigned char texture[]){




    spriteViewportColIdx          = column;
    spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
    spriteTextureLinIdx           = 0;
    spriteTextureColIdx           = 0;

    spriteNbColumn                = height; // number of column on Screen of the Sprite
    spriteNbLine                  = height; // number of line on Screen of the Sprite

    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (spriteViewportColIdx>>1));

    // Parcours colonne
    do {

        wallheight = TableVerticalPos[spriteViewportColIdx-VIEWPORT_START_COLUMN]; // (100-TableVerticalPos[spriteViewportColIdx])/4;
        if (height > wallheight) {
            spriteTextureLinIdx           = 0;
            spriteViewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE; // TODO : remove
            spriteNbLine                  = height;  // TODO : remove
            while ((spriteViewportLinIdx++) < VIEWPORT_START_LINE) {
                spriteTextureLinIdx ++;
            }

            theAdr              = (unsigned char *)((int)baseAdr + ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx])) ); // multi120[spriteViewportLinIdx]); // 
            // Parcours ligne
            texcolumn           = precalTexPixelOffset [spriteTextureColIdx];
            offTexture          = (multi32_high[texcolumn] << 8) | multi32_low[texcolumn];
            do {


                texline             = precalTexPixelOffset [spriteTextureLinIdx];
                renCurrentColor     = texture[offTexture + texline];
                if (renCurrentColor != EMPTY_ALPHA) {
                    if ((spriteViewportColIdx&0x01) != 0){
                        colorLeftTexel();
                    } else {
                        colorRightTexel();
                    }
                }else{
                   theAdr              += 120; 
                }
                spriteTextureLinIdx       ++;
                
            // Jusqu'à indice ligne > 64 
            } while (((++spriteViewportLinIdx) < VIEWPORT_START_LINE+VIEWPORT_HEIGHT) && ((--spriteNbLine) != 0));

        }
        spriteTextureColIdx       ++;
        if ((spriteViewportColIdx&0x01) == 0){
            baseAdr             += 1;
        }
        spriteViewportColIdx++;
    } while ((spriteViewportColIdx < VIEWPORT_START_COLUMN + VIEWPORT_WIDTH - 2) && ((--spriteNbColumn) > 0));
    // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  spriteNbColumn = 0

}



#define min(x,y)          (((x)<(y))?(x):(y))
void drawSprite (){

    signed char     column;
    unsigned char visibility;  

    unsigned char *texture;
    unsigned char   objHeight;
    
    // compute objAngle, objLogDist
    objX = objPosX[engCurrentObjectIdx];
    objY = objPosY[engCurrentObjectIdx];
    visibility = isVisibleSprite();

    if (visibility == 0) return ;

    if ((objHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;

    texture = objTexture[engCurrentObjectIdx];

    // computeLogDist (); 
    precalcTexPixelRunthrough(objHeight*2);

    if (visibility == 1){
        column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        displaySprite03(column, objHeight*2,texture);
    } else if (visibility == 2) {
        column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
        displaySpriteRightVisible(column, objHeight*2,texture);

    } else if (visibility == 3) {
        column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];
        displaySpriteLeftVisible(column, objHeight*2,texture);
    }
// Assert 0 < HALF_FOV_FIX_ANGLE-ATAN2(deltaY, deltaX) -rayCamRotZ < 81 
    // column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle];

    // if (abs(objAngle) < HALF_FOV_FIX_ANGLE) {
    //     column = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle];
    //     // height = dist2hh(objLogDist); 
    //     displaySprite03(column, objHeight*2,texture);
    // }
}


void drawSprites (){
    int ii;
    ii= dichoNbVal;
    while (ii >0) {
        ii -= 1;
        // printf("%d\t", tabDichoIdxs[ii]);
        engCurrentObjectIdx = tabDichoIdxs[ii];
        drawSprite (); //objPosX[engCurrentObjectIdx], objPosY[engCurrentObjectIdx], objTexture[engCurrentObjectIdx]);
    }

}