;
; TimerInterrupt_Assembly.asm
;
; Created: 3/28/2024 8:48:52 AM
; Author : MSI
;


; Replace with your application code
	.include "M328Pdef.inc"
	.Cseg
	.org 0

	sbi DDRB,0 //setting PORTB pin 0 to output mode
start:
	//sbi PORTB,0 //light on
	//call delay1
	//cbi PORTB,0 //light off
	//call delay1
	
	sbi PORTB,0//light on
	//small delay
	cbi PORTB,0//light off
	//small delay
	sbi PORTB,0//light on
	//small delay
	cbi PORTB,0//light off
	call delay//long delay
    rjmp start

delay1:
	ldi R16,70
loop1:	
	ldi R17,255
	loop2:
		ldi R18,255
		loop3:
			dec R18
			brne loop3
		dec R17
		brne loop2
	dec R16
	brne loop1
ret

delay2:
	ldi R18,70
loop1:	
	ldi R19,255
	loop2:
		ldi R20,255
		loop3:
			dec R20
			brne loop3
		dec R19
		brne loop2
	dec R18
	brne loop1
ret

