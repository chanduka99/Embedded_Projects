/*
 * LEDblinkAtmel.c
 *
 * Created: 3/14/2024 9:16:36 AM
 * Author : MSI
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


volatile int toggle = 0;

ISR (INT1_vect){
	if (toggle)
	{
		PORTB |= 0B00100000;
	}else{
		PORTB &= 0B11011111;
	}
	toggle = 1-toggle;
}



int main(void)
{
    /* Replace with your application code */
	/*DDRB |= 0B00100000;*/
	
   /* while (1) 
    {
		portb |= 0b00100000;
		_delay_ms(1000);
		
		portb &= 0b11011111;
		_delay_ms(1000);
    }*/
   
   /*toggle switch */
   	DDRB |= 0B00100000;
   	DDRB &= 0B11111110;
   
       while (1)
       {
		   if(PINB & 0B00000001){
			   PORTB |= 0B00100000;
			   if(PINB & 0B00100000 ){
				   PORTB &= 0B11011111;
			   }
			   
		   }else{
			   PORTB &= 0B11011111;
		   }
       }
}

