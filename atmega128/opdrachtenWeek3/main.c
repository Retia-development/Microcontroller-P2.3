#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

int main( void )
{
	DDRD = 0xFF;

	init_4bits_mode();

	lcd_write_string("OwO you are not");

	while (1)
	{
		PORTD ^= (1<<7);
		_delay_ms( 1000 );
	}

	return 1;
}

void lcd_strobe_lcd_e(void)
{
PORTC |= (1<<LCD_E);	
_delay_ms(1);			
PORTC &= ~(1<<LCD_E);  
_delay_ms(1);			
}

void init_4bits_mode(void)
{

DDRC = 0xFF;
PORTC = 0x00;

PORTC = 0x20;
lcd_strobe_lcd_e();

PORTC = 0x20; 
lcd_strobe_lcd_e();
PORTC = 0x80;
lcd_strobe_lcd_e();

PORTC = 0x00;  
lcd_strobe_lcd_e();
PORTC = 0xF0;
lcd_strobe_lcd_e();

PORTC = 0x00; 
lcd_strobe_lcd_e();
PORTC = 0x60;
lcd_strobe_lcd_e();

}

void lcd_write_string(char *str)
{
for(;*str; str++){
lcd_write_data(*str);
}
}


void lcd_write_data(unsigned char byte)
{

PORTC = byte;
PORTC |= (1<<LCD_RS);
lcd_strobe_lcd_e();

PORTC = (byte<<4);
PORTC |= (1<<LCD_RS);
lcd_strobe_lcd_e();
}

void lcd_write_command(unsigned char byte)
{
PORTC = byte;
PORTC &= ~(1<<LCD_RS);
lcd_strobe_lcd_e();

PORTC = (byte<<4);
PORTC &= ~(1<<LCD_RS);
lcd_strobe_lcd_e();
}



/******************************************************************/
//int main( void )
///*
//short:			main() loop, entry point of executable
//inputs:
//outputs:
//notes:			Slow background task after init ISR
//Version :    	DMK, Initial code
//*******************************************************************/
//{
//// Init I/O
//DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input
//
//// Init LCD
//init_4bits_mode();
//
//// Write sample string
//lcd_write_string("Yedi you are");
//
//// Loop forever
//while (1)
//{
//PORTD ^= (1<<7);	// Toggle PORTD.7
//_delay_ms( 1000 );
//}
//
//return 1;
//}
