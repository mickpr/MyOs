#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <util/twi.h>
#include "UART/uart.h"
#include "SYSCLK/sysclk.h"
//#include "i2c.h"
//#include "spi.h"
#include <inttypes.h>
#include "avr_compat.h"

//!!!

// definiowanie statycznej tablicy string we flash
#define P(name)   static const prog_uchar name[] PROGMEM  // declare a static string

/*
#include <avr/eeprom.h>

uint8_t eeprom_read_byte (const uint8_t *addr)
void eeprom_write_byte (uint8_t *addr, uint8_t value)
uint16_t eeprom_read_word (const uint16_t *addr)
void eeprom_write_word (uint16_t *addr, uint16_t value)
void eeprom_read_block (void *pointer_ram, const void *pointer_eeprom, size_t n)
void eeprom_write_block (void *pointer_eeprom, const void *pointer_ram, size_t n)

uint8_t ByteOfData;
ByteOfData = eeprom_read_byte((uint8_t*)46);

uint16_t WordOfData;
WordOfData = eeprom_read_word((uint16_t*)46);

uint8_t StringOfData[10];
eeprom_read_block((void*)&StringOfData, (const void*)12, 10);
------------------
#include <avr/eeprom.h>

uint8_t  EEMEM NonVolatileChar;
uint16_t EEMEM NonVolatileInt;
uint8_t  EEMEM NonVolatileString[10];

int main(void)
{
    uint8_t  SRAMchar;
    uint16_t SRAMint;
    uint8_t  SRAMstring[10];

    SRAMchar = eeprom_read_byte(&NonVolatileChar);
    SRAMint  = eeprom_read_word(&NonVolatileInt);
    eeprom_read_block((void*)&SRAMstring, (const void*)&NonVolatileString, 10);
}
-----------------
uint8_t EEMEM SomeVariable = 12;  // you must write eeprom!!! epp file while flashing

 */


void test1()
{
	uart_send_string_from_FLASH(PSTR("a"));
}
void test2()
{
	uart_send_string_from_FLASH(PSTR("b"));
}


//========================================================
//
//========================================================
int main()
{


	cli();
	//PORTB = 0xED; //
//	DDRB  = 0xBF; //MISO line input, rest output
//
//	//PORTD 7 output
//	DDRD  = 0b11000000; //0xC0; //PORTD7 and PORTD6 output, rest input
//	PORTD=0x00;
	//spi_init();
	MCUCR = 0x00;
	GICR  = 0x00;
	TIMSK = 0x00;
	//delay_ms(50);

	sei();                                     //enable global interrupts
	uart_init();


	init_sysclk(); // no. of TASKS in sysclk.h

	process_add(0,test1,1000);
	process_add(1,test2,2000);

	uart_send_string_from_FLASH(PSTR("Starting...\r\n"));
	//uart_print("Starting...\n\r");
	wdt_enable(WDTO_1S);
    //uart_printf("Reset ENC28J60\n\r");

    while(1){
    	wdt_reset();
    	uart_send_string_from_FLASH(PSTR("."));
    	_delay_ms(100);
    }
    return (0);
}
//========================================================
