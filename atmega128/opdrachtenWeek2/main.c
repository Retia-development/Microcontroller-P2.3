/*
* opdrachtenWeek2.c
*
* Created: 06-Feb-19 11:01:21 AM
* Author : corna
*/

#include <avr/io.h>


int main(void)
{
	/* Replace with your application code */
	while (1)
	{
		B3();
	}
}

void B3()
{
	typedef struct {
		unsigned long data;
		unsigned int delay ;
	} PATTERN_STRUCT;
	
	PATTERN_STRUCT pattern[] = {
		{0b00111111,0},
		{0b00000110,1},
		{0b01011011,2},
		{0b01001111,3},
		{0b01100110,4},
		{0b01101101,5},
		{0b01111101,6},
		{0b00000111,7},
		{0b01111111,8},
		{0b01101111,9},
		{0b01110111,10},
		{0b011}
	};
	DDRA = 0b11111111;
		
	while (1)
	{
		int i = 0;
		
		while( pattern[i].delay < 20 ) {
			
			PORTA = pattern[i].data;
			
			wait(5000);
			
			i++;
		}
	}
}
