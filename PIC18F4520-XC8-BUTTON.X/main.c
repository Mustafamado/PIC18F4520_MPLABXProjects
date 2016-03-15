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

/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

int main(void) {

    /* Initializes RC1 pin as output (LED1) */
    TRISCbits.RC1 = 0; 
    /* Initializes RB0 pin as input (KEY1) */
    TRISBbits.RB0 = 1;
    /* Initializes RB1 pin as input (KEY2) */
    TRISBbits.RB1 = 1; 

    while(1) {
        
        if (PORTBbits.RB0 == 0) /* If RB0 pin is equal to 0 (If KEY1 is pressed) */
            LATCbits.LATC1 = 1; /* Sets RC1 pin (LED1) */

        if (PORTBbits.RB1 == 0) /* If RB1 pin is equal to 0 (if KEY2 is pressed) */
            LATCbits.LATC1 = 0; /* Resets RC1 pin (LED1) */

    }
}
