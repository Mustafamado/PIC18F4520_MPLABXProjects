/**
 * MPLABX IDE project example for blinking LED with Timer1 Interrupt
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

/* Timer1 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR1_value = 2^TMR1bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 8
 * TMR1bit = 16
 * DesiredInterruptTime = 10ms
 * TMR1_value = 55536
 */

int TMR1_value = 55536; // Required value for 10ms Timer1 Interrupt
int flag = 0; // LED toogle control flag
int counter = 0; // To obtain 1s (10ms*100 = 1s)

void main(void) {
    
    TRISCbits.RC1 = 0;
    LATCbits.LATC1 = 0;

    OpenTimer1( TIMER_INT_ON    & // Enable TIMER Interrupt
                T1_16BIT_RW     & // Enables register read/write of Timer1 in one 16-bit operation
                T1_SOURCE_INT   & // Internal instruction cycle clock (CLKO) acts as source of clock
                T1_PS_1_8       & // 1:8 prescaler value
                T1_OSC1EN_OFF   & // Timer 1 oscilator enable off
                T1_SYNC_EXT_OFF );// Do not synchronize external clock input
    
    WriteTimer1(TMR1_value); // Write TMR1 value to Timer1 to count

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

    if(PIR1bits.TMR1IF == 1) { // if Timer1 Interrupt is occurred
        PIR1bits.TMR1IF = 0; // Clear the interrupt flag
        WriteTimer1(TMR1_value); // Update TMR1 value
        counter++;
        if(counter > 99) {
            counter = 0;
            flag = 1;
        }
        
    }
}
