/*******************************************************************************
 *
 *                  Pulsador
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430G2231
 * Complier:        CCS 6.0.0
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:		Cambia el estado del LED dependiendo del estado del boton
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      12/02/2015		Creación del firmware
 ******************************************************************************/

#include  <msp430g2231.h>

void main(void){
  WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
  P1DIR |= BIT0 + BIT6;		// P1.0 y P1.6 como salidas
  P1DIR &= ~ BIT3; 	// P1.3 entrada con pullup
  P1REN |= BIT3;	// Activa resistencia de pullup en P1.3

  while (1){
    if (P1IN & BIT3){	//Si BIT3 es HIGH
    	P1OUT = BIT0;	//LED Rojo on
    	P1OUT = ~ BIT6;	//LED Verde off
    }
    else{
    	P1OUT = ~BIT0;	//LED Rojo off
    	P1OUT = BIT6;	//LED Verde on
    }
  }
}
