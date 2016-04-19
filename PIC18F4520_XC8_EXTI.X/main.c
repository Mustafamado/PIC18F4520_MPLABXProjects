/**
 * MPLABX IDE project example for External Interrupt
 * 
 * @author   Burak Enez
 * @email    burakenez@gmail.com
 * @website  http://burakenez.org
 * @ide      MPLAB X IDE
 * @compiler XC8
 * @license  GNU GPL v3
 */

/* Include core modules */
#include <xc.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

void main() {
    TRISBbits.RB0 = 1; // Set RB0 as input
    TRISBbits.RB1 = 1; // Set RB1 as input
    TRISCbits.RC1 = 0; // Set RC1 as output
    TRISCbits.RC2 = 0; // Set RC2 as output

    LATCbits.LATC1 = 0; // Reset RC1
    LATCbits.LATC2 = 0; // Reset RC2

    INTCONbits.INT0E = 1; // Enable Interrupt 0 (RB0 as interrupt)
    INTCON2bits.INTEDG0 = 1; // Interrupt 0 occurs at rising edge
    INTCONbits.INT0F = 0; // Clear Interrupt 0 flag

    INTCON3bits.INT1E = 1; // Enable Interrupt 1 (RB1 as interrupt)
    INTCON2bits.INTEDG1 = 1; // Interrupt 1 occurs at rising edge
    INTCON3bits.INT1F = 0; // Clear Interrupt 0 flag

    INTCONbits.GIE = 1; // Global Interrupt Enable
    
    /* Loop forever */
    while(1) {
    
    }
}

void interrupt ISR(void) {
    // Checks Receive Interrupt 0 Flag bit
    if(INTCONbits.INT0F == 1) {
        INTCONbits.INT0F = 0;  // Clear Interrupt 0 Flag       
        LATCbits.LATC1 = ~ LATCbits.LATC1; // Toogle RC1
    }
    // Checks Receive Interrupt 1 Flag bit
    if(INTCON3bits.INT1F == 1) {
        INTCON3bits.INT1F = 0;  // Clear Interrupt 1 Flag
        LATCbits.LATC2 = ~ LATCbits.LATC2; // Toogle RC2
    }
}
