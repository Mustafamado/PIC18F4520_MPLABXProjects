/**
 * MPLABX IDE project example for Keypad
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
#include <stdio.h> //for printf()
#include <stdlib.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"
#include "pic18f4520_hd44780.h"
#include "pic18f4520_keypad.h"

/* Time counter as seconds and prints passed time to the lcd */

/* Rectangle for custom character */
/* xxx means doesn't care, lower 5 bits are important for LCD */
unsigned char customChar[] = {
    0x1F,    /*  xxx 11111 */
    0x11,    /*  xxx 10001 */
    0x11,    /*  xxx 10001 */
    0x11,    /*  xxx 10001 */
    0x11,    /*  xxx 10001 */
    0x11,    /*  xxx 10001 */
    0x11,    /*  xxx 10001 */
    0x1F     /*  xxx 11111 */
};
    
int main(void) {

    /* Initialize LCD 16 cols x 2 rows */
    HD44780_Init(16, 2);
    
    /* Save custom character on location 0 in LCD */
    HD44780_CreateChar(0, customChar);
    
    /* Put string to LCD */
    HD44780_Puts(3, 0, "PIC18F4520");
    HD44780_Puts(0, 1, "16x2 HD44780 LCD");
 
    /* Wait a little */
    Delayms(3000);
    
    /* Clear LCD */
    HD44780_Clear();
    
    /* Show cursor */
    HD44780_CursorOn();
    
    /* Write new text */
    HD44780_Puts(0, 1, "CLEARED!");
    
    /* Wait a little */
    Delayms(1000);
    
    /* Enable cursor blinking */
    HD44780_BlinkOn();
    
    /* Show custom character at x = 1, y = 2 from RAM location 0 */
    HD44780_PutCustom(1, 2, 0);
    
    while (1) {
        /* Do nothing */
    }
}
