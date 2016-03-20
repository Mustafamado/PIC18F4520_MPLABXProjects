/**	
 * ----------------------------------------------------------------------
 *  Copyright (C) Burak Enez, 2016
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------
 */

#include <xc.h>
#include "pic18f4520_keypad.h"

void KEYPAD_Init(void) {
    
    /* Rows are input */
    TRIS_KEYPAD_ROW1 = 1; 
    TRIS_KEYPAD_ROW2 = 1;
    TRIS_KEYPAD_ROW3 = 1;
    TRIS_KEYPAD_ROW4 = 1;
    /* Cols are output */
    TRIS_KEYPAD_COL1 = 0;
    TRIS_KEYPAD_COL2 = 0;
    TRIS_KEYPAD_COL3 = 0;
    TRIS_KEYPAD_COL4 = 0;
    
    PORT_KEYPAD_ROW1 = 0;
    PORT_KEYPAD_ROW2 = 0;
    PORT_KEYPAD_ROW3 = 0;
    PORT_KEYPAD_ROW4 = 0;
    PORT_KEYPAD_COL1 = 0;
    PORT_KEYPAD_COL2 = 0;
    PORT_KEYPAD_COL3 = 0;
    PORT_KEYPAD_COL4 = 0;    
}

int KEYPAD_Read(void) {
    
    /* Start the scanning process */
    /* Set only COL1 to 1 and read each row one by one until finding the pressed key */
    PORT_KEYPAD_COL1=1; PORT_KEYPAD_COL2=0; 
    PORT_KEYPAD_COL3=0; PORT_KEYPAD_COL4=0;
    if(PORT_KEYPAD_ROW1) return 1; if(PORT_KEYPAD_ROW2) return 4; 
    if(PORT_KEYPAD_ROW3) return 7; if(PORT_KEYPAD_ROW4) return 14;
    __delay_us(10);
    /* Set only COL2 to 1 and read each row one by one until finding the pressed key */
    PORT_KEYPAD_COL1=0; PORT_KEYPAD_COL2=1; 
    PORT_KEYPAD_COL3=0; PORT_KEYPAD_COL4=0;
    if(PORT_KEYPAD_ROW1) return 2; if(PORT_KEYPAD_ROW2) return 5;
    if(PORT_KEYPAD_ROW3) return 8; if(PORT_KEYPAD_ROW4) return 0;
    __delay_us(10);
    /* Set only COL3 to 1 and read each row one by one until finding the pressed key */
    PORT_KEYPAD_COL1=0; PORT_KEYPAD_COL2=0;
    PORT_KEYPAD_COL3=1; PORT_KEYPAD_COL4=0;
    if(PORT_KEYPAD_ROW1) return 3; if(PORT_KEYPAD_ROW2) return 6;
    if(PORT_KEYPAD_ROW3) return 9; if(PORT_KEYPAD_ROW4) return 15;
    __delay_us(10);
    /* Set only COL4 to 1 and read each row one by one until finding the pressed key */
    PORT_KEYPAD_COL1=0; PORT_KEYPAD_COL2=0;
    PORT_KEYPAD_COL3=0; PORT_KEYPAD_COL4=1;
    if(PORT_KEYPAD_ROW1) return 10; if(PORT_KEYPAD_ROW2) return 11;
    if(PORT_KEYPAD_ROW3) return 12; if(PORT_KEYPAD_ROW4) return 13;
    __delay_us(10);

    return 0xFF; /* Not pressed condition */
}

char KEYPAD_KeytoASCII (int KeyNumber) {
    
    /* If number is from 0 to 9, convert to ASCII character by adding 0x30 */
    if (KeyNumber < 10) return KeyNumber + 0x30;
    /* If number is greater than 9, it is alphabet and symbol */
    if (KeyNumber == 10) return 'A'; /* Convert to ASCII A */
    if (KeyNumber == 11) return 'B'; /* Convert to ASCII B */
    if (KeyNumber == 12) return 'C'; /* Convert to ASCII C */
    if (KeyNumber == 13) return 'D'; /* Convert to ASCII D */
    if (KeyNumber == 14) return '*'; /* Convert to ASCII * */
    if (KeyNumber == 15) return '#'; /* Convert to ASCII # */
    return 0; /* No key pressed, Return null */
}

int KEYPAD_WaitUntilRelease(void) {
    
    /* The pressed key. */
    int PressedKey = 0xFF;
    /* Wait until the key is pressed. */
    do {
        PressedKey = KEYPAD_Read();
    }
    while (PressedKey == 0xFF);
    /* Wait until the key is released. */
    while (KEYPAD_Read() != 0xFF);
    return PressedKey;
}
