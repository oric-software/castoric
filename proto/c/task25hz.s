
_mesure .dsb 1
_temps .dsb 1
_fraction .dsb 1

task_25Hz:
.(
    inc _fraction
    lda _fraction
    cmp #25
    bne task25hz_done
    lda #0
    sta _fraction
    inc _temps
    lda _temps
    cmp #4
    bne task25hz_done
    lda #0
    sta _temps
    inc _mesure


task25hz_done:

.)
    rts