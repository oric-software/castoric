#include "config.h"

#ifndef USE_C_ENGINEPULSE

_engPulse
.(
    ldy #OBJECTS_MAX: sty _engCurrentObjectIdx
engPulseLoop
        ldy _engCurrentObjectIdx
        beq engPulseEndLoop
        dey : sty _engCurrentObjectIdx
        lda _objActive, y
        beq EndIfObjectIsActive
            ldy #0: jsr _engObjectPulse
EndIfObjectIsActive
        jmp engPulseLoop
engPulseEndLoop
.)
    rts


_engInitObjects
.(
    ldy #OBJECTS_MAX: sty _engCurrentObjectIdx
engInitLoop
        ldy _engCurrentObjectIdx
        beq engInitEndLoop
        dey : sty _engCurrentObjectIdx
        lda #0
        sta _objActive, y
        jmp engInitLoop
engInitEndLoop
.)
    rts


;; _engAddObject
;; .(
;;     lda #0
;;     sta _engCurrentObjectIdx
;; addObjectLoop
;;     sta _engCurrentObjectIdx
;;     cmp #OBJECTS_MAX
;;     beq engAddObjectDone
;;     tay 
;;     lda _objActive,y
;;     beq foundafreeslot
;;     jmp addObjectLoop
;; foundafreeslot
;;     lda #1 : sta _objActive,y
;;     
;; engAddObjectDone
;; .)
;;     rts
#endif ;; USE_C_ENGINEPULSE

