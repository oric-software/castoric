
#include "via.h"
#include "tasks_s.s"

.zero

; Interruption Context Saving 
irq_A               .byt 0
irq_X               .byt 0
irq_Y               .byt 0


.text

jmp_old_handler
	    jmp 0000



irq_handler:
	; sei
	
    ; Save Context
    php

	;Preserve registers 
	sta irq_A
	stx irq_X
	sty irq_Y

	TASK_100Hz


skipNormalItHandler:


    ; Acknowledge Interruption
    ;bit $304

	;Clear IRQ event 
	lda via_t1cl 

	;Restore Registers 
	lda irq_A
	ldx irq_X
	ldy irq_Y

    ; Restore Context
    plp

	; cli 

	rti

_kernelInit:
.(

	sei

	; Save the old handler value
	lda $245
	sta jmp_old_handler+1
	lda $246
	sta jmp_old_handler+2

	lda #0
	sta _kernel_cs
	sta _kernel_s


	; Since this is an slow process, we set the VIA timer to 
	; issue interrupts at 25Hz, instead of 100 Hz. This is 
	; not necessary -- it depends on your needs
	; lda #<40000
	; sta via_t1ll 
	; lda #>40000
	; sta via_t1lh


	; Install our own handler
	lda #<irq_handler
	sta $245
	lda #>irq_handler
	sta $246

    cli 
    rts
.)


_kernelEnd:
.(
	sei
	; Restore the old handler value
	lda jmp_old_handler+1
	sta $245
	lda jmp_old_handler+2
	sta $246
	cli
    rts
.)

