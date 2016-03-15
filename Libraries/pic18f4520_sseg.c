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

#include "sseg.h"

/* Private variables */
/* sseg_codes from 0 to 9 and from A to F there are 16 values */
static int sseg_codes[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 
                           0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

/* Public functions */
void SSEG_Init(void) {
    
    TRIS_SSEG_CC1 = 0;
    TRIS_SSEG_CC2 = 0;
    TRIS_SSEG_A = 0;
    TRIS_SSEG_B = 0;
    TRIS_SSEG_C = 0;
    TRIS_SSEG_D = 0;
    TRIS_SSEG_E = 0;
    TRIS_SSEG_F = 0;
    TRIS_SSEG_G = 0;
    TRIS_SSEG_DP = 0;
    
    LAT_SSEG_CC1 = 0;
    LAT_SSEG_CC2 = 0;
    LAT_SSEG_A = 0;
    LAT_SSEG_B = 0;
    LAT_SSEG_C = 0;
    LAT_SSEG_D = 0;
    LAT_SSEG_E = 0;
    LAT_SSEG_F = 0;
    LAT_SSEG_G = 0;
    LAT_SSEG_DP = 0;
}

void SSEG_Print(int sseg, int n) {
    
    LAT_SSEG_CC1 = (sseg == 1) ? 1 : 0;
    LAT_SSEG_CC2 = (sseg == 2) ? 1 : 0;    
    LAT_SSEG_A = ((sseg_codes[n] & (0x01 << 0)) >> 0);
    LAT_SSEG_B = ((sseg_codes[n] & (0x01 << 1)) >> 1);
    LAT_SSEG_C = ((sseg_codes[n] & (0x01 << 2)) >> 2);
    LAT_SSEG_D = ((sseg_codes[n] & (0x01 << 3)) >> 3);
    LAT_SSEG_E = ((sseg_codes[n] & (0x01 << 4)) >> 4);
    LAT_SSEG_F = ((sseg_codes[n] & (0x01 << 5)) >> 5);
    LAT_SSEG_G = ((sseg_codes[n] & (0x01 << 6)) >> 6);
    LAT_SSEG_DP = ((sseg_codes[n] & (0x01 << 7)) >> 7);
}
