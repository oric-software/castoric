#include "config.h"
;; 6502 Assembly routine for  Digital Differential Analyzer Algorithm
;; 
;; Author : Jean-Baptiste PERIN
;; Date : 2021

#ifndef USE_C_DDA
.zero
;; void            (*ddaStepFunction)(); 
_ddaStepFunction    .dsb 2


;; unsigned char   ddaNbVal;
_ddaNbVal       .dsb 1 ;; TODO : remove me cause I'm allways #TEXTURE_SIZE
;; unsigned char   ddaNbStep;
_ddaNbStep      .dsb 1

;; unsigned char   ddaStartValue;
_ddaStartValue  .dsb 1 ;; TODO : remove me cause I'm allways 0


;; unsigned char   ddaCurrentValue;
_ddaCurrentValue    .dsb 1
;; unsigned char   ddaEndValue;
_ddaEndValue        .dsb 1 ;; TODO : remove me cause I'm allways #TEXTURE_SIZE


;; signed char     ddaCurrentError;
_ddaCurrentError    .dsb 1



.text


; void ddaStep0(){
;     ddaCurrentValue         += 1;
; }
_ddaStep0
.(
    inc         _ddaCurrentValue
.)
    rts

; void ddaStep1(){
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
;         ddaCurrentError         -= ddaNbStep;
;         ddaCurrentValue         += 1;
;     }
;     ddaCurrentError     += ddaNbVal;
; }
_ddaStep1
.(
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
loop
    lda         _ddaCurrentError
    bmi         end_loop
    asl         
    cmp         _ddaNbStep
    bcc         end_loop
            lda         _ddaCurrentError
            sec ;; FIXME : this sec is useless
            sbc         _ddaNbStep
            sta         _ddaCurrentError
            inc         _ddaCurrentValue
    jmp         loop
end_loop
    lda         _ddaCurrentError
    clc
    adc         #TEXTURE_SIZE
    sta         _ddaCurrentError
.)
    rts


; void ddaStep2(){
;     ddaCurrentError         -= ddaNbVal;
;     if ((ddaCurrentError<<1) < ddaNbStep) {
;         ddaCurrentError     += ddaNbStep;
;         ddaCurrentValue     += 1;
;     }
; }
_ddaStep2
.(
;     ddaCurrentError         -= ddaNbVal;
    lda         _ddaCurrentError
    sec
    sbc         #TEXTURE_SIZE
    sta         _ddaCurrentError
;     if ((ddaCurrentError<<1) < ddaNbStep) {
    bmi         updateError
    asl
    cmp         _ddaNbStep
    bcc         updateError
    rts
updateError
;         ddaCurrentError     += ddaNbStep;
            lda         _ddaCurrentError
            clc
            adc         _ddaNbStep
            sta         _ddaCurrentError
;         ddaCurrentValue     += 1;
            inc         _ddaCurrentValue
;     }

.)
    rts



; void ddaInit(){
;     ddaCurrentValue         = ddaStartValue;
;     ddaEndValue             = ddaStartValue + ddaNbVal;
; 
;     if          (ddaNbVal > ddaNbStep) {
;         ddaCurrentError     = ddaNbVal;
;         ddaStepFunction     = &ddaStep1;
;     } else if   (ddaNbVal < ddaNbStep) {
;         ddaCurrentError     = ddaNbStep;
;         ddaStepFunction     = &ddaStep2;
;     } else {
;         ddaCurrentError     = ddaEndValue;
;         ddaStepFunction     = &ddaStep0;
;     }
; }

_ddaInit
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
            sta         _ddaStepFunction
            lda         #>(_ddaStep1)
            sta         _ddaStepFunction+1

    jmp     ddaInitDone
;     } else if   (ddaNbVal < ddaNbStep) {
NbStepGreaterThanNbVal    
;         ddaCurrentError     = ddaNbStep;
            lda         _ddaNbStep
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep2;
            lda         #<(_ddaStep2)
            sta         _ddaStepFunction
            lda         #>(_ddaStep2)
            sta         _ddaStepFunction+1
    jmp     ddaInitDone
;     } else {
NbStepEqualsNbVal    
;         ddaCurrentError     = ddaEndValue;
            lda         _ddaEndValue
            sta         _ddaCurrentError
;         ddaStepFunction     = &ddaStep0;
            lda         #<(_ddaStep0)
            sta         _ddaStepFunction
            lda         #>(_ddaStep0)
            sta         _ddaStepFunction+1
;     }
ddaInitDone
.)
    rts

#endif // USE_C_DDA    