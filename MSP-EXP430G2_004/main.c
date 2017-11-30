/*******************************************************************************
 *
 *  MSP-EXP430G2_004: LED Intermitente
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430G2231
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:		Cambia el estado del LED cada cierto tiempo
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.00      12/02/2015		Creación del firmware
 *   v0.01      29/11/2017      Se compilo con CCS 7.2.0.00013
 ******************************************************************************/

#include <msp430g2231.h>

volatile unsigned int i=0;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |= BIT6 + BIT0;	//LED ROJO(P1.0) y LED VERDE(P1.6) como salida
    P1OUT &= ~BIT6;	//BIT6 en cero, para alternar el encencido en while

while(1){
	P1OUT ^= BIT0 + BIT6;	//Cambiamos el estado de los LEDs
							//Considerando encendido alternadamente
	for(i=0; i<50000; i++);	//Pequeño retardo con un ciclo for
	}
}
