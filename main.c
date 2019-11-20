#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

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

	UBRR0H = BRC>>8;
	UBRR0L = BRC;
	sei();


	while (1) {

	if(BIT_IS_CLEAR(PINB, PB0)) {
		serialWrite("No voice detected\r\n");
} 
	else if(BIT_IS_SET(PINB, PB0)) {
		serialWrite("voice detected!\r\n");
			} 
		_delay_ms(1000);
		
    }
}


void appendSerial(char c)
{
	serialBuffer[SerialWritePos] =c;
	SerialWritePos++;
	if(SerialWritePos >= TX_BUFFER)
	{
		SerialWritePos = 0;
	}
}

void serialWrite(char c[])
{
	for(uint8_t i = 0;i<strlen(c);i++)
	{
		appendSerial(c[i]);
	}
	if(UCSR0A & (1<< UDRE0))
	{
		UDR0 = 0;
	}
}

ISR(USART_TX_vect)
{
	if(serialReadPos != SerialWritePos)
	{
		UDR0 = serialBuffer[serialReadPos];
		serialReadPos++;
		
		if(serialReadPos >= TX_BUFFER)
		{
			serialReadPos++;
		}
	}
}

