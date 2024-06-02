/*
 * LCDdisplay.cpp
 *
 * Created: 4/18/2024 9:35:57 AM
 * Author : MSI
 */ 

 #include <avr/io.h>
 #include <util/delay.h>
 
  // Define CPU frequency for delay functions
  #define F_CPU 16000000UL
  // Define LCD data and control bus pins
  #define LcdDataBus PORTA
  #define LcdControlBus PORTA
  #define LcdDataBusDirnReg DDRA
  // Define LCD control pins
  #define LCD_RS 0
  #define LCD_RW 1
  #define LCD_EN 2
  
  
  
  
  // Function to initialize I/O ports for LCD
  void initPorts(void)
  {
	  LcdDataBusDirnReg = 0xFF; // Set data bus pins as output
	  DDRB |= 0B10000000; // Set PB7 (Power Indicator LED) as output
  }
  
  // Function to turn on Power Indicator LED
  void Turn_Power_Indicator_LED_ON(void)
  {
	  PORTB |= 0B10000000; // Set PB7 high to turn on the LED
  }
  
  // Function to write a command to the LCD
  void Lcd_CmdWrite(char cmd)
  {
	  LcdDataBus = (cmd & 0xF0); // Send higher nibble of command
	  LcdControlBus &= ~(1<<LCD_RS); // Set RS (Register Select) low for command
	  LcdControlBus &= ~(1<<LCD_RW); // Set RW (Read/Write) low for write mode
	  LcdControlBus |= (1<<LCD_EN); // Set EN (Enable) high to enable LCD
	  _delay_ms(10); // Delay
	  LcdControlBus &= ~(1<<LCD_EN); // Clear EN to latch command
	  
	  _delay_ms(10); // Delay
	  
	  LcdDataBus = ((cmd<<4) & 0xF0); // Send lower nibble of command
	  LcdControlBus |= (1<<LCD_RS); // Set RS high for data register
	  LcdControlBus &= ~(1<<LCD_RW); // Set RW low for write mode
	  LcdControlBus |= (1<<LCD_EN); // Set EN high to enable LCD
	  _delay_ms(10); // Delay
	  LcdControlBus &= ~(1<<LCD_EN); // Clear EN to latch command
	  _delay_ms(10); // Delay
  }

  // Function to write data to the LCD
  void Lcd_DataWrite(char dat)
  {
	  LcdDataBus = (dat & 0xF0);
	  LcdControlBus |= (1<<LCD_RS);
	  LcdControlBus &= ~(1<<LCD_RW);
	  LcdControlBus |= (1<<LCD_EN);
	  _delay_ms(10);
	  LcdControlBus &= ~(1<<LCD_EN);
	  _delay_ms(10);
	  LcdDataBus = ((dat<<4) & 0xF0); // Send higher nibble of data
	  LcdControlBus |= (1<<LCD_RS); // Set RS high for data register
	  LcdControlBus &= ~(1<<LCD_RW); // Set RW low for write mode
	  LcdControlBus |= (1<<LCD_EN); // Set EN high to enable LCD
	  _delay_ms(10); // Delay
	  LcdControlBus &= ~(1<<LCD_EN); // Clear EN to latch data
	  _delay_ms(10); // Delay
  }
  
  // Function to initialize the LCD
  void Lcd_init(void)
  {
	  Lcd_CmdWrite(0x02); // Return Home
	  Lcd_CmdWrite(0x28); // 4-bit mode, 2 lines, 5x7 font
	  Lcd_CmdWrite(0x0E); // Display ON, cursor ON
	  Lcd_CmdWrite(0x01); // Clear display
	  Lcd_CmdWrite(0x80); // Move cursor to beginning of the first line
  }


int main(void)
{
 // Initialize I/O ports
 initPorts();
 // Turn on Power Indicator LED
 Turn_Power_Indicator_LED_ON();
 // Initialize the LCD
 Lcd_init();
 // Write characters to display "HELLO"
 Lcd_DataWrite('H');
 Lcd_DataWrite('E');
 Lcd_DataWrite('L');
 Lcd_DataWrite('L');
 Lcd_DataWrite('O');
 // Infinite loop
 while (1)#define F_CPU 16000000UL
 #include <avr/io.h>
 #include <util/delay.h>

 #define LcdDataBus PORTA
 #define LcdControlBus PORTA
 #define LcdDataBusDirnReg DDRA

 #define LCD_RS 0
 #define LCD_RW 1
 #define LCD_EN 2

 void initPorts(void) {
	 LcdDataBusDirnReg = 0xFF; // Set data bus pins as output
	 DDRA |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN); // Set control pins as output
 }

 void Turn_Power_Indicator_LED_ON(void) {
	 DDRB |= (1 << 7); // Set PB7 (Power Indicator LED) as output
	 PORTB |= (1 << 7); // Set PB7 high to turn on the LED
 }

 void Lcd_CmdWrite(char cmd) {
	 LcdDataBus = (cmd & 0xF0);
	 LcdControlBus &= ~(1 << LCD_RS);
	 LcdControlBus &= ~(1 << LCD_RW);
	 LcdControlBus |= (1 << LCD_EN);
	 _delay_ms(10);
	 LcdControlBus &= ~(1 << LCD_EN);

	 _delay_ms(10);

	 LcdDataBus = ((cmd << 4) & 0xF0);
	 LcdControlBus |= (1 << LCD_EN);
	 _delay_ms(10);
	 LcdControlBus &= ~(1 << LCD_EN);
	 _delay_ms(10);
 }

 void Lcd_DataWrite(char dat) {
	 LcdDataBus = (dat & 0xF0);
	 LcdControlBus |= (1 << LCD_RS);
	 LcdControlBus &= ~(1 << LCD_RW);
	 LcdControlBus |= (1 << LCD_EN);
	 _delay_ms(10);
	 LcdControlBus &= ~(1 << LCD_EN);
	 _delay_ms(10);
	 LcdDataBus = ((dat << 4) & 0xF0);
	 LcdControlBus |= (1 << LCD_EN);
	 _delay_ms(10);
	 LcdControlBus &= ~(1 << LCD_EN);
	 _delay_ms(10);
 }

 void Lcd_init(void) {
	 Lcd_CmdWrite(0x02); // Return Home
	 Lcd_CmdWrite(0x28); // 4-bit mode, 2 lines, 5x7 font
	 Lcd_CmdWrite(0x0E); // Display ON, cursor ON
	 Lcd_CmdWrite(0x01); // Clear display
	 Lcd_CmdWrite(0x80); // Move cursor to beginning of the first line
 }

 int main(void) {
	 initPorts();
	 Turn_Power_Indicator_LED_ON();
	 Lcd_init();
	 Lcd_DataWrite('H');
	 Lcd_DataWrite('E');
	 Lcd_DataWrite('L');
	 Lcd_DataWrite('L');
	 Lcd_DataWrite('O');
	 while (1) {
		 // Code execution stays in this loop
	 }
	 return 0;
 }

 {
	 // Code execution stays in this loop
 }
 return 0; // Return from main (never reached)
}

