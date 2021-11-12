;;
;; Circular Buffer 
;;
;; Author :  Jean-Baptiste PERIN
;;


#define TEMPLATE keybuf

// BEWARE : Only use Power of Two ::
#define NB_MAX_KEY_EVENT    16

.text

c_keybuf        .dsb NB_MAX_KEY_EVENT

iR_keybuf            .byt 0
iW_keybuf             .byt 0
_nbE_keybuf            .byt 0

; Register A contains element to add in buffer
add_keybuf:
.(
    ; Buff[iW ] = E
    ; iW = (iW + 1)%NBM
    ; SI iW == iR Alors
    ;   iR = (iR+1)%NBM
    ; Sinon
    ;   nbE = nbE + 1
    ; Finsi

    ; Buff[iW ] = E
    ldy         iW_keybuf
    sta         c_keybuf, Y

    ; iW = (iW + 1)%NBM
    inc         iW_keybuf
    lda         iW_keybuf
    and         #(NB_MAX_KEY_EVENT-1)
    sta         iW_keybuf

    ; SI iW == iR Alors
    cmp         iR_keybuf
    bne         noOverload
    ;   iR = (iR+1)%NBM
        inc         iR_keybuf
        lda         iR_keybuf
        and         #(NB_MAX_KEY_EVENT-1)
        sta         iR_keybuf
    jmp         endif
    ; Sinon
noOverload:
    ;   nbE = nbE + 1
        inc         _nbE_keybuf
    ; Finsi
endif:

.)
    rts

_get_keyevent:
.(
    ldx _nbE_keybuf
    beq no_keyevent
    ldy iR_keybuf
	lda c_keybuf, Y: sta tmp0
    ;   iR = (iR+1)%NBM
    inc         iR_keybuf
    lda         iR_keybuf

    iny
    tya
    and         #(NB_MAX_KEY_EVENT-1)
    sta         iR_keybuf
    dec _nbE_keybuf
    ;: sta tmp0 :
	lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :
	ldx tmp0 : lda tmp0+1 :
no_keyevent:

.)
    rts