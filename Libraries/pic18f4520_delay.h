/**
 * @author  Burak Enez
 * @email   burakenez@gmail.com
 * @website http://burakenez.org
 * @version v1.0
 * @ide     MPLAB X IDE
 * @license GNU GPL v3
 * @brief   Delay library for milliseconds and microseconds delays
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
 
#ifndef _DELAY_H
#define	_DELAY_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup DELAY
 * @brief    DELAY driver library for PIC18F4520
 * @{
 * 
 */

/**
 * @defgroup DELAY_Includes
 * @brief    Library includes
 * @{
 */
#include <xc.h>
#include "pic18f4520_config.h"

/**
 * @}
 */

/**
 * @defgroup DELAY_Public_Functions
 * @brief    Library Public Functions
 * @{
 */

/**
 * @brief   
 * @param	
 * @retval 
 */
void Delayms(int ms) {
    
    for(int i=0; i<ms ; i++) __delay_ms(1);
}

/**
 * @brief   
 * @param	
 * @retval 
 */
void Delay(int us) {
    
    for(int i=0; i<us ; i++) __delay_us(1);
}

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

#endif /* _DELAY_H */
