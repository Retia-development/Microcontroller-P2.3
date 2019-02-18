#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

int main(void){
	DDRC = 0b11111111;
	DDRD = 0b11111111;

	init_lcd();
	lcd_data(0b00110001);
	while(1){

	}
	
	return 1;
}

void init_lcd(void)
{
	// return home
	lcd_command( 0x02 );
	// mode: 4 bits interface data, 2 lines, 5x8 dots
	lcd_command( 0x28 );
	// display: on, cursor off, blinking off
	lcd_command( 0x0C );
	// entry mode: cursor to right, no shift
	lcd_command( 0x06 );
	// RAM adress: 0, first position, line 1
	lcd_command( 0x80 );
}

void lcd_command ( unsigned char dat )
{
	PORTC = dat & 0xF0;			// hoge nibble
	PORTC = PORTC | 0x08;			// data (RS=0),										// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x04;					// stop (EN = 0)
	
	PORTC = (dat & 0x0F) << 4;	// lage nibble
	PORTC = PORTC | 0x08;			// data (RS=0),										// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x00;					// stop 										// (EN=0 RS=0)
}


void lcd_data(unsigned char byte)
/*
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_writeChar( unsigned char dat )
{
	PORTC = dat & 0xF0;			// hoge nibble
	PORTC = PORTC | 0x0C;			// data (RS=1),										// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x04;					// stop (EN = 0)
	
	PORTC = (dat & 0x0F) << 4;	// lage nibble
	PORTC = PORTC | 0x0C;			// data (RS=1),										// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x00;					// stop 										// (EN=0 RS=0)
}
