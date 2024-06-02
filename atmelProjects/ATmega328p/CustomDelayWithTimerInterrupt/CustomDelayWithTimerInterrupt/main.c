/*
 * CustomDelayWithTimerInterrupt.c
 *
 * Created: 5/24/2024 11:23:21 AM
 * Author : MSI
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


int volatile toggle = 0;
int volatile toggle2 = 0;
void PORT_CONFIG (void){
		//initializing DDRB
		DDRB |= 0B00000001;
		
}

void TIMER_CONFIG (void){
	TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS12);//ctc mode set,prescaler 1024
	OCR1AH = 0x3D;
	OCR1AL =0x09; //set for one second
	TIMSK1 |=(1<<OCIE1A);
	TCNT1 = 0;
	toggle = 1;		
	return;
}

void DELAY (void){
	TIMER_CONFIG();
	while (toggle == 1)
	{
	}
	return;
}

void START(void){
	while(1){
		if(toggle2==0){
	
				PORTB |= 0B00000001; // light on
				DELAY();
		}else{
			PORTB &= 0B11111110;//light off
			DELAY();
		}
		toggle2 = 1- toggle2;
	}
}
	

ISR(TIMER1_COMPA_vect){
	toggle = 0;
	TCCR1B &= 0B11111010; //counter stopped
}


//ISR(TIMER1_COMPA_vect){
	//
	//if(toggle){
		//PORTB |= 0B00000001; // light on
		//TIFR1 &= 0B11111101;
		//
		//}else{
		//PORTB &= 0B11111110; // light off
		//TIFR1 &= 0B11111101;
	//}
	//toggle = 1 - toggle;
//}


int main(void)
{
	sei();
	PORT_CONFIG();
	START();
    /* Replace with your application code */
    while (1) 
    {
    }
}



