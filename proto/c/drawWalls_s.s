;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 
#include "config.h"

.zero 

;; Variables shared with sprite
;; unsigned char *         ptrTexture;
_ptrTexture             .dsb 2 ;; TODO: Remove me cause i am useless

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

.text

; PREPARE
; .(
;     ; columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);\
;     ; offTexture          = (multi32_high[columnTextureCoord] << 8) | multi32_low[columnTextureCoord];\
;     ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: 
;     tay
;     lda _multi32_low,Y: sta _offTexture : lda _multi32_high,Y : sta _offTexture+1
;     ; ptrTexture          = (unsigned char *)((wallTexture_high[wallId] << 8) | wallTexture_low[wallId]);\
;     ; ptrReadTexture      = &(ptrTexture[offTexture]);\
;     ldy _wallId: lda _wallTexture_low,Y: 
;     clc
;     adc _offTexture
;     sta _ptrReadTexture: ; sta _ptrTexture
;     lda _wallTexture_high,Y: adc _offTexture+1: 
;     sta _ptrReadTexture+1: ; sta _ptrTexture+1
;     ; columnHeight        = TableVerticalPos[idxCurrentSlice];\
;     ; ddaNbStep           = columnHeight<<1;\
;     ldy _idxCurrentSlice
;     lda _TableVerticalPos,Y
;     sta _columnHeight
;     asl : sta _ddaNbStep
;     ; idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;\
;     sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine
;     ; ddaCurrentValue     = 0;
;     lda #0 : sta _ddaCurrentValue
; .)
;     rts
; 

#define PREPARE :.(:\
    ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: :\
    tay:\
    lda _multi32_low,Y: sta _offTexture : lda _multi32_high,Y : sta _offTexture+1:\
    ldy _wallId: lda _wallTexture_low,Y: :\
    clc:\
    adc _offTexture:\
    sta _ptrReadTexture:\
    lda _wallTexture_high,Y: adc _offTexture+1:\
    sta _ptrReadTexture+1::\
    ldy _idxCurrentSlice:\
    lda _TableVerticalPos,Y:\
    sta _columnHeight:\
    asl : sta _ddaNbStep:\
    sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine:\
    lda #0 : sta _ddaCurrentValue:\
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


; DDA_STEP_0
; .(
;     inc         _ddaCurrentValue
; .)
;     rts
#define DDA_STEP_0 inc _ddaCurrentValue:

; DDA_STEP_1
; .(
; loop
;     lda         _ddaCurrentError
;     bmi         end_loop
;     asl         
;     cmp         _ddaNbStep
;     bcc         end_loop
;             lda         _ddaCurrentError
;             sec ;; FIXME : this sec is useless
;             sbc         _ddaNbStep
;             sta         _ddaCurrentError
;             inc         _ddaCurrentValue
;     jmp         loop
; end_loop
;     lda         _ddaCurrentError
;     clc
;     adc         #TEXTURE_SIZE
;     sta         _ddaCurrentError
; .)
;     rts

;; FIXME : this sec is useless
#define DDA_STEP_1 :.(:loop:\
    lda         _ddaCurrentError:\
    bmi         end_loop:\
    asl         :\
    cmp         _ddaNbStep:\
    bcc         end_loop:\
            lda         _ddaCurrentError:\
            sec :\
            sbc         _ddaNbStep:\
            sta         _ddaCurrentError:\
            inc         _ddaCurrentValue:\
    jmp         loop:\
end_loop:\
    lda         _ddaCurrentError:\
    clc:\
    adc         #TEXTURE_SIZE:\
    sta         _ddaCurrentError:\
.):


; DDA_STEP_2
; .(
;     lda         _ddaCurrentError
;     sec
;     sbc         #TEXTURE_SIZE
;     sta         _ddaCurrentError
; ;     if ((ddaCurrentError<<1) < ddaNbStep) {
;     bmi         updateError
;     asl
;     cmp         _ddaNbStep
;     bcc         updateError
;     rts
; updateError
; ;         ddaCurrentError     += ddaNbStep;
;             lda         _ddaCurrentError
;             clc
;             adc         _ddaNbStep
;             sta         _ddaCurrentError
; ;         ddaCurrentValue     += 1;
;             inc         _ddaCurrentValue
; ;     }
; .)
;     rts

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

UNDER_SAMPLE_LEFT
.(
    ; ddaCurrentError     = TEXTURE_SIZE;\
    lda     #TEXTURE_SIZE: sta _ddaCurrentError
    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_1;\
    ;     idxScreenLine   += 1;\
    ; } \ TODO : this loop is useless when undersampling 
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_1
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_1;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_1

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_LEFT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts

