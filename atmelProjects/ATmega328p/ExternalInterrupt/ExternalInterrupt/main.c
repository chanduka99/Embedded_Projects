/*
 * ExternalInterrupt.c
 *
 * Created: 3/21/2024 9:06:42 AM
 * Author : MSI
 */ 
#define F_CPU 16000000UL;
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int toggle = 1;

int main(void)
{
	//Making PORTB pin 0 as output
		DDRB |= 0B00000001;
	//Setting the external interrupt to trigger at rising edge
		EICRA |= 0B00000011;
	//Setting external interrupt  for INT0 
		EIMSK |= 0B00000001; 	
	//Enabling the global interrupt
		sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
	return 0;
}

ISR(INT0_vect){
	if (toggle)
	{
		PORTB |= 0B00000001;
	}else{
		PORTB &= 0B11111110;
	}
	toggle = 1 - toggle;
}
