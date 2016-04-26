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

/* Prints the Keypad value to the LCD Display
 * There are 2 methods. Two methods are identical but approach to the result with
 * different ways. To use method 2 you need to uncomment method 2 and You need
 * to comment out method 1.
 */

void main() {
    
    int int_key = 0xFF;
    char char_key;
    
    /* Initialize LCD 16 cols x 2 rows */
    HD44780_Init(16, 2);
    
    /* Initialize Keypad */
    KEYPAD_Init();

    while(1) {
/********************* Method 1 *********************/
        int_key = KEYPAD_Read(); /* Get the pressed key as integer */
        /* Convert integer to char. (char) type casting is needed */
        char_key = (char)KEYPAD_KeytoASCII(int_key); 
        /* Check if any key is pressed */
        if (int_key != 0xFF) {
            HD44780_Clear(); /* Clear the LCD display */
            HD44780_CursorSet(0,0); /* Move to the beginning of the first line */
            printf("Key Value is:"); /* Print to the first line */
            HD44780_CursorSet(0,1); /* Move to the beginning of the second line */
            printf("%c", char_key); /* Print the char. value of pressed key to the second line */
            Delayms(100);
        }
/*************** End of the Method 1 ****************/

///********************* Method 2 *********************/        
//        /* Wait until any key is relased and Get the pressed key as integer */
//        int_key = KEYPAD_WaitUntilRelease();
//        /* Convert integer to char. (char) type casting is needed */
//        char_key = (char)KEYPAD_KeytoASCII(int_key); 
//        /* Clear LCD */
//        HD44780_Clear();
//        HD44780_CursorSet(0,0); /* Move to the beginning of the first line */
//        printf("Key Value is:"); /* Print to the first line */
//        HD44780_CursorSet(0,1); /* Move to the beginning of the second line */
//        printf("%c", char_key); /* Print the char. value of pressed key to the second line */
//        Delayms(100);
///*************** End of the Method 2 ****************/
    }
}
