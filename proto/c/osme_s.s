
#define DEFAULT_BPM		100
#define NB_INT_PER_MINUTE	6000 

_kernel_tempo 			.byt	DEFAULT_BPM

_kernel_fraction 		.dsb	1
_kernel_beat 			.dsb	1

kernel_tempo_err 		.dsb	2

; Number of Beat Fraction Per Minute
; shall contains tempo_BPM * 12 
kernel_bfpm 			.dsb	2

tempo2bfpm:
.(
	; kernel_bfpm <- tempo_bpm * 12
	lda 	#0
	sta		kernel_bfpm+1
	lda 	_kernel_tempo
	asl							; 
	rol		kernel_bfpm+1
	clc							; useless
	adc 	_kernel_tempo
	sta		kernel_bfpm
	bcc 	skipCarryPropagation
	lda		kernel_bfpm+1
	adc		#0
	sta 	kernel_bfpm+1
skipCarryPropagation:

	lda 	kernel_bfpm
	asl							; 
	rol		kernel_bfpm+1
	asl							; 
	rol		kernel_bfpm+1
	sta		kernel_bfpm

.)
    rts



_setTempo:
.(
	ldx #6 : lda #0 : jsr enter :
	ldy #0 : lda (ap),y : sta _kernel_tempo :
    jsr     tempo2bfpm
	jmp leave :
.)

_getTempo:
.(
	lda _kernel_tempo : sta tmp0 :
	lda tmp0 : sta tmp0 : lda #0 : sta tmp0+1 :
	ldx tmp0 : lda tmp0+1 :
.)
    rts

_osmeInit:
.(

    ;
    lda     #0
    sta     _kernel_fraction
    sta     _kernel_beat

	; E <- ITPM
	lda #<NB_INT_PER_MINUTE
	sta kernel_tempo_err
	lda #>NB_INT_PER_MINUTE
	sta kernel_tempo_err+1

    jsr tempo2bfpm

osmeInitDone:
.)
	rts

osmePulse:
.(
	; E <- E - BFPM
	sec 
	lda 	kernel_tempo_err
	sbc 	kernel_bfpm
	sta 	kernel_tempo_err
	lda		kernel_tempo_err+1
	sbc		kernel_bfpm+1
	sta		kernel_tempo_err+1

	bmi		pulseFraction
	; SI 2*E < BFPM ALORS
	asl
	sec
	sbc		kernel_bfpm+1
	bvc		LABEL_1
	eor		#$80
LABEL_1
	bmi		pulseFraction
	bvc		LABEL_2
	eor		#$80
LABEL_2
	bne		PulseNoFraction
	lda		kernel_tempo_err
	asl
	sbc 	kernel_bfpm
	bcc 	pulseFraction
PulseNoFraction:
	jmp osmePulseDone

pulseFraction:
	;	E <- E + ITPM
	clc
	lda 	kernel_tempo_err
	adc 	#<NB_INT_PER_MINUTE
	sta 	kernel_tempo_err
	lda 	kernel_tempo_err+1
	adc 	#>NB_INT_PER_MINUTE
	sta 	kernel_tempo_err+1

	jsr		task_fraction

osmePulseDone:
.)
	rts


; task_fraction:
; .(
; 	lda		_kernel_fraction
; 	clc
; 	adc		#1
; 	sta		_kernel_fraction
; 	cmp		#12
; 	bne		taskfraction_done
; 	lda		#0
; 	sta		_kernel_fraction
; 	jsr		task_beat
; taskfraction_done:
; .)
;     rts    

task_fraction:
.(
	inc		_kernel_fraction
	lda		_kernel_fraction
	eor		#12
	bne		not_beat
	sta		_kernel_fraction
	jsr		task_beat

not_beat:
;;	lda		_ayReg8
;;	beq		soundoff
;;	sec
;;	sbc		#1
;;	sta		_ayReg8
;;	jsr 	_ayUpdate
soundoff:	
taskfraction_done:
.)
    rts    

task_beat:
.(
	inc		_kernel_beat
taskbeat_done:
.)
    rts    
