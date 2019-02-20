
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit1( void )
{
	ADMUX  = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b1100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

void adcInit2( void )
{
	ADMUX  = 0b11100001;			// AREF=2,56 V, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}

// Main program: ADC at PF1
int main( void )
{
	B2();
}

void B1()
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	
	DDRB = 0xFF;				// set PORTB for output
	DDRA = 0xFF;				// set PORTA for output
	adcInit1();					// initialize ADC

	while (1)
	{
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
	}
}

void B2()
{
	DDRD = 0x00;					// set PORTD for input (btn)
	DDRF = 0x00;					// set PORTF for input (ADC)
	DDRA = 0xFF;					// set PORTA for output
	adcInit2();						// initialize ADC
	PORTD &= ~BIT(0);
	
	while (1)
	{
		
		if(PIND == BIT(0) )
		{
			ADCSRA |= BIT(6);
		}
		
		while ( ADCSRA & BIT(6) ) ;		// Wait for completion
		PORTA = ADCH;					// Show MSB (bit 9:2) of ADC
		wait(500);						// every 50 ms (busy waiting)
	}
}