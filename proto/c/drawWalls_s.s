;; Author : Jean-Baptiste PERIN
;; Date : 2021
;; 
#include "config.h"

.zero 

;; Variables shared with sprite
;; unsigned char *         ptrTexture;
_ptrTexture             .dsb 2

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
_columnTextureCoord     .dsb 1

;; unsigned char       wallId;
_wallId                 .dsb 1

.text

;; void drawWalls(){
_drawWalls
.(


	;; save context
    pha:txa:pha:tya:pha
	lda tmp0: pha: lda tmp0+1 : pha


;;     idxScreenCol        = VIEWPORT_START_COLUMN-1;
;;     ddaNbVal            = TEXTURE_SIZE;
;;     baseAdr             = (unsigned char *)(HIRES_SCREEN_ADDRESS + (idxScreenCol>>1));
;;     idxCurrentSlice     = 0;
;;     ddaStartValue       = 0;


        lda     #TEXTURE_SIZE
        sta     _ddaNbVal

        lda     #VIEWPORT_START_COLUMN-1
        sta     _idxScreenCol
        lsr     ;"

        adc     #<($A000)
        sta     _baseAdr
        lda     #>($A000)
        adc     #0
        sta     _baseAdr+1

        lda     #0
        sta     _ddaStartValue
        sta     _idxCurrentSlice



;;     do {
drawWalls_loop

;;         baseAdr             += 1;
;;         idxScreenCol        += 1;
;;         wallId              = raywall[idxCurrentSlice];

            inc _baseAdr: .( : bne skip : inc _baseAdr+1: skip:.)
            inc _idxScreenCol
            ldy _idxCurrentSlice
            lda _raywall,Y
            sta _wallId

;;         if (wallId !=255) {
                lda     _wallId
                cmp     #$FF
                .( : bne LeftSliceNotEmpy : jmp LeftSliceEmpty : LeftSliceNotEmpy : .)
;; 
;;     // =====================================
;;     // ============ LEFT TEXEL
;;     // =====================================
;; 
;; 
;;             columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1); // modulo 32
;;             offTexture          = multi32[columnTextureCoord];

                ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: sta _columnTextureCoord
                lda _columnTextureCoord: asl : tay : lda _multi32,Y: sta _offTexture : iny : lda _multi32,Y : sta _offTexture+1


;;             ptrTexture          = wallTexture[wallId];

                lda _wallId: asl: tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1

;;             ptrReadTexture      = &(ptrTexture[offTexture]);

                clc
                lda _ptrTexture
                adc _offTexture
                sta _ptrReadTexture
                lda _ptrTexture+1
                adc _offTexture+1
                sta _ptrReadTexture+1


;;             columnHeight        = TableVerticalPos[idxCurrentSlice]; 

                ldy _idxCurrentSlice
                lda _TableVerticalPos,Y
                sta _columnHeight

;;             ddaNbStep           = columnHeight<<1;

                lda _columnHeight : asl : sta _ddaNbStep

;;             ddaInit();

                ;; jsr _ddaInit

.(
;     ddaCurrentValue         = ddaStartValue;
    lda     _ddaStartValue
    sta     _ddaCurrentValue

;     ddaEndValue             = ddaStartValue + ddaNbVal;
    lda     _ddaNbVal
    clc
    adc     _ddaStartValue
    sta     _ddaEndValue
; 
;     if          (ddaNbVal > ddaNbStep) {
    lda     _ddaNbStep
    cmp     _ddaNbVal
    beq     NbStepEqualsNbVal
    bcs     NbStepGreaterThanNbVal
;         ddaCurrentError     = ddaNbVal;
            lda         _ddaNbVal
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep1;
            lda         #<(_ddaStep1)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_01+1
            sta         _patchCallStep_02+1
            lda         #>(_ddaStep1)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_01+2
            sta         _patchCallStep_02+2

    jmp     ddaInitDone
;     } else if   (ddaNbVal < ddaNbStep) {
NbStepGreaterThanNbVal    
;         ddaCurrentError     = ddaNbStep;
            lda         _ddaNbStep
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep2;
            lda         #<(_ddaStep2)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_01+1
            sta         _patchCallStep_02+1
            lda         #>(_ddaStep2)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_01+2
            sta         _patchCallStep_02+2
    jmp     ddaInitDone
;     } else {
NbStepEqualsNbVal    
;         ddaCurrentError     = ddaEndValue;
            lda         _ddaEndValue
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep0;
            lda         #<(_ddaStep0)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_01+1
            sta         _patchCallStep_02+1
            lda         #>(_ddaStep0)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_01+2
            sta         _patchCallStep_02+2
;     }
ddaInitDone
.)                

;;             idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;

                sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine

;; 
;;             while (idxScreenLine < VIEWPORT_START_LINE){
;;                 (*ddaStepFunction)();
;;                 idxScreenLine   += 1;
;;             } 


loop_000 : lda _idxScreenLine : 
                cmp #VIEWPORT_START_LINE : 
                bpl end_loop_000 

                   ;; jsr (_ddaStepFunction)
	               ;; lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :
	               ;;.( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
_patchCallStep_01 
                    jsr 0000

                   inc _idxScreenLine
                   jmp loop_000 
                end_loop_000



;;             // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
;;             theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]); 

                lda _idxScreenLine
                asl
                tay
                lda _multi120,Y
                iny
                clc
                adc _baseAdr
                sta _theAdr
                lda _multi120,Y
                adc _baseAdr+1
                sta _theAdr+1

;;             do {
;;                 (*ddaStepFunction)();
                   ;; jsr (_ddaStepFunction)
;;                 renCurrentColor = ptrReadTexture[ddaCurrentValue];
;;                 colorLeftTexel();  // theAdr          += 120;
;;                 idxScreenLine   += 1;
;;             } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


                 
LeftCol_loop_001 :


                    ;; lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1
                    ;; .( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .)
_patchCallStep_02 : jsr 0000
                    ldy _ddaCurrentValue : lda _ptrReadTexture,Y : sta _renCurrentColor : 
                 	lda _ddaCurrentValue : sta tmp0 :
                 	lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :
                 	lda _ptrReadTexture : sta tmp1 : lda _ptrReadTexture+1 : sta tmp1+1 :
                 	clc : lda tmp0 : adc tmp1 : sta tmp0 : lda tmp0+1 : adc tmp1+1 : sta tmp0+1 :
                 	ldy #0 : lda (tmp0),y : sta tmp0 :
                 	lda tmp0 : sta _renCurrentColor :   


                    ;; jsr _colorLeftTexel : 
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

                    inc _idxScreenLine : 
                    lda _idxScreenLine : 
                    cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
                    bcs LeftCol_endloop_001 : 
                    lda _ddaCurrentValue : 
                    cmp _ddaEndValue : 
                    bcs LeftCol_endloop_001 : 
                    jmp LeftCol_loop_001 : 
                    LeftCol_endloop_001 



;;         }
LeftSliceEmpty
;; 
;;         idxScreenCol        += 1;
;;         idxCurrentSlice     += 1;
;;         wallId              = raywall[idxCurrentSlice];

            inc _idxScreenCol : inc _idxCurrentSlice : ldy _idxCurrentSlice : lda _raywall,Y : sta _wallId

;;         if (wallId !=255) {
                lda     _wallId
                cmp     #$FF
                .( : bne RightSliceNotEmpy : jmp RightSliceEmpty : RightSliceNotEmpy : .)



;;             ptrTexture          = wallTexture[wallId];

                lda _wallId: asl : tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1

;;     // =====================================
;;     // ============ RIGHT TEXEL
;;     // =====================================
;;             columnHeight        = TableVerticalPos[idxCurrentSlice];
                ldy _idxCurrentSlice : lda _TableVerticalPos,Y : sta _columnHeight

;;             columnTextureCoord  = tabTexCol[idxCurrentSlice]&(TEXTURE_SIZE-1);  // modulo 32
;;             offTexture          = multi32[columnTextureCoord];

                ldy _idxCurrentSlice: lda _tabTexCol,Y: and #TEXTURE_SIZE-1: sta _columnTextureCoord
                lda _columnTextureCoord: asl : tay : lda _multi32,Y: sta _offTexture : iny : lda _multi32,Y : sta _offTexture+1


;;             ptrTexture          = wallTexture[wallId];

                lda _wallId: asl: tay: lda _wallTexture,Y: sta _ptrTexture: iny: lda _wallTexture,Y: sta _ptrTexture+1

;;             ptrReadTexture      = &(ptrTexture[offTexture]);

                clc
                lda _ptrTexture
                adc _offTexture
                sta _ptrReadTexture
                lda _ptrTexture+1
                adc _offTexture+1
                sta _ptrReadTexture+1



;;             idxScreenLine       = VIEWPORT_HEIGHT/2 - columnHeight + VIEWPORT_START_LINE;
                sec : lda #VIEWPORT_HEIGHT/2+VIEWPORT_START_LINE : sbc _columnHeight : sta _idxScreenLine
;; 
;;             ddaNbStep           = columnHeight<<1;

                lda _columnHeight : asl : sta _ddaNbStep

;;             ddaInit();

                ;;jsr _ddaInit

.(
;     ddaCurrentValue         = ddaStartValue;
    lda     _ddaStartValue
    sta     _ddaCurrentValue

;     ddaEndValue             = ddaStartValue + ddaNbVal;
    lda     _ddaNbVal
    clc
    adc     _ddaStartValue
    sta     _ddaEndValue
; 
;     if          (ddaNbVal > ddaNbStep) {
    lda     _ddaNbStep
    cmp     _ddaNbVal
    beq     NbStepEqualsNbVal
    bcs     NbStepGreaterThanNbVal
;         ddaCurrentError     = ddaNbVal;
            lda         _ddaNbVal
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep1;
            lda         #<(_ddaStep1)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_03+1
            sta         _patchCallStep_04+1
            lda         #>(_ddaStep1)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_03+2
            sta         _patchCallStep_04+2

    jmp     ddaInitDone
;     } else if   (ddaNbVal < ddaNbStep) {
NbStepGreaterThanNbVal    
;         ddaCurrentError     = ddaNbStep;
            lda         _ddaNbStep
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep2;
            lda         #<(_ddaStep2)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_03+1
            sta         _patchCallStep_04+1
            lda         #>(_ddaStep2)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_03+2
            sta         _patchCallStep_04+2
    jmp     ddaInitDone
;     } else {
NbStepEqualsNbVal    
;         ddaCurrentError     = ddaEndValue;
            lda         _ddaEndValue
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep0;
            lda         #<(_ddaStep0)
            ;; sta         _ddaStepFunction
            sta         _patchCallStep_03+1
            sta         _patchCallStep_04+1
            lda         #>(_ddaStep0)
            ;; sta         _ddaStepFunction+1
            sta         _patchCallStep_03+2
            sta         _patchCallStep_04+2
;     }
ddaInitDone
.)



;;             while (idxScreenLine < VIEWPORT_START_LINE){
;;                 (*ddaStepFunction)();
;;                 idxScreenLine   += 1;
;;             } 

loop_002 : lda _idxScreenLine :
                cmp #VIEWPORT_START_LINE :
                bpl end_loop_002 : 

                   ;; jsr (_ddaStepFunction)
	               ;; lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :
	               ;; .( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
_patchCallStep_03 : jsr 0000

                   inc _idxScreenLine :
                   jmp loop_002 :
                end_loop_002


;;             // theAdr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi120[idxScreenLine] + (idxScreenCol>>1));
;;             theAdr              = (unsigned char *)(baseAdr + multi120[idxScreenLine]);

                lda _idxScreenLine
                asl
                tay
                lda _multi120,Y
                iny
                clc
                adc _baseAdr
                sta _theAdr
                lda _multi120,Y
                adc _baseAdr+1
                sta _theAdr+1


;;             do {
;;                 (*ddaStepFunction)();
;;                 renCurrentColor = ptrReadTexture [ddaCurrentValue];
;;                 colorRightTexel(); // theAdr          += 120;
;;                 idxScreenLine   += 1;
;;             } while ((ddaCurrentValue < ddaEndValue) && (idxScreenLine < VIEWPORT_HEIGHT + VIEWPORT_START_LINE));


RightCol_loop_003 : 
                    ;; lda _ddaStepFunction : sta tmp0 : lda _ddaStepFunction+1 : sta tmp0+1 :
                    ;; .( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :

_patchCallStep_04 : jsr 0000

                	lda _ddaCurrentValue : sta tmp0 :
                	lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :
                	lda _ptrReadTexture : sta tmp1 : lda _ptrReadTexture+1 : sta tmp1+1 :
                	clc : lda tmp0 : adc tmp1 : sta tmp0 : lda tmp0+1 : adc tmp1+1 : sta tmp0+1 :
                	ldy #0 : lda (tmp0),y : sta tmp0 :
                	lda tmp0 : sta _renCurrentColor : 


                    ;; jsr _colorRightTexel : 

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

                    
                    inc _idxScreenLine : 
                    lda _idxScreenLine : 
                    cmp #VIEWPORT_HEIGHT + VIEWPORT_START_LINE : 
                    bcs RightCol_endloop_003 : 
                    lda _ddaCurrentValue : 
                    cmp _ddaEndValue : 
                    bcs RightCol_endloop_003 : 
                    jmp RightCol_loop_003 : 
                    RightCol_endloop_003

;;         }
RightSliceEmpty

;;         idxCurrentSlice++;
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
