/**
 * MPLABX IDE project example for Homework 1 (in "Documents" folder)
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
    int delay = 500; // Variable for changing delay
    TRISBbits.RB0 = 1; // KEY1 is input
    TRISBbits.RB1 = 1; // KEY2 is input
    TRISCbits.RC1 = 0; // LED1 is output
    LATCbits.LATC1 = 0; // LED1 is off
    while(1) {
        LATCbits.LATC1 = ~LATCbits.LATC1; // Toogle LED1
        Delayms(delay); // Delay
        if (PORTBbits.RB0 == 0) { // if KEY1 is pressed
            while(PORTBbits.RB0 == 0); // Trap until KEY1 is released
            delay = delay - 100; // Decrease delay by 100
            if(delay < 0) delay = 0; // delay won't be smaller than 0
        }
        if (PORTBbits.RB1 == 0) { // if KEY2 is pressed
            while(PORTBbits.RB1 == 0); // Trap until KEY2 is released
            delay = delay + 100; // Increase delay by 100
            if(delay > 1000) delay = 1000; // delay won't be greater than 1000
        }
    }
}
