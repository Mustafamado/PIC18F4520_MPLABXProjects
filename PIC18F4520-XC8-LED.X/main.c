/**
 * MPLABX IDE project example for blinking LED
 * 
 * @author   Burak Enez
 * @email    burakenez@gmail.com
 * @website  http://burakenez.org
 * @ide      MPLAB X IDE
 * @compiler XC8
 * @license  GNU GPL v3
 */

/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

int main(void) {
    
    /* Initializes RC1 pin as output (LED1) */
    TRISCbits.RC1 = 0;
    
    /* Loop forever */
    while(1) {
        
        /* Sets RC1 pin (LED1) */
        LATCbits.LATC1 = 1;
        
        /* 1000ms delay */
        Delayms(1000);

        /* Resets RC1 pin (LED1) */
        LATCbits.LATC1 = 0;
        
        /* 1000ms delay */
        Delayms(1000);
    }
}
