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
/*! \brief fréquence du qwark du µcontroller*/
#define FOSC 16000000
/*! \brief nombre de changement d'état par seconde(vitesse d'envoi de données)*/
#define BAUD 9600
/*! \brief calcul servant à trouver le numéro du registre*/
#define MYUBRR FOSC / 16 / BAUD - 1
unsigned char flag = 0;
unsigned char data;


void USART_Init(unsigned int ubrr) {
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr >> 8);
UBRR0L = (unsigned char)ubrr;
/*autoriser  transmitter allumer le bit n3 */
UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (3 << UCSZ00);
DDRB = 0B00100000;
PORTB = 0B00000000;
}

void USART_Transmit(unsigned char data) {
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1 << UDRE0)))
  ;
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive(void) {
/* Wait for data to be received */
while (!(UCSR0A & (1 << RXC0)))
  ;
/* Get and return received data from buffer */
return UDR0;
}


ISR(USART_RX_vect) {
data = UDR0;
flag = 1;
}

void USART_puts(unsigned char *str)
{
do
{
USART_Transmit(*str);
} while (*++str!=0);
}


int main(void) {

USART_Init(MYUBRR);
sei();
while (1) {
  if (flag == 1) {
    /* PORTB=0B00100000;//Allumer la led quand l'interruption est réalisée*/
    //USART_Transmit(data + 1);
    flag = 0;
  }
  _delay_ms(1);
}
}
