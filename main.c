#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "serial.h"
#include "timer.h"
#include "util.h"

#define F_CPU	16000000
#define BAUD	9600
#define BRC		((F_CPU/16/BAUD)-1)
#define TX_BUFFER 128

#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))

char serialBuffer[TX_BUFFER];
uint8_t serialReadPos = 0;
uint8_t SerialWritePos = 0;

void appendSerial(char c);
void serialWrite(char c[]);


void main (void) {

	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);

	UBRR0H = BRC>>8;
	UBRR0L = BRC;
	sei();


	while (1) {


	}

}


void appendSerial(char c){
}

void serialWrite(char c[]){
}


