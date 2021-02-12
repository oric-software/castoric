#define USE_C_DRAWWALLS
#ifdef USE_C_DRAWWALLS

unsigned char *wallTexture[] = {texture_christmas, texture_logo};

unsigned char *ptrTexture;

void drawWalls(){
    unsigned char       idxCurrentSlice;

    signed char         idxScreenLine, idxScreenCol;
    unsigned char       columnHeight, columnTextureCoord;

    idxScreenCol        = 1;
    ddaStartValue       = 0;
    ddaNbVal            = TEXTURE_HEIGHT;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));

    for (idxCurrentSlice = 2; idxCurrentSlice < NB_SLICES-1; ) {
        baseAdr             += 1;
        idxScreenCol        += 1;
        if (raywall[idxCurrentSlice]!=255) {
            ptrTexture = wallTexture[raywall[idxCurrentSlice]];

    // =====================================
    // ============ LEFT TEXEL
    // =====================================

            columnHeight              = (100-TableVerticalPos[idxCurrentSlice])/4; // tabHeight[idxCurrentSlice];
            columnTextureCoord           = tabTexCol[idxCurrentSlice]&31; // modulo 32
            offTexture          = multi32[columnTextureCoord];

            
            
            idxScreenLine       = 32 - columnHeight;

            ddaNbStep           = columnHeight<<1;

            

            ddaInit();

            while (idxScreenLine < 0){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]); 

            do {
                (*ddaStepFunction)();

                // colorEvenSquare(bufimg[multi40[ddaCurrentValue] + columnTextureCoord]);
                renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];
                colorLeftTexel();

                idxScreenLine   += 1;
                // theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }

        idxCurrentSlice++;
        idxScreenCol        += 1;
        if (raywall[idxCurrentSlice]!=255) {
            ptrTexture = wallTexture[raywall[idxCurrentSlice]];

    // =====================================
    // ============ RIGHT TEXEL
    // =====================================
            columnHeight              = (100-TableVerticalPos[idxCurrentSlice])/4; // tabHeight[ii];
            columnTextureCoord           = tabTexCol[idxCurrentSlice]&31;  // modulo 32
            offTexture          = multi32[columnTextureCoord];
            

            idxScreenLine       = 32 - columnHeight;

            ddaNbStep           = columnHeight<<1;

            ddaInit();

            while (idxScreenLine < 0){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]);
            
            do {
                (*ddaStepFunction)();

                // colorOddSquare(bufimg[multi40[ddaCurrentValue] + columnTextureCoord]);
                renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];
                colorRightTexel();

                idxScreenLine   += 1;
                // theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }
        idxCurrentSlice++;
    }
   
}

#endif // USE_C_DRAWWALLS