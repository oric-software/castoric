

#include "iea2d.c"


unsigned char           texcolumn, texline;


//precalTexPixelOffset[N] =  Nth value of Incremental Error Algo (nbStep = Height on screen , nbVal = TEXTURE_DIMENSION)
unsigned char           precalTexPixelOffset[80];
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



void displaySprite02(unsigned char column, unsigned char height){

    signed char         viewportColIdx, viewportLinIdx;

    unsigned char       idxLinTexture, idxColTexture;
    unsigned char       nbColumn, nbLine;
    unsigned char       wallheight;

    int adrScreenCol        = 0;
    int adrScreenWrt        = 0;

    // ptrTexture = texture_pillar;
    precalcTexPixelRunthrough(height);
    // for (idxTexPixel = 0; idxTexPixel <= iea2NbStep; idxTexPixel ++) {
    //     printf ("%d\n", precalTexPixelOffset [idxTexPixel]);
    // }

    viewportColIdx          = column - height/2 + VIEWPORT_START_COLUMN;
    viewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
    idxLinTexture           = 0;
    idxColTexture           = 0;
    adrScreenCol            = 0;
    adrScreenWrt            = 0;
    nbColumn                = height; // number of column on Screen of the Sprite
    nbLine                  = height; // number of line on Screen of the Sprite

    // Rejoindre la bordure gauche
    while ((viewportColIdx < VIEWPORT_START_COLUMN) && (nbColumn != 0)) {
        nbColumn            --;
        viewportColIdx      ++;
        idxColTexture       ++;
#ifdef DEBUG
        printf ("skipped column %d (nbColumn = %d)\n", viewportColIdx, nbColumn);
#endif
    }
    if (nbColumn == 0) return ;


    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (viewportColIdx>>1));

    // Parcours colonne
    do {
#ifdef DEBUG        
        printf ("--== drawing column %d (nbColumn = %d) ==-- \n", viewportColIdx, nbColumn);
#endif
        // Si Profondeur [colonne] < DistanceObject
        // On determine ici la colonne du sprite est visible en comparant la hauteur à l'ecran du sprite à celle du 
        // Cela évite d'utiliser la 
        // si l'objet du sprite est plus grand ou plus petit que le mur affiche sur cette colonne
        //          if (rayzbuffer[RaySliceIdx] < DistanceObject) {
        //          if (raylogdist[RaySliceIdx] < 32*log2(DistanceObject) ){
        wallheight = TableVerticalPos[viewportColIdx]; // (100-TableVerticalPos[viewportColIdx])/4;
        if (height > wallheight) {
            // Rejoindre la bordure haute de l'ecran
            idxLinTexture           = 0;
            viewportLinIdx          = VIEWPORT_HEIGHT/ 2 - height/2 + VIEWPORT_START_LINE;
            nbLine                  = height;
            while ((viewportLinIdx++) < VIEWPORT_START_LINE) {
#ifdef DEBUG                
                printf ("skipped lin %d \n", viewportLinIdx, nbColumn);
#endif
                idxLinTexture ++;
            }
            theAdr              = (unsigned char *)((int)baseAdr + ((int)(multi120_high[viewportLinIdx]<<8) | (int)(multi120_low[viewportLinIdx])) ); // multi120[viewportLinIdx]); // 
            // Parcours ligne
            do {

                // baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));                
                // theAdr              = (unsigned char *)(baseAdr + multi120[idxLinTexture]); 
                // Si couleur [ligneTGexture][colonneTexture] != EMPTY
                texcolumn           = precalTexPixelOffset [idxColTexture];
                offTexture          = (multi32_high[texcolumn] << 8) | multi32_low[texcolumn];
                texline             = precalTexPixelOffset [idxLinTexture];
                renCurrentColor     = ptrTexture[offTexture + texline];
                if (renCurrentColor != EMPTY_ALPHA) {
                    // afficher texel [couleur] a ligneViewport, colonneViewpport
#ifdef DEBUG                    
                    printf ("display color %d (= texture [%d, %d]) at position(%d, %d)\n", renCurrentColor, texline, texcolumn, viewportLinIdx, viewportColIdx);
#endif 
                    // colorSquare(unsigned char line, unsigned char column, unsigned char theColor);
                    // printf ("%d %d\n", viewportLinIdx, viewportColIdx);get();
                    // colorSquare(viewportLinIdx, viewportColIdx, renCurrentColor);
                    if ((viewportColIdx&0x01) != 0){
                        colorLeftTexel();
                    } else {
                        colorRightTexel();
                    }
                }else{
                   theAdr              += 120; 
                }
                idxLinTexture       ++;
                
                // theAdr              += 120;
                
            // Jusqu'à indice ligne > 64 
            } while (((++viewportLinIdx) < VIEWPORT_START_LINE+VIEWPORT_HEIGHT) && ((--nbLine) != 0));
        }
        idxColTexture       ++;
        if ((viewportColIdx&0x01) == 0){
            baseAdr             += 1;
        }
    } while (((++viewportColIdx) < VIEWPORT_START_COLUMN + VIEWPORT_WIDTH) && ((--nbColumn) > 0));
    // Jusqu'à idxColonne = VIEWPORT_RIGHT_COLUMN ou  nbColumn = 0


}




void drawSprite (signed char posX, signed char posY, unsigned char texture[]){

    signed char     deltaX, deltaY;
    signed char     alpha;
    unsigned char   log2Delta;
    unsigned int    log2dist;
    unsigned char   height;
    signed char     column;

    deltaX          = posX-rayCamPosX;
    deltaY          = posY-rayCamPosY;
    if ((deltaX == 0) && (deltaY == 0)) return;
    alpha           = ATAN2(deltaY, deltaX);
    if (abs(alpha-rayCamRotZ) < HALF_FOV_FIX_ANGLE) {
        // if (lWallsCosBeta[RayCurrentWall] == 0){    // Wall is O,y aligned   
        //     RayWallLog      = log2_tab[(unsigned char)(abs(lPointsX[RayIdXPoint1]-glCamPosX))];
        //     tab_denom       = tab_1overcos;
        // } else {                                    // Wall is O,x aligned
        //     RayWallLog      = log2_tab[(unsigned char)(abs(lPointsY[RayIdXPoint1]-glCamPosY))];
        //     tab_denom       = tab_1oversin;
        // }
        column = tabAngle2Col[HALF_FOV_FIX_ANGLE-alpha+rayCamRotZ];
        if (abs(deltaX) > abs(deltaY)) {
            log2Delta = log2_tab[(unsigned char)(abs(deltaX))];
            // unsigned char dist2hh(unsigned int x)
            // signed char log2sin(unsigned char x)
            // signed char log2cos(unsigned char x)
            // distance = RayWallLog + (unsigned int)tab_denom[(unsigned char)RayAlpha];
            
            log2dist = log2Delta + (unsigned int)tab_1overcos[(unsigned char)alpha];

            // if (unfish[column] < log2dist)
            //     log2dist -= unfish[column];

            height = dist2hh(log2dist); // (100-dist2hh(log2dist))/4;
        } else {
            log2Delta = log2_tab[(unsigned char)(abs(deltaY))];
            log2dist = log2Delta + (unsigned int)tab_1oversin[(unsigned char)alpha];
            


            // if (unfish[column] < log2dist)
            //     log2dist -= unfish[column];


            height = dist2hh(log2dist);
        }


        //alpha glCamRotZ
        ptrTexture = texture ;             // Address of the texture 

        displaySprite02(column, height*2);
    } else {
        // displaySprite02(column, height);
    }
    
}