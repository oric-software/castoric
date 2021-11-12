
.zero

_spritePtrReadTexture .dsb 2

.text


_unrollRightColumnASM
.(
loopLine
    ;; renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
    ldy _spriteTextureLinIdx
    lda _precalTexPixelOffset,Y
    tay
    lda (_spritePtrReadTexture),Y
    sta _renCurrentColor
    ;; if (renCurrentColor != EMPTY_ALPHA) {
    cmp #EMPTY_ALPHA
    beq skipTexel
        ;; jsr _colorRightTexel

    ldx         _renCurrentColor

    ;; *theAdr = ((*theAdr)&0xF8) | tabRightRed[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    ldy         #0
    lda         (_theAdr),y
    and         #$F8
    ora         _tabRightRed,x
    sta         (_theAdr),y

;;     clc     
;;     lda         _theAdr
;;     adc         #40
;;     sta         _theAdr
;; .(  
;;     bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr = ((*theAdr)&0xF8) | tabRightGreen[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    ldy         #40
    lda         (_theAdr),y
    and         #$F8
    ora         _tabRightGreen,x
    sta         (_theAdr),y

    ;; *theAdr = ((*theAdr)&0xF8) | tabRightBlue[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    ldy         #80
    lda         (_theAdr),y
    and         #$F8
    ora         _tabRightBlue,x
    sta         (_theAdr),y

;;     clc     
;;     lda         _theAdr 
;;     adc         #120
;;     sta         _theAdr
;; .(: bcc skip:    inc _theAdr+1: skip .)





;;        jmp endIf
    ;; else
skipTexel
        clc   
        lda         _theAdr
        adc         #120
        sta         _theAdr
        .(:bcc skip:    inc _theAdr+1: skip:.):
endIf
    inc _spriteTextureLinIdx:

    dec _spriteNbLoopLine:
    bne loopLine

.)
    rts



_unrollLeftColumnASM
.(
loopLine
    ;; renCurrentColor     = spritePtrReadTexture[precalTexPixelOffset [spriteTextureLinIdx]];
    ldy _spriteTextureLinIdx
    lda _precalTexPixelOffset,Y
    tay
    lda (_spritePtrReadTexture),Y
    sta _renCurrentColor
    ;; if (renCurrentColor != EMPTY_ALPHA) {
    cmp #EMPTY_ALPHA
    beq skipTexel
        ;; jsr _colorLeftTexel
    ldx         _renCurrentColor

    ;; *theAdr = tabLeftRed[renCurrentColor]|((*theAdr)&0x07);
    ;; theAdr += NEXT_SCANLINE_INCREMENT;
    ldy         #0
    lda         (_theAdr),y
    and         #$07 
    ora         _tabLeftRed,x
    sta         (_theAdr),y

    ;; *theAdr = tabLeftGreen[renCurrentColor]|((*theAdr)&0x07);
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    ldy         #40
    lda         (_theAdr),y
    and         #$07 
    ora         _tabLeftGreen,x
    sta         (_theAdr),y

    ;; *theAdr = tabLeftBlue[renCurrentColor]|((*theAdr)&0x07);
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    ldy         #80
    lda         (_theAdr),y
    and         #$07
    ora         _tabLeftBlue,x
    sta         (_theAdr),y

;;     clc     
;;     lda         _theAdr
;;     adc         #120
;;     sta         _theAdr
;; .(:bcc skip:    inc _theAdr+1: skip .)




;;        jmp endIf
    ;; else
skipTexel
        clc   
        lda         _theAdr
        adc         #120
        sta         _theAdr
        .(:bcc skip:    inc _theAdr+1: skip:.):
endIf
    inc _spriteTextureLinIdx:

    dec _spriteNbLoopLine:
    bne loopLine

.)
    rts    