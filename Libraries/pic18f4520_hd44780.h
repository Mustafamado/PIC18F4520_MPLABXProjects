/**
 * @author  Burak Enez
 * @email   burakenez@gmail.com
 * @website http://burakenez.org
 * @version v1.0
 * @ide     MPLAB X IDE
 * @license GNU GPL v3
 * @brief   HD44780 LCD driver library for STM32Fxxx
 * @note    This library is mostly obtained from http://stm32f4-discovery.com/
 *          website. I only migrated and slightly changed it from STM32Fxxx 
 *          devices to PIC18F4520. Thanks to Tilen Majerle for his great work.
 * @link    http://stm32f4-discovery.com/2015/07/hal-library-15-hd44780-for-stm32fxxx/
 *
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

#ifndef _HD44780_H
#define _HD44780_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup HD44780
 * @brief    HD44780 LCD driver library for PIC18F4520
 * @{
 *
 *	It also supports all HD44780 compatible LCD drivers.
 */	

/*
LCD   PIC18F4520        DESCRIPTION

GND   GND               Ground
VCC   +5V               Power supply for LCD
V0    Potentiometer	    Contrast voltage. Connect to potentiometer
RS    PB2               Register select, can be overwritten in your project's defines.h file
RW    GND               Read/write
E     PB3               Enable pin, can be overwritten in your project's defines.h file
D0    -                 Data 0 - doesn't care
D1    -                 Data 1 - doesn't care
D2    -                 Data 2 - doesn't care
D3    -                 Data 3 - doesn't  care
D4    PB4               Data 4, can be overwritten in your project's defines.h file
D5    PB5               Data 5, can be overwritten in your project's defines.h file
D6    PB6               Data 6, can be overwritten in your project's defines.h file
D7    PB7               Data 7, can be overwritten in your project's defines.h file
A     5V                Back light positive power
K     GND               Ground for back light
*/

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
//#include "delay.h"

/**
 * @defgroup HD44780_Macros
 * @brief    Library defines
 * @{
 */

/* Use this to select which device is used by printf. */
#define USE_HD44780_PRINTF
    
/* 4 bit mode */
/* Control pins, can be overwritten */
/* RS - Register select pin */
#define TRIS_HD44780_RS  TRISBbits.RB2
#define PORT_HD44780_RS  PORTBbits.RB2    
/* E - Enable pin */
#define TRIS_HD44780_E   TRISBbits.RB3
#define PORT_HD44780_E   PORTBbits.RB3
/* Data pins */
/* D4 - Data 4 pin */
#define TRIS_HD44780_D4  TRISBbits.RB4
#define PORT_HD44780_D4  PORTBbits.RB4
/* D5 - Data 5 pin */
#define TRIS_HD44780_D5  TRISBbits.RB5
#define PORT_HD44780_D5  PORTBbits.RB5
/* D6 - Data 6 pin */
#define TRIS_HD44780_D6  TRISBbits.RB6
#define PORT_HD44780_D6  PORTBbits.RB6
/* D7 - Data 7 pin */
#define TRIS_HD44780_D7  TRISBbits.RB7
#define PORT_HD44780_D7  PORTBbits.RB7

/**
 * @}
 */

/**
 * @defgroup HD44780_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Microseconds delay for HD44780 LCD Library
 * @param  us: microseconds
 * @retval None
 */
void HD44780_Delay (int us);

/**
 * @brief  Initializes HD44780 LCD
 * @param  cols: Width of lcd
 * @param  rows: Height of lcd
 * @retval None
 */
void HD44780_Init(unsigned char cols, unsigned char rows);

/**
 * @brief  Turn display on
 * @param  None
 * @retval None
 */
void HD44780_DisplayOn(void);

/**
 * @brief  Turn display off
 * @param  None
 * @retval None
 */
void HD44780_DisplayOff(void);

/**
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */
void HD44780_Clear(void);

/**
 * @brief  Puts string on lcd
 * @param  x: X location where string will start
 * @param  y; Y location where string will start
 * @param  *str: pointer to string to display
 * @retval None
 */
void HD44780_Puts(unsigned char x, unsigned char y, char* str);

/**
 * @brief  Enables cursor blink
 * @param  None
 * @retval None
 */
void HD44780_BlinkOn(void);

/**
 * @brief  Disables cursor blink
 * @param  None
 * @retval None
 */
void HD44780_BlinkOff(void);

/**
 * @brief  Shows cursor
 * @param  None
 * @retval None
 */
void HD44780_CursorOn(void);

/**
 * @brief  Hides cursor
 * @param  None
 * @retval None
 */
void HD44780_CursorOff(void);

/**
 * @brief  Scrolls display to the left
 * @param  None
 * @retval None
 */
void HD44780_ScrollLeft(void);

/**
 * @brief  Scrolls display to the right
 * @param  None
 * @retval None
 */
void HD44780_ScrollRight(void);

/**
 * @brief  Creates custom character
 * @param  location: Location where to save character on LCD. LCD supports up to 8 custom characters, so locations are 0 - 7
 * @param *data: Pointer to 8-bytes of data for one character
 * @retval None
 */
void HD44780_CreateChar(unsigned char location, unsigned char* data);

/**
 * @brief  Puts custom created character on LCD
 * @param  x: X location where character will be shown
 * @param  y: Y location where character will be shown
 * @param  location: Location on LCD where character is stored, 0 - 7
 * @retval None
 */
void HD44780_PutCustom(unsigned char x, unsigned char y, unsigned char location);

/**
 * @brief  Sets cursor position on LCD
 * @param  col: column number where cursor will be set
 * @param  row: row number where cursor will be set
 * @retval None
 */
void HD44780_CursorSet(char col, char row);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* _HD44780_H */
