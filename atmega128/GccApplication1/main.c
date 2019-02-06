
#define F_CPU 8000000UL
#include <avr/io.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main( void )
{
	
	DDRD = 0xF0;

	EICRA |= 0x0B;			
	EIMSK |= 0x03;			
	op2();
	sei();				

	while (1)
	{
		PORTD ^= (1<<7);	
		wait( 500 );								
	}

	return 1;
}

ISR( INT0_vect )
{
	inteen();
    //PORTD |= (1<<5);		
}

ISR( INT1_vect )
{
	intnul();
	
    //PORTD &= ~(1<<5);		
}
//Op2>
void op2()
{
	PORTA = 0b11111111;
	DDRA = 1<<3;
}
void intnul()
{
	if(DDRA != 1<<7){
		DDRA = DDRA << 1;
	}
}
void inteen()
{
	if(DDRA != 1){
		DDRA = DDRA >> 1;
	}	
}
//<
void wait( int ms )

{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );	
	}
}