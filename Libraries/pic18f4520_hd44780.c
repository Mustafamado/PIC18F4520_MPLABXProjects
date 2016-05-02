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

#include "pic18f4520_hd44780.h"

/* Private HD44780 structure */
typedef struct {
	char DisplayControl;
	char DisplayFunction;
	char DisplayMode;
	char Rows;
	char Cols;
	char currentX;
	char currentY;
} HD44780_Options_t;

/* Private functions */
static void HD44780_InitPins(void);
static void HD44780_Cmd(char cmd);
static void HD44780_Cmd4bit(char cmd);
static void HD44780_Data(char data);
//static void HD44780_CursorSet(char col, char row);

/* Private variable */
static HD44780_Options_t HD44780_Opts;

#define HD44780_RS_LOW              PORT_HD44780_RS = 0
#define HD44780_RS_HIGH             PORT_HD44780_RS = 1
#define HD44780_E_LOW               PORT_HD44780_E = 0
#define HD44780_E_HIGH              PORT_HD44780_E = 1

#define HD44780_E_BLINK             HD44780_E_HIGH; HD44780_Delay(20); HD44780_E_LOW; HD44780_Delay(20)
//#define HD44780_Delay(x)            Delay(x)

/* Commands*/
#define HD44780_CLEARDISPLAY        0x01
#define HD44780_RETURNHOME          0x02
#define HD44780_ENTRYMODESET        0x04
#define HD44780_DISPLAYCONTROL      0x08
#define HD44780_CURSORSHIFT         0x10
#define HD44780_FUNCTIONSET         0x20
#define HD44780_SETCGRAMADDR        0x40
#define HD44780_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define HD44780_ENTRYRIGHT          0x00
#define HD44780_ENTRYLEFT           0x02
#define HD44780_ENTRYSHIFTINCREMENT 0x01
#define HD44780_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define HD44780_DISPLAYON           0x04
#define HD44780_CURSORON            0x02
#define HD44780_BLINKON             0x01

/* Flags for display/cursor shift */
#define HD44780_DISPLAYMOVE         0x08
#define HD44780_CURSORMOVE          0x00
#define HD44780_MOVERIGHT           0x04
#define HD44780_MOVELEFT            0x00

/* Flags for function set */
#define HD44780_8BITMODE            0x10
#define HD44780_4BITMODE            0x00
#define HD44780_2LINE               0x08
#define HD44780_1LINE               0x00
#define HD44780_5x10DOTS            0x04
#define HD44780_5x8DOTS             0x00

