
;; Author: Jean-Baptiste PERIN 

#include "via.h"

.zero

_ayReg0      .dsb 1    ; R0  : Chan A Tone Period Fine (LSB)
_ayReg1      .dsb 1    ; R1  : Chan A Tone Period Coarse (HSB)
_ayReg2      .dsb 1    ; R2  : Chan B Tone Period Fine (LSB)
_ayReg3      .dsb 1    ; R3  : Chan B Tone Period Coarse (HSB)
_ayReg4      .dsb 1    ; R4  : Chan C Tone Period Fine (LSB)
_ayReg5      .dsb 1    ; R5  : Chan C Tone Period Coarse (HSB)
_ayReg6      .dsb 1    ; R6  : Noise Period 
_ayReg7      .dsb 1    ; R7  : Mixer 
_ayReg8      .dsb 1    ; R8  : Chan A Amplitude 
_ayReg9      .dsb 1    ; R9  : Chan B Amplitude
_ayReg10     .dsb 1    ; R10 : Chan C Amplitude
_ayReg11     .dsb 1    ; R11 : Envelope Period Fine 
_ayReg12     .dsb 1    ; R12 : Envelope Period Coarse 
_ayReg13     .dsb 1    ; R13 : Envelope Shape / Cycle 

; store precalculated values to write in via PCR for latch sequence
ayLatch_N   .dsb 1
ayLatch_V   .dsb 1
ayUnlatch   .dsb 1

; temporary variable
ayTmp       .dsb 1

.text

#define LATCH_REG_NUMBER     sta via_porta:lda ayLatch_N:sta via_pcr:lda ayUnlatch: sta via_pcr
#define LATCH_REG_VALUE      sta via_porta:lda ayLatch_V:sta via_pcr:lda ayUnlatch: sta via_pcr


_ayInit:
    lda #0 
    sta _ayReg0 
    sta _ayReg1 
    sta _ayReg2 
    sta _ayReg3 
    sta _ayReg4 
    sta _ayReg5 
    sta _ayReg6 
    sta _ayReg8 
    sta _ayReg9 
    sta _ayReg10
    sta _ayReg11
    sta _ayReg12
    sta _ayReg13

    lda #$3F    
    sta _ayReg7 
   
_ayUpdate:

    ; sei

    ;; Save bits 
    lda     via_pcr
    and     #$11
    sta     ayTmp

    ;; Prepare values used in latch sequence of VIA 6522
    ora     #$EE     
    sta     ayLatch_N
    lda     ayTmp
    ora     #$EC
    sta     ayLatch_V
    lda     ayTmp
    ora     #$CC
    sta     ayUnlatch

    ;; Tranfert registers one by one

;    lda     #0
;    LATCH_REG_NUMBER
;    sta     via_porta 
;    lda     ayLatch_N
;    sta     via_pcr 
;    lda     ayUnlatch
;    sta     via_pcr
;    lda     _ayReg0
;    LATCH_REG_VALUE
;    sta     via_porta 
;    lda     ayLatch_V
;    sta     via_pcr 
;    lda     ayUnlatch
;    sta     via_pcr

    lda #0 : LATCH_REG_NUMBER: lda _ayReg0 : LATCH_REG_VALUE
    lda #1 : LATCH_REG_NUMBER: lda _ayReg1 : LATCH_REG_VALUE
    lda #2 : LATCH_REG_NUMBER: lda _ayReg2 : LATCH_REG_VALUE
    lda #3 : LATCH_REG_NUMBER: lda _ayReg3 : LATCH_REG_VALUE
    lda #4 : LATCH_REG_NUMBER: lda _ayReg4 : LATCH_REG_VALUE
    lda #5 : LATCH_REG_NUMBER: lda _ayReg5 : LATCH_REG_VALUE
    lda #6 : LATCH_REG_NUMBER: lda _ayReg6 : LATCH_REG_VALUE
    lda #7 : LATCH_REG_NUMBER: lda _ayReg7 : ORA #$40: LATCH_REG_VALUE
    lda #8 : LATCH_REG_NUMBER: lda _ayReg8 : LATCH_REG_VALUE
    lda #9 : LATCH_REG_NUMBER: lda _ayReg9 : LATCH_REG_VALUE
    lda #10: LATCH_REG_NUMBER: lda _ayReg10: LATCH_REG_VALUE
    lda #11: LATCH_REG_NUMBER: lda _ayReg11: LATCH_REG_VALUE
    lda #12: LATCH_REG_NUMBER: lda _ayReg12: LATCH_REG_VALUE
    lda #13: LATCH_REG_NUMBER: lda _ayReg13: LATCH_REG_VALUE    


