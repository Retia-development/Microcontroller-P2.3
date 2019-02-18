#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"

#include "LCD.h"



int main (void)
{
	B1();
	while(1)
	{
	}
}

void B1()
{
	char c[] = "positie 20";
	init_lcd();
	_delay_ms(25);
	
	lcd_command(0x01);
	lcd_writeLine(c, 1);
	lcd_setCursorPosition(20);
	lcd_writeChar('A');
	
}
