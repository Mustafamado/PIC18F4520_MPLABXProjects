/**
 * MPLABX IDE project example for SSEG TMR0I
 * 
 * @author   Burak Enez
 * @email    burakenez@gmail.com
 * @website  http://burakenez.org
 * @ide      MPLAB X IDE
 * @compiler XC8 v1.34
 * @license  GNU GPL v3
 */
/* Include core modules */
#include <xc.h>
#include <plib/timers.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"
#include "pic18f4520_sseg.h"

/* Timer0 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR0_value = 2^TMR0bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 16
 * TMR0bit = 16
 * DesiredInterruptTime = 10ms
 * TMR0_value = 60536
 */

int TMR0_value = 60536; // Required value for 10ms Timer0 Interrupt
int counter = 0; // Value that will be shown on ssegs
int timer_flag = 0; // To divide time between ssegs

void main(void) {

    SSEG_Init(); // Initialize SSEGs
    // Configure Timer0
    OpenTimer0(TIMER_INT_ON &  // Enable TIMER Interrupt
               T0_16BIT &      // Timer0 is configured as an 16-bit timer/counter
               T0_SOURCE_INT & // Internal instruction cycle clock (CLKO) acts as source of clock
               T0_PS_1_16);   // 1:16 Prescaler value
               
    WriteTimer0(TMR0_value); // Write Timer0 value to Timer0 to count

    INTCONbits.GIE = 1; // Enables all unmasked interrupts
    
    while(1) { 
        Delayms(1000);
        counter++; // Increase counter by one
        if(counter > 99) counter = 0; // counter won't be greater than 99
    }
}

void interrupt ISR(void) {
    
    if(INTCONbits.TMR0IF==1) { // if Timer0 Interrupt is occurred
        INTCONbits.TMR0IF = 0; // Clear the interrupt flag
        WriteTimer0(TMR0_value); // Update TMR0 value
        if(timer_flag == 0) { // if it is first 10ms
            SSEG_Print(1,counter%10); // Shows ones of counter at first sseg
            timer_flag = 1;
        }
        else { // if it is second 10ms
            SSEG_Print(2,counter/10); // Shows tens of counter at second sseg
            timer_flag = 0;
        }
    }
}
