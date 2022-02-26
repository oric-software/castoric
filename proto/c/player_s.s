
#include "config.h"

#ifndef USE_C_MOVE
_oneStepForward:
.(
;; #$a0 = -96
lda _rayCamRotZ:sec:sbc #$a0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm96
    dec _rayCamPosX
jmp oneStepForward_done
higherthanm96:
;; #$c0 = -64
lda _rayCamRotZ:sec:sbc #$c0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm64
    dec _rayCamPosX
    dec _rayCamPosY
jmp oneStepForward_done
higherthanm64:
;; #$e0 = -32
lda _rayCamRotZ:sec:sbc #$e0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm32
    dec _rayCamPosY
jmp oneStepForward_done
higherthanm32:
;; #$00 = -0
lda _rayCamRotZ:sec:sbc #$00:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm0
    inc _rayCamPosX
    dec _rayCamPosY
jmp oneStepForward_done
higherthanm0:
;; #$20 = 32
lda _rayCamRotZ:sec:sbc #$20:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp32
    inc _rayCamPosX
jmp oneStepForward_done
higherthanp32:
;; #$40 = 64
lda _rayCamRotZ:sec:sbc #$40:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp64
    inc _rayCamPosX
    inc _rayCamPosY
jmp oneStepForward_done
higherthanp64:
;; #$60 = 96
lda _rayCamRotZ:sec:sbc #$60:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp96
    inc _rayCamPosY
jmp oneStepForward_done
higherthanp96:
;; #$7f = 127
lda _rayCamRotZ:sec:sbc #$7f:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp127
    dec _rayCamPosX
    inc _rayCamPosY
jmp oneStepForward_done
higherthanp127:
    dec _rayCamPosX
oneStepForward_done
.)
    rts

_oneStepBackward:
.(
;; #$a0 = -96
lda _rayCamRotZ:sec:sbc #$a0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm96
    inc _rayCamPosX
jmp oneStepBackward_done
higherthanm96:
;; #$c0 = -64
lda _rayCamRotZ:sec:sbc #$c0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm64
    inc _rayCamPosX
    inc _rayCamPosY
jmp oneStepBackward_done
higherthanm64:
;; #$e0 = -32
lda _rayCamRotZ:sec:sbc #$e0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm32
    inc _rayCamPosY
jmp oneStepBackward_done
higherthanm32:
;; #$00 = -0
lda _rayCamRotZ:sec:sbc #$00:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm0
    dec _rayCamPosX
    inc _rayCamPosY
jmp oneStepBackward_done
higherthanm0:
;; #$20 = 32
lda _rayCamRotZ:sec:sbc #$20:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp32
    dec _rayCamPosX
jmp oneStepBackward_done
higherthanp32:
;; #$40 = 64
lda _rayCamRotZ:sec:sbc #$40:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp64
    dec _rayCamPosX
    dec _rayCamPosY
jmp oneStepBackward_done
higherthanp64:
;; #$60 = 96
lda _rayCamRotZ:sec:sbc #$60:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp96
    dec _rayCamPosY
jmp oneStepBackward_done
higherthanp96:
;; #$7f = 127
lda _rayCamRotZ:sec:sbc #$7f:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp127
    inc _rayCamPosX
    dec _rayCamPosY
jmp oneStepBackward_done
higherthanp127:
    inc _rayCamPosX    
oneStepBackward_done
.)
    rts

_oneStepLeft:
.(
;; #$a0 = -96
lda _rayCamRotZ:sec:sbc #$a0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm96
    dec _rayCamPosY
jmp oneStepLeft_done
higherthanm96:
;; #$c0 = -64
lda _rayCamRotZ:sec:sbc #$c0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm64
    inc _rayCamPosX
    dec _rayCamPosY
jmp oneStepLeft_done
higherthanm64:
;; #$e0 = -32
lda _rayCamRotZ:sec:sbc #$e0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm32
    inc _rayCamPosX
jmp oneStepLeft_done
higherthanm32:
;; #$00 = -0
lda _rayCamRotZ:sec:sbc #$00:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm0
    inc _rayCamPosX
    inc _rayCamPosY
jmp oneStepLeft_done
higherthanm0:
;; #$20 = 32
lda _rayCamRotZ:sec:sbc #$20:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp32
    inc _rayCamPosY
jmp oneStepLeft_done
higherthanp32:
;; #$40 = 64
lda _rayCamRotZ:sec:sbc #$40:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp64
    dec _rayCamPosX
    inc _rayCamPosY
jmp oneStepLeft_done
higherthanp64:
;; #$60 = 96
lda _rayCamRotZ:sec:sbc #$60:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp96
    dec _rayCamPosX
jmp oneStepLeft_done
higherthanp96:
;; #$7f = 127
lda _rayCamRotZ:sec:sbc #$7f:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp127
    dec _rayCamPosX
    dec _rayCamPosY
jmp oneStepLeft_done
higherthanp127:
    dec _rayCamPosY       
oneStepLeft_done
.)
    rts

_oneStepRight:
.(
;; #$a0 = -96
lda _rayCamRotZ:sec:sbc #$a0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm96
    inc _rayCamPosY
jmp oneStepRight_done
higherthanm96:
;; #$c0 = -64
lda _rayCamRotZ:sec:sbc #$c0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm64
    dec _rayCamPosX
    inc _rayCamPosY
jmp oneStepRight_done
higherthanm64:
;; #$e0 = -32
lda _rayCamRotZ:sec:sbc #$e0:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm32
    dec _rayCamPosX
jmp oneStepRight_done
higherthanm32:
;; #$00 = -0
lda _rayCamRotZ:sec:sbc #$00:.(:bvc skip:eor #$80:skip:.):
bpl higherthanm0
    dec _rayCamPosX
    dec _rayCamPosY
jmp oneStepRight_done
higherthanm0:
;; #$20 = 32
lda _rayCamRotZ:sec:sbc #$20:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp32
    dec _rayCamPosY
jmp oneStepRight_done
higherthanp32:
;; #$40 = 64
lda _rayCamRotZ:sec:sbc #$40:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp64
    inc _rayCamPosX
    dec _rayCamPosY
jmp oneStepRight_done
higherthanp64:
;; #$60 = 96
lda _rayCamRotZ:sec:sbc #$60:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp96
    inc _rayCamPosX
jmp oneStepRight_done
higherthanp96:
;; #$7f = 127
lda _rayCamRotZ:sec:sbc #$7f:.(:bvc skip:eor #$80:skip:.):
bpl higherthanp127
    inc _rayCamPosX
    inc _rayCamPosY
jmp oneStepRight_done
higherthanp127:
    inc _rayCamPosX        
oneStepRight_done
.)
    rts



#endif ;; USE_C_MOVE