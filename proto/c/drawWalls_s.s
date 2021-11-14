;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 
#include "config.h"
#include "tabAdrTabIdxRd.h"
.zero 

;; Variables shared with sprite
;; unsigned char *         ptrTexture;
_ptrTexture             .dsb 2 ;; TODO: Remove me cause i am useless

;; unsigned char *ptrOffsetIndex;
_ptrOffsetIndex         .dsb 2

.text

;; unsigned int offTexture;
_offTexture              .dsb 2

#ifndef USE_C_DRAWWALLS


.zero
;; unsigned char *     ptrReadTexture;             // Address of the texture 
_ptrReadTexture         .dsb 2


;; unsigned char *     ptrTexture;             // Address of the texture 
_prtTexture             .dsb 2

;; unsigned char       idxCurrentSlice;
_idxCurrentSlice        .dsb 1

;; unsigned char *     baseAdr;
_baseAdr                .dsb 2

;; signed char         idxScreenLine, idxScreenCol;
_idxScreenLine          .dsb 1
_idxScreenCol           .dsb 1

;; unsigned char       columnHeight, columnTextureCoord;
_columnHeight           .dsb 1
_columnTextureCoord     .dsb 1 ;; TODO remove me cause I'm useless

;; unsigned char       wallId;
_wallId                 .dsb 1

;; unsigned char       ddaNbIter;
_ddaNbIter              .dsb 1

.text


#define PREPARE :.(:\
    ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: :\
    tay:\
    lda _multi32_low,Y: sta _offTexture : lda _multi32_high,Y : sta _offTexture+1:\
    ldy _idxCurrentSlice:\
    lda _TableVerticalPos,Y:\
    .(:cmp #48:bcc skip: lda #47: skip:.):\
    sta _columnHeight:\
    asl : sta _ddaNbStep: sta _ddaNbIter :\
    sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine:\
    lda #0 : sta _ddaCurrentValue:\
    ldy _wallId: lda _wallTexture_low,Y: :\
    clc:\
    adc _offTexture:\
    sta _ptrReadTexture:\
    lda _wallTexture_high,Y: adc _offTexture+1:\
    sta _ptrReadTexture+1::\
.)



#define PREPARE_UNROLL_SAMPLE :.(:\
        lda _ddaNbStep: sta _ddaNbIter :\
        tay  :\
        lda _adrTabIdxRd_low,Y :\
        sta _ptrOffsetIndex :\
        lda _adrTabIdxRd_high,Y :\
        sta _ptrOffsetIndex+1 :\
        lda #0 : sta _nxtOffsetIndex :\
.)

; x contains _renCurrentColor
#define COLOR_LEFT_TEXEL :.(:\
    lda         _tabLeftRed,x:\
    ldy         #0:\
    sta         (_theAdr),y:\
    lda         _tabLeftGreen,x:\
    ldy         #40:\
    sta         (_theAdr),y:\
    lda         _tabLeftBlue,x:\
    ldy         #80:\
    sta         (_theAdr),y:\
    clc     :\
    lda         _theAdr:\
    adc         #120:\
    sta         _theAdr:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)


; x contains _renCurrentColor
#define COLOR_LEFT_TEXEL_FIRST :.(:\
    lda         _tabLeftRed,x:\
    ldy         #0:\
    sta         (_theAdr),y:\
    lda         _tabLeftGreen,x:\
    ldy         #40:\
    sta         (_theAdr),y:\
    lda         _tabLeftBlue,x:\
    ldy         #80:\
    sta         (_theAdr),y:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)


; x contains _renCurrentColor
#define COLOR_LEFT_TEXEL_SECOND :.(:\
    lda         _tabLeftRed,x:\
    ldy         #120:\
    sta         (_theAdr),y:\
    lda         _tabLeftGreen,x:\
    ldy         #160:\
    sta         (_theAdr),y:\
    lda         _tabLeftBlue,x:\
    ldy         #200:\
    sta         (_theAdr),y:\
    clc     :\
    lda         _theAdr:\
    adc         #240:\
    sta         _theAdr:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)

