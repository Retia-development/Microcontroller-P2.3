
#define F_CPU 8000000UL
#include <avr/io.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void op4();
void op2();
void intnul2();
void inteen2();
void wait( int ms );

int main( void )
{
	
	DDRD = 0xF0;

	EICRA |= 0x0B;			
	EIMSK |= 0x03;	
			
	op4();
	
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
	inteen2();
    //PORTD |= (1<<5);		
}

ISR( INT1_vect )
{
	intnul2();
	
    //PORTD &= ~(1<<5);		
}
//Op4>
void op4()
{
	
	typedef struct {
		unsigned char data;
		unsigned int delay ;
	} PATTERN_STRUCT;
	
	PATTERN_STRUCT pattern[] = {
		{0b00100001,80},
		{0b00000011,80},
		{0b01000010,40},
		{0b01010000,40},
		{0b00011000,80},
		{0b00001100,80},
		{0b01000100,40},
		{0b01100000,40},

			
		{0x00, 0x00}
	};
	DDRA = 0b11111111;
	while (1)
	{
		
		int i = 0;
		
		while( pattern[i].delay != 0 ) {
			PORTA = pattern[i].data;
			
			wait(pattern[i].delay);
			
			i++;
		}
	}
}


//<


//Op2>
void op2()
{
	DDRA = 0b11111111;
	PORTA = 1<<3;
}
void intnul2()
{
	if(PORTA != 1<<7){
		PORTA = PORTA << 1;
	}
}
void inteen2()
{
	if(PORTA != 1){
		PORTA = PORTA >> 1;
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