


.zero

_theAdr .dsb  2

.text


_colorLeftTexel 
.(
    ldx         #0;"
    ldy         _renCurrentColor;"

    ;; *theAdr = tabLeftGreen[renCurrentColor];
    ;; theAdr += NEXT_LINE_INCREMENT;

    lda         _tabLeftRed,y
    sta         (_theAdr,x)
    clc     
    lda         _theAdr
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr = tabLeftGreen[renCurrentColor];
    ;; theAdr += NEXT_LINE_INCREMENT;

    lda         _tabLeftGreen,y
    sta         (_theAdr,x)

    clc     
    lda         _theAdr
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr = tabLeftBlue[renCurrentColor];
    ;; theAdr += NEXT_LINE_INCREMENT;


    lda         _tabLeftBlue,y
    sta         (_theAdr,x)
    clc     
    lda         _theAdr
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


.)
    rts

_colorRightTexel 
.(

    ldx         #0;"
    ldy         _renCurrentColor;"

    lda         _tabRightRed,y
    ora         (_theAdr,x)
    sta         (_theAdr,x)
    clc     
    lda         _theAdr
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr |= tabRightGreen[renCurrentColor];
    ;; theAdr += NEXT_LINE_INCREMENT;

    lda         _tabRightGreen,y
    ora         (_theAdr,x)
    sta         (_theAdr,x)
    clc     
    lda         _theAdr;" // TODO : optimize by adding constant (use bcc as in https://codebase64.org/doku.php?id=base:16bit_addition_and_subtraction
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)


    ;; *theAdr |= tabRightBlue[renCurrentColor];
    ;; theAdr += NEXT_LINE_INCREMENT;


    lda         _tabRightBlue,y
    ora         (_theAdr,x)
    sta         (_theAdr,x)
    clc     
    lda         _theAdr ;; TODO : optimize by adding constant (use bcc as in https://codebase64.org/doku.php?id=base:16bit_addition_and_subtraction) 
    adc         #40
    sta         _theAdr
.(  
    bcc skip:    inc _theAdr+1: skip .)

.)
    rts