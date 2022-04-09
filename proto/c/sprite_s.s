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
#endif ;;USE_C_SPRITE
