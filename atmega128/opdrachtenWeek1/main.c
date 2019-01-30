#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BIT(x) (1<<(x))

int main(void)
{
	B22();
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

