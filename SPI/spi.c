#include <avr/io.h>
#include "spi.h"

//SPI initialize for SD card
//clock rate: fclk/4
void spi_init(void)
{
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPI2X)|(1<<SPR0);
	//SPCR = 0x52; //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
	SPSR = 0x00;
	DDRB &= ~(1<<PB6); //clear PB6 (MISO line) - to set is as input (0)
	DDRB |= (1<<PB7) | (1<<PB5) | (1<<PB4); // set SCK (PB7), MOSI(PB5), SS(PB4) set to is as output (1)
}

unsigned char SPI_transmit(unsigned char data)
{
	// Start transmission
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	return(data);
}

unsigned char SPI_receive(void)
{
	unsigned char data;
	// Wait for reception complete
	SPDR = 0xff;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	// Return data register
	return data;
}
