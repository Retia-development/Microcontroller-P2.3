
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB // spi Data direction register
#define PORT_SPI PORTB // spi Output register
#define SPI_SCK 1 // PB1: spi Pin System Clock
#define SPI_MOSI 2 // PB2: spi Pin MOSI
#define SPI_MISO 3 // PB3: spi Pin MISO
#define SPI_SS 0 // PB0: spi Pin Slave Select
// wait(): busy waiting for 'ms' millisecond - used library: util/delay.h


void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);
}

void spi_masterInit(void)
{
	DDR_SPI = 0xff; // All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO); // except: MISO input
	PORT_SPI |= BIT(SPI_SS); // SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64
	// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}

// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
}
// Write a byte from master to slave and read a byte from slave - not used here

char spi_writeRead( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
	data = SPDR; // New received data (eventually, MISO) in SPDR
	return data; // Return received byte
}
// Select device on pinnumer PORTB

void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}
// Deselect device on pinnumer PORTB

void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

// Initialize the driver chip (type MAX 7219)

void displayDriverInit()
{
	spi_slaveSelect(0); // Select display chip (MAX7219)
	 spi_write(0x09); // Register 09: Decode Mode
	 spi_write(0xFF); // -> 1's = BCD mode for all digits
	 spi_slaveDeSelect(0); // Deselect display chip
	 spi_slaveSelect(0); // Select dispaly chip
	 spi_write(0x0A); // Register 0A: Intensity
	 spi_write(0x0F); // -> Level 4 (in range [1..F])
	 spi_slaveDeSelect(0); // Deselect display chip
	 spi_slaveSelect(0); // Select display chip
	 spi_write(0x0B); // Register 0B: Scan-limit
	 spi_write(0x03); // -> 1 = Display digits 0..1
	 spi_slaveDeSelect(0); // Deselect display chip
	 spi_slaveSelect(0); // Select display chip
	 spi_write(0x0C); // Register 0B: Shutdown register
	 spi_write(0x01); // -> 1 = Normal operation
	 spi_slaveDeSelect(0); // Deselect display chip
}
// Set display on ('normal operation')
void displayOn()
{
	 spi_slaveSelect(0); // Select display chip
	 spi_write(0x0C); // Register 0B: Shutdown register
	 spi_write(0x01); // -> 1 = Normal operation
	 spi_slaveDeSelect(0); // Deselect display chip
}
// Set display off ('shut down')
void displayOff()
{
	 spi_slaveSelect(0); // Select display chip
	 spi_write(0x0C); // Register 0B: Shutdown register
	 spi_write(0x00); // -> 1 = Normal operation
	 spi_slaveDeSelect(0); // Deselect display chip
}

void spi_writeWord ( unsigned char adress, unsigned char data )
{
	spi_slaveSelect(0); 
	spi_write(adress);
	spi_write(data); 
	spi_slaveDeSelect(0);
}

void writeNegLedDisplay( int value){
	
	
	int val1;
	int val2;
	int val3;
	int val4;
	if(value < 0){
		val1 = (abs(value)%10);
		val2 = (abs(value)%100-val1)/10;
		val3 = (abs(value)%1000-val2-val1)/100;
		val4 = 10;
	}else{
		val1 = (value%10);
		val2 = (value%100-val1)/10;
		val3 = (value%1000-val2-val1)/100;
		val4 = 0b1111;
	}
	
	spi_writeWord(1,val1);
	spi_writeWord(2,val2);
	spi_writeWord(3,val3);
	spi_writeWord(4,val4);
}

void writeLedDisplay( int value ){

	int val1 = (value%10);
	int val2 = (value%100-val1)/10;
	int val3 = (value%1000-val2-val1)/100;
	int val4 = (value%10000-val3-val2-val1)/1000;

	spi_writeWord(1,val1);
	spi_writeWord(2,val2);
	spi_writeWord(3,val3);
	spi_writeWord(4,val4);
	
}


// Write a word = address byte + data byte from master to slave

int main()
{
	DDRB=0x01; // Set PB0 pin as output for display select
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip
	// clear display (all zero's)
	
	wait(1000);
	// write 4-digit data
	for (int i =50; i>=-999; i--)
	{
		writeNegLedDisplay(i);
		wait(1000);
	}
	wait(1000);
	return (1);
}