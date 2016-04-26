/**
 * MPLABX IDE project example for blinking LED
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
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

int main(void) {
    
    TRISCbits.RC1 = 0; // Initializes RC1 pin as output (LED1)
    
    /* Loop forever */
    while(1) {
        LATCbits.LATC1 = 1; // Sets RC1 pin (LED1)
        Delayms(1000); // 1sec delay
        LATCbits.LATC1 = 0; // Resets RC1 pin (LED1)
        Delayms(1000); // 1sec delay
    }
}
