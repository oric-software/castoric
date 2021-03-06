#include "config.h"

#include "dda.c"

extern unsigned int offTexture;
#ifdef USE_C_DRAWWALLS
unsigned char *     ptrTexture;             // Address of the texture 


unsigned char *     ptrReadTexture;             // Address of the texture 
unsigned char       idxCurrentSlice;
unsigned char *     baseAdr;
signed char         idxScreenLine, idxScreenCol;
unsigned char       columnHeight, columnTextureCoord;
unsigned char       wallId;

void drawWalls(){


    ddaNbVal            = TEXTURE_SIZE;
    idxScreenCol        = VIEWPORT_START_COLUMN-1;
    baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
    ddaStartValue       = 0;
    idxCurrentSlice     = 0;

    // asm (
    //     "lda #TEXTURE_SIZE;"
    //     "sta _ddaNbVal;"

    //     "lda #VIEWPORT_START_COLUMN-1;"
    //     "sta    _idxScreenCol;"
    //     "lsr;"

    //     "adc #<(HIRES_SCREEN_ADDRESS);"
    //     "sta _baseAdr;"
    //     "lda #>(HIRES_SCREEN_ADDRESS);"
    //     "adc #0;"
    //     "sta _baseAdr+1;"

    //     "lda #0;"
    //     "sta _ddaStartValue;"
    //     "sta _idxCurrentSlice;"
    // );



    do {
        baseAdr             += 1;
        idxScreenCol        += 1;
        wallId              = raywall[idxCurrentSlice];

        // asm (
        //     "inc _baseAdr: .( : bne skip : inc _baseAdr+1: skip:.);"
        //     "inc _idxScreenCol;"
        //     "ldy _idxCurrentSlice;"
        //     "lda _raywall,Y"
        //     "sta _wallId"
        // );

        if (wallId !=255) {

    // =====================================
    // ============ LEFT TEXEL
    // =====================================


            columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1); // modulo 32
            offTexture          = multi32[columnTextureCoord];
            // asm (
            //     "ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: sta _columnTextureCoord;"
            //     "lda _columnTextureCoord: asl : tay : lda _multi32,Y: sta _offTexture : iny : lda _multi32,Y : sta _offTexture+1"
            // );

            ptrTexture          = wallTexture[wallId];
            // asm (
            //     "lda _wallId: asl: tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1"
            // );

            ptrReadTexture      = &(ptrTexture[offTexture]);
            // asm (
            //     "clc;"
            //     "lda _ptrTexture;"
            //     "adc _offTexture;"
            //     "sta _ptrReadTexture;"
            //     "lda _ptrTexture+1;"
            //     "adc _offTexture+1;"
            //     "sta _ptrReadTexture+1;"
            // );
            
            columnHeight        = TableVerticalPos[idxCurrentSlice]; 
            // asm (
            //     "ldy _idxCurrentSlice;"
            //     "lda _TableVerticalPos,Y;"
            //     "sta _columnHeight;"
            // );

            ddaNbStep           = columnHeight<<1;
            // asm ("lda _columnHeight : asl : sta _ddaNbStep;");

            ddaInit();
            // asm ("jsr _ddaInit");

            idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;
            // asm ("sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine;");

            while (idxScreenLine < VIEWPORT_START_LINE){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 
            // asm (
            //     ".( : loop : lda _idxScreenLine : "
            //     "cmp #VIEWPORT_START_LINE : "
            //     "bpl end_loop : "
            //         // "jsr (_ddaStepFunction) : "
	        //         "lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :"
	        //         ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            //         "inc _idxScreenLine : "
            //         "jmp loop : "
            //     "end_loop : .) : "
            // );

            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]); 

            // asm (
            //     "lda _idxScreenLine;"
            //     "asl;"
            //     "tay;"
            //     "lda _multi120,Y;"
            //     "iny;"
            //     "clc;"
            //     "adc _baseAdr;"
            //     "sta _theAdr;"
            //     "lda _multi120,Y;"
            //     "adc _baseAdr+1;"
            //     "sta _theAdr+1;"
            // );



            do {
                (*ddaStepFunction)();
                renCurrentColor = ptrReadTexture[ddaCurrentValue];
                colorLeftTexel(); // theAdr          += 120;
                idxScreenLine   += 1;
            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));

            // asm (
            //     ".( : LeftCol_loop : "
            //         "lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :"
            //         ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            //     );
            // asm (
            // //         "ldy _ddaCurrentValue : lda _ptrReadTexture,Y : sta _renCurrentColor : "
            //     	"lda _ddaCurrentValue : sta tmp0 :"
            //     	"lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :"
            //     	"lda _ptrReadTexture : sta tmp1 : lda _ptrReadTexture+1 : sta tmp1+1 :"
            //     	"clc : lda tmp0 : adc tmp1 : sta tmp0 : lda tmp0+1 : adc tmp1+1 : sta tmp0+1 :"
            //     	"ldy #0 : lda (tmp0),y : sta tmp0 :"
            //     	"lda tmp0 : sta _renCurrentColor :                "
            // );
            // asm (
            //         "jsr _colorLeftTexel : "
            //         "inc _idxScreenLine : "
            //         "lda _idxScreenLine : "
            //         "cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : "
            //         "bcs LeftCol_endloop : "
            //         "lda _ddaCurrentValue : "
            //         "cmp _ddaEndValue : "
            //         "bcs LeftCol_endloop : "
            //         "jmp LeftCol_loop : "
            //         "LeftCol_endloop : .) : " 

            // );


        }

        idxScreenCol        += 1;
        idxCurrentSlice     += 1;
        wallId              = raywall[idxCurrentSlice];
        // asm (
        //     "inc _idxScreenCol : inc _idxCurrentSlice : ldy _idxCurrentSlice : lda _raywall,Y : sta _wallId"
        // );

        if (wallId !=255) {

            ptrTexture          = wallTexture[wallId];
            // asm ("lda _wallId: asl : tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1");

    // =====================================
    // ============ RIGHT TEXEL
    // =====================================
            columnHeight        = TableVerticalPos[idxCurrentSlice];
            // asm (
            //     "ldy _idxCurrentSlice;"
            //     "lda _TableVerticalPos,Y;"
            //     "sta _columnHeight;"
            // );

            columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);  // modulo 32
            offTexture          = multi32[columnTextureCoord];
            // asm (
            //     "ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: sta _columnTextureCoord;"
            //     "lda _columnTextureCoord: asl : tay : lda _multi32,Y: sta _offTexture : iny : lda _multi32,Y : sta _offTexture+1"
            // );
           
            ptrTexture          = wallTexture[wallId];
            // asm (
            //     "lda _wallId: asl: tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1"
            // );

            ptrReadTexture      = &(ptrTexture[offTexture]);
            // asm (
            //     "clc;"
            //     "lda _ptrTexture;"
            //     "adc _offTexture;"
            //     "sta _ptrReadTexture;"
            //     "lda _ptrTexture+1;"
            //     "adc _offTexture+1;"
            //     "sta _ptrReadTexture+1;"
            // );
            
            idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;
            // asm ("sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine;");

            ddaNbStep           = columnHeight<<1;
            // asm ("lda _columnHeight : asl : sta _ddaNbStep;");

            ddaInit();
            // asm ("jsr _ddaInit");


            while (idxScreenLine < VIEWPORT_START_LINE){
                (*ddaStepFunction)();
                idxScreenLine   += 1;
            } 

            // asm (
            //     ".( : loop : lda _idxScreenLine : "
            //     "cmp #VIEWPORT_START_LINE : "
            //     "bpl end_loop : "
            //         // "jsr (_ddaStepFunction) : "
	        //         "lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :"
	        //         ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            //         "inc _idxScreenLine : "
            //         "jmp loop : "
            //     "end_loop : .) : "
            // );



            // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
            theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]);
            // asm (
            //     "lda _idxScreenLine;"
            //     "asl;"
            //     "tay;"
            //     "lda _multi120,Y;"
            //     "iny;"
            //     "clc;"
            //     "adc _baseAdr;"
            //     "sta _theAdr;"
            //     "lda _multi120,Y;"
            //     "adc _baseAdr+1;"
            //     "sta _theAdr+1;"
            // );
            
            do {
                (*ddaStepFunction)();
                renCurrentColor = ptrReadTexture [ddaCurrentValue];
                colorRightTexel(); // theAdr          += 120;
                idxScreenLine   += 1;
            } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


            // asm (
            //     ".( : RightCol_loop : "
            //         "lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :"
            //         ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            //     );
            // asm (
            // //         "ldy _ddaCurrentValue : lda _ptrReadTexture,Y : sta _renCurrentColor : "
            //     	"lda _ddaCurrentValue : sta tmp0 :"
            //     	"lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :"
            //     	"lda _ptrReadTexture : sta tmp1 : lda _ptrReadTexture+1 : sta tmp1+1 :"
            //     	"clc : lda tmp0 : adc tmp1 : sta tmp0 : lda tmp0+1 : adc tmp1+1 : sta tmp0+1 :"
            //     	"ldy #0 : lda (tmp0),y : sta tmp0 :"
            //     	"lda tmp0 : sta _renCurrentColor :                "
            // );
            // asm (
            //         "jsr _colorRightTexel : "
            //         "inc _idxScreenLine : "
            //         "lda _idxScreenLine : "
            //         "cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : "
            //         "bcs RightCol_endloop : "
            //         "lda _ddaCurrentValue : "
            //         "cmp _ddaEndValue : "
            //         "bcs RightCol_endloop : "
            //         "jmp RightCol_loop : "
            //         "RightCol_endloop : .) : " 

            // );


        }

        idxCurrentSlice++;
        // asm ("inc _idxCurrentSlice");

    } while (idxCurrentSlice < NUMBER_OF_SLICE-2);
}
#else
extern unsigned char *baseAdr;
extern void drawWalls();
#endif // USE_C_DRAWWALLS