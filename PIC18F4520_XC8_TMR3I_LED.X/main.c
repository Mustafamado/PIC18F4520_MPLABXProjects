/**
 * MPLABX IDE project example for blinking LED with Timer3 Interrupt
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

/* Timer3 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR3_value = 2^TMR3bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 8
 * TMR3bit = 16
 * DesiredInterruptTime = 10ms
 * TMR3_value = 55536
 */

int TMR3_value = 55536; // Required value for 10ms Timer1 Interrupt
int flag = 0; // LED toogle control flag
int counter = 0; // To obtain 1s (10ms*100 = 1s)

void main(void) {
    
    TRISCbits.RC1 = 0;
    LATCbits.LATC1 = 0;

    OpenTimer3( TIMER_INT_ON    &
                T3_16BIT_RW     &
                T3_SOURCE_INT   &
                T3_PS_1_8       &
                T3_SYNC_EXT_OFF );
    
    WriteTimer3(TMR3_value); // Write TMR3 value to Timer3 to count

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

    if(PIR2bits.TMR3IF == 1) { // if Timer3 Interrupt is occurred
        PIR2bits.TMR3IF = 0; // Clear the interrupt flag
        WriteTimer3(TMR3_value); // Update TMR3 value
        counter++;
        if(counter > 99) {
            counter = 0;
            flag = 1;
        }
        
    }
}
