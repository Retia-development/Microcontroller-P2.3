#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BIT(x) (1<<(x))

int main(void)
{
	B7();
	return 1;
}

void B22(){
	DDRD = 0b11111111;
	PORTD = 0x80;
	while(1)
	{
		PORTD ^= BIT(7);
		PORTD ^= BIT(6);
		
		wait(200);
	}
}

void B2(){
	DDRD = 0b11111111;
	
	int light = 0x80;
	
	
	while(1)
	{
		PORTD = light;
		if(light == 0x80)
		{
			light = 0x40;
		}
		else{
			light = 0x80;
		}
		wait(200);
	}
	
}

void B3(){
	DDRD |= BIT(7);			// alleen pin 7 is output
	PORTC &= ~BIT(0);		// alleen pin 0 is input
	while(1)
	{
		if(PINC == BIT(0))
		{
			PORTD |= BIT(7);
			wait(500);
			PORTD &= ~BIT(7);
			wait(500);
		}
	}
}

void B4(){
	DDRD = 0b11111111;
	
	int light = 0x1;
	int updown = 1;
	while(1){
		PORTD = light;
		if(updown){
			light = light << 1;
		}
		else{
			light = light >> 1;
		}
		if (light >= 0x80 || light <= 0x1)
		{
			updown = !updown;
		}
		wait(50);
	}
}

void B5(){
	typedef struct {
		unsigned long data;
		unsigned int delay ;
	} PATTERN_STRUCT;
	
	PATTERN_STRUCT pattern[] = {
		//{0x3A, 500},{0x3A0A, 500},{0x3A0A3E, 500},{0x3A0A3E28, 500},
		//{0x0A3E282E, 500},{0x3E282E00, 500},{0x282E0000, 500},{0x2E000000, 500},
		
		{0x01010101, 200},{0x02030202, 200},{0x05070505, 200},{0x0A0E0A0A, 200},
		{0x141D1515, 200},{0x293A2B2A, 200},{0x52755755, 200},{0xA4EAAEAA, 200},
		{0x49D45D55, 200},{0x92A8BAAA, 200},{0x24507454, 200},{0x48A0E8A8, 200},
		{0x9040D050, 200},{0x2080A020, 200},{0x40004040, 200},{0x80008080, 200},
		
		{0x00000000, 200},{0x3C000000, 200},{0x423C0000, 200},{0x3C423C00, 200},
		{0x003C423C, 200},{0x70003C42, 200},{0x8070003C, 200},{0x60807000, 200},
		{0x80608070, 200},{0x70806080, 200},{0x00708060, 200},{0x3C007080, 200},
		{0x423C0070, 200},{0x3C423C00, 200},{0x003C423C, 200},{0x00003C42, 200},
		{0x0000003C, 200},{0x00000000, 200},{0x00000000, 200},{0x00000000, 200},
		
		{0x00, 0x00}
	};
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	
	while (1==1)
	{
		
		int i = 0;
		
		while( pattern[i].delay != 0 ) {
			PORTA = pattern[i].data;
			PORTB = pattern[i].data >> 8;
			PORTC = pattern[i].data >> 16;
			PORTD = pattern[i].data >> 24;
			
			wait(pattern[i].delay);
			
			i++;
		}
	}
}

void B6()
{
	DDRD |= BIT(7);
	PORTC &= ~BIT(0);
	int delay = 1000;
	int pressed = 1;
	int cycle = 0;
	
	while(1)
	{
		if(PINC == BIT(0) && pressed)
		{
			pressed = 0;
			if (delay == 1000)
			{
				delay = 250;
			}
			else
			{
				delay = 1000;
			}
		}
		
		if(PINC != BIT(0)){
			pressed = 1;
		}
		
		if (cycle >= delay)
		{
			PORTD ^= BIT(7);
			cycle = 0;
		}
		
		cycle++;
		wait(1);
	}
}

void setCharliePlexingLed(int lednr)
{
	switch(lednr)
	{
		case 1: //0 aan, 1 uit, 2 tri-state
		PORTC = 0b00000001;
		DDRC = 0b11111011;
		break;
		case 2:
		PORTC = 0b00000010;
		DDRC = 0b11111011;
		break;
		case 3:
		PORTC = 0b00000010;
		DDRC = 0b11111110;
		break;
		case 4:
		PORTC = 0b00000100;
		DDRC = 0b11111110;
		break;
		case 5:
		PORTC = 0b00000100;
		DDRC = 0b11111101;
		break;
		case 6:
		PORTC = 0b00000001;
		DDRC = 0b11111101;
		break;
	}
}

void b7()
{
	char i = 1;
	while(1)
	{
		setCharliePlexingLed(i);
		i = i << 1;
		if(i == 0x40) i = i >> 6;
		wait(500);
	}
}

void GolvendeLichtjes(){
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRG = 0b11111111;
	
	// All pins PORTD are set to output
	int lights[7];
	lights[0] = 0x1;
	lights[1] = 0x2;
	lights[2] = 0x4;
	lights[3] = 0x8;
	lights[4] = 0x40;
	lights[5] = 0x20;
	lights[6] = 0x10;
	int updown[7];
	for(int i = 0; i < 7; i++){
		updown[i] = 1;
	}
	
	int lights2[7];
	lights2[0] = 0x80;
	lights2[1] = 0x40;
	lights2[2] = 0x20;
	lights2[3] = 0x10;
	lights2[4] = 0x2;
	lights2[5] = 0x4;
	lights2[6] = 0x8;
	int updown2[7];
	for(int i = 0; i < 7; i++){
		updown2[i] = 0;
	}
	while (1)
	{
		PORTA = lights[0] + lights2[0];
		PORTB = lights[1] + lights2[1];
		PORTC = lights[2] + lights2[2];
		PORTD = lights[3] + lights2[3];
		PORTE = lights[4] + lights2[4];
		PORTF = lights[5] + lights2[5];
		//PORTG = lights[6] + lights2[6];
		for(int i = 0; i < 7; i++){
			if(updown[i]){
				lights[i] = lights[i] << 1;
			}
			else{
				lights[i] = lights[i] >> 1;
			}
			if (lights[i] >= 0x80 || lights[i] <= 0x1)
			{
				updown[i] = !updown[i];
			}
		}
		for(int i = 0; i < 7; i++){
			if(updown2[i]){
				lights2[i] = lights2[i] << 1;
			}
			else{
				lights2[i] = lights2[i] >> 1;
			}
			if (lights2[i] >= 0x80 || lights2[i] <= 0x1)
			{
				updown2[i] = !updown2[i];
			}
		}
		
		wait( 40 );
		
	}

}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

