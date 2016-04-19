/**
 * MPLABX IDE project example for SSEG
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
#include "pic18f4520_sseg.h"

int main(void) {
    unsigned int counter = 0;    
    TRISBbits.RB0 = 1; // B0 is set as input(KEY1)
    TRISBbits.RB1 = 1; // B1 is set as input(KEY2)
    SSEG_Init(); // sseg pins are set as output

    while(1) {
        // if B0 is 0 (KEY1 is pressed)
        if (PORTBbits.RB0 == 0) { 
            while(PORT_KEY1 == 0) Delayms(50);
            counter--;
            SSEG_Print(1,counter%16); // between 0 and F
        }
        // if B1 is 0 (KEY2 is pressed)
        if (PORTBbits.RB1 == 0) { 
            while(PORT_KEY2 == 0) Delayms(50);
            counter++;
            SSEG_Print(1,counter%16); // between 0 and F
        }
        
    }
}
