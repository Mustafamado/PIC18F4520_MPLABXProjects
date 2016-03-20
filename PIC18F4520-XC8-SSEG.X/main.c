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

/* If key1 is pressed number on sseg1 will be decreased */
/* If key2 is pressed number on sseg1 will be decreased */

/* KEY1 */
#define TRIS_KEY1   TRISBbits.RB0
#define PORT_KEY1   PORTBbits.RB0
/* KEY2 */
#define TRIS_KEY2   TRISBbits.RB1
#define PORT_KEY2   PORTBbits.RB1

int main(void) {
    unsigned int counter = 0;    
    TRIS_KEY1 = 1; /* B0 is set as input(KEY1) */
    TRIS_KEY2 = 1; /* B1 is set as input(KEY2) */
    SSEG_Init(); /* sseg pins are set as output. */

    while(1) {
        
        if (PORT_KEY1 == 0) { /* if B0 is 0 (KEY1 is pressed) */
            while(PORT_KEY1 == 0) Delayms(50);
            counter--;
            SSEG_Print(1,counter%16); /* between 0 and 9 */
        }
        if (PORT_KEY2 == 0) { /* if B1 is 0 (KEY2 is pressed) */
            while(PORT_KEY2 == 0) Delayms(50);
            counter++;
            SSEG_Print(1,counter%16); /* between 0 and 9 */
        }
        
    }
}

