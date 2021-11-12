



;; Taken from http://6502org.wikidot.com/software-output-decimal
#define LORES_SCREEN_ADDRESS            48000
#define NUM_LIGNE 26
#define NUM_COLONNE 17
#define ADR_WRITE LORES_SCREEN_ADDRESS+NUM_LIGNE*40+NUM_COLONNE


.zero
;; tmpY .dsb 1
.text

;; varA .byt  128,160,200
;; varB .dsb  1
;; varC .dsb  1

;; idwWrt .dsb 1


;; OUTPUT:
;; .(
;;     sty tmpY
;;     ldy idwWrt
;;     sta ADR_WRITE, Y
;;     inc idwWrt
;;     ldy tmpY
;; .)
;;     rts
;; _OUTDEC8S:
;; .(
;;             LDA _remaining_seconds
;;             LDX #1
;;             STX varC
;;             INX
;;             LDY #$40
;; label1      STY varB
;;             LSR
;; label2      ROL
;;             BCS label3
;;             CMP varA,X
;;             BCC label4
;; label3      SBC varA,X
;;             SEC
;; label4      ROL varB
;;             BCC label2
;;             TAY
;;             CPX varC
;;             LDA varB
;;             BCC label5
;;             BEQ label6
;;             STX varC
;; label5      EOR #$10
;; label6      EOR #$20
;;             JSR OUTPUT
;;             TYA
;;             LDY #$10
;;             DEX
;;             BPL label1
;; .)
;;    RTS




game_pulse:
.(
;;     lda _running
;;     beq game_pulse_done
;;     lda _remaining_seconds
;;     beq skip_dec
;;     dec _remaining_seconds
;; skip_dec
;;     lda #0
;;     sta idwWrt
;;     jsr _OUTDEC8S
game_pulse_done:    
.)
    rts