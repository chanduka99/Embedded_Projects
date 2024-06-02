/*
 * USARTtransmitterTEST.c
 *
 * Created: 5/13/2024 4:12:18 PM
 * Author : MSI
 */ 
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_Value ((F_CPU/16/BAUD)-1)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int volatile toggle = 0;
int volatile toggle2 = 0;


void USART_CONFIG(void){
	
	//baude rate set
	UBRR0H = (unsigned char)(UBRR_Value>>8);
	UBRR0L = (unsigned char)UBRR_Value;
	
	//enable transmitter:UCSR0B
	UCSR0B |= (1<<TXEN0);
	//set frame format: 8bits data, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
}

void TIMER_CONFIG(void){
		TCCR1B |= (1<<WGM12)|(1<<CS12);//ctc mode set,prescaler 256
		OCR1AH = 0x30;
		OCR1AL =0xD4; //set for one second
		TIMSK1 |=(1<<OCIE1A); //enable timer compare interrupt
		TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect){
	toggle2 = 0;
	TCCR1B &= 0B11111011; //stopping the counter
}

void BUTTON_CONFIG(void){
	
	//external interrupt enable on PD2 INT0
	EIMSK |= 0B00000001;
	//interrupt set for rising edge
	EICRA |= 0B00000011;
	
	
}



void DELAY(void){
	TIMER_CONFIG();
	toggle2 = 1;
	while(toggle2 == 1){
		//looping in this until toggle2 will be zero by the ISR
	}
	return;
}

void transmitDATA(unsigned char data){
	while (!(UCSR0A & (1<<UDRE0))){
		//waiting until transmit buffer is empty
	}
	UDR0 = data;
	return;
}

void transmit1(void){
	
	transmitDATA('H');
	DELAY();
	transmitDATA('E');
	DELAY();
	transmitDATA('L');
	DELAY();
	transmitDATA('L');
	DELAY();
	transmitDATA('O');
	DELAY();
	transmitDATA('!');
	return;
}


void transmit2(){
	transmitDATA('W');
	DELAY();
	transmitDATA('O');
	DELAY();
	transmitDATA('R');
	DELAY();
	transmitDATA('L');
	DELAY();
	transmitDATA('D');
	DELAY();
	return;
}



void START(void){
	while(1){
		//if toggle==1 then transmit1
		if(toggle == 1){
			transmit1();
			}else{
		//if toggle ==0 then tranmit2	
			transmit2();
		}
	}
}

ISR(INT0_vect){
	toggle = 1-toggle;
	START();
}

int main(void)
{	
	
	//configure the USART transmitter
	USART_CONFIG();
	//configure the external interrupt
	BUTTON_CONFIG();
	//enable global interrupts
	sei();

	START();
    while (1) 
    {	
    }	
	return 0;
}
