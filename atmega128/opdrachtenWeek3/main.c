#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"

#define BIT(x) (1<<(x))

int msCount = 0;
char isOn = 0;

int main (void)
{
	B3();
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

B3()
{	
	DDRD = 0xFF; // set PORTD for output (toggle PD7)
	timer2Init();
	while (1)
	{
		// do something else
		wait(1000); // every 1000 ms (busy waiting
	}
}

void timer2Init( void )
{
	OCR2 = 250;				// Compare value of counter 2
	TIMSK |= BIT(7);		// T2 compare match interrupt enable
	SREG |= BIT(7);			// turn_on intr all
	TCCR2 = 0b00001011;		// Initialize T2: timer, prescaler=32,
	// compare output disconnected,CTC,RUN
}

ISR( TIMER2_COMP_vect )
{
	msCount++; // Increment ms counter
	if ( msCount == 25 && isOn == 0)
	{
		isOn = 1;
		PORTD ^= BIT(7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	}
	else if(msCount == 15 && isOn == 1) 
	{
		isOn = 0;
		PORTD ^= BIT(7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	}
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}