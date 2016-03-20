/**
 * @author  Burak Enez
 * @email   burakenez@gmail.com
 * @website http://burakenez.org
 * @version v1.0
 * @ide     MPLAB X IDE
 * @license GNU GPL v3
 * @brief   This file provides the functions for the 4x4 Keypad on PTK40A
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

#ifndef _KEYPAD_H
#define _KEYPAD_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup KEYPAD
 * @brief    KEYPAD driver library for PIC18F4520
 * @{
 * 
 *  This library is for 4x4 KEYPAD
 */

/**
 * @defgroup KEYPAD_Includes
 * @brief    Library includes
 * @{
 */

#include "pic18f4520_config.h"

/**
 * @}
 */

/**
 * @defgroup KEYPAD_Macros
 * @brief    Library defines
 * @{
 */
/* KEYPAD_ROW1 */
#define TRIS_KEYPAD_ROW1 TRISDbits.RD7
#define PORT_KEYPAD_ROW1 PORTDbits.RD7
/* KEYPAD_ROW2 */
#define TRIS_KEYPAD_ROW2 TRISDbits.RD6
#define PORT_KEYPAD_ROW2 PORTDbits.RD6
/* KEYPAD_ROW3 */
#define TRIS_KEYPAD_ROW3 TRISDbits.RD5
#define PORT_KEYPAD_ROW3 PORTDbits.RD5
/* KEYPAD_ROW4 */
#define TRIS_KEYPAD_ROW4 TRISDbits.RD4
#define PORT_KEYPAD_ROW4 PORTDbits.RD4
/* KEYPAD_COL1 */
#define TRIS_KEYPAD_COL1 TRISDbits.RD3
#define PORT_KEYPAD_COL1 PORTDbits.RD3
/* KEYPAD_COL2 */
#define TRIS_KEYPAD_COL2 TRISDbits.RD2
#define PORT_KEYPAD_COL2 PORTDbits.RD2
/* KEYPAD_COL3 */
#define TRIS_KEYPAD_COL3 TRISDbits.RD1
#define PORT_KEYPAD_COL3 PORTDbits.RD1
/* KEYPAD_COL4 */
#define TRIS_KEYPAD_COL4 TRISDbits.RD0
#define PORT_KEYPAD_COL4 PORTDbits.RD0

/**
 * @}
 */

/**
 * @defgroup KEYPAD_Public_Functions
 * @brief    Library Public Functions
 * @{
 */

/**
 * @brief  Initializes KEYPAD
 * @retval None
 */
void KEYPAD_Init(void);

/**
 * @brief   
 * @retval 
 */
int KEYPAD_Read(void);

/**
 * @brief   
 * @param	
 * @retval 
 */
char KEYPAD_KeytoASCII (int key_number);

/**
 * @brief   
 * @retval 
 */
int KEYPAD_WaitUntilRelease(void);

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

#endif /* _KEYPAD_H */
