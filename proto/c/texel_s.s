


.zero

_theAdr .dsb  2

.text

_colorLeftTexel 
.(
    ldx         _renCurrentColor

    ;; *theAdr = tabLeftGreen[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    lda         _tabLeftRed,x
    ldy         #0
    sta         (_theAdr),y

    ;; *theAdr = tabLeftGreen[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    lda         _tabLeftGreen,x
    ldy         #40
    sta         (_theAdr),y

    ;; *theAdr = tabLeftBlue[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    lda         _tabLeftBlue,x
    ldy         #80
    sta         (_theAdr),y

    clc     
    lda         _theAdr
    adc         #120
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


.)
    rts

_colorRightTexel 
.(

    ldy         #0
    ldx         _renCurrentColor

    lda         _tabRightRed,x
    ora         (_theAdr),y
    ;; ldy         #0
    sta         (_theAdr),y
;;     clc     
;;     lda         _theAdr
;;     adc         #40
;;     sta         _theAdr
;; .(  
;;     bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr |= tabRightGreen[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    lda         _tabRightGreen,x
    ldy         #40
    ora         (_theAdr),y
    sta         (_theAdr),y

    ;; *theAdr |= tabRightBlue[renCurrentColor];
    ;; theAdr += NEXT_SCANLINE_INCREMENT;

    lda         _tabRightBlue,x
    ldy         #80
    ora         (_theAdr),y
    sta         (_theAdr),y

    clc     
    lda         _theAdr 
    adc         #120
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)

.)
    rts