/**
 * @author  Burak Enez
 * @email   burakenez@gmail.com
 * @website http://burakenez.org
 * @version v1.0
 * @ide     MPLAB X IDE
 * @license GNU GPL v3
 * @brief   SSEG Library for PIC18F4520
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

#ifndef _SSEG_H
#define _SSEG_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup SSEG
 * @brief    SSEG driver library for PIC18F4520
 * @{
 * 
 *  This library is for 2 ssegs. 
 */

/**
 * @defgroup SSEG_Includes
 * @brief    Library includes
 * @{
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pic18f4520_config.h"

/**
 * @}
 */

/**
 * @defgroup SSEG_Macros
 * @brief    Library defines
 * @{
 */
/* SSEG - Common Cathode 1 */
#define TRIS_SSEG_CC1   TRISCbits.RC0
#define LAT_SSEG_CC1    LATCbits.LATC0
/* SSEG - Common Cathode 2 */
#define TRIS_SSEG_CC2   TRISCbits.RC5
#define LAT_SSEG_CC2    LATCbits.LATC5   
/* SSEG - A */
#define TRIS_SSEG_A     TRISEbits.RE2
#define LAT_SSEG_A      LATEbits.LATE2
/* SSEG - B */
#define TRIS_SSEG_B     TRISEbits.RE1
#define LAT_SSEG_B      LATEbits.LATE1
/* SSEG - C */
#define TRIS_SSEG_C     TRISAbits.RA2
#define LAT_SSEG_C      LATAbits.LATA2
/* SSEG - D */
#define TRIS_SSEG_D     TRISAbits.RA3
#define LAT_SSEG_D      LATAbits.LATA3
/* SSEG - E */
#define TRIS_SSEG_E     TRISAbits.RA4
#define LAT_SSEG_E      LATAbits.LATA4
/* SSEG - F */
#define TRIS_SSEG_F     TRISEbits.RE0
#define LAT_SSEG_F      LATEbits.LATE0
/* SSEG - G */
#define TRIS_SSEG_G     TRISAbits.RA5
#define LAT_SSEG_G      LATAbits.LATA5
/* SSEG - DP */
#define TRIS_SSEG_DP    TRISAbits.RA1
#define LAT_SSEG_DP     LATAbits.LATA1

/**
 * @}
 */

/**
 * @defgroup SSEG_Public_Functions
 * @brief    Library Public Functions
 * @{
 */

/**
 * @brief  Initializes SSEGs
 * @retval None
 */
void SSEG_Init(void);

/**
 * @brief  Prints nth character of sseg_code to chosen sseg.
 * @param  sseg: Number of chosen sseg
 * @param  n: Index of sseg_code to print on chosen sseg
 * @retval None
 */
void SSEG_Print(int sseg, int n);

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

#endif /* _SSEG_H */