#ifdef USE_HD44780_PRINTF
void putch(char c) {
    
		if (HD44780_Opts.currentX >= HD44780_Opts.Cols) {
			HD44780_Opts.currentX = 0;
			HD44780_Opts.currentY++;
			HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		if (c == '\n') {
			HD44780_Opts.currentY++;
            HD44780_Opts.currentX = 0;
			HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		} else if (c == '\r') {
			HD44780_CursorSet(0, HD44780_Opts.currentY);
		} else {
			HD44780_Data(c);
			HD44780_Opts.currentX++;
		}
}
#endif /* USE_HD44780_PRINTF */

void HD44780_Delay (int us) {
    
    for(int i=0; i<us ; i++) __delay_us(1);
}

void HD44780_Init(char cols, char rows) {
	
	/* Init pinout */
	HD44780_InitPins();
	
	/* At least 40ms */
	HD44780_Delay(45000);
	
	/* Set LCD width and height */
	HD44780_Opts.Rows = rows;
	HD44780_Opts.Cols = cols;
	
	/* Set cursor pointer to beginning for LCD */
	HD44780_Opts.currentX = 0;
	HD44780_Opts.currentY = 0;
	
	HD44780_Opts.DisplayFunction = HD44780_4BITMODE | HD44780_5x8DOTS | HD44780_1LINE;
	if (rows > 1) {
		HD44780_Opts.DisplayFunction |= HD44780_2LINE;
	}
	
	/* Try to set 4bit mode */
	HD44780_Cmd4bit(0x03);
	HD44780_Delay(4500);
	
	/* Second try */
	HD44780_Cmd4bit(0x03);
	HD44780_Delay(4500);
	
	/* Third goo! */
	HD44780_Cmd4bit(0x03);
	HD44780_Delay(4500);	
	
	/* Set 4-bit interface */
	HD44780_Cmd4bit(0x02);
	HD44780_Delay(100);
	
	/* Set # lines, font size, etc. */
	HD44780_Cmd(HD44780_FUNCTIONSET | HD44780_Opts.DisplayFunction);

	/* Turn the display on with no cursor or blinking default */
	HD44780_Opts.DisplayControl = HD44780_DISPLAYON;
	HD44780_DisplayOn();

	/* Clear lcd */
	HD44780_Clear();

	/* Default font directions */
	HD44780_Opts.DisplayMode = HD44780_ENTRYLEFT | HD44780_ENTRYSHIFTDECREMENT;
	HD44780_Cmd(HD44780_ENTRYMODESET | HD44780_Opts.DisplayMode);

	/* Delay */
	HD44780_Delay(4500);
}

void HD44780_Clear(void) {
	HD44780_Cmd(HD44780_CLEARDISPLAY);
	HD44780_Delay(3000);
}

void HD44780_Puts(char x, char y, char* str) {
	HD44780_CursorSet(x, y);
	while (*str) {
		if (HD44780_Opts.currentX >= HD44780_Opts.Cols) {
			HD44780_Opts.currentX = 0;
			HD44780_Opts.currentY++;
			HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		if (*str == '\n') {
			HD44780_Opts.currentY++;
			HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		} else if (*str == '\r') {
			HD44780_CursorSet(0, HD44780_Opts.currentY);
		} else {
			HD44780_Data(*str);
			HD44780_Opts.currentX++;
		}
		str++;
	}
}

void HD44780_DisplayOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_DISPLAYON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_DisplayOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_DISPLAYON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_BlinkOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_BLINKON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_BlinkOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_BLINKON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_CursorOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_CURSORON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_CursorOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_CURSORON;
	HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void HD44780_ScrollLeft(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVELEFT);
}

void HD44780_ScrollRight(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVERIGHT);
}

void HD44780_CreateChar(char location, char *data) {
	char i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	HD44780_Cmd(HD44780_SETCGRAMADDR | (location << 3));
	
	for (i = 0; i < 8; i++) {
		HD44780_Data(data[i]);
	}
}

void HD44780_PutCustom(char x, char y, char location) {
	HD44780_CursorSet(x, y);
	HD44780_Data(location);
}

/*static*/ void HD44780_CursorSet(char col, char row) {
	char row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	
	/* Go to beginning */
	if (row >= HD44780_Opts.Rows) {
		row = 0;
	}
	
	/* Set current column and row */
	HD44780_Opts.currentX = col;
	HD44780_Opts.currentY = row;
	
	/* Set location address */
	HD44780_Cmd(HD44780_SETDDRAMADDR | (col + row_offsets[row]));
}

/* Private functions */
static void HD44780_Cmd(char cmd) {
	/* Command mode */
	HD44780_RS_LOW;
	
	/* High nibble */
	HD44780_Cmd4bit(cmd >> 4);
	/* Low nibble */
	HD44780_Cmd4bit(cmd & 0x0F);
}

static void HD44780_Data(char data) {
	/* Data mode */
	HD44780_RS_HIGH;
	
	/* High nibble */
	HD44780_Cmd4bit(data >> 4);
	/* Low nibble */
	HD44780_Cmd4bit(data & 0x0F);
}

static void HD44780_Cmd4bit(char cmd) {
    /* Set output port */
    PORT_HD44780_D7 = (cmd & 0x08) ? 1 : 0;
    PORT_HD44780_D6 = (cmd & 0x04) ? 1 : 0;
    PORT_HD44780_D5 = (cmd & 0x02) ? 1 : 0;
    PORT_HD44780_D4 = (cmd & 0x01) ? 1 : 0;
	HD44780_E_BLINK;
}

static void HD44780_InitPins(void) {
	/* Init all pins */
    TRIS_HD44780_RS = 0;
    TRIS_HD44780_E = 0;
    TRIS_HD44780_D4 = 0;
    TRIS_HD44780_D5 = 0;
    TRIS_HD44780_D6 = 0;
    TRIS_HD44780_D7 = 0;

	/* Set pins low */
    PORT_HD44780_RS = 0;
    PORT_HD44780_E = 0;
    PORT_HD44780_D4 = 0;
    PORT_HD44780_D5 = 0;
    PORT_HD44780_D6 = 0;
    PORT_HD44780_D7 = 0;
}
