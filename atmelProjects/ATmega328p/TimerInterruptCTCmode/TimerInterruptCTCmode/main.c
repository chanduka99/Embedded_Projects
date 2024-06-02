/*
 * TimerInterruptCTCmode.c
 *
 * Created: 5/15/2024 10:36:52 PM
 * Author : MSI
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void Timer_Interrupt_Config(int value){
		Counter_RESET();
		//set CTC mode:0100 for WGM13 WGM12 WGM01 WGM00 and pre-scaler to 256
		TCCR1B = (1<<WGM12)|(1<<CS12);
		//unsigned int value = 62500;
		OCR1AH = (unsigned char)(value >> 8); // Load the high byte
		OCR1AL = (unsigned char)(value & 0xFF); // Load the low byte
		//set the value in OCR1A to give 200ms
		//OCR1AL = (unsigned char)(62500);
		//OCR1AH = 0B00110001;
		//OCR1A = 65200;
		//OCR1AL = 0B00000101;
		//OCR1AH = (unsigned char)(62500>>8);
		//enable output compare interrupt:OCIE1A of TIMSK1
		TIMSK1 = (1<<OCIE1A);
}

void Port_Config(void){
	//set PORTD pin one as output
	DDRD |= 0B00000001;
	PORTD =0x00;
}



int main(void)
{
	Port_Config();
	//enable global interrupt
	sei();
	//Timer Interrupt for 200ms
	//unsigned int compareValue = (16000000/256);
	Timer_Interrupt_Config(65200);
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

void Counter_RESET(){
	TCNT1H = 0x00;
	TCNT1L = 0x00;
}

ISR(TIMER1_COMPA_vect){
	if(PIND & 0B00000001){
		PORTD = 0x00;
		Counter_RESET();
		TCCR1B &= 0B11111011; 
	}else{
		PORTD |= 0B00000001;
		Counter_RESET();
	}
	
}
