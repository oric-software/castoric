#define USE_C_DRAWWALLS

#ifdef USE_C_DRAWWALLS


unsigned char *     ptrTexture;             // Address of the texture 
unsigned char *     ptrReadTexture;             // Address of the texture 
unsigned char       idxCurrentSlice;
unsigned char *     baseAdr;
signed char         idxScreenLine, idxScreenCol;
unsigned char       columnHeight, columnTextureCoord;
unsigned char       wallId;

void drawWalls(){

    idxScreenCol        = 1;
    ddaStartValue       = 0;
    ddaNbVal            = TEXTURE_HEIGHT;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));

    for (idxCurrentSlice = 2; idxCurrentSlice < NB_SLICES-1; ) {
        baseAdr             += 1;
        idxScreenCol        += 1;
        wallId              = raywall[idxCurrentSlice];
        if (wallId !=255) {

    // =====================================
    // ============ LEFT TEXEL
    // =====================================


            columnTextureCoord  = tabTexCol[idxCurrentSlice]&31; // modulo 32
            offTexture          = multi32[columnTextureCoord];
            ptrTexture          = wallTexture[wallId];
            ptrReadTexture      = &(ptrTexture[offTexture]);
            

            columnHeight        = (100-TableVerticalPos[idxCurrentSlice])/4; // tabHeight[idxCurrentSlice];
            

            ddaNbStep           = columnHeight<<1;
            ddaInit();

            idxScreenLine       = 32 - columnHeight;

            while (idxScreenLine < 0){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]); 

            do {
                (*ddaStepFunction)();

                // colorEvenSquare(bufimg[multi40[ddaCurrentValue] + columnTextureCoord]);
                // renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];

                renCurrentColor = ptrReadTexture[ddaCurrentValue];
                colorLeftTexel();

                idxScreenLine   += 1;
                // theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }

        idxScreenCol        += 1;
        idxCurrentSlice     += 1;
        wallId              = raywall[idxCurrentSlice];

        if (wallId !=255) {
            ptrTexture          = wallTexture[wallId];

    // =====================================
    // ============ RIGHT TEXEL
    // =====================================
            columnHeight        = (100-TableVerticalPos[idxCurrentSlice])/4; // tabHeight[ii];
            columnTextureCoord  = tabTexCol[idxCurrentSlice]&31;  // modulo 32
            offTexture          = multi32[columnTextureCoord];
            ptrTexture          = wallTexture[wallId];
            ptrReadTexture      = &(ptrTexture[offTexture]);
            
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
                // renCurrentColor = ptrTexture[offTexture + ddaCurrentValue];
                renCurrentColor = ptrReadTexture [ddaCurrentValue];
                colorRightTexel();

                idxScreenLine   += 1;
                // theAdr          += 120;

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < 64));
        }
        idxCurrentSlice++;
    }
}

#endif // USE_C_DRAWWALLS