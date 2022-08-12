#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define USART_BAUD 115200ul
#define USART_UBBR_VALUE ((F_CPU/(USART_BAUD<<4))-1)

#define TX_NEWLINE {uart_send(0x0d); uart_send(0x0a);}

void uart_init(void);
void uart_send(uint8_t u8Data);
uint8_t uart_receive();
void uart_send_string_from_FLASH(const char* string);
void uart_send_string(char* string);
int uart_printf (const char *fmt, ...);

#endif /* UART_H_ */


