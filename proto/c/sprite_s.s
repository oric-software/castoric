#include "config.h"

.zero

#ifndef USE_C_SPRITE
_tabPrecalcSpriteOffset .dsb 2
_spritePtrReadTexture .dsb 2
#endif

.text

#ifndef USE_C_SPRITE
;; 
;; _unrollRightColumnASM
;; .(
;; loopLine
;;     ;; renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
;;     ldy _spriteTextureLinIdx
;;     lda _precalTexPixelOffset,Y
;;     tay
;;     lda (_spritePtrReadTexture),Y
;;     sta _renCurrentColor
;;     ;; if (renCurrentColor != EMPTY_ALPHA) {
;;     cmp #EMPTY_ALPHA
;;     beq skipTexel
;;         ;; jsr _colorRightTexel
;; 
;;     ldx         _renCurrentColor
;; 
;;     ;; *theAdr = ((*theAdr)&0xF8) | tabRightRed[renCurrentColor];
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;; 
;;     ldy         #0
;;     lda         (_theAdr),y
;;     and         #$F8
;;     ora         _tabRightRed,x
;;     sta         (_theAdr),y
;; 
;; ;;     clc     
;; ;;     lda         _theAdr
;; ;;     adc         #40
;; ;;     sta         _theAdr
;; ;; .(  
;; ;;     bcc skip:    inc _theAdr+1: skip .)
;; 
;; 
;;     ;; *theAdr = ((*theAdr)&0xF8) | tabRightGreen[renCurrentColor];
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;; 
;;     ldy         #40
;;     lda         (_theAdr),y
;;     and         #$F8
;;     ora         _tabRightGreen,x
;;     sta         (_theAdr),y
;; 
;;     ;; *theAdr = ((*theAdr)&0xF8) | tabRightBlue[renCurrentColor];
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;; 
;;     ldy         #80
;;     lda         (_theAdr),y
;;     and         #$F8
;;     ora         _tabRightBlue,x
;;     sta         (_theAdr),y
;; 
;; ;;     clc     
;; ;;     lda         _theAdr 
;; ;;     adc         #120
;; ;;     sta         _theAdr
;; ;; .(: bcc skip:    inc _theAdr+1: skip .)
;; 
;; 
;; 
;; 
;; 
;; ;;        jmp endIf
;;     ;; else
;; skipTexel
;;         clc   
;;         lda         _theAdr
;;         adc         #120
;;         sta         _theAdr
;;         .(:bcc skip:    inc _theAdr+1: skip:.):
;; endIf
;;     inc _spriteTextureLinIdx:
;; 
;;     dec _spriteNbLoopLine:
;;     bne loopLine
;; 
;; .)
;;     rts
;; 
;; 
;; 
;; _unrollLeftColumnASM
;; .(
;; loopLine
;;     ;; renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
;;     ldy _spriteTextureLinIdx
;;     lda _precalTexPixelOffset,Y
;;     tay
;;     lda (_spritePtrReadTexture),Y
;;     sta _renCurrentColor
;;     ;; if (renCurrentColor != EMPTY_ALPHA) {
;;     cmp #EMPTY_ALPHA
;;     beq skipTexel
;;         ;; jsr _colorLeftTexel
;;     ldx         _renCurrentColor
;; 
;;     ;; *theAdr = tabLeftRed[renCurrentColor]|((*theAdr)&0x07);
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;;     ldy         #0
;;     lda         (_theAdr),y
;;     and         #$07 
;;     ora         _tabLeftRed,x
;;     sta         (_theAdr),y
;; 
;;     ;; *theAdr = tabLeftGreen[renCurrentColor]|((*theAdr)&0x07);
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;; 
;;     ldy         #40
;;     lda         (_theAdr),y
;;     and         #$07 
;;     ora         _tabLeftGreen,x
;;     sta         (_theAdr),y
;; 
;;     ;; *theAdr = tabLeftBlue[renCurrentColor]|((*theAdr)&0x07);
;;     ;; theAdr += NEXT_SCANLINE_INCREMENT;
;; 
;;     ldy         #80
;;     lda         (_theAdr),y
;;     and         #$07
;;     ora         _tabLeftBlue,x
;;     sta         (_theAdr),y
;; 
;; ;;     clc     
;; ;;     lda         _theAdr
;; ;;     adc         #120
;; ;;     sta         _theAdr
;; ;; .(:bcc skip:    inc _theAdr+1: skip .)
;; 
;; 
;; 
;; 
;; ;;        jmp endIf
;;     ;; else
;; skipTexel
;;         clc   
;;         lda         _theAdr
;;         adc         #120
;;         sta         _theAdr
;;         .(:bcc skip:    inc _theAdr+1: skip:.):
;; endIf
;;     inc _spriteTextureLinIdx:
;; 
;;     dec _spriteNbLoopLine:
;;     bne loopLine
;; 
;; .)
;;     rts    
;; 
;; 
;; 
;; _spriteDrawColumn   
;; .(
;; 
;;     ;; if ((objLogDistance[engCurrentObjectIdx] < raylogdist[spriteViewportColIdx-VIEWPORT_START_COLUMN-1])
;;     ;;  || (raywall[spriteViewportColIdx-VIEWPORT_START_COLUMN-1] == 255)) {
;; 
;;     ;; FIXME : ugly hack because raylogdist is array of 16 bits
;;     lda _spriteViewportColIdx
;;     sec
;;     sbc #VIEWPORT_START_COLUMN+1 
;;     tay
;;     asl
;;     sta tmp5
;; 
;;     lda _raywall, Y
;;     eor #$FF
;;     beq noWallOnCol
;; 
;;     ldy _engCurrentObjectIdx
;;     lda _objLogDistance,Y
;;     ldy tmp5
;;     cmp _raylogdist,Y
;;     bcs spriteDrawColumn_Done
;; 
;; noWallOnCol:
;;         ;; spriteTextureLinIdx     = spriteSavTextureLinIdx;
;;         ;; spriteNbLoopLine              = spriteSavNbLoopLine;
;;         lda _spriteSavTextureLinIdx
;;         sta _spriteTextureLinIdx
;;         lda _spriteSavNbLoopLine
;;         sta _spriteNbLoopLine
;; 
;;         ;; theAdr                  = (unsigned char *)((int)baseAdr + spriteScreenOffset ); // multi120[spriteViewportLinIdx]); // 
;;         clc
;;         lda _spriteScreenOffset
;;         adc _baseAdr
;;         sta _theAdr
;;         lda _spriteScreenOffset+1
;;         adc _baseAdr+1
;;         sta _theAdr+1
;; 
;;         ;; spriteTexColumn               = precalTexPixelOffset [spriteTextureColIdx];
;;         ;; spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);
;; 
;;         ldy _spriteTextureColIdx
;;         lda _precalTexPixelOffset,Y
;;         sta _spriteTexColumn
;;         ldy _spriteTexColumn
;;         lda _multi32_low,Y
;;         clc
;;         adc _spriteTexture
;;         sta _spritePtrReadTexture
;;         lda _multi32_high,Y
;;         adc _spriteTexture+1
;;         sta _spritePtrReadTexture+1
;; 
;;         ;; if ((spriteViewportColIdx&0x01) != 0){
;;         ;;     unrollLeftColumnASM();
;;         ;; } else {
;;         ;;     unrollRightColumnASM();
;;         ;; }
;; .(
;;             lda _spriteViewportColIdx
;;             and #$01
;;             beq drawRight
;;                 jsr _unrollLeftColumnASM
;;             jmp endIf
;; drawRight
;;                 jsr _unrollRightColumnASM
;; endIf
;; .)
;; 
;; spriteDrawColumn_Done
;; .)
;;     rts
;; 
;; 
;; _prepareScreenAdr
;; .(
;;     ;; spriteScreenOffset = ((int)(multi120_high[spriteViewportLinIdx]<<8) | (int)(multi120_low[spriteViewportLinIdx]));
;;     ldy _spriteViewportLinIdx
;;     lda _multi120_low, y
;;     sta _spriteScreenOffset
;;     lda _multi120_high, y
;;     sta _spriteScreenOffset+1
;; 
;;     ;; baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + 1 + (spriteViewportColIdx>>1));
;;     lda _spriteViewportColIdx
;;     lsr
;;     clc
;;     adc #<($A001)
;;     sta _baseAdr
;;     lda #>($A001)
;;     adc #0
;;     sta _baseAdr+1
;; 
;; 
;; .)
;;     rts



_precalcSpriteTexPixelRunthrough:
.(

;     if (spriteHeight >= 64) {
    lda _spriteHeight
    cmp #64
    bcc spriteSmallerThan64

;         // idxTexPixel         = 0;

;         // iea2StartValue      = 0;
;         // iea2NbVal           = TEXTURE_SIZE-1;
;         // iea2NbStep          = spriteHeight;

;         // iea2CurrentValue         = iea2StartValue;
;         // iea2EndValue             = iea2StartValue + iea2NbVal;
;         // iea2CurrentError     = iea2NbStep;


        lda #0
        sta _idxTexPixel: sta _iea2StartValue:
        lda #TEXTURE_SIZE-1: sta _iea2NbVal
        lda _spriteHeight: sta _iea2NbStep
        lda _iea2StartValue: sta _iea2CurrentValue
        clc: adc _iea2NbVal: sta _iea2EndValue
        lda _iea2NbStep: sta _iea2CurrentError

iea2_loop:
;         do {
;             // precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
;             // iea2CurrentError         -= iea2NbVal;
;             // if ((iea2CurrentError<<1) < iea2NbStep) {
;             //     iea2CurrentError     += iea2NbStep;
;             //     iea2CurrentValue     += 1;
;             // }
            ldy _idxTexPixel: lda _iea2CurrentValue: sta _precalTexPixelOffset,y :iny: sty _idxTexPixel
            lda _iea2CurrentError: sec: sbc _iea2NbVal: sta _iea2CurrentError
            :.(:bmi updateError
            asl
            cmp _iea2NbStep
            bcc updateError: jmp endUpdateError
            updateError
            lda _iea2CurrentError: clc: adc _iea2NbStep: sta _iea2CurrentError
            inc _iea2CurrentValue
            :endUpdateError:.)


        lda _iea2CurrentValue
        cmp _iea2EndValue
        bcc iea2_loop
;         } while (iea2CurrentValue < iea2EndValue);

;         // precalTexPixelOffset [idxTexPixel++] = iea2CurrentValue;
        ldy _idxTexPixel: lda _iea2CurrentValue: sta _precalTexPixelOffset,y: iny: sty _idxTexPixel
;         // tabPrecalTexPixelOffset[engCurrentObjectIdx] = precalTexPixelOffset; // &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)/2]);
        lda _engCurrentObjectIdx: asl: tay
        lda #<(_precalTexPixelOffset): sta _tabPrecalTexPixelOffset,y
        iny
        lda #>(_precalTexPixelOffset)
        sta _tabPrecalTexPixelOffset,y
    jmp EndIfSpriteSmallerThan64
;     } else {
spriteSmallerThan64:
;         tabPrecalTexPixelOffset[engCurrentObjectIdx] = &(tabIdxRdTexture[((spriteHeight+1)*spriteHeight)>>1]);

        lda _engCurrentObjectIdx : sta tmp0 :
        lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :
        lda tmp0 : asl : sta tmp0 : lda tmp0+1 : rol : sta tmp0+1 :
        clc : lda #<(_tabPrecalTexPixelOffset) : adc tmp0 : sta tmp0 : lda #>(_tabPrecalTexPixelOffset) : adc tmp0+1 : sta tmp0+1 :
        lda _spriteHeight : sta tmp1 :
        lda tmp1 : sta tmp1 : lda #0 : sta tmp1+1 :
        clc : lda #<(1) : adc tmp1 : sta tmp2 : lda #>(1) : adc tmp1+1 : sta tmp2+1 :
        lda tmp2 : sta op1 : lda tmp2+1 : sta op1+1 : lda tmp1 : sta op2 : lda tmp1+1 : sta op2+1 : jsr mul16i : stx tmp1 : sta tmp1+1 :
        lda tmp1 : sta tmp : lda tmp1+1 : ldx #1 : beq *+8 : lsr : ror tmp : dex : bne *-4 : ldx tmp : : stx tmp1 : sta tmp1+1 :
        clc : lda #<(_tabIdxRdTexture) : adc tmp1 : sta tmp1 : lda #>(_tabIdxRdTexture) : adc tmp1+1 : sta tmp1+1 :
        ldy #0 : lda tmp1 : sta (tmp0),y : iny : lda tmp1+1 : sta (tmp0),y :



;     }
EndIfSpriteSmallerThan64:

precalcSpriteTexPixelRunthroughDone
.)
    rts

_prepareDrawSprites
.(

    ;; unCompteur= dichoNbVal;
    ;; while (unCompteur >0) {
    ;;     unCompteur -= 1;
    ;;     engCurrentObjectIdx = tabDichoIdxs[unCompteur];
    ;;     prepareDrawSprite ();
    ;;     
    ;; }



    lda _dichoNbVal
    sta _unCompteur
loop
    lda _unCompteur
    bne higherthanzero
    jmp prepareDrawSpritesDone
higherthanzero
        dec _unCompteur
        ldy _unCompteur
        lda _tabDichoIdxs, Y
        sta _engCurrentObjectIdx
        ldy #0: jsr _prepareDrawSprite
        jmp loop
prepareDrawSpritesDone
.)
    rts


_drawSpriteCol:
.(
    ;; unCompteur= dichoNbVal;
    ;; while (unCompteur >0) {

    lda _dichoNbVal
    sta _unCompteur
loop
    lda _unCompteur
    bne higherthanzero
    jmp endloop
higherthanzero
        ;; unCompteur -= 1;
        ;; engCurrentObjectIdx = tabDichoIdxs[unCompteur];
        ;; spriteTexture = objTexture[engCurrentObjectIdx];
        dec _unCompteur
        ldy _unCompteur
        lda _tabDichoIdxs, y
        sta _engCurrentObjectIdx
        asl
        tay
        lda _objTexture,y: sta _spriteTexture
        iny: lda _objTexture,y: sta _spriteTexture+1

    ;;    if ((tabSpriteNbLoopColumn[engCurrentObjectIdx] != 0)
    ;;        && (idxCurrentSlice >= tabSpriteViewportColIdx[engCurrentObjectIdx]) ) {
        ldy _engCurrentObjectIdx
        lda _tabSpriteNbLoopColumn,Y
        bne somemorecol2draw
        jmp end_if_01
somemorecol2draw
        lda _tabSpriteViewportColIdx, y
        cmp _idxCurrentSlice
        bcc then_01
        beq then_01
        jmp end_if_01
then_01
    ;;        if (
    ;;            (objLogDistance[engCurrentObjectIdx] < raylogdist[idxCurrentSlice])
    ;;        || (raywall[idxCurrentSlice] == 255)) {
            ldy _idxCurrentSlice
            lda _raywall,Y
            cmp #255
            beq then_02
            ;; FIXME : ugly hack because raylogdist is array of 16 bits
            tya:asl:tay:
            lda _raylogdist,y
            ldy _engCurrentObjectIdx
            cmp _objLogDistance,y
            beq goto_endif
            bcs then_02
goto_endif            
            jmp end_if_02
then_02
                ;; spriteTextureLinIdx     = tabSpriteSavTextureLinIdx[engCurrentObjectIdx];
                ;; spriteNbLoopLine        = tabSpriteSavNbLoopLine[engCurrentObjectIdx];
                ;; idxBufVertCol = tabSpriteViewportLinIdx[engCurrentObjectIdx]-VIEWPORT_START_LINE;

                ldy _engCurrentObjectIdx: lda _tabSpriteSavTextureLinIdx,y: sta _spriteTextureLinIdx
                lda _tabSpriteSavNbLoopLine,y: sta _spriteNbLoopLine
                lda _tabSpriteViewportLinIdx,y
                sec: sbc #VIEWPORT_START_LINE
                sta _idxBufVertCol

                ;; tabPrecalcSpriteOffset = tabPrecalTexPixelOffset[engCurrentObjectIdx];
                lda _engCurrentObjectIdx: asl: tay
                lda _tabPrecalTexPixelOffset, y: sta _tabPrecalcSpriteOffset: iny: lda _tabPrecalTexPixelOffset, y: sta _tabPrecalcSpriteOffset+1

                ;; spriteTexColumn               = tabPrecalcSpriteOffset [tabSpriteTextureColIdx[engCurrentObjectIdx]];
                ldy _engCurrentObjectIdx: lda _tabSpriteTextureColIdx, y: tay: lda (_tabPrecalcSpriteOffset), y
                sta _spriteTexColumn

                ;; spritePtrReadTexture    = spriteTexture + (unsigned int)((multi32_high[spriteTexColumn] << 8) | multi32_low[spriteTexColumn]);
                ldy _spriteTexColumn
                lda _multi32_low,Y
                clc
                adc _spriteTexture
                sta _spritePtrReadTexture
                lda _multi32_high,Y
                adc _spriteTexture+1
                sta _spritePtrReadTexture+1

    ;;          if ((idxCurrentSlice&0x01) == 0){
                lda _idxCurrentSlice
                and #$01
                beq then_03
                jmp else_if_03
then_03

                ;;    do {
                ;;        renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                ;;        if (renCurrentColor != EMPTY_ALPHA) {
                ;;            bufVertColLeft[idxBufVertCol] = renCurrentColor;
                ;;        }
                ;;        idxBufVertCol += 1;
                ;;        spriteTextureLinIdx       ++;
                ;;    } while ((--spriteNbLoopLine) != 0);
.(
loopbasic
                            ldy _spriteTextureLinIdx
                            lda (_tabPrecalcSpriteOffset), y
                            tay
                            lda (_spritePtrReadTexture), y
                            sta _renCurrentColor
                            cmp #EMPTY_ALPHA:
                            beq donotdrawtex
                                ldy _idxBufVertCol
                                lda _renCurrentColor
                                sta _bufVertColLeft, y
donotdrawtex
                            inc _idxBufVertCol
                            inc _spriteTextureLinIdx
                            dec _spriteNbLoopLine
                            beq end_loop
                            jmp loopbasic:
end_loop:.)

                jmp end_if_03
else_if_03

                ;;    do {
                ;;        renCurrentColor     = spritePtrReadTexture[tabPrecalcSpriteOffset [spriteTextureLinIdx]];
                ;;        if (renCurrentColor != EMPTY_ALPHA) {
                ;;            bufVertColRight[idxBufVertCol] = renCurrentColor;
                ;;        }
                ;;        idxBufVertCol               += 1;
                ;;        spriteTextureLinIdx       ++;
                ;;    } while ((--spriteNbLoopLine) != 0);

.(:
loopbasic
                            ldy _spriteTextureLinIdx
                            lda (_tabPrecalcSpriteOffset), y
                            tay
                            lda (_spritePtrReadTexture), y
                            sta _renCurrentColor
                            cmp #EMPTY_ALPHA
                            beq donotdrawtex
                                ldy _idxBufVertCol
                                lda _renCurrentColor
                                sta _bufVertColRight, y
donotdrawtex
                            inc _idxBufVertCol
                            inc _spriteTextureLinIdx
                            dec _spriteNbLoopLine
                            beq end_loop
                            jmp loopbasic:
end_loop:.)

end_if_03

end_if_02

            ;; tabSpriteTextureColIdx[engCurrentObjectIdx] += 1;
            ;; tabSpriteNbLoopColumn[engCurrentObjectIdx]  -= 1;
        ldx _engCurrentObjectIdx
        inc _tabSpriteTextureColIdx, x
        dec _tabSpriteNbLoopColumn, x

end_if_01
    jmp loop
endloop
drawSpriteColDone
.)
    rts


_prepareDrawSprite:
.(
    // compute objAngle, objLogDist
    // objX = objPosX[engCurrentObjectIdx];
    // objY = objPosY[engCurrentObjectIdx];
    ldy _engCurrentObjectIdx
    lda _objPosX,y
    sta _objX
    lda _objPosY,y
    sta _objY

    // theVisibility = isVisibleSprite();
    jsr _elaborateSpriteVisibility
    lda _visi_SpriteVisibility
    sta _theVisibility

    ; if ((theObjHeight=dist2hh(objLogDistance[engCurrentObjectIdx])) == 0) return;
    ldy _engCurrentObjectIdx
    lda _objLogDistance,y
    tay
    lda         _unlogd2hh, Y
    sta _theObjHeight
    bne heightNotNull
    rts

heightNotNull

    // spriteHeight            = theObjHeight*2;
    lda _theObjHeight
    asl
    sta _spriteHeight


    ; precalcSpriteTexPixelRunthrough();
    ldy #0: jsr _precalcSpriteTexPixelRunthrough


    ; if (theVisibility == 1){
    lda _theVisibility
    cmp #1
    beq visibilityEquals1
    jmp visibilityNot1
visibilityEquals1:
    ;     // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngle[engCurrentObjectIdx]];
        ldy _engCurrentObjectIdx: lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngle,y: tay: lda _tabAngle2Col,y
        sta _spriteRefColumn


    ;     // Rejoindre la bordure gauche
    ;     if (spriteRefColumn <= spriteHeight/2) {
        lda _spriteHeight    
        lsr
        cmp _spriteRefColumn
        bcc refColumnHigherThanHeight_00
    ;         // tabSpriteViewportColIdx[engCurrentObjectIdx]       = 0 ; // VIEWPORT_START_COLUMN + 1;
            lda #0: ldy _engCurrentObjectIdx: sta _tabSpriteViewportColIdx,y
    ;         // tabSpriteTextureColIdx[engCurrentObjectIdx]         = spriteHeight/2 - spriteRefColumn + 2;
            lda _spriteHeight: lsr: clc: adc #2: sec: sbc _spriteRefColumn
            ldy _engCurrentObjectIdx: sta _tabSpriteTextureColIdx,y // TODO: Remove loading of engCurrentObjectIdx cause it is already loaded

    ;         // tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH - 3,spriteHeight/2+spriteRefColumn-2);
            lda _spriteHeight: lsr: clc: adc _spriteRefColumn : sec: sbc #2
            .(:cmp #VIEWPORT_WIDTH - 3:bcc skip:lda #VIEWPORT_WIDTH - 3:skip:.)
            ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y
        jmp enfIfrefColumnHigherThanHeight_00
refColumnHigherThanHeight_00:
    ;     } else {
    ;         // tabSpriteViewportColIdx[engCurrentObjectIdx]       = spriteRefColumn - spriteHeight/2; // + VIEWPORT_START_COLUMN;
            lda _spriteHeight: lsr: eor #$FF: sec: adc #1: clc: adc _spriteRefColumn
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportColIdx,y
    ;         // tabSpriteTextureColIdx[engCurrentObjectIdx]        = 0;
            lda #0: ldy _engCurrentObjectIdx: sta _tabSpriteTextureColIdx,y
    ;         // tabSpriteNbLoopColumn[engCurrentObjectIdx] = min(VIEWPORT_WIDTH-2-spriteRefColumn+spriteHeight/2,spriteHeight);
            lda _spriteHeight: lsr: clc: adc #VIEWPORT_WIDTH-2: sec: sbc _spriteRefColumn
            .(:cmp _spriteHeight: bcc skip: lda _spriteHeight :skip:.)
            ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y
enfIfrefColumnHigherThanHeight_00
    ;     }

    ;     if (spriteHeight > VIEWPORT_HEIGHT){
        lda #VIEWPORT_HEIGHT
        cmp _spriteHeight
        bcs spriteHeightNotHigherThanViewportHeight_00
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_START_LINE + 1;
            lda #VIEWPORT_START_LINE+1
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = spriteHeight/2 - VIEWPORT_HEIGHT/ 2 + 1;
            lda _spriteHeight:lsr: sec
            sbc #VIEWPORT_HEIGHT/2
            clc: adc #1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = VIEWPORT_HEIGHT  - 1;
            lda #VIEWPORT_HEIGHT-1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
        jmp endIfSpriteHeightHigherThanViewportHeight_00
spriteHeightNotHigherThanViewportHeight_00
    ;     } else {
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]    = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
            lda _spriteHeight: lsr: eor #$FF: clc: adc #1: clc: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]  = 0;
            lda #0
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]           = spriteHeight ;
            lda _spriteHeight
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
endIfSpriteHeightHigherThanViewportHeight_00
    ;     }
    jmp endSwitchVisibility
visibilityNot1:
    ; } else if (theVisibility == 2) {
    lda _theVisibility
    cmp #2
    bne visibilityNot2
    ;     // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleRight];
        lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngleRight:tay:lda _tabAngle2Col,y
        sta _spriteRefColumn
       

    ;     // displaySpriteRightVisible();
    ;     // tabSpriteViewportColIdx[engCurrentObjectIdx]          = 0; 
    ;     // tabSpriteTextureColIdx[engCurrentObjectIdx]           = spriteHeight-spriteRefColumn-1;
    ;     // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = spriteRefColumn; // spriteRefColumn-VIEWPORT_START_COLUMN;
        ldy _engCurrentObjectIdx
        lda #0
        sta _tabSpriteViewportColIdx,y
        lda _spriteHeight: sec: sbc _spriteRefColumn: sec : sbc #1 
        sta _tabSpriteTextureColIdx,y
        lda _spriteRefColumn
        sta _tabSpriteNbLoopColumn,y


    ;     if (spriteHeight > VIEWPORT_HEIGHT){
        lda #VIEWPORT_HEIGHT
        cmp _spriteHeight
        bcs spriteHeightNotHigherThanViewportHeight_01
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
            lda #VIEWPORT_START_LINE + 1
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
            lda _spriteHeight: lsr: sec: sbc #VIEWPORT_HEIGHT/2:clc: adc #1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
            lda #VIEWPORT_HEIGHT-1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
        jmp endIfSpriteHeightHigherThanViewportHeight_01
    ;     } else {
spriteHeightNotHigherThanViewportHeight_01
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
            lda #0
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
            lda _spriteHeight: lsr: eor #$FF: clc: adc #1: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
            lda _spriteHeight
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
endIfSpriteHeightHigherThanViewportHeight_01
    ;     }

    jmp endSwitchVisibility
visibilityNot2:
    cmp #2
    bne visibilityNot3
    ; } else if (theVisibility == 3) {
    ;     // spriteRefColumn = tabAngle2Col[HALF_FOV_FIX_ANGLE-objAngleLeft];
        lda #HALF_FOV_FIX_ANGLE: sec: sbc _objAngleLeft: tay: lda _tabAngle2Col,y
        sta _spriteRefColumn

    ;     // tabSpriteViewportColIdx[engCurrentObjectIdx]        = spriteRefColumn;
    ;     // tabSpriteTextureColIdx[engCurrentObjectIdx]         = 0;
    ;     // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = VIEWPORT_WIDTH-spriteRefColumn;
        ldy _engCurrentObjectIdx
        lda _spriteRefColumn
        sta _tabSpriteViewportColIdx,y
        lda #0
        sta _tabSpriteTextureColIdx,y
        lda #VIEWPORT_WIDTH: sec: sbc _spriteRefColumn
        sta _tabSpriteNbLoopColumn,y



    ;     if (spriteHeight > VIEWPORT_HEIGHT){
        lda #VIEWPORT_HEIGHT
        cmp _spriteHeight
        bcs spriteHeightNotHigherThanViewportHeight_02
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_START_LINE + 1;
            lda #VIEWPORT_START_LINE+1
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = spriteHeight/2 - VIEWPORT_HEIGHT/ 2  + 1;
            lda _spriteHeight: lsr: sec: sbc #VIEWPORT_HEIGHT/2+1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = VIEWPORT_HEIGHT  - 1;
            lda #VIEWPORT_HEIGHT-1
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
        jmp endIfSpriteHeightHigherThanViewportHeight_02
    ;     } else {
spriteHeightNotHigherThanViewportHeight_02
    ;         // tabSpriteViewportLinIdx[engCurrentObjectIdx]        = VIEWPORT_HEIGHT/ 2 - spriteHeight/2 + VIEWPORT_START_LINE;
            lda _spriteHeight: lsr: eor #$FF: clc: adc #1: clc: adc #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE
            ldy _engCurrentObjectIdx: sta _tabSpriteViewportLinIdx,y
    ;         // tabSpriteSavTextureLinIdx[engCurrentObjectIdx]      = 0;
            lda #0
            ldy _engCurrentObjectIdx: sta _tabSpriteSavTextureLinIdx,y
    ;         // tabSpriteSavNbLoopLine[engCurrentObjectIdx]               = spriteHeight ;
            lda _spriteHeight
            ldy _engCurrentObjectIdx: sta _tabSpriteSavNbLoopLine,y
endIfSpriteHeightHigherThanViewportHeight_02
    ;     }

    jmp endSwitchVisibility
visibilityNot3:
    ; } else {
    ;     // tabSpriteNbLoopColumn[engCurrentObjectIdx]                = 0;
        lda #0
        ldy _engCurrentObjectIdx: sta _tabSpriteNbLoopColumn,y
        
    ; }
endSwitchVisibility
prepareDrawSpriteDone
.)
    rts

#endif ;;USE_C_SPRITE