;    lda #0 : ldx _ayReg0 : jsr ayWriteRegister
;    lda #1 : ldx _ayReg1 : jsr ayWriteRegister
;    lda #2 : ldx _ayReg2 : jsr ayWriteRegister
;    lda #3 : ldx _ayReg3 : jsr ayWriteRegister
;    lda #4 : ldx _ayReg4 : jsr ayWriteRegister
;    lda #5 : ldx _ayReg5 : jsr ayWriteRegister
;    lda #6 : ldx _ayReg6 : jsr ayWriteRegister
;    lda #7 : ldx _ayReg7 : jsr ayWriteRegister
;    lda #8 : ldx _ayReg8 : jsr ayWriteRegister
;    lda #9 : ldx _ayReg9 : jsr ayWriteRegister
;    lda #10: ldx _ayReg10: jsr ayWriteRegister
;    lda #11: ldx _ayReg11: jsr ayWriteRegister
;    lda #12: ldx _ayReg12: jsr ayWriteRegister
;    lda #13: ldx _ayReg13: jsr ayWriteRegister
    

    ; cli
    rts     


; parametre A = register number of 8912
; parametre X = donnée à transférer
ayWriteRegister:
.(
    PHP              
    SEI              
    STA via_porta    
    TAY              
    TXA              
    CPY #$07         
    BNE WriteToAY_F59D        
    ORA #$40         
WriteToAY_F59D:
    PHA              
    LDA via_pcr      
    ORA #$EE         
    STA via_pcr      
    AND #$11         
    ORA #$CC         
    STA via_pcr      
    TAX              
    PLA              
    STA via_porta    
    TXA              
    ORA #$EC         
    STA via_pcr      
    AND #$11         
    ORA #$CC         
    STA via_pcr      
    plp
.)              
    rts              


;; Compute amplitude command to store in PSG register based on:
;;  the required volume in register X and consigne in register A
;; INPUTS :
;; Consigne in 4 LSB of register A
;; Volume  in 4 MSB of register X
;; OUTPUT :
;; Command in 4 LSB of register A
;; Destroys registers A and X

compensate:
.(
    stx     ayTmp
    and     ayTmp
    tax
    lda     compensAY,x
.)
    rts

compensAY 	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1
	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2
	.byt 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3
	.byt 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4
	.byt 0, 0, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5
	.byt 0, 0, 0, 1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6
	.byt 0, 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7
	.byt 0, 0, 2, 3, 4, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8
	.byt 0, 1, 3, 4, 5, 6, 6, 7, 7, 8, 8, 8, 8, 9, 9, 9
	.byt 0, 2, 4, 5, 6, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10
	.byt 0, 3, 5, 6, 7, 8, 8, 9, 9, 10, 10, 10, 10, 11, 11, 11
	.byt 0, 4, 6, 7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 12, 12, 12
	.byt 0, 5, 7, 8, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13
	.byt 0, 6, 8, 9, 10, 11, 11, 12, 12, 13, 13, 13, 13, 14, 14, 14
	.byt 0, 7, 9, 10, 11, 12, 12, 13, 13, 14, 14, 14, 14, 15, 15, 15

