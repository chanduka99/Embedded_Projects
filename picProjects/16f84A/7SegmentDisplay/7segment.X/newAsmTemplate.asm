processor 16F84A 
    
#include <xc.inc>
    
radix       dec         ;default are decade numbers

PSECT code
 
; CONFIG
  CONFIG  FOSC = XT     ; Oscillator Selection bits (XT oscillator)
  CONFIG  WDTE = OFF    ; Watchdog Timer (WDT disabled)
  CONFIG  PWRTE = OFF   ; Power-up Timer Enable bit (Power-up Timer is disabled)
  CONFIG  CP = OFF      ; Code Protection bit (Code protection disabled)
 

  count1 equ 20h
  count2 equ 21h
code:
    BSF     STATUS, 5   ;Select memory Bank 1
    BCF	    TRISA,0 
    BCF	    TRISA,1
    BCF	    TRISA,2
    BCF	    TRISA,3
    BSF	    TRISB,7
    BCF     STATUS, 5   ;Back to Bank 0
;    GOTO INIT
    GOTO MAIN
    
INIT:			;WITHOUT INITIALIZING THE COUNT VARIABLES CODE WONT'T WORK
    MOVLW 0xFF        ; Initialize count1 to 255
    MOVWF 20h
    MOVLW 0xFF        ; Initialize count2 to 255
    MOVWF 21h
    GOTO MAIN
MAIN:
    CALL CHECK
    MOVLW 0b00000000
    MOVWF PORTA		    ;OUPUT 0
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000001
    MOVWF PORTA		    ;OUPUT 1
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000010
    MOVWF PORTA		    ;OUPUT 2
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000011
    MOVWF PORTA		    ;OUPUT 3
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000100
    MOVWF PORTA		    ;OUTPUT 4
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000101	    
    MOVWF PORTA		    ;OUTPUT 5
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000110
    MOVWF PORTA		    ;OUTPUT 6
    CALL DELAY
    CALL CHECK
    MOVLW 0b00000111
    MOVWF PORTA		    ;OUTPUT 7
    CALL DELAY
    CALL CHECK
    MOVLW 0b00001000
    MOVWF PORTA		    ;OUTPUT 8
    CALL DELAY
    CALL CHECK
    MOVLW 0b00001001	    ;OUTPUT 9
    MOVWF PORTA
    CALL DELAY
    CALL CHECK
    GOTO MAIN
DELAY:
    DECFSZ count1,1
    GOTO DELAY2
    RETURN
DELAY2:
    DECFSZ count2,1
    GOTO DELAY2
    GOTO DELAY
CHECK:
    BTFSS PORTB,7
    GOTO CHECK
    RETURN
END code
    