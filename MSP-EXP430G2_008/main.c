/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, PWM TA1-2, Up Mode, DCO SMCLK
//
//  Description: This program generates one PWM output on P1.2 using
//  Timer_A configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the value in CCR1 the PWM duty cycles.
//  A 75% duty cycle on P1.2.
//  ACLK = na, SMCLK = MCLK = TACLK = default DCO
//
//               MSP430G2xx1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//
//  D. Dang
//  Texas Instruments, Inc
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

/*******************************************************************************
 *
 *      MSP_008: Uso basico de PWM
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430G2231
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Para este ejemplo obtenedremos un PWM en P1.6 (LED_GREEN),
 *                  usando el Timer_A, la rutina de delay es muy basica y no
 *                  es la mejor opcion pero cumple el objetivo.
 *******************************************************************************
 * Historial del firmware
 * Rev.     Date        Comment
 *  v0.01   29/11/2017  - Testing using MSP430G2231
 *                      - Modificacion para hacer el duty_cycle variable
 ******************************************************************************/
#include <msp430.h> 

unsigned char DutyPWM = 10;

/********** P R O T O T Y P E S *************/
void MCU_Delayms(unsigned int time);

int main(void){
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT6;              // P1.6 output
	P1SEL |= BIT6;              // P1.6 TA1/2 options
	P1OUT &= ~BIT6;             // P1.6 set LOW (Green LED)
	CCR0 = 200-1;               // PWM Period (Aprox. 5KHz)
	CCTL1 = OUTMOD_7;           // CCR1 reset/set
	CCR1 = DutyPWM;             // CCR1 PWM duty cycle
	TACTL = TASSEL_2 + MC_1;    // SMCLK, up mode
	//_BIS_SR(CPUOFF);            // Enter LPM0
	while(1){
	    for(DutyPWM=10; DutyPWM<190; DutyPWM++){
	        CCR1 = DutyPWM;
	        MCU_Delayms(100);
	    }
	    for(DutyPWM=190; DutyPWM>10; DutyPWM--){
	        CCR1 = DutyPWM;
	        MCU_Delayms(100);
	    }
	}
}

void MCU_Delayms(unsigned int time){
    unsigned int delayCount;
    for (delayCount=0; delayCount<time; ++delayCount)
        __delay_cycles(1000); // 1ms = 1000 clocks at 1MHz
    return;
}