; x contains _renCurrentColor
#define COLOR_RIGHT_TEXEL :.(:\
    lda         _tabRightRed,x:\
    ldy         #0:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightGreen,x:\
    ldy         #40:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightBlue,x:\
    ldy         #80:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    clc     :\
    lda         _theAdr :\
    adc         #120:\
    sta         _theAdr:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)


; x contains _renCurrentColor
#define COLOR_RIGHT_TEXEL_FIRST :.(:\
    lda         _tabRightRed,x:\
    ldy         #0:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightGreen,x:\
    ldy         #40:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightBlue,x:\
    ldy         #80:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)

; x contains _renCurrentColor
#define COLOR_RIGHT_TEXEL_SECOND :.(:\
    lda         _tabRightRed,x:\
    ldy         #120:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightGreen,x:\
    ldy         #160:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    lda         _tabRightBlue,x:\
    ldy         #200:\
    ora         (_theAdr),y:\
    sta         (_theAdr),y:\
    clc     :\
    lda         _theAdr :\
    adc         #240:\
    sta         _theAdr:\
.(  :\
    bcc skip:    inc _theAdr+1: skip .):\
.)

;; ddaCurrentValue = ptrOffsetIndex[nxtOffsetIndex++];
#define DDA_STEP :.( :\
     ldy        _nxtOffsetIndex:\
     lda        (_ptrOffsetIndex), Y:\
     sta        _ddaCurrentValue:\
     iny:\
     sty         _nxtOffsetIndex:\
.):
;; FIXME : this clc is useless
#define DDA_STEP_2 :.( :\
     lda         _ddaCurrentError:\
     sec:\
     sbc         #TEXTURE_SIZE:\
     sta         _ddaCurrentError:\
     bmi         updateError:\
     asl:\
     cmp         _ddaNbStep:\
     bcs         step2Done:\
updateError:\
        lda         _ddaCurrentError:\
        clc:\
        adc         _ddaNbStep:\
        sta         _ddaCurrentError:\
        inc         _ddaCurrentValue:\
step2Done:\
 .)




#define OVER_SAMPLE(prim) :.(:\
    lda _ddaNbStep: sta _ddaCurrentError:\
loop_000 : lda _idxScreenLine :\
        cmp #VIEWPORT_START_LINE :\
        bpl end_loop_000:\
        DDA_STEP_2:\
        inc _idxScreenLine:\
        jmp loop_000 :\
end_loop_000:\
    ldy _idxScreenLine:lda _multi120_low,Y:clc:adc _baseAdr:sta _theAdr:lda _multi120_high,Y:adc _baseAdr+1:sta _theAdr+1 :\
loop_001 :\
        DDA_STEP_2:\
        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y :\
        tax:\
        prim:\
        inc _idxScreenLine :\
        lda _idxScreenLine :\
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE :\
        bcs endloop_001 :\
        jmp loop_001 :\
endloop_001 :\
.)


#define UNROLL_SAMPLE(prim_frst,prim_scnd) :.(:\
    lda     #TEXTURE_SIZE: sta _ddaCurrentError:\
loop_000 : lda _idxScreenLine :\
        cmp #VIEWPORT_START_LINE :\
        bpl end_loop_000:\
        DDA_STEP:\
        dec _ddaNbIter:\
        inc _idxScreenLine:\
        jmp loop_000 :\
end_loop_000:\
    ldy _idxScreenLine:lda _multi120_low,Y:clc:adc _baseAdr:sta _theAdr:lda _multi120_high,Y:adc _baseAdr+1:sta _theAdr+1 :\
loop_001 :\
        DDA_STEP:\
        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y :\
        tax:\
        prim_frst:\
        inc _idxScreenLine:\
        dec _ddaNbIter:\
        beq endloop_001 : \
        DDA_STEP:\
        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y :\
        tax:\
        prim_scnd:\
        inc _idxScreenLine:\
        lda _idxScreenLine :\
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE :\
        bcs endloop_001 :\
        dec _ddaNbIter:\
        beq endloop_001 : \
        jmp loop_001 :\
