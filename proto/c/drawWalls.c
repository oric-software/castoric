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

    idxScreenCol        = VIEWPORT_START_COLUMN-1;
    ddaStartValue       = 0;
    ddaNbVal            = TEXTURE_SIZE;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));

    for (idxCurrentSlice = 2; idxCurrentSlice < NUMBER_OF_SLICE-1; ) {
        baseAdr             += 1;
        idxScreenCol        += 1;
        wallId              = raywall[idxCurrentSlice];
        if (wallId !=255) {

    // =====================================
    // ============ LEFT TEXEL
    // =====================================


            columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1); // modulo 32
            offTexture          = multi32[columnTextureCoord];
            ptrTexture          = wallTexture[wallId];
            ptrReadTexture      = &(ptrTexture[offTexture]);
            

            columnHeight        = TableVerticalPos[idxCurrentSlice]; 
            

            ddaNbStep           = columnHeight<<1;
            ddaInit();

            idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight;

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

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT));
        }

        idxScreenCol        += 1;
        idxCurrentSlice     += 1;
        wallId              = raywall[idxCurrentSlice];

        if (wallId !=255) {
            ptrTexture          = wallTexture[wallId];

    // =====================================
    // ============ RIGHT TEXEL
    // =====================================
            columnHeight        = TableVerticalPos[idxCurrentSlice];
            columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);  // modulo 32
            offTexture          = multi32[columnTextureCoord];
            ptrTexture          = wallTexture[wallId];
            ptrReadTexture      = &(ptrTexture[offTexture]);
            
            idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight;

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

            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT));
        }
        idxCurrentSlice++;
    }
}

#endif // USE_C_DRAWWALLS