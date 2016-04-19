/**
 * MPLABX IDE project example for Button
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

int main(void) {
    TRISCbits.RC1 = 0; // Initializes RC1 pin as output (LED1)
    TRISBbits.RB0 = 1; // Initializes RB0 pin as input (KEY1)
    TRISBbits.RB1 = 1; // Initializes RB1 pin as input (KEY2)
    
    while(1) {
        // If RB0 pin is equal to 0 (if KEY1 is pressed)
        if (PORTBbits.RB0 == 0) 
            LATCbits.LATC1 = 1; // Sets RC1 pin (LED1)
        // If RB1 pin is equal to 0 (if KEY2 is pressed)
        if (PORTBbits.RB1 == 0) 
            LATCbits.LATC1 = 0; // Resets RC1 pin (LED1)
    }
}
