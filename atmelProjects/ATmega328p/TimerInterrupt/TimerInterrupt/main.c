/*
 * TimerInterrupt.c
 *
 * Created: 3/21/2024 6:45:54 AM
 * Author : MSI
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


volatile int toggle = 1;

int main(void)
{
	//Make portB pin 0 output
		DDRB |= 0B00000001;
	//Setting the timer counter register to 3037
		TCNT1L = 0B11011101;
		TCNT1H = 0B00001011;
	
	//Setting normal mode of operation and pre-scaler
		TCCR1A &= 0B11111100;
		TCCR1B |= 0B00000100;
		TCCR1B &= 0B11100100;
	//Enabling Timer interrupt
		TIMSK1 |= 0B00000001;
		
	//Enabling the Global interrupt
		sei();
	//
    /* Replace with your application code */
    while (1) 
    {
    }
}
ISR(TIMER1_OVF_vect){
	if(toggle){
		//light the led
		PORTB |= 0B00000001;
		TIFR1 &= 0B11111110;
	}else{
		PORTB &= 0B11111110;
		TIFR1 &= 0B11111110;
	}
	toggle = 1- toggle;	
}
