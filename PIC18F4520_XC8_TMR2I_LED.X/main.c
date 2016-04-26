/**
 * MPLABX IDE project example for blinking LED with Timer2 Interrupt
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

/* Timer2 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR2_value = 2^TMR2bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 8
 * TMR2bit = 8
 * DesiredInterruptTime = 100us
 * TMR2_value = 206
 */

int TMR2_value = 206; // Required value for 10ms Timer2 Interrupt
int flag = 0; // LED toogle control flag
int counter = 0; // To obtain 1s (100us*10000 = 1s)

void main(void) {
    
    TRISCbits.RC1 = 0;
    LATCbits.LATC1 = 0;

    OpenTimer2( TIMER_INT_ON    &
                T2_PS_1_16      &
                T2_POST_1_1);
    
    WriteTimer2(TMR2_value); // Write TMR2 value to Timer2 to count

    INTCONbits.GIE = 1; // Enables all unmasked interrupts
    INTCONbits.PEIE = 1; // Enables all unmasked peripheral interrupts
    
    while(1) { 
        if(flag == 1) {
            LATCbits.LATC1 = ~LATCbits.LATC1;
            flag = 0;
        }
    }
}

void interrupt ISR(void) {

    if(PIR1bits.TMR2IF == 1) { // if Timer2 Interrupt is occurred
        PIR1bits.TMR2IF = 0; // Clear the interrupt flag
        WriteTimer2(TMR2_value); // Update TMR2 value
        counter++;
        if(counter > 9999) {
            counter = 0;
            flag = 1;
        }
        
    }
}