endloop_001 :\
.)
    ;; TODO : replace by bcc loop_001

drawLeftColumn
.(
    PREPARE
    lda _ddaNbStep: 
    cmp #64
    bcs goOverSample
    jmp goUnroll
goOverSample    
        ;; PREPARE_OVER_SAMPLE
        OVER_SAMPLE(COLOR_LEFT_TEXEL)
    jmp drawLeftColumnDone
goUnroll    
        PREPARE_UNROLL_SAMPLE
        DDA_STEP

        UNROLL_SAMPLE(COLOR_LEFT_TEXEL_FIRST,COLOR_LEFT_TEXEL_SECOND)

drawLeftColumnDone
.)
    rts

drawRightColumn
.(
    PREPARE

    
    lda _ddaNbStep:
    cmp #64
    bcs goOverSample
    jmp goUnroll
goOverSample    

        OVER_SAMPLE(COLOR_RIGHT_TEXEL)

    jmp drawRightColumnDone
goUnroll    
        PREPARE_UNROLL_SAMPLE

        DDA_STEP

        UNROLL_SAMPLE(COLOR_RIGHT_TEXEL_FIRST,COLOR_RIGHT_TEXEL_SECOND)

drawRightColumnDone
.)
    rts

;; void drawWalls(){
_drawWalls
.(


	;; save context
    ;; pha:txa:pha:tya:pha
	;; lda tmp0: pha: lda tmp0+1 : pha

    ; idxScreenCol        = VIEWPORT_START_COLUMN;
    ; baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
    ; idxCurrentSlice     = 0;

    lda     #VIEWPORT_START_COLUMN
    sta     _idxScreenCol
    lsr     

    adc     #<($A000)
    sta     _baseAdr
    lda     #>($A000)
    adc     #0
    sta     _baseAdr+1

    lda     #0
    sta     _idxCurrentSlice

    
;;     do {
drawWalls_loop
          

;;         baseAdr             += 1;
;;         idxScreenCol        += 1;
;;         wallId              = raywall[idxCurrentSlice];

            inc _baseAdr: .( : bne skip : inc _baseAdr+1: skip:.)
            inc _idxScreenCol

            jsr _clearColumn
            
            ldy _idxCurrentSlice
            lda _raywall,Y
            sta _wallId

;;         if (wallId !=255) {
                ; SAVED lda     _wallId : cause A already contains wallId
            cmp     #$FF
            .( : bne LeftSliceNotEmpy : jmp LeftSliceEmpty : LeftSliceNotEmpy : .)

            jsr drawLeftColumn

;;         }
LeftSliceEmpty
;; 
;;         idxScreenCol        += 1;
;;         idxCurrentSlice     += 1;
;;         wallId              = raywall[idxCurrentSlice];

            inc _idxScreenCol : inc _idxCurrentSlice : ldy _idxCurrentSlice : lda _raywall,Y : sta _wallId

;;         if (wallId !=255) {
                ; SAVED because A already contains _wallId : lda     _wallId
            cmp     #$FF
            .( : bne RightSliceNotEmpy : jmp RightSliceEmpty : RightSliceNotEmpy : .)
                jsr drawRightColumn
;;         }
RightSliceEmpty
            inc         _idxCurrentSlice

;;     } while (idxCurrentSlice < NUMBER_OF_SLICE-1);
        lda         _idxCurrentSlice
        cmp         #NUMBER_OF_SLICE-2
        beq         end_drawWalls
        jmp         drawWalls_loop
end_drawWalls
;; }

	;; restore context
	;;pla: sta tmp0+1: pla: sta tmp0
	;;pla:tay:pla:tax:pla


.)
    rts


#endif // USE_C_DRAWWALLS
