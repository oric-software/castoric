
#define USE_OSME

#ifdef USE_OSME
#include "osme_s.s"
#endif ;; USE_OSME


.zero

_kernel_cs .dsb	1
_kernel_s .dsb	1

_50hzFlipFlop   .byt 0

.text


#ifdef USE_OSME
#define HASOSME    jsr osmePulse
#else
#define HASOSME
#endif ;; USE_OSME

#define TASK_100Hz :.(:\
    HASOSME:\
	inc _kernel_cs:\
 	lda _kernel_cs:\
	eor #100:\
	bne not_1Hz:\
	sta _kernel_cs:\
is1Hz:\
    TASK_1Hz:\
	TASK_50Hz:\
	TASK_25Hz:\
	jmp task100hz_done:\
not_1Hz:\
    lda _50hzFlipFlop:\
    eor #1:\
    sta _50hzFlipFlop:\
    beq not_50Hz:\
    TASK_50Hz:\
	TASK_25Hz:\
	jmp task100hz_done:\
not_50Hz:\
	lda _kernel_cs:\
	and #$03:\
	bne not_25Hz:\
	TASK_25Hz:\
not_25Hz:\
task100hz_done:\
.)

#define TASK_50Hz : .( :\
    jsr ReadKeyboard:\
    jsr detectKeyEvent:\
.)


#define TASK_25Hz :.(:\
.)

#define TASK_1Hz :.(:\
    inc _kernel_s:\
    lda _kernel_s:\
    cmp #60:\
    bne skip_minute:\
    lda #0:\
    sta _kernel_s:\
skip_minute:\
    jsr game_pulse:\
task1hz_done:\
.)

