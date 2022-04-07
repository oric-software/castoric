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
#endif ;; USE_C_ENGINEPULSE

