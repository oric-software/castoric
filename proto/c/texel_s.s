
#include "config.h"

.zero

_theAdr .dsb  2

.text

#ifndef USE_C_COLORTEXEL

_colorLeftTexel 
.(
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

    clc     
    lda         _theAdr 
    adc         #120
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)

.)
    rts

#endif // USE_C_COLORTEXEL    