

/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief
*      laisison serie
*
*      This file contains the full implementation of the motor control,
*      except the PID-controller.
*
* \par Application note:
*      AVR447: Sinusoidal driving of three-phase permanent motor using
*      ATmega48/88/168
*
* \par Documentation
*      For comprehensive code documentation, supported compilers, compiler
*      settings and supported devices see readme.html
*
* \author
*      Atmel Corporation: cihanhesen1@gmail.com \n
*      Support email: avr@atmel.com
*
* $Name: Jehan_1_0 $
* $Revision: 1.8 $
* $RCSfile: main.c,v $
* $Date: 2006/03/27 07:20:51 $  \n
******************************************************************************/



#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
int main()
{
USART_Init(MYUBRR);




while(1)
{
USART_Transmit(65);
}




}




void USART_Init(unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*Enable receiver and transmitter */
UCSR0B = (1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);




}
void USART_Transmit(unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)));
/* Put data into buffer, sends the data */
UDR0 = data;
}
