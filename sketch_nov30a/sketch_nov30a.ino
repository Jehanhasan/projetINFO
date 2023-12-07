
/*! \brief fréquence du qwark du µcontroller*/
#define FOSC 16000000
/*! \brief nombre de changement d'état par seconde(vitesse d'envoi de données)*/
#define BAUD 9600
/*! \brief calcul servant à trouver le numéro du registre*/
#define MYUBRR FOSC / 16 / BAUD - 1
unsigned char flag0 = 0;
unsigned char flag3 = 0;
unsigned char data;




/*INIT */
void USART0_Init(unsigned int ubrr) {
 /* Définir le taux de bauds */
 UBRR0H = (unsigned char)(ubrr >> 8);
 UBRR0L = (unsigned char)ubrr;


 /*autoriser  transmitter allumer le bit n3 */
 UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);


 /* Définir le format de trame : 8 bits de données, 1 bit d'arrêt */
 UCSR0C = (3 << UCSZ00);


}
void USART3_Init(unsigned int ubrr) {
 /* Définir le taux de bauds */
 UBRR3H = (unsigned char)(ubrr >> 8);
 UBRR3L = (unsigned char)ubrr;


 /*autoriser  transmitter allumer le bit n3 */
 UCSR3B = (1 << RXEN3) | (1 << TXEN3) | (1 << RXCIE3);


 /* Définir le format de trame : 8 bits de données, 1 bit d'arrêt */
 UCSR3C = (3 << UCSZ30);
}


/*  TRANSMETTRE -----------------------------*/
void USART0_Transmit(unsigned char data) {


 /* Attendre que le tampon de transmission soit vide */
 while (!(UCSR0A & (1 << UDRE0)))
   ;
 /* Placer les données dans le tampon, envoyer les données */
 UDR0 = data;
}
void USART3_Transmit(unsigned char data) {


 /* Attendre que le tampon de transmission soit vide */
 while (!(UCSR3A & (1 << UDRE3)))
   ;
 /* Placer les données dans le tampon, envoyer les données */
 UDR3 = data;
}


/* RECEVOIR ----------------------------------*/
unsigned char USART0_Receive(void) {
 /* Attendre que les données soient reçues */
 while (!(UCSR0A & (1 << RXC0)))
   ;
 /* Obtenir et renvoyer les données reçues depuis le tampon */
 return UDR0;
}
unsigned char USART3_Receive(void) {
 /* Attendre que les données soient reçues */
 while (!(UCSR3A & (1 << RXC3)))
   ;
 /* Obtenir et renvoyer les données reçues depuis le tampon */
 return UDR3;
}


/* INTERRUPTION ----------------------------------*/
ISR(USART0_RX_vect) {
 PORTB=0B10000000;
// data = UDR0;
 flag0 = 1;
}
ISR(USART3_RX_vect) {
 PORTB=0B10000000;
// data = UDR3;
 flag3 = 1;
}


/* BOUCLE ----------------------------------------*/
void USART0_puts(unsigned char *str) {
 // Boucle tant que le caractère pointé par 'str' n'est pas nul (fin de la chaîne)
 do {
   // Transmettre le caractère actuel pointé par 'str'
   USART0_Transmit(*str);
 } while (*++str != 0);  // Passer au caractère suivant dans la chaîne
}


void USART3_puts(unsigned char *str) {
 // Boucle tant que le caractère pointé par 'str' n'est pas nul (fin de la chaîne)
 do {
   // Transmettre le caractère actuel pointé par 'str'
   USART3_Transmit(*str);
 } while (*++str != 0);  // Passer au caractère suivant dans la chaîne
}


/* MAIN ------------------------------------*/
int main(void) {


 USART0_Init(MYUBRR);
 USART3_Init(MYUBRR);
 DDRB = 0B10000000;
 PORTB = 0B00000000;
 sei();
 while (1) {
   if (flag0 == 1) {
     //PORTB=0B10000000;//Allumer la led quand l'interruption est réalisée*/


     USART3_Transmit(UDR0);
     flag0 = 0;
   }
  
    if (flag3 == 1) {
       //PORTB=0B00100000;//Allumer la led quand l'interruption est réalisée*/
       USART0_Transmit(UDR3);
     flag3 = 0;
   }


   _delay_ms(1);
 }
}



void USART_Transmit(unsigned char data) {
 /* Wait for empty transmit buffer */
 while (!(UCSR0A & (1 << UDRE0)))
   ;
 /* Put data into buffer, sends the data */
 UDR0 = data;
}


/*! \brief USART_Receive function / recetption
la fonction sert à recevoir une chaine de caractère
*/
unsigned char USART_Receive(void) {
 /* Wait for data to be received */
 while (!(UCSR0A & (1 << RXC0)))
   ;
 /* Get and return received data from buffer */
 return UDR0;
}




/*! \brief fonction d'interruption
la fonction sera éxécutée quand l'interruption sera cativée
*/
ISR(USART_RX_vect) {
 data = UDR0;
 flag = 1;
}


/*! \brief Main function
utilisée pour appeler les fonctions init et et démarrer la transmmission
*/
int main(void) {


 USART_Init(MYUBRR);
 sei();
 while (1) {
   if (flag == 1) {
     /* PORTB=0B00100000;//Allumer la led quand l'interruption est réalisée*/
     USART_Transmit(data + 1);
     flag = 0;
   }
   _delay_ms(1);
 }
}
 {
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
