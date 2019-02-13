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

/******************************************************************/
void lcd_strobe_lcd_e(void)
/*
short:			Strobe LCD module E pin --__
inputs:
outputs:
notes:			According datasheet HD44780
Version :    	DMK, Initial code
*******************************************************************/
{
PORTC |= (1<<LCD_E);	// E high
_delay_ms(1);			// nodig
PORTC &= ~(1<<LCD_E);  	// E low
_delay_ms(1);			// nodig?
}

/******************************************************************/
void init_4bits_mode(void)
/*
short:			Init LCD module in 4 bits mode.
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
// PORTC output mode and all low (also E and RS pin)
DDRC = 0xFF;
PORTC = 0x00;

// Step 2 (table 12)
PORTC = 0x20;	// function set
lcd_strobe_lcd_e();

// Step 3 (table 12)
PORTC = 0x20;   // function set
lcd_strobe_lcd_e();
PORTC = 0x80;
lcd_strobe_lcd_e();

// Step 4 (table 12)
PORTC = 0x00;   // Display on/off control
lcd_strobe_lcd_e();
PORTC = 0xF0;
lcd_strobe_lcd_e();

// Step 4 (table 12)
PORTC = 0x00;   // Entry mode set
lcd_strobe_lcd_e();
PORTC = 0x60;
lcd_strobe_lcd_e();

}

/******************************************************************/
void lcd_write_string(char *str)
/*
short:			Writes string to LCD at cursor position
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
// Het kan met een while:

// while(*str) {
// 	lcd_write_data(*str++);
// }

// of met een for:
for(;*str; str++){
lcd_write_data(*str);
}
}


/******************************************************************/
void lcd_write_data(unsigned char byte)
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

/******************************************************************/
void lcd_write_command(unsigned char byte)
/*
short:			Writes 8 bits COMMAND to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
// First nibble.
PORTC = byte;
PORTC &= ~(1<<LCD_RS);
lcd_strobe_lcd_e();

// Second nibble
PORTC = (byte<<4);
PORTC &= ~(1<<LCD_RS);
lcd_strobe_lcd_e();
}



/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
// Init I/O
DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

// Init LCD
init_4bits_mode();

// Write sample string
lcd_write_string("Yedi you are");

// Loop forever
while (1)
{
PORTD ^= (1<<7);	// Toggle PORTD.7
_delay_ms( 1000 );
}

return 1;
}
