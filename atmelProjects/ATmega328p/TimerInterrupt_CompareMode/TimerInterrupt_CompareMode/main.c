/*
 * TimerInterrupt_CompareMode.c
 *
 * Created: 3/28/2024 12:58:58 AM
 * Author : MSI
 */ 
#define F_CPU 16000000UL;
#include <avr/io.h>
#include <avr/interrupt.h>


int volatile toggle = 1;

int main(void)
{
	//initializing DDRB
		DDRB |= 0B00000001; 
	//initializing TCCR1
		//mode set to CTC
		TCCR1B &= 0B11101111; //WGM13 = 0
		TCCR1A &= 0B11111100; //WGM11,WGM10 = 0
		TCCR1B |= 0B00001000; //WGM 12 = 0
		//setting prescaler to 256
		TCCR1B |= 0B00000100; //CS12 = 1
		TCCR1A &= 0B11111100; //CS11,CS10 = 0
	//initializing TCNT1 to zero
		TCNT1H = 0x00;
		TCNT1L = 0x00;
	//initializing OCR1A
		OCR1AH = 0xF2;
		OCR1AL = 0x24;
	//Configuring TIMSK1
		TIMSK1 |= 0B00000010; //OCIE1A = 1
	//setting the global interrupt service
		sei();
    /* Replace with your application code */
    while (1) 
    {

    }
}

ISR(TIMER1_COMPA_vect){
	
	if(toggle){
		PORTB |= 0B00000001; // light on	
		TIFR1 &= 0B11111101;
		  
	}else{
		PORTB &= 0B11111110; // light off	
		TIFR1 &= 0B11111101;
	}
	toggle = 1 - toggle;
}