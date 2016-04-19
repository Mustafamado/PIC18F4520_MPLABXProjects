/**
 * MPLABX IDE project example for SSEG2
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

/* Counter from 0 to 99 and display it on sseg displays */
 
int main(void) {
    unsigned int counter = 0;
    SSEG_Init();
    while(1) {
        SSEG_Print(1,counter%10);
        Delayms(10);
        SSEG_Print(2,counter/10);
        Delayms(10);
        counter++;
        if(counter > 99) counter = 0; /* between 0 and 99 */
    }
}
