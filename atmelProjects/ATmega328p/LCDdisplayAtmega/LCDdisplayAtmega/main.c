#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LcdDataBus PORTA
#define LcdControlBus PORTA
#define LcdDataBusDirnReg DDRA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void Turn_Power_Indicator_LED_ON(void);
void initPorts(void);
void Lcd_CmdWrite (char cmd);
void Lcd_DataWrite(char dat);
void Lcd_init (void);

int count = 0;

int digit1;
int digit10;
int digit100;

int main(void)
{
	/* Replace with your application code */
	initPorts();
	Turn_Power_Indicator_LED_ON();
	Lcd_init();
	//initUSART();
	Lcd_DataWrite('R');
	Lcd_DataWrite('A');
	Lcd_DataWrite('J');
	Lcd_DataWrite('A');

	while (1) {
		digit1 = count % 10;
		digit10 = (count % 100) / 10;
		digit100 = (count % 1000) / 100;
		if ((PIND & 0B00000001) == 0) {
			Lcd_CmdWrite(0xC0);
			Lcd_DataWrite(0x30 + digit100);
			Lcd_DataWrite(0x30 + digit10);
			Lcd_DataWrite(0x30 + digit1);
			count++;
			_delay_ms(1000);
		}
	}

	return 0;
}

void initPorts(void)
{
	LcdDataBusDirnReg = 0xFF;
	// DDRA =0xFF;
	DDRB |= (1 << 7);
	DDRD &= ~(1 << 0);
}

void Turn_Power_Indicator_LED_ON(void)
{
	PORTB |= (1 << 7);
}

void Lcd_CmdWrite(char cmd)
{
	LcdDataBus = (cmd & 0xF0);
	LcdControlBus &= ~(1 << LCD_RS);
	LcdControlBus &= ~(1 << LCD_RW);
	LcdControlBus |= (1 << LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);
	_delay_ms(10);

	LcdDataBus = ((cmd << 4) & 0xF0);
	LcdControlBus &= ~(1 << LCD_RS);
	LcdControlBus &= ~(1 << LCD_RW);
	LcdControlBus |= (1 << LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);
	_delay_ms(10);
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus = (dat & 0xF0);
	LcdControlBus |= (1 << LCD_RS);
	LcdControlBus &= ~(1 << LCD_RW);
	LcdControlBus |= (1 << LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);
	_delay_ms(10);

	LcdDataBus = ((dat << 4) & 0xF0);
	LcdControlBus |= (1 << LCD_RS);
	LcdControlBus &= ~(1 << LCD_RW);
	LcdControlBus |= (1 << LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);
	_delay_ms(10);
}

void Lcd_init(void)
{
	Lcd_CmdWrite(0x02); //initialize LCD  in 4bit mode
	Lcd_CmdWrite(0x28); // enable 5x7 mode for chars
	Lcd_CmdWrite(0x0E); //Display OFF, cursor ON
	Lcd_CmdWrite(0x01); // clear Display
	Lcd_CmdWrite(0x80); // Move the cursor to beginning or first line
}