OVER_SAMPLE_LEFT
.(
    ; ddaCurrentError     = ddaNbStep;\
    lda _ddaNbStep: sta _ddaCurrentError

    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_2;\
    ;     idxScreenLine   += 1;\
    ; } \
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_2
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_2;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_2

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_LEFT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts

COPY_SAMPLE_LEFT
.(
    ; ddaCurrentError     = TEXTURE_SIZE;\
    lda     #TEXTURE_SIZE: sta _ddaCurrentError

    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_0;\
    ;     idxScreenLine   += 1;\
    ; } \ TODO : this loop is useless when undersampling 
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_0
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_0;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_0

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_LEFT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts


UNDER_SAMPLE_RIGHT
.(
    ; ddaCurrentError     = TEXTURE_SIZE;\
    lda     #TEXTURE_SIZE: sta _ddaCurrentError
    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_1;\
    ;     idxScreenLine   += 1;\
    ; } \ TODO : this loop is useless when undersampling 
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_1
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_1;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_1

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_RIGHT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts

OVER_SAMPLE_RIGHT
.(
    ; ddaCurrentError     = ddaNbStep;\
    lda _ddaNbStep: sta _ddaCurrentError

    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_2;\
    ;     idxScreenLine   += 1;\
    ; } \
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_2
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_2;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_2

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_RIGHT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts

COPY_SAMPLE_RIGHT
.(
    ; ddaCurrentError     = TEXTURE_SIZE;\
    lda     #TEXTURE_SIZE: sta _ddaCurrentError

    ; while (idxScreenLine < VIEWPORT_START_LINE){\
    ;     DDA_STEP_0;\
    ;     idxScreenLine   += 1;\
    ; } \ TODO : this loop is useless when undersampling 
loop_000 : lda _idxScreenLine : 
        cmp #VIEWPORT_START_LINE : 
        bpl end_loop_000 
        DDA_STEP_0
        inc _idxScreenLine
        jmp loop_000 
end_loop_000

    ; theAdr              = (unsigned char *)(baseAdr + (int)((multi120_high[idxScreenLine]<<8) | multi120_low[idxScreenLine]));\
    ldy _idxScreenLine
    lda _multi120_low,Y
    clc
    adc _baseAdr
    sta _theAdr
    lda _multi120_high,Y
    adc _baseAdr+1
    sta _theAdr+1

    ; do {\
    ;     DDA_STEP_0;\
    ;     renCurrentColor = ptrReadTexture [ddaCurrentValue];\
    ;     prim;\
    ;     idxScreenLine   += 1;\
    ; } while ((ddaCurrentValue < TEXTURE_SIZE) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));
loop_001 :

        DDA_STEP_0

        ldy _ddaCurrentValue : lda (_ptrReadTexture),Y : 
        tax ;; SAVED sta _renCurrentColor : 

        COLOR_RIGHT_TEXEL

        inc _idxScreenLine

        lda _idxScreenLine : 
        cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
        bcs endloop_001 : 
        lda _ddaCurrentValue : 
        cmp #TEXTURE_SIZE 
        bcs endloop_001 : ;; TODO : replace by bcc loop_001
        jmp loop_001 : 
endloop_001 
.)
    rts

drawLeftColumn
.(
    PREPARE

    lda     _ddaNbStep
    cmp     #TEXTURE_SIZE
    beq     NbStepEqualsNbVal
    bcs     NbStepGreaterThanNbVal
        jsr UNDER_SAMPLE_LEFT
    jmp     drawLeftColumnDone
NbStepGreaterThanNbVal    
        jsr OVER_SAMPLE_LEFT
    jmp     drawLeftColumnDone
NbStepEqualsNbVal    
        jsr COPY_SAMPLE_LEFT
drawLeftColumnDone
   
.)
    rts

drawRightColumn
.(
    PREPARE

    lda     _ddaNbStep
    cmp     #TEXTURE_SIZE
    beq     NbStepEqualsNbVal
    bcs     NbStepGreaterThanNbVal
        jsr UNDER_SAMPLE_RIGHT
    jmp     drawRightColumnDone
NbStepGreaterThanNbVal    
        jsr OVER_SAMPLE_RIGHT
    jmp     drawRightColumnDone
NbStepEqualsNbVal    
        jsr COPY_SAMPLE_RIGHT
drawRightColumnDone
.)
    rts

;; void drawWalls(){
_drawWalls
.(


	;; save context
    pha:txa:pha:tya:pha
	lda tmp0: pha: lda tmp0+1 : pha

    ; idxScreenCol        = VIEWPORT_START_COLUMN-1;
    ; baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
    ; idxCurrentSlice     = 0;

    lda     #VIEWPORT_START_COLUMN-1
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
	pla: sta tmp0+1: pla: sta tmp0
	pla:tay:pla:tax:pla


.)
    rts


#endif // USE_C_DRAWWALLS
