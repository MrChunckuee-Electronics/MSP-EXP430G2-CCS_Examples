/*******************************************************************************
 *
 * MSP-EXP430G2_008: Manejo de LCD 16x2 "Mostrar Variables tipo Int"
 *
 *******************************************************************************
 * FileName:        lcd.c
 * Processor:       MSP430G2231 (Puede ser otro)
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:		Considerar la distribucion de pines especificada en lcd.h
 * 					Ejemplo para mostar  variables tipo int
 *******************************************************************************
 * Historial del firmware
 * Rev.		Date		Comment
 * 	v0.00   21/10/2015  Creación del firmware
 * 	v0.01   29/11/2017  Se compilo con CCS 7.2.0.00013
 ******************************************************************************/
#include <msp430g2231.h>
#include "lcd.h"
#include "special.h"

int int_Value = 10;
char char_LCD[8], i;

void Delay_Seg(volatile unsigned int t);

void main(void) {
	WDTCTL = WDTPW + WDTHOLD;//Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;// Use 1Mhz cal data for DCO
	DCOCTL = CALDCO_1MHZ;// Use 1Mhz cal data for DCO
	P1DIR = 0xFF;
	P1OUT = 0x00;
	LCD_Init();//Se inicializa LCD
	while(1){
		LCD_WriteCommand(LCD_CLEAR_SCREEN);
		LCD_WriteROMString("Uso de LCD 16x2",0,0);
		LCD_WriteROMString("MostrarVariables",0,1);
		Delay_Seg(3);
		LCD_WriteCommand(LCD_CLEAR_SCREEN);
		for(i=0; i<8; i++){ char_LCD[i]=0; } //Clear char_LCD
		itoa(int_Value, char_LCD, 10); //Pasar int_Value a decimal
		LCD_WriteROMString("Dec:  Bin:  Hex:",0,0);
		LCD_WriteString(char_LCD,0,1);
		for(i=0; i<8; i++){ char_LCD[i]=0; } //Clear char_LCD
		itoa(int_Value, char_LCD, 2); //Pasar int_Value a binario
		LCD_WriteString(char_LCD,6,1);
		for(i=0; i<8; i++){ char_LCD[i]=0; } //Clear char_LCD
		itoa(int_Value, char_LCD, 16); //Pasar int_Value a hexadecimal
		LCD_WriteString(char_LCD,12,1);
		Delay_Seg(3);
	}
}

/*******************************************************************************
 * Function:        void Delay_Seg(volatile unsigned int t)
 * Description:     Realiza retardo en segundos
 * Precondition:    None
 * Parameters:      t = Tiempo de espera
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void Delay_Seg(volatile unsigned int t){
	volatile unsigned int i;
	for (i=0 ;i<t; i++){
			__delay_cycles(1000000);
	}
}